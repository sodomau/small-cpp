---
title: 작은 수부터 순서 정하기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 작은 수부터 순서 정하기
related-example: reference/array
---

## 이번에 배울 것

**정렬**은 정한 기준에 맞게 순서를 바꾸는 일입니다. 이번 방법은 남은 값 중 최솟값을 찾아 앞자리부터 채웁니다.

## 실행해 보기

@code example1.cpp

바깥 반복은 채울 자리 i, 안쪽 반복은 남은 부분의 최솟값 위치를 찾습니다.

두 값을 바꿀 때 temp에 한 값을 잠시 보관합니다. 곧바로 덮어쓰면 원래 값을 잃기 때문입니다. 출력이 2, 4, 5, 7, 9 순서인지 보세요.

## Exercise — 오름차순 정렬

`{10, 3, 8, 1, 6}`을 Selection Sort로 작은 순서로 정렬하세요.

@exercise exercise1_starter.cpp

### Hint

Lesson의 smallest index 패턴을 그대로 적용하세요.

@solution exercise1_solution.cpp

