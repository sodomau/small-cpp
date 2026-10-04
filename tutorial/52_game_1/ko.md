---
title: 배운 것을 묶어 작은 게임 만들기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 배운 것을 묶어 작은 게임 만들기
related-example: programs/pong
---

## 이번에 배울 것

**게임**은 입력을 받아 상태를 바꾸고 그 상태를 그림으로 보여 주는 프로그램입니다. 이번은 새 문법 수업이 아니라 조립 활동입니다.

## 실행해 보기

@code example1.cpp

예제를 실행하고 방향키 위·아래로 막대를 움직이세요. 코드는 ① 시간·입력 읽기 ② 위치 바꾸기 ③ 충돌 처리 ④ 그리기 순서입니다.

충돌은 물체가 서로 닿았는지 판단하는 일입니다. 벽을 넘었을 때 방향만 바꾸지 않고 위치도 경계로 돌려놓습니다. 한 번에 전체를 고치지 말고 막대 이동 부분부터 찾으세요.

## Exercise — paddle이 화면 밖으로 못 나가게

시작 코드는 첫 Pong 예제에서 paddle 이동만 분리한 것입니다. paddle_y가 0보다 작아지거나 420보다 커지지 않도록 제한하는 코드를 추가하세요. 위아래 방향키를 오래 눌러도 paddle 전체가 창 안에 남아 있어야 합니다. 확인한 제한 코드는 첫 Pong 예제에도 옮겨 사용할 수 있습니다.

@exercise exercise1_starter.cpp

### Hint

입력으로 paddle_y를 바꾼 뒤 두 개의 if로 0과 420 범위에 맞추세요.

@solution exercise1_solution.cpp

