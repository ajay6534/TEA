#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tea.h"

int readInFile(char * inputFileName,unsigned long ** inputBuffer);
void outputFile(char * outputFileName,unsigned long * outputBuffer);
void checkValidInput(char* input,char* name);
void generateKey(int entropy,unsigned long * key);
void processRequest(char * mode,char *blockCipherMode,int entropy, char * inputFileName, char * outputFileName);

int main(int argc,char **argv)
{
    checkValidInput(argv[1],"Mode? Encryption or Decryption");
//    char * mode=argv[1];
    checkValidInput(argv[2],"Block Cipher Mode");
//    char * blockCipherMode=argv[2];
    checkValidInput(argv[3],"key");
    checkValidInput(argv[4],"input file name");
//    char * inputFileName=argv[4];
    checkValidInput(argv[5],"output file name");
//    char * outputFileName=argv[5];
    processRequest(argv[1],argv[2],strtol(argv[3], NULL, 0),argv[4],argv[5]);
}

void processRequest(char * mode,char *blockCipherMode,int entropy, char * inputFileName, char * outputFileName){
    unsigned long key[4];
    //generate the key
    generateKey(entropy,key);
//    int i=0;
//    for(i=0;i<4;i++){
//        printf("%lu\n",key[i]);
//    }
    //read in the input file and stored it in a char * with the size
    unsigned long * inputBuffer;
    int inputBufferSize;
    printf( "input file location: %s\n", inputFileName );
    inputBufferSize=readInFile(inputFileName,&inputBuffer);
    unsigned long * outputBuffer;
    printf( "size: %d\n", inputBufferSize );
    //    check block cipher mode
    if(strcmp(blockCipherMode,"CBT")==0){
        printf("CBT Mode\n");
        if(strcmp("-e",mode)==0){ //encrypt
            printf("Encryption\n");
            cbc_encrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
        }else{  //decrypt
            printf("Decryption\n");
            cbc_decrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
        }
    }else if(strcmp(blockCipherMode,"CTR")==0){
        printf("CTR Mode\n");
        if(strcmp("-e",mode)==0){ //encrypt
            printf("Encryption\n");
            ctr_encrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
        }else if(strcmp("-d",mode)==0){  //decrypt
            printf("Decryption\n");
            ctr_decrypt(inputBufferSize,inputBuffer,&outputBuffer,key);
        }else{
            printf("Invalid Operation Mode: %s. Valid Mode: -e, -d\n",mode);
        }
    }else{
        fprintf(stderr, "Invalid Block Cipher Mode: %s!\n Valid Values: CBT, CTR.",blockCipherMode);
        exit(1);
    }
    printf( "output file location: %s\n", outputFileName );
    outputFile(outputFileName,outputBuffer);

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

void outputFile(char * outputFileName,unsigned long * outputBuffer){
    FILE *ofp;
    ofp = fopen(outputFileName, "w+"); //input file (plaintext or ciphertext)
    if(ofp==NULL){
        fprintf(stderr, "Can't open/create output file %s!\n",
                outputFileName);
        exit(1);
    }
    fprintf(ofp, "%s",(char*)outputBuffer);
    fclose(ofp);
}


int readInFile(char * inputFileName,unsigned long ** inputBuffer){
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