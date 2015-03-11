echo "Start Example"
sh 64build.sh
./program -e tea CBT key input.txt ciphertext
./program -d tea CBT key ciphertext plaintext
./program -e tea CTR key input.txt ciphertext
./program -d tea CTR key ciphertext plaintext
./program -e tea OFB key input.txt ciphertext
./program -d tea OFB key ciphertext plaintext
./program -e des CBT key input.txt ciphertext
./program -d des CBT key ciphertext plaintext
./program -e des OFB key input.txt ciphertext
./program -d des OFB key ciphertext plaintext
./program -e test OFB key input.txt ciphertext
./program -e performance OFB key sample.txt ciphertext
#executable [operation mode -e(encription) or -d(decription] [Block Cipher: tea or des] [Block Cipher Mode: CBT, or OFB] [Key file name(8 integer numbers one on each line)] [input file name] [output file name]
echo "END Example"