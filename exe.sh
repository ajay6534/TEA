echo "Start Execution"
gcc -m32 -o tea.o -c tea.c
gcc -m32 XinghuangXu.TEA.c tea.o -lcrypto
./a.out -e tea CBT key input.txt ciphertext
./a.out -d tea CBT key ciphertext plaintext
./a.out -e tea CTR key input.txt ciphertext
./a.out -d tea CTR key ciphertext plaintext
./a.out -e tea OFB key input.txt ciphertext
./a.out -d tea OFB key ciphertext plaintext
./a.out -e des CBT key input.txt ciphertext
./a.out -d des CBT key ciphertext plaintext
./a.out -e des OFB key input.txt ciphertext
./a.out -d des OFB key ciphertext plaintext
./a.out -e test OFB key input.txt ciphertext
./a.out -e performance OFB key input.txt ciphertext
echo "END Execution"