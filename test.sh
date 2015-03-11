echo "Start testing"
sh build.sh
./program -e test OFB key input.txt ciphertext
echo "END testing"