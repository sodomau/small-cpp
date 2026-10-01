---
title: 타이머의 값을 화면에 표시하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 타이머의 값을 화면에 표시하기
related-example: reference/timer
---

## 이번에 배울 것

콜백에서는 값을 바꾸고, 창의 반복문에서는 그 값을 읽어 그림을 그릴 수 있습니다.

## 실행해 보기

@code example2.cpp

OnSecond가 전역 seconds를 늘리고 DrawText가 현재 값을 표시합니다. **Format**은 글자와 값을 이어 붙인 String을 돌려줍니다. Print와 달리 직접 출력하지 않습니다.

Timer는 별도 계산 스레드가 아닙니다. Show나 Sleep이 이벤트를 처리할 때 콜백을 실행하므로 긴 계산은 호출을 늦출 수 있습니다. 정확한 시간 측정은 StopWatch로 하세요.

## Exercise — 창의 제목 바꾸기

Timer callback이 1초마다 level을 1씩 증가시키게 하세요. Window loop에서는 현재 level을 `SetTitle("Level ", level)`로 제목에 표시하세요.

@exercise exercise2_starter.cpp

### Hint

callback에서는 전역 int level만 바꾸고, Window title은 main loop에서 갱신하면 간단합니다.

@solution exercise2_solution.cpp
