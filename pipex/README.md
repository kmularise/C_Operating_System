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
## todo list
- [ ] 관련 개념 이해하기
    - [ ] 시스템 콜 이해하기
- [ ] PATH 환경 변수 이해하기
- [ ] 시스템 프로그래밍
## 확인할 사항
- 기능 만들 때, malloc과 free는 다른 곳에서 하는 게 좋을 것 같다.
    그 이유는 입력 변수로 stack 영역에 있는 변수와 heap 영역에 있는 변수를 모두 넣을 수 있기 때문에, 함수의 재사용도가 높아지기 때문이다.
## 참고자료
- https://m.blog.naver.com/occidere/220821140420
