---
title: 큰 수부터 순서 정하기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 큰 수부터 순서 정하기
related-example: reference/array
---

## 이번에 배울 것

같은 절차에서 비교 기준을 바꾸면 순서도 바뀝니다. 큰 수부터 나열하는 것을 **내림차순**이라고 합니다.

## 실행해 보기

@code example2.cpp

이번에는 남은 값 중 최댓값을 찾습니다. 비교가 <에서 >로 바뀌고 출력은 9, 7, 5, 4, 2가 됩니다.

정렬 방향을 바꾸려고 반복문 전체를 다시 만들 필요는 없습니다. 어떤 값을 먼저 고르는지 바꾸면 됩니다.

## Exercise — 큰 순서로 바꾸기

Selection Sort를 수정해 큰 값부터 작은 값 순서로 정렬하세요.

@exercise exercise2_starter.cpp

### Hint

smallest 대신 largest를 찾고 비교 방향을 `>`로 바꾸세요.

@solution exercise2_solution.cpp
