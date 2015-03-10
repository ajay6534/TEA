#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void encrypt(int key,char* plainTextFile);
void checkValidInput(char* input,char* name);

int main(int argc,char **argv)
{
    checkValidInput(argv[1],"key");
    checkValidInput(argv[2],"input file name");
    int key= strtol(argv[1], NULL, 0);
    encrypt(key,argv[2]);
    
}

void checkValidInput(char* input,char* name){
    if (input==NULL) {
        printf("%s is empty\n Usage: ./executableName.out [key] [inputFileName]\n",name);
        exit(1);
    }
}

/*
 *Can be use to both encryt and decrypt since both procedures are the same
 */
void encrypt(int key,char* plainTextFile){
    srand(key);
    int r;
    
    FILE *ifp, *ofp;
    char outputFilename[256];
    sprintf(outputFilename, "output%ld", time(NULL));
    
    ifp = fopen(plainTextFile, "rb"); //input file (plaintext or ciphertext)
    ofp = fopen(outputFilename, "ab"); //output file(plaintext or ciphertext)
    
    if (ifp == NULL) {
        
        fprintf(stderr, "Can't open input file %s!\n",plainTextFile);
        exit(1);
    }
    if (ofp == NULL) {
        fprintf(stderr, "Can't open/create output file %s!\n",
                outputFilename);
        exit(1);
    }
    
    fseek(ifp, 0, SEEK_END);
    long fsize = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, ifp);
    for(int i=0;i<fsize;i++){
        r = rand();
        fprintf(ofp, "%c",string[i]^r);
    }
    
    fclose(ifp);
    fclose(ofp);
    printf("\nOutput file name: %s\n",outputFilename);
}