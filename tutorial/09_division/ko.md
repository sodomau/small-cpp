---
title: 몫과 나머지
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 사탕 18개를 5개씩 담을 때 봉지 수와 남는 수를 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

`/`는 나누기, `%`는 정수 나눗셈의 나머지입니다. 사탕 17개를 5개씩 담으면 세 봉지를 만들고 2개가 남습니다.

## 실행해 보기

@code example.cpp

정수끼리 나누면 소수 부분을 버립니다. `5 / 2`는 2이지만, `5.0 / 2`처럼 한쪽이 double이면 2.5입니다. 결과를 담는 변수만 double로 바꾸어도 먼저 계산한 `5 / 2`는 2입니다.

나누는 수에 0을 넣으면 안 됩니다. /와 %는 곱셈처럼 덧셈보다 먼저 계산합니다.

예상 출력:

```text
3
2
2.5
```

## Exercise — 한 가지 바꾸기

사탕 18개를 5개씩 담을 때 봉지 수와 남는 수를 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
