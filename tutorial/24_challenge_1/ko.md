---
title: 도전 문제 (선택)
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 도전 문제 (선택)
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 두 번째로 큰 값 찾기

### 이번에 배울 것

새 문제를 풀기 전에 **무엇을 답으로 할지와 입력의 가정**을 정합니다. 이번에는 두 자리의 후보를 기억합니다.

### 실행해 보기

@code example1.cpp

예제는 원소가 적어도 두 개이며, 두 번째 순위에 중복도 포함합니다. {9, 9, 3}이라면 답은 9입니다. 서로 다른 값 중 둘째라는 뜻은 아닙니다.

새 최댓값을 만나면 이전 최댓값을 second로 옮깁니다. 8, 3, 12, 5, 10에서는 답이 10입니다.

## 가장 큰 값이 몇 개인지 세기

### 이번에 배울 것

이미 아는 절차 두 개를 이어 붙이면 새 문제를 해결할 수 있습니다.

### 실행해 보기

@code challenge_2_example2.cpp

먼저 최댓값을 찾고, 두 번째 반복에서 그 값과 같은 원소를 셉니다. 출력은 Largest: 9, How many: 2입니다.

두 반복을 억지로 하나로 합치기보다 각 단계가 맡은 일을 먼저 분명히 하세요. 배열에는 원소가 하나 이상 있어야 합니다.

## Exercise — 두 번째로 작은 값

서로 다른 값이 두 개 이상 있다고 가정하고 두 번째로 작은 값을 찾으세요.

@exercise exercise1_starter.cpp

### Hint

smallest와 second를 기억하고, 새 값이 smallest보다 작을 때 두 값을 함께 갱신하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 가장 큰 값은 몇 번?

Array의 가장 큰 값을 먼저 찾고, 그 값이 몇 번 나타나는지 두 번째 loop에서 세세요.

@exercise challenge_2_exercise2_starter.cpp

### Hint

첫 loop는 largest, 두 번째 loop는 `numbers[i] == largest`인 횟수를 셉니다.

@solution challenge_2_exercise2_solution.cpp
