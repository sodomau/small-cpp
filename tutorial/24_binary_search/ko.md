---
title: Binary Search
part: algorithms
part-title: Part III — Thinking with Programs
goal: 정렬된 데이터의 성질을 이용해 탐색 범위를 절반씩 줄이는 Binary Search를 만듭니다.
related-example: reference/array
---

## 정렬되어 있다면 더 영리하게 찾을 수 있습니다
Linear Search는 앞에서부터 하나씩 봅니다. 하지만 숫자가 정렬되어 있다면 가운데 값을 보고 찾는 값이 왼쪽에 있을지 오른쪽에 있을지 결정할 수 있습니다.

한 번 비교할 때마다 필요 없는 절반을 버리는 것이 Binary Search의 핵심입니다.

## 먼저 실행해 보세요

@code example1.cpp

## left와 right가 남은 범위입니다
처음에는 Array 전체가 후보입니다. middle을 확인한 뒤 찾는 값이 더 작으면 right를 왼쪽으로, 더 크면 left를 오른쪽으로 옮깁니다. `left > right`가 되면 남은 후보가 없다는 뜻입니다.

중요한 전제는 **Array가 정렬되어 있어야 한다**는 것입니다. 정렬되지 않은 데이터에서는 어느 절반을 버려도 되는지 알 수 없습니다.

## 조금 바꾸어 보기

@code example2.cpp

## 절반씩 줄어드는 힘
1,000개 중 하나를 찾는다고 해도 범위는 대략 1000 → 500 → 250 → 125처럼 빠르게 줄어듭니다. 다음 lesson에서는 Linear Search와 실제 비교 횟수를 나란히 측정해 봅니다.

## Exercise — Binary Search 완성

정렬된 `{4, 8, 15, 16, 23, 42}`에서 23을 찾아 index를 출력하는 Binary Search를 작성하세요.

@exercise exercise1_starter.cpp

### Hint

left, right, middle 세 변수를 사용하고 매번 범위를 절반으로 줄이세요.

@solution exercise1_solution.cpp

## Exercise — 비교 횟수 세기

Binary Search가 값을 찾을 때 몇 번 비교했는지 count를 추가해 출력하세요.

@exercise exercise2_starter.cpp

### Hint

while을 한 번 돌 때마다 comparisons를 1 증가시키세요.

@solution exercise2_solution.cpp
