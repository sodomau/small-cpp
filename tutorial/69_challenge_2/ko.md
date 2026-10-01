---
title: 가장 큰 값이 몇 개인지 세기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 가장 큰 값이 몇 개인지 세기
related-example: reference/array
---

## 이번에 배울 것

이미 아는 절차 두 개를 이어 붙이면 새 문제를 해결할 수 있습니다.

## 실행해 보기

@code example2.cpp

먼저 최댓값을 찾고, 두 번째 반복에서 그 값과 같은 원소를 셉니다. 출력은 Largest: 9, How many: 2입니다.

두 반복을 억지로 하나로 합치기보다 각 단계가 맡은 일을 먼저 분명히 하세요. 배열에는 원소가 하나 이상 있어야 합니다.

## Exercise — 가장 큰 값은 몇 번?

Array의 가장 큰 값을 먼저 찾고, 그 값이 몇 번 나타나는지 두 번째 loop에서 세세요.

@exercise exercise2_starter.cpp

### Hint

첫 loop는 largest, 두 번째 loop는 `numbers[i] == largest`인 횟수를 셉니다.

@solution exercise2_solution.cpp
