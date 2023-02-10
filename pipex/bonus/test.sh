# ./a.out test1 "tr a f" "tr f d" "tr d g" test3
# ./a.out test1 "tr a f" "tr f d" "tr d g" test3
# echo "test3"
# cat test3
# rm -rf test3
./a.out test1 "tr a f" "tr f d" "tr d g" "tr g k" "tr k t" "tr t q" "sleep 2" "head -2" test3
# ./a.out test1 "tr a f" "tr f d" "tr d g" test3
echo "test3"
cat test3
rm -rf test3