echo "Start Execution"
gcc -m32 -o tea.o -c tea.c
gcc -m32 XinghuangXu.TEA.c tea.o
./a.out -e CBT 123 input.txt ciphertext
./a.out -d CBT 123 ciphertext plaintext
echo "END Execution"