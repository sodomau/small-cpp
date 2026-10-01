---
title: 지금까지 가장 큰 값 기억하기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 지금까지 가장 큰 값 기억하기
related-example: reference/array
---

## 이번에 배울 것

**최댓값 찾기**는 지금까지 본 가장 큰 값을 기억하고, 더 큰 값을 만나면 바꾸는 절차입니다.

## 실행해 보기

@code example1.cpp

첫 원소 7을 시작값으로 정합니다. 2는 작아서 그대로, 9는 커서 바꿉니다. 결과는 Largest: 9입니다.

0으로 시작하면 모든 값이 음수일 때 잘못될 수 있습니다. 이 예제는 원소가 하나 이상인 배열을 사용합니다.

## Exercise — 가장 작은 값

Array에서 가장 작은 값을 찾아 출력하세요.

@exercise exercise1_starter.cpp

### Hint

첫 번째 값을 smallest로 두고 index 1부터 비교하세요.

@solution exercise1_solution.cpp

