echo "Start testing"
sh 64build.sh
./program -e test OFB key input.txt ciphertext
echo "END testing"