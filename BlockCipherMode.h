void cbc_encrypt(int size, char * plaintext, char ** ciphertext,
              const unsigned long *const k);
void cbc_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);
void ctr_encrypt(int size, char * plaintext, char ** ciphertext,
                 const unsigned long *const k);
void ctr_decrypt(int size, char * ciphertext, char ** plaintext,
                 const unsigned long *const k);
