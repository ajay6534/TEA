echo "Start Performance Measure"
sh build.sh
./program -e performance OFB key sample.txt ciphertext
echo "END Performance Measure"