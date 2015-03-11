#include <stdio.h>
#include <stdlib.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <string.h>

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

void tea_cbc_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    int i=0;
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
    
}

void tea_cbc_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    int i=0;
    unsigned long * v;
    unsigned long * iv; //initial iv to 0
    int threshold=2*sizeof(unsigned long);
    *plaintext= (char *)malloc(size); //increase the size for padding
    unsigned long * w;
    for(i=0;i < size;i+=threshold){ //process two 4 or 8 bytes at a time
        v= (unsigned long *)(ciphertext+i);
        w=(unsigned long *)((*plaintext)+i);
        decipher(v,w,k);
        if(i!=0){
            iv=(unsigned long *)(ciphertext+i-threshold);
            w[0]=iv[0]^w[0];
            w[1]=iv[1]^w[1];
        }
    }
}


void tea_ofb_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    int i=0;
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
}

void tea_ofb_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    int i=0;
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
}

void tea_ctr_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    int i=0;
    unsigned long * v=malloc(sizeof(unsigned long)*2);
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
}

void tea_ctr_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    
    int i=0;
    unsigned long * v=malloc(sizeof(unsigned long)*2);
    unsigned long * w=malloc(sizeof(unsigned long)*2);
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
}

void xxh_des_encrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *key){
    DES_cblock ivsetup = {0xE1, 0xE2, 0xE3, 0xD4, 0xD5, 0xC6, 0xC7, 0xA8}; //iv
    DES_key_schedule keysched;
    DES_set_odd_parity(key);
    if (DES_set_key_checked(key, &keysched))
    {
        fprintf(stderr, "ERROR: Unable to set key schedule\n");
        exit(1);
    }
    *outputBuffer=malloc(inputBufferSize);
    DES_ncbc_encrypt(inputBuffer, *outputBuffer, inputBufferSize, &keysched, &ivsetup, DES_ENCRYPT);
    
}

void xxh_des_decrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *key){

    DES_cblock ivsetup = {0xE1, 0xE2, 0xE3, 0xD4, 0xD5, 0xC6, 0xC7, 0xA8}; //iv
    DES_key_schedule keysched;
    DES_set_odd_parity(key);
    if (DES_set_key_checked(key, &keysched))
    {
        fprintf(stderr, "ERROR: Unable to set key schedule\n");
        exit(1);
        
    }
    *outputBuffer=malloc(inputBufferSize);
    DES_ncbc_encrypt(inputBuffer, *outputBuffer, inputBufferSize, &keysched, &ivsetup, DES_DECRYPT);
}

void xxh_des_ofb_encrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *key){
    DES_cblock ivecstr = {0xE1, 0xE2, 0xE3, 0xD4, 0xD5, 0xC6, 0xC7, 0xA8};
    DES_cblock ivec;
    DES_key_schedule ks;
    int result;
    if ((result = DES_set_key_checked(key, &ks)) != 0) {
        if (result == -1) {
            printf("ERROR: key parity is incorrect\n");
        } else {
            printf("ERROR: weak or semi-weak key\n");
        }
        exit(1);
    }
    *outputBuffer=malloc(inputBufferSize);
    DES_ofb_encrypt(inputBuffer, *outputBuffer, 8,inputBufferSize, &ks, &ivecstr);
}