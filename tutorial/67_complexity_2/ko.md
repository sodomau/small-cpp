---
title: 반씩 줄이는 일은 얼마나 반복될까
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 반씩 줄이는 일은 얼마나 반복될까
related-example: reference/array
---

## 이번에 배울 것

범위를 매번 반으로 줄이면 데이터가 커져도 반복 횟수는 천천히 늘어납니다. 이런 증가를 O(log n)이라고 합니다.

## 실행해 보기

@code example2.cpp

1024를 정수 나눗셈으로 계속 반으로 줄입니다. 1024, 512, …, 1을 처리하므로 Steps: 11입니다.

이 수는 예제의 반복 횟수이지 모든 이진 검색의 정확한 비교 횟수는 아닙니다. Big-O는 증가 경향을 요약한 표기입니다.

## Exercise — 몇 번 반으로 나눌까

n=1000을 시작으로 n이 0이 될 때까지 2로 나누며 몇 단계가 필요한지 세세요.

@exercise exercise2_starter.cpp

### Hint

while 안에서 `n = n / 2`와 count 증가를 함께 하세요.

@solution exercise2_solution.cpp
