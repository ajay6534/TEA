void encipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k);
void decipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k);
void tea_cbc_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);
void tea_cbc_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);
void tea_ctr_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);
void tea_ctr_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);
void tea_ofb_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);
void tea_ofb_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);
void xxh_des_decrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *seed);
void xxh_des_encrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *seed);
void xxh_ofb_encrypt(int inputBufferSize,char * inputBuffer,char **outputBuffer, DES_cblock *seed);
