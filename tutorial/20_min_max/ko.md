---
title: Finding the Largest and Smallest
part: algorithms
part-title: Part III — Thinking with Programs
goal: Array를 한 번 훑어 가장 큰 값, 가장 작은 값과 위치를 찾습니다.
related-example: reference/array
---

## 지금까지 본 것 중 가장 큰 값 기억하기
가장 큰 값을 찾으려면 첫 번째 값을 `largest`로 기억한 뒤 나머지를 하나씩 비교합니다. 더 큰 값을 만나면 기억을 바꿉니다.

## 먼저 실행해 보세요

@code example1.cpp

## 값뿐 아니라 위치도 기억할 수 있습니다
때로는 가장 작은 값 자체보다 **어디에 있는지**가 필요합니다. 그럴 때는 `smallestIndex`를 기억하고 비교할 때 `numbers[smallestIndex]`를 사용합니다.

첫 값을 시작점으로 쓰기 때문에 이 lesson의 Array는 비어 있지 않다고 가정합니다.

## 조금 바꾸어 보기

@code example2.cpp

## 좋은 초기값은 데이터에서 가져옵니다
`largest = 0`으로 시작하면 모든 값이 음수일 때 틀립니다. 첫 번째 실제 값을 초기 답으로 삼으면 그런 특별한 가정이 필요 없습니다. 이 패턴은 앞으로 정렬에서도 다시 사용합니다.

## Exercise — 가장 작은 값

Array에서 가장 작은 값을 찾아 출력하세요.

@exercise exercise1_starter.cpp

### Hint

첫 번째 값을 smallest로 두고 index 1부터 비교하세요.

@solution exercise1_solution.cpp

## Exercise — 가장 큰 값의 위치

가장 큰 값의 index를 찾아 값과 index를 함께 출력하세요.

@exercise exercise2_starter.cpp

### Hint

largestIndex를 0으로 시작하고 `numbers[i] > numbers[largestIndex]`를 비교하세요.

@solution exercise2_solution.cpp
