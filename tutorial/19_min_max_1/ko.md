---
title: 가장 큰 값 찾기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 가장 큰 값 찾기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 지금까지 가장 큰 값 기억하기

### 이번에 배울 것

**최댓값 찾기**는 지금까지 본 가장 큰 값을 기억하고, 더 큰 값을 만나면 바꾸는 절차입니다.

### 실행해 보기

@code example1.cpp

첫 원소 7을 시작값으로 정합니다. 2는 작아서 그대로, 9는 커서 바꿉니다. 결과는 Largest: 9입니다.

0으로 시작하면 모든 값이 음수일 때 잘못될 수 있습니다. 이 예제는 원소가 하나 이상인 배열을 사용합니다.

## 값이 있는 위치 기억하기

### 이번에 배울 것

값 대신 **인덱스**를 기억하면 가장 작은 값이 무엇인지와 어디 있는지를 함께 알 수 있습니다.

### 실행해 보기

@code min_max_2_example2.cpp

smallest_index는 가장 작은 원소의 위치입니다. `numbers[smallest_index]`로 그 값을 읽습니다. 예제의 최솟값은 1, 위치는 3입니다.

값과 위치를 혼동하지 않게 변수 이름에 Index를 붙였습니다. 같은 최솟값이 여러 개면 현재의 < 비교는 먼저 만난 위치를 남깁니다.

## Exercise — 가장 작은 값

Array에서 가장 작은 값을 찾아 출력하세요.

@exercise exercise1_starter.cpp

### Hint

첫 번째 값을 smallest로 두고 index 1부터 비교하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 가장 큰 값의 위치

가장 큰 값의 index를 찾아 값과 index를 함께 출력하세요.

@exercise min_max_2_exercise2_starter.cpp

### Hint

largest_index를 0으로 시작하고 `numbers[i] > numbers[largest_index]`를 비교하세요.

@solution min_max_2_exercise2_solution.cpp
