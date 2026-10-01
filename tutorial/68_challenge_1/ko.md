---
title: 두 번째로 큰 값 찾기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 두 번째로 큰 값 찾기
related-example: reference/array
---

## 이번에 배울 것

새 문제를 풀기 전에 **무엇을 답으로 할지와 입력의 가정**을 정합니다. 이번에는 두 자리의 후보를 기억합니다.

## 실행해 보기

@code example1.cpp

예제는 원소가 적어도 두 개이며, 두 번째 순위에 중복도 포함합니다. {9, 9, 3}이라면 답은 9입니다. 서로 다른 값 중 둘째라는 뜻은 아닙니다.

새 최댓값을 만나면 이전 최댓값을 second로 옮깁니다. 8, 3, 12, 5, 10에서는 답이 10입니다.

## Exercise — 두 번째로 작은 값

서로 다른 값이 두 개 이상 있다고 가정하고 두 번째로 작은 값을 찾으세요.

@exercise exercise1_starter.cpp

### Hint

smallest와 second를 기억하고, 새 값이 smallest보다 작을 때 두 값을 함께 갱신하세요.

@solution exercise1_solution.cpp

