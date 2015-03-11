echo "Start Execution"
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
./program -e performance OFB key input.txt ciphertext
echo "END Execution"