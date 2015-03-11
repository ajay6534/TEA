echo "Start Performance Measure"
sh 64build.sh
./program -e performance OFB key input.txt ciphertext
echo "END Performance Measure"