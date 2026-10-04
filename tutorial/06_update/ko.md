---
title: 기억한 값으로 계산하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 남은 기회 lives를 3으로 만들고, 1을 줄인 뒤 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

변수에 저장한 값도 계산에 사용할 수 있습니다. 계산한 결과를 다시 저장하면 점수를 올릴 수 있습니다.

## 실행해 보기

@code example.cpp

`score = score + 5;`는 ① 현재 값 10을 읽고 ② 5를 더하고 ③ 결과 15를 score에 저장합니다. 수학의 등식처럼 양쪽이 같다는 뜻이 아닙니다.

`print(score + 5);`만 실행하면 계산 결과를 보여 줄 뿐, score 자체는 바뀌지 않습니다.

예상 출력:

```text
15
```

## Exercise — 한 가지 바꾸기

남은 기회 lives를 3으로 만들고, 1을 줄인 뒤 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
