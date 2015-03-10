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
    int i=0,j=0;
    printf("plaintext: %s\n",plaintext);
    unsigned long * v;
//    if(size%4==0){
    int threshold=2*sizeof(unsigned long);
    *ciphertext= (char *)malloc(threshold*(size/threshold)+threshold); //increase the size for padding
    printf("original ciphertext: %s\n",*ciphertext);
//    }
    unsigned long * w;
//    char * temp;
    char *p;
    for ( i = 0; i < size; i ++) {
        (*ciphertext)[i]=plaintext[i];
//        printf(" %02x", plaintext[i]);
    }
    
    printf("\n");
//    printf("Size of Unsigned Long: %lu\n",sizeof(unsigned long));
    for(i=0;i+threshold<=size;i+=threshold){ //process two 4 or 8 bytes at a time
//        p =plaintext+i;
//        printf("pointer location %d: %s\n",i,p);
//        printf("pointer location %d: %p\n",i,(plaintext+i));
        v= (unsigned long *)((*ciphertext)+i);
//        printf("New Location %p\n",v);
//        w=(unsigned long*)((*ciphertext)+i);
        encipher(v,v,k);
//        for(j=0;j<2;j++){
//            printf("v %d : %lx\n",j,v[j]);
//            printf("w %d : %lx\n",j,w[j]);
//        }
//        decipher(w,w,k);
//        for(j=0;j<2;j++){
//            printf("decipher: v %d : %lx\n",j,v[j]);
//            printf("decipher: w %d : %lx\n",j,w[j]);
//        }
//        for(j=0;j<4;j++){
//            *ciphertext[i+j]= temp[j];
//        }
    }
    
       //padding
//    (*ciphertext)[size]='\0';
    printf("ciphtertext: %s\n",*ciphertext);
    //pad the rest
}
void cbc_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    
}
void ctr_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k){
    
}
void ctr_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k){
    
}