---
title: 값을 차례로 더하기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 값을 차례로 더하기
related-example: reference/array
---

## 이번에 배울 것

**알고리즘**은 답을 구하는 절차입니다. 합계는 지금까지 더한 값을 기억하면서 다음 값을 더해 구합니다.

## 실행해 보기

@code example1.cpp

total은 0 → 3 → 10 → 12 → 21 → 25로 바뀝니다. 예상 출력은 Sum: 25입니다.

아직 더한 값이 없을 때의 합은 0이므로 시작값도 0입니다. 반복문 안에서 total을 매번 0으로 만들면 누적되지 않습니다.

## Exercise — 평균 구하기

Array의 합계를 구한 뒤 값의 개수로 나누어 평균을 출력하세요. 실수 나눗셈이 되도록 total을 double로 만들어 보세요.

@exercise exercise1_starter.cpp

### Hint

`double total = 0;`으로 시작하고 마지막에 `total / numbers.Length()`를 계산하세요.

@solution exercise1_solution.cpp

