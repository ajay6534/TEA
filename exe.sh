echo "Start Execution"
gcc -m32 -o tea.o -c tea.c
gcc -m32 XinghuangXu.TEA.c tea.o -lcrypto
#./a.out -e tea CBT 123 input.txt ciphertext
#./a.out -d tea CBT 123 ciphertext plaintext
#./a.out -e tea CTR 123 input.txt ciphertext
#./a.out -d tea CTR 123 ciphertext plaintext
#./a.out -e tea OFB 123 input.txt ciphertext
#./a.out -d tea OFB 123 ciphertext plaintext
#./a.out -e des CBT 123 input.txt ciphertext
#./a.out -d des CBT 123 ciphertext plaintext
#./a.out -e des OFB 123 input.txt ciphertext
#./a.out -d des OFB 123 ciphertext plaintext
./a.out -e test OFB 123 input.txt ciphertext
echo "END Execution"