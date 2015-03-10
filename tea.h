void encipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k);
void decipher(unsigned long *const v,unsigned long *const w,
              const unsigned long *const k);
void cbc_encrypt(int size, unsigned long * plaintext, unsigned long ** ciphertext,
                 const unsigned long *const k);
void cbc_decrypt(int size, unsigned long * ciphertext, unsigned long ** plaintext,
                 const unsigned long *const k);
void ctr_encrypt(int size, unsigned long * plaintext, unsigned long ** ciphertext,
                 const unsigned long *const k);
void ctr_decrypt(int size, unsigned long * ciphertext, unsigned long ** plaintext,
                 const unsigned long *const k);
