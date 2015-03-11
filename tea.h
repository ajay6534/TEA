
/*
 TEA  Encryption function copy from online source
 */
void encipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k);

/*
 TEA  Decripton function copy from online source
 */
void decipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k);

/*
 TEA  CBC Mode Encryption
 */
void tea_cbc_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);

/*
 TEA  CBC Mode Decryption
 */
void tea_cbc_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);

/*
 TEA  CTR Mode Encryption
 */
void tea_ctr_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);

/*
 TEA  CTR Mode Decryption
 */
void tea_ctr_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);

/*
 TEA  OFB Mode Encryption
 */
void tea_ofb_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);

/*
 TEA  OFB Mode Decryption
 */
void tea_ofb_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);

/*
 DES CBC Mode Encryption function
 */
void xxh_des_decrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *seed);

/*
 DES CBC Mode Decryption function
 */
void xxh_des_encrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *seed);

/*
 DES OFB Mode Encryption function
 */
void xxh_des_ofb_encrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *seed);
