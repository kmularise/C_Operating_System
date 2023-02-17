### 적용해야 할 쿼리 명령어
ex) < infile ls -l | wc -l > outfile

### 보너스 히어독 양식
cmd << LIMITER | cmd1 >> file

### pipex infile fd
```c
pipex.infile = open(argv[1], O_RDONLY);
```
### pipex outfile fd
```c
pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
```
* 644인 이유 : shell 명령어 시행 시 이렇게 만든다.

### 참고 문서
https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-waitpid-wait-specific-child-process-end

https://reakwon.tistory.com/105
