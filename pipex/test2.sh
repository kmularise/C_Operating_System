# ./a.out sample "tr a k" "tr k b" outfile
# cat outfile
# ./a.out sample "tr a k" "tr k b" outfile
# cat outfile
./a.out /dev/urandom "cat" "head -1" outfile
cat outfile
rm outfile
# ./a.out sample "sleep 3" "ls" outfile
# cat outfile
# ./a.out sample "sleep 5" "sleep 3" outfile
# cat outfile
