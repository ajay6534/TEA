#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <sys/time.h>
#include "tea.h"

#define BUFSIZE 512 

int readInFile(char * inputFileName,char ** inputBuffer);
void outputFile(char * outputFileName,int size,char * outputBuffer);
void checkValidInput(char* input,char* name);
void generateKey(int entropy,unsigned long * key);
void processRequest(char * mode,char * blockCipher,char *blockCipherMode,int entropy, char * inputFileName, char * outputFileName);

int main(int argc,char **argv)
{
    checkValidInput(argv[1],"Mode? Encryption or Decryption");
    checkValidInput(argv[2],"Block Cipher (des or tea)");
    checkValidInput(argv[3],"Block Cipher Mode");
    checkValidInput(argv[4],"key");
    checkValidInput(argv[5],"input file name");
    checkValidInput(argv[6],"output file name");
    processRequest(argv[1],argv[2],argv[3],strtol(argv[4], NULL, 0),argv[5],argv[6]);
}

void processRequest(char * mode,char *blockCipher,char *blockCipherMode,int entropy, char * inputFileName, char * outputFileName){
    //read in the input file and stored it in a char * with the size
    char * inputBuffer;
    int inputBufferSize;
    printf( "input file location: %s\n", inputFileName );
    inputBufferSize=readInFile(inputFileName,&inputBuffer);
    
    char * outputBuffer;
    printf( "size: %d\n", inputBufferSize );
    if(strcmp(blockCipher,"tea")==0){
        unsigned long key[4];
        //generate the key
        generateKey(entropy,key);
        //    check block cipher mode
        if(strcmp(blockCipherMode,"CBT")==0){
            printf("CBT Mode\n");
            if(strcmp("-e",mode)==0){ //encrypt
                printf("Encryption\n");
                tea_cbc_encrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
            }else{  //decrypt
                printf("Decryption\n");
                tea_cbc_decrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
            }
        }else if(strcmp(blockCipherMode,"CTR")==0){
            printf("CTR Mode\n");
            if(strcmp("-e",mode)==0){ //encrypt
                printf("Encryption\n");
                tea_ctr_encrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
            }else if(strcmp("-d",mode)==0){  //decrypt
                printf("Decryption\n");
                tea_ctr_decrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
            }else{
                printf("Invalid Operation Mode: %s. Valid Mode: -e, -d\n",mode);
            }
        }else if(strcmp(blockCipherMode,"OFB")==0){
            printf("OFB Mode\n");
            if(strcmp("-e",mode)==0){ //encrypt
                printf("Encryption\n");
                tea_ofb_encrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
            }else if(strcmp("-d",mode)==0){  //decrypt
                printf("Decryption\n");
                tea_ofb_decrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
            }else{
                printf("Invalid Operation Mode: %s. Valid Mode: -e, -d\n",mode);
            }
        }else{
            fprintf(stderr, "Invalid Block Cipher Mode: %s!\n Valid Values: CBT, OFB, CTR.",blockCipherMode);
            exit(1);
        }

    }else if(strcmp(blockCipher,"des")==0){ //DES
        printf("DES\n");
        DES_cblock key = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
                //    check block cipher mode
        if(strcmp(blockCipherMode,"CBT")==0){
            printf("CBT Mode\n");
            inputBufferSize=8*(inputBufferSize/8)+8; //accomodate for the padding
            if(strcmp("-e",mode)==0){ //encrypt
                printf("Encryption\n");
                xxh_des_encrypt(inputBufferSize,inputBuffer,&outputBuffer,&key);
                
            }else{  //decrypt
                printf("Decryption\n");
                xxh_des_decrypt(inputBufferSize,inputBuffer,&outputBuffer,&key);
            }
        }else if(strcmp(blockCipherMode,"CTR")==0){
            fprintf(stderr, "Invalid Block Cipher Mode for DES: %s!\n Valid Values: CBT, OFB.",blockCipherMode);
            exit(1);
        }else if(strcmp(blockCipherMode,"OFB")==0){//OFB mode
            
            printf("OFB Mode\n");
            if(strcmp("-e",mode)==0){ //encrypt
                printf("Encryption\n");
                xxh_des_ofb_encrypt(inputBufferSize,inputBuffer,&outputBuffer,&key);
            }else if(strcmp("-d",mode)==0){  //decrypt
                printf("Decryption\n");
                xxh_des_ofb_encrypt(inputBufferSize,inputBuffer,&outputBuffer,&key);
            }else{
                printf("Invalid Operation Mode: %s. Valid Mode: -e, -d\n",mode);
            }
        }else{
            fprintf(stderr, "Invalid Block Cipher Mode: %s!\n Valid Values: CBT, CTR.",blockCipherMode);
            exit(1);
        }
    }else{ //test
        //create difference input size
        DES_cblock key = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
        int i,count=0;
        int size[5] = {64,512,4096,32768};
        struct timeval t0;
        struct timeval t1;
        char * temp;
        printf("sizeof the array: %d \n",sizeof(size));
        return;
        for(i=0;i<sizeof(size)/sizeof(int);i++){
            count=0;
            temp=malloc(size[i]);
            while(count<=size[i]){
                temp[i]=inputBuffer[i];
                count++;
            }
            gettimeofday(&t0, 0);
            xxh_des_ofb_encrypt(count,temp,&outputBuffer,&key);
            gettimeofday(&t1, 0);
            //des cbc mode
            long long elapsed = (t1.tv_sec-t0.tv_sec)*1000000LL + t1.tv_usec-t0.tv_usec;
            printf("Time Elapsed: %llu\n",elapsed);
            free(temp);
        }
        
    }
    printf( "output file location: %s\n", outputFileName );
    outputFile(outputFileName,inputBufferSize,outputBuffer);

}

void generateKey(int entropy,unsigned long * key){
    srand(entropy);
    int i=0;
    for(i=0;i<4;i++){
        key[i]=rand();
    }
    
}

void checkValidInput(char* input,char* name){
    if (input==NULL) {
        printf("%s is empty\n Usage: ./executableName.out [encryption -e or decryption -d] [Block Cipher Mode: CBT or CTR ] [key] [inputFileName] [outputFileName]\n",name);
        exit(1);
    }
}

void outputFile(char * outputFileName,int size, char * outputBuffer){
    FILE *ofp;
    ofp = fopen(outputFileName, "w+"); //input file (plaintext or ciphertext)
    if(ofp==NULL){
        fprintf(stderr, "Can't open/create output file %s!\n",
                outputFileName);
        exit(1);
    }
    int i=0;
    for(i=0;i<size;i++){
        fprintf(ofp, "%c",outputBuffer[i]);
    }
    fclose(ofp);
}


int readInFile(char * inputFileName,char ** inputBuffer){
    FILE *ifp;
    ifp = fopen(inputFileName, "rb"); //input file (plaintext or ciphertext)
    if (ifp == NULL) {
        
        fprintf(stderr, "Can't open input file %s!\n",inputFileName);
        exit(1);
    }
    fseek(ifp, 0, SEEK_END);
    long fsize = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    *inputBuffer = malloc(fsize);
    fread(*inputBuffer, fsize, 1, ifp);
    
    fclose(ifp);
    return fsize;
}