echo "Start Build"
gcc -m32 -o tea.o -c tea.c
gcc -o program -m32 XinghuangXu.TEA.c tea.o -lcrypto
echo "END Build"