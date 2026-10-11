---
title: 반씩 줄여서 찾기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 반씩 줄여서 찾기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 찾을 범위를 반으로 줄이기

### 이번에 배울 것

**이진 검색**은 가운데 값과 비교하여 가능한 범위를 반씩 줄이는 방법입니다. 배열이 먼저 작은 순서로 정렬되어 있어야 합니다.

### 실행해 보기

@code example1.cpp

left와 right는 남은 범위의 양 끝입니다. 가운데보다 찾는 값이 작으면 오른쪽 절반을, 크면 왼쪽 절반을 제외합니다.

11의 위치는 5입니다. 못 찾으면 -1을 돌려줍니다. 가운데 위치도 검사했으므로 다음 범위에서는 middle을 빼고 시작합니다.

## 어떤 값을 비교했는지 보기

### 이번에 배울 것

중간에 값을 출력하면 프로그램이 답을 찾는 과정을 추적할 수 있습니다.

### 실행해 보기

@code binary_search_2_example2.cpp

예제는 23을 찾으며 Checking 12, Checking 23을 출력합니다. 비교 횟수는 2입니다.

이번 예제는 비교 과정을 관찰하는 용도입니다. value를 없는 값으로 바꾸면 범위가 비어 끝나지만, 별도의 성공 안내는 출력하지 않습니다.

## Exercise — Binary Search 완성

정렬된 `{4, 8, 15, 16, 23, 42}`에서 23을 찾아 index를 출력하는 Binary Search를 작성하세요.

@exercise exercise1_starter.cpp

### Hint

left, right, middle 세 변수를 사용하고 매번 범위를 절반으로 줄이세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 비교 횟수 세기

Binary Search가 값을 찾을 때 몇 번 비교했는지 count를 추가해 출력하세요.

@exercise binary_search_2_exercise2_starter.cpp

### Hint

while을 한 번 돌 때마다 comparisons를 1 증가시키세요.

@solution binary_search_2_exercise2_solution.cpp
