## philosopher 과제 목표
1. 식사하는 철학자 문제에서 철학자들이 먹고 자고 생각하는 프로그램을 구현한다.
2. 멀티 쓰레드 환경에서 dead lock과 data race 문제에 유의하여 구현한다.
3. 멀티 프로세스 환경에서 dead lock과 data race 문제에 유의하여 구현한다.

## 주요 개념
### The Deadlock Problem
- 두 개 이상의 프로세스나 스레드가 서로 자원을 얻지 못해서 다음 처리를 하지 못하여, 무한히 다음 자원을 기다리게 되는 상태

### Deadlock 발생의 4가지 조건
4가지 모두 성립해야 데드락 발생
(하나라도 성립하지 않으면 데드락 문제 해결 가능)
- 상호 배제(Mutual exclusion)
    - 자원은 한번에 한 프로세스만 사용할 수 있음
- 점유 대기(Hold and wait)
    - 최소한 하나의 자원을 점유하고 있으면서 다른 프로세스에 할당되어 사용하고 있는 자원을 추가로 점유하기 위해 대기하는 프로세스가 존재해야 함
- 비선점(No preemption)
    - 다른 프로세스에 할당된 자원은 사용이 끝날 때까지 강제로 빼앗을 수 없음
- 순환 대기(Circular wait)
    - 프로세스의 집합에서 순환 형태로 자원을 대기하고 있어야 함

### Deadlock의 처리 방법
- Deadlock Prevention
    - 자원 할당 시 Deadlock의 4가지 필요 조건 중 어느 하나가 만족되지 않도록 하는 것
- Deadlock Avoidance
    - 자원 요청에 대한 부가적인 정보를 이용해서 deadlock의 가능성이 없는 경우에만 자원을 할당
    - 시스템 state가 원래 state로 돌아올 수 있는 경우에만 자원 할당
- Deadlock Detection and recovery
    - Deadlock 발생은 허용하되 그에 대한 detection 루틴을 두어 deadlock 발견 시 recover
- Deadlock Ignorance
    - Deadlock을 시스템이 책임지지 않음
    - Unix를 포함한 대부분의 OS가 채택

1. Deadlock Prevention
- Mutual Exclusion
    - 공유해서는 안되는 자원의 경우 반드시 성립해야 함 → 모든 걸 hold하고 시작
- Hold and Wait
    - 프로세스가 자원을 요청할 때 다른 어떤 자원도 가지고 있지 않아야 한다.
    - 방법 1.  프로세스 시작 시 모든 필요한 자원을 할당 받게 하는 방법 - 이미 hold한 자원도 뱉어놓고 시작 preemption
    - 방법 2. 자원이 필요할 경우 보유 자원을 모두 놓고 다시 요청
- No Preemption
    - process가 어떤 자원을 기다려야 하는 경우 이미 보유한 자원이 선점됨
    - 모든 필요한 자원을 얻을 수 있을 때 그 프로세스는 다시 시작된다.
    - State를 쉽게 save하고 restore할 수 있는 자원에서 주로 사용(CPU, memory)
- Circular Wait
    - 모든 자원 유형에 할당 순서를 정하여 정해진 순서대로만 자원 할당
    - 예를 들어 순서가 3인 자원 Ri를 보유 중인 프로세스가 순서가 1인 자원 Ri을 할당받기 위해서는 우선 Ri를 release해야 한다.

→ Utilization(자원의 이용률) 저하, throughout 감소,  starvation 문제
