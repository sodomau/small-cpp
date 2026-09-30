---
title: 어떤 값을 비교했는지 보기
part: algorithms
part-title: Part III — Thinking with Programs
goal: 어떤 값을 비교했는지 보기
related-example: reference/array
---

## 이번에 배울 것

중간에 값을 출력하면 프로그램이 답을 찾는 과정을 추적할 수 있습니다.

## 실행해 보기

@code example2.cpp

예제는 23을 찾으며 Checking 12, Checking 23을 출력합니다. 비교 횟수는 2입니다.

이번 예제는 비교 과정을 관찰하는 용도입니다. value를 없는 값으로 바꾸면 범위가 비어 끝나지만, 별도의 성공 안내는 출력하지 않습니다.

## Exercise — 비교 횟수 세기

Binary Search가 값을 찾을 때 몇 번 비교했는지 count를 추가해 출력하세요.

@exercise exercise2_starter.cpp

### Hint

while을 한 번 돌 때마다 comparisons를 1 증가시키세요.

@solution exercise2_solution.cpp
