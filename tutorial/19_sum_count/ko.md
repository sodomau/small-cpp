---
title: Counting and Summing
part: algorithms
part-title: Part III — Thinking with Programs
goal: 여러 값을 훑으며 합계와 개수를 누적하는 기본 알고리즘을 만듭니다.
related-example: reference/array
---

## 반복하면서 답을 만들어 가기
Array의 모든 값을 한 번씩 보면서 하나의 답을 만들어 낼 수 있습니다. 합계를 구할 때는 `total`을 0에서 시작하고 값을 하나씩 더합니다. 이런 변수를 **accumulator**라고 부르기도 합니다.

## 먼저 실행해 보세요

@code example1.cpp

## 세는 것도 같은 패턴입니다
조건에 맞는 값을 만날 때마다 `count = count + 1`을 하면 개수를 셀 수 있습니다. 합계와 개수는 이후 평균, 검색, 통계 같은 많은 알고리즘의 재료가 됩니다.

지금은 Array를 함수에 전달할 때도 `Array<int> numbers`처럼 값으로 받습니다. reference는 Lesson 31에서 다룹니다.

## 조금 바꾸어 보기

@code example2.cpp

## 알고리즘은 작은 단계의 조합입니다
처음에는 `for`, `if`, 변수만 보이지만, 이제 이 도구들을 조합해 **문제를 푸는 절차**를 만들고 있습니다. 앞으로는 같은 Array를 어떻게 더 영리하게 살펴볼지 생각합니다.

## Exercise — 평균 구하기

Array의 합계를 구한 뒤 값의 개수로 나누어 평균을 출력하세요. 실수 나눗셈이 되도록 total을 double로 만들어 보세요.

@exercise exercise1_starter.cpp

### Hint

`double total = 0;`으로 시작하고 마지막에 `total / numbers.Length()`를 계산하세요.

@solution exercise1_solution.cpp

## Exercise — 양수 개수 세기

Array에서 0보다 큰 값이 몇 개인지 세어 출력하세요.

@exercise exercise2_starter.cpp

### Hint

각 값에 대해 `numbers[i] > 0`인지 검사하고 count를 1 증가시키세요.

@solution exercise2_solution.cpp
