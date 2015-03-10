#include <stdio.h>
#include <stdlib.h>

void encipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k)
{
    register unsigned long       y=v[0],z=v[1],sum=0,delta=0x9E3779B9,
				a=k[0],b=k[1],c=k[2],d=k[3],n=32;
    
    while(n-->0)
    {
        sum += delta;
        y += (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        z += (y << 4)+c ^ y+sum ^ (y >> 5)+d;
    }
    
    w[0]=y; w[1]=z;
}

void decipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k)
{
    register unsigned long       y=v[0],z=v[1],sum=0xC6EF3720,
				delta=0x9E3779B9,a=k[0],b=k[1],
				c=k[2],d=k[3],n=32;
    
    /* sum = delta<<5, in general sum = delta * n */
    
    while(n-->0)
    {
        z -= (y << 4)+c ^ y+sum ^ (y >> 5)+d;
        y -= (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        sum -= delta;
    }
    
    w[0]=y; w[1]=z;
}

void cbc_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    printf("\nCBC Encryption Mode:\n");
    int i=0;
    printf("plaintext:\n%s\n",plaintext);
    unsigned long * v;
    unsigned long * iv; //initial iv to 0
    int threshold=2*sizeof(unsigned long);
    *ciphertext= (char *)malloc(threshold*(size/threshold)+threshold); //increase the size for padding
    unsigned long * w;
    for ( i = 0; i < size; i ++) {
        (*ciphertext)[i]=plaintext[i];
    }
    
    for(i=0;i<=size;i+=threshold){ //process two 4 or 8 bytes at a time
        v= (unsigned long *)((*ciphertext)+i);
        if(i!=0){
            iv=(unsigned long *)((*ciphertext)+i-threshold);
            v[0]=iv[0]^v[0];
            v[1]=iv[1]^v[1];
        }
        encipher(v,v,k);
    }
    printf("ciphtertext:\n%s\n",*ciphertext);
    
}

void cbc_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    printf("\nCBC Decryption Mode:\n");
    int i=0;
    printf("ciphertext:\n%s\n",ciphertext);
    unsigned long * v;
    unsigned long * iv; //initial iv to 0
    int threshold=2*sizeof(unsigned long);
    *plaintext= (char *)malloc(threshold*(size/threshold)); //increase the size for padding
    unsigned long * w;
    for(i=0;i+threshold<=size;i+=threshold){ //process two 4 or 8 bytes at a time
        v= (unsigned long *)(ciphertext+i);
        w=(unsigned long *)((*plaintext)+i);
        decipher(v,w,k);
        if(i!=0){
            iv=(unsigned long *)(ciphertext+i-threshold);
            w[0]=iv[0]^w[0];
            w[1]=iv[1]^w[1];
        }
    }
    printf("plaintext:\n%s\n",*plaintext);
}


void ofb_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    printf("\nOFB Encryption Mode:\n");
    int i=0;
    printf("plaintext:\n%s\n",plaintext);
    int blockSize=2*sizeof(unsigned long);
    *ciphertext= (char *)malloc(blockSize*(size/blockSize)+blockSize); //increase the size for padding
    int blockNumber=size/blockSize+1;
    unsigned long * w=malloc(2); //initial iv
    w[0]=0;
    w[1]=1;
    for ( i = 0; i < size; i ++) {
        (*ciphertext)[i]=plaintext[i]; //update ciphertext to be plaintext
    }
    unsigned long * c;
    for(i=0;i<blockNumber;i++){
        encipher(w,w,k); //generate random number in w
        c=(unsigned long *)((*ciphertext)+i*blockSize);
        c[0]=c[0]^w[0];  //encrypt plaintext at location i*blockSize
        c[1]=c[1]^w[1];
    }
    printf("ciphtertext:\n%s\n",*ciphertext);
}

void ofb_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    printf("\nOFB Decryption Mode:\n");
    int i=0;
    printf("ciphertext:\n%s\n",ciphertext);
    unsigned long * v;
    unsigned long * w=malloc(2); //initial iv
    w[0]=0;
    w[1]=1;
    unsigned long * c;
    int blockSize=2*sizeof(unsigned long);
    int blockNumber=size/blockSize;
    *plaintext= (char *)malloc(size);
    for(i=0;i<blockNumber;i++){
        encipher(w,w,k); //generate random number in w
        c=(unsigned long *)(ciphertext+i*blockSize);
        c[0]=c[0]^w[0];
        c[1]=c[1]^w[1];
    }
    for(i=0;i<size;i++){
        (*plaintext)[i]=ciphertext[i];
    }
    printf("plaintext:\n%s\n",*plaintext);
}

void ctr_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    printf("\nCTR Encryption Mode:\n");
    int i=0;
    printf("plaintext:\n%s\n",plaintext);
    unsigned long * v;
    unsigned long counter=0; //initial counter to 0
    
    int blockSize=2*sizeof(unsigned long);
    *ciphertext= (char *)malloc(blockSize*(size/blockSize)+blockSize); //increase the size for padding
    int blockNumber=size/blockSize+1;
    unsigned long * w=malloc(2);
    for ( i = 0; i < size; i ++) {
        (*ciphertext)[i]=plaintext[i];
    }
    unsigned long * c;
    for(i=0;i<blockNumber;i++){
        v[0]=counter;
        v[1]=counter+1;
        encipher(v,w,k); //generate random number in w
        c=(unsigned long *)((*ciphertext)+i*blockSize);
        c[0]=c[0]^w[0];
        c[1]=c[1]^w[1];
        counter+=2;  //increment the counter
    }
    printf("ciphtertext:\n%s\n",*ciphertext);
}

void ctr_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    printf("\nCTR Decryption Mode:\n");
    int i=0;
    printf("ciphertext:\n%s\n",ciphertext);
    unsigned long * v;
    unsigned long * w=malloc(2);
    unsigned long * c;
    unsigned long counter=0; //initial counter to 0
    int blockSize=2*sizeof(unsigned long);
    int blockNumber=size/blockSize;
    *plaintext= (char *)malloc(size); //increase the size for padding
    unsigned long * p;
    for(i=0;i<blockNumber;i++){
        v[0]=counter;
        v[1]=counter+1;
        encipher(v,w,k); //generate random number in w
        c=(unsigned long *)(ciphertext+i*blockSize);
        c[0]=c[0]^w[0];
        c[1]=c[1]^w[1];
        counter+=2;  //increment the counter
    }
    for(i=0;i<size;i++){
        (*plaintext)[i]=ciphertext[i];
    }
    printf("plaintext:\n%s\n",*plaintext);
}