# pipex
## 문제조건
|항목|조건|
|------|---|
|Program name|pipex|
|Turn in files|Makefile, *.h, *.c|
|Makefile|NAME, all, clean, fclean, re|
|Arguments|file1 cmd1 cmd2 file2|
|External functs|* open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid <br> * ft_printf and any equivalent YOU coded

## 기능 목록
- [ ] 명령어 파싱
- [ ] 명령어 경로 찾기
- [ ] shell 환경에 따라 다르게 에러메시지 띄우기
- [ ] infile과 outfile 공통으로 해야 할 조건 처리
- [ ] infile 관련된 프로세스 처리
- [ ] outfile 관련된 프로세스 처리
- [ ] 메모리 누수 확인하기
## todo list
- [ ] 관련 개념 이해하기
    - [ ] 시스템 콜 이해하기
- [ ] PATH 환경 변수 이해하기
- [ ] 시스템 프로그래밍
- [ ] pipe 통신 공부하기
- [ ] 메모리 누수 확인하기
- [ ] heardoc 알아보기
- [ ] lldb 알아보기
## 확인할 사항
- 기능 만들 때, malloc과 free는 다른 곳에서 하는 게 좋을 것 같다.
    그 이유는 입력 변수로 stack 영역에 있는 변수와 heap 영역에 있는 변수를 모두 넣을 수 있기 때문에, 함수의 재사용도가 높아지기 때문이다.
- 리눅스 상대경로
- exec를 할 때 메모리영역의 변화를 확인할 필요가 있음.
- 에러는 perror 처리
- fork 뿐만 아니라 dup, pipe
## 참고자료
- https://m.blog.naver.com/occidere/220821140420
- https://80000coding.oopy.io/3c770884-c5f1-4888-a4df-638cb17bdaa8
- https://dining-developer.tistory.com/13 : gdb 사용법
- https://iredays.tistory.com/126 : process, thread 실습
- wait, waitpid https://codingdog.tistory.com/entry/%EB%A6%AC%EB%88%85%EC%8A%A4-waitpid-%ED%95%A8%EC%88%98-%EC%9E%90%EC%8B%9D-%ED%94%84%EB%A1%9C%EC%84%B8%EC%8A%A4%EB%A5%BC-%EA%B8%B0%EB%8B%A4%EB%A6%B0%EB%8B%A4
- https://www.it-note.kr/133 : waitpid 관련
- https://stackoverflow.com/questions/23208405/debugging-multiprocess-program-in-c : gdb 이용한 디버그

### 히어독
```sh
# 이런식으로 쓰면 limit를 칠때까지 표준 입력을 받고
# 표준입력을 받은 부분을 표준 출력으로 내보낸다.
cat << limit
heredoc> fsdfdkjsfjsl
heredoc> dssdfjsdlkjsdklf
heredoc> sdfsdjfldksjflskjdsfklsf
heredoc> sdjksdfjkllsdfjlksdjkl
heredoc> sdffjsdlfjklsdjklsdfj
heredoc> dsdsds
heredoc> limit 
fsdfdkjsfjsl
dssdfjsdlkjsdklf
sdfsdjfldksjflskjdsfklsf
sdjksdfjkllsdfjlksdjkl
sdffjsdlfjklsdjklsdfj
dsdsds
```
