echo "Start Performance Measure"
sh build.sh
./program -e performance OFB key input.txt ciphertext
echo "END Performance Measure"