---
title: Make a Game
part: making_things
part-title: Part II — Making Things
goal: Window, 입력, animation, 시간과 sound를 하나의 작은 게임으로 결합합니다.
related-example: programs/pong
---

## 지금까지 배운 것을 하나로 묶기
게임은 새로운 마법 기능 하나가 아니라 우리가 이미 배운 작은 아이디어들의 조합입니다. Window에 그리고, 키보드를 읽고, frame마다 위치를 바꾸고, StopWatch로 실제 시간을 측정하고, 사건이 생기면 소리를 냅니다.

간단한 Pong의 한쪽 paddle과 공을 만들어 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## 게임 loop를 네 부분으로 읽기
긴 코드도 역할로 나누어 보면 단순합니다.

1. **Time** — dt를 측정합니다.
2. **Input** — 키보드를 읽습니다.
3. **Update** — paddle과 공의 위치, 충돌을 계산합니다.
4. **Draw** — 현재 상태를 화면에 그립니다.

아직 class가 없어도 변수와 함수만으로 작은 게임을 충분히 만들 수 있습니다.

## 충돌에서는 위치도 함께 고칩니다
공이 한 frame에 벽을 조금 넘어갈 수 있기 때문에 속도의 방향만 바꾸면 다음 frame에도 여전히 벽 밖에 있을 수 있습니다. 그러면 방향이 다시 뒤집혀 공이 벽에 붙은 것처럼 보일 수 있습니다.

그래서 이 예제는 충돌을 발견하면 **먼저 공을 경계 위치로 되돌리고, 그다음 속도의 방향을 바꿉니다.**

`collision → position correction → velocity response`

Paddle 충돌과 벽 충돌 모두 같은 원칙을 사용합니다.

## 조금 바꾸어 보기

@code example2.cpp

## 완성보다 바꾸어 보는 것이 중요합니다
게임 코드는 정답 하나가 있는 문제가 아닙니다. 속도, 크기, 색, 규칙을 조금씩 바꾸면 전혀 다른 느낌이 납니다. 기존 코드를 이해한 뒤 한 가지 규칙을 추가하는 것이 좋은 다음 단계입니다.

Part II는 여기서 끝납니다. 다음 Part에서는 새로운 화면 기능보다, 지금까지 배운 변수·반복·함수·Array를 사용해 **문제를 해결하는 알고리즘**을 만들어 봅니다.

## Exercise — paddle이 화면 밖으로 못 나가게

첫 Pong 예제에서 paddleY가 0보다 작아지거나 420보다 커지지 않도록 제한하는 코드를 추가하세요.

@exercise exercise1_starter.cpp

### Hint

입력으로 paddleY를 바꾼 뒤 두 개의 if로 0과 420 범위에 맞추세요.

@solution exercise1_solution.cpp

## Exercise — score를 제목에 표시

공이 paddle에 맞을 때 score를 1 증가시키고 `window.SetTitle("Score: ", score)`로 창 제목에 표시하세요.

@exercise exercise2_starter.cpp

### Hint

score는 loop 밖에서 0으로 만들고 충돌 if 안에서 증가시키세요.

@solution exercise2_solution.cpp
