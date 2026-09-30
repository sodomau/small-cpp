---
title: 게임에 점수 붙이기
part: making_things
part-title: Part II — Making Things
goal: 게임에 점수 붙이기
related-example: programs/pong
---

## 이번에 배울 것

**게임 규칙**은 어떤 사건이 일어났을 때 상태를 어떻게 바꿀지 정한 것입니다. 공을 받아 냈을 때만 점수를 늘립니다.

## 실행해 보기

@code example2.cpp

좌우 키로 막대를 움직이세요. 공이 막대의 범위에 닿으면 튕기고 score가 1 증가합니다. SetTitle은 현재 점수를 창 제목에 보여 줍니다.

놓쳤을 때는 공만 시작 위치로 돌립니다. 적중과 실패를 각각 시험하세요. 문제가 있으면 위치 갱신·조건·점수 변경 중 어느 단계인지 나누어 확인합니다.

## Exercise — score를 제목에 표시

시작 코드의 paddle을 좌우 방향키로 움직여 보세요. 공이 paddle에 맞을 때만 score를 1 증가시키고 `window.SetTitle("Score: ", score)`로 창 제목에 표시하세요. paddle을 옆으로 치워 공을 놓쳤을 때에는 점수가 늘어나면 안 됩니다. 충돌 검사는 시작 코드에 제공되어 있습니다.

@exercise exercise2_starter.cpp

### Hint

score는 loop 밖에서 0으로 만들고 충돌 if 안에서 증가시키세요.

@solution exercise2_solution.cpp
