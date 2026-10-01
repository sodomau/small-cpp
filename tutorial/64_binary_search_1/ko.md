---
title: 찾을 범위를 반으로 줄이기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 찾을 범위를 반으로 줄이기
related-example: reference/array
---

## 이번에 배울 것

**이진 검색**은 가운데 값과 비교하여 가능한 범위를 반씩 줄이는 방법입니다. 배열이 먼저 작은 순서로 정렬되어 있어야 합니다.

## 실행해 보기

@code example1.cpp

left와 right는 남은 범위의 양 끝입니다. 가운데보다 찾는 값이 작으면 오른쪽 절반을, 크면 왼쪽 절반을 제외합니다.

11의 위치는 5입니다. 못 찾으면 -1을 돌려줍니다. 가운데 위치도 검사했으므로 다음 범위에서는 middle을 빼고 시작합니다.

## Exercise — Binary Search 완성

정렬된 `{4, 8, 15, 16, 23, 42}`에서 23을 찾아 index를 출력하는 Binary Search를 작성하세요.

@exercise exercise1_starter.cpp

### Hint

left, right, middle 세 변수를 사용하고 매번 범위를 절반으로 줄이세요.

@solution exercise1_solution.cpp

