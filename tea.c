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

void cbc_encrypt(int size, unsigned long * plaintext, unsigned long ** ciphertext,
                 const unsigned long *const k){
    int i=0,j=0;
    printf("plaintext: %s\n",(char*)plaintext);
    unsigned long * v;
//    if(size%4==0){
    *ciphertext= malloc(size);
    printf("original ciphertext: %s\n",(char*)*ciphertext);
//    }
    unsigned long * w;
//    char * temp;
    unsigned long *p;
    for(i=0;i<size;i+=4){
        p =plaintext+i;
//        printf("pointer location %d: %s\n",i,(char*)p);
//        printf("pointer location %d: %p\n",i,(char*)(plaintext+i));
        v= &(plaintext[i/4]);
//        printf("New Location %p\n",v);
        w=&((*ciphertext)[i/4]);
//        printf("New W Location %p\n",w);
        encipher(v,w,k);
//        decipher(w,w,k);
//        for(j=0;j<4;j++){
//            *ciphertext[i+j]= temp[j];
//        }
    }
    printf("ciphtertext: %s\n",(char*)*ciphertext);
    //pad the rest
}
void cbc_decrypt(int size, unsigned long * ciphertext, unsigned long ** plaintext,
                 const unsigned long *const k){
    
}
void ctr_encrypt(int size, unsigned long * plaintext, unsigned long ** ciphertext,
                 const unsigned long *const k){
    
}
void ctr_decrypt(int size, unsigned long * ciphertext, unsigned long ** plaintext,
                 const unsigned long *const k){
    
}