echo "Start Build"
gcc -o tea.o -c tea.c
gcc -o program XinghuangXu.TEA.c tea.o -lcrypto
echo "END Build"