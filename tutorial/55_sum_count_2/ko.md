---
title: 조건에 맞는 값 세기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 조건에 맞는 값 세기
related-example: reference/array
---

## 이번에 배울 것

개수를 셀 때는 조건에 맞는 원소를 만날 때만 1을 더합니다.

## 실행해 보기

@code example2.cpp

`numbers[i] % 2 == 0`은 2로 나눈 나머지가 0, 즉 짝수인지 묻습니다. 8, 4, 10이 해당해 Even: 3이 나옵니다. 0도 이 조건을 만족합니다.

CountEven은 배열을 매개변수로 받습니다. 지금은 Array<int> 값을 복사해서 받으며, 복사를 피하는 방법은 뒤의 참조 수업에서 배웁니다.

## Exercise — 양수 개수 세기

Array에서 0보다 큰 값이 몇 개인지 세어 출력하세요.

@exercise exercise2_starter.cpp

### Hint

각 값에 대해 `numbers[i] > 0`인지 검사하고 count를 1 증가시키세요.

@solution exercise2_solution.cpp
