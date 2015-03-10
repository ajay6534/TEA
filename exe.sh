echo "Start Execution"

gcc -o tea.o -c tea.c
gcc XinghuangXu.TEA.c tea.o
./a.out -e CBT 123 pg100.txt output1.txt

echo "END Execution"