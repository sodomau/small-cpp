---
title: 합계와 개수 구하기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 합계와 개수 구하기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 값을 차례로 더하기

### 이번에 배울 것

**알고리즘**은 답을 구하는 절차입니다. 합계는 지금까지 더한 값을 기억하면서 다음 값을 더해 구합니다.

### 실행해 보기

@code example1.cpp

total은 0 → 3 → 10 → 12 → 21 → 25로 바뀝니다. 예상 출력은 Sum: 25입니다.

아직 더한 값이 없을 때의 합은 0이므로 시작값도 0입니다. 반복문 안에서 total을 매번 0으로 만들면 누적되지 않습니다.

## 조건에 맞는 값 세기

### 이번에 배울 것

개수를 셀 때는 조건에 맞는 원소를 만날 때만 1을 더합니다.

### 실행해 보기

@code sum_count_2_example2.cpp

`numbers[i] % 2 == 0`은 2로 나눈 나머지가 0, 즉 짝수인지 묻습니다. 8, 4, 10이 해당해 Even: 3이 나옵니다. 0도 이 조건을 만족합니다.

count_even은 배열을 매개변수로 받습니다. 지금은 Array<int> 값을 복사해서 받으며, 복사를 피하는 방법은 뒤의 참조 수업에서 배웁니다.

## Exercise — 평균 구하기

Array의 합계를 구한 뒤 값의 개수로 나누어 평균을 출력하세요. 실수 나눗셈이 되도록 total을 double로 만들어 보세요.

@exercise exercise1_starter.cpp

### Hint

`double total = 0;`으로 시작하고 마지막에 `total / numbers.length()`를 계산하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 양수 개수 세기

Array에서 0보다 큰 값이 몇 개인지 세어 출력하세요.

@exercise sum_count_2_exercise2_starter.cpp

### Hint

각 값에 대해 `numbers[i] > 0`인지 검사하고 count를 1 증가시키세요.

@solution sum_count_2_exercise2_solution.cpp
