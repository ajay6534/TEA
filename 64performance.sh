echo "Start Performance Measure"
sh 64build.sh
./program -e performance OFB key sample.txt ciphertext
echo "END Performance Measure"