# ./pipex_bonus infile "sleep 1" "sleep 1" "sleep 1" outfile
./pipex_bonus here_doc END "cat" "head -1" outfile_here_doc
# ./pipex_bonus pp "rm pp" "ls -al" outfile