---
title: Algorithm Challenge
part: algorithms
part-title: Part III — Thinking with Programs
goal: 새 문법 없이 문제를 작은 단계로 나누어 두 번째로 큰 값을 찾습니다.
related-example: reference/array
---

## 이제 문제를 먼저 봅니다
이번 lesson에는 새로운 문법이나 API가 없습니다. 목표는 문제를 읽고 이미 아는 도구를 조합하는 것입니다.

문제: **서로 다른 숫자들이 들어 있는 Array에서 두 번째로 큰 값을 찾아라.**

한 가지 방법은 largest와 second를 함께 기억하면서 Array를 한 번 훑는 것입니다.

## 먼저 실행해 보세요

@code example1.cpp

## 먼저 가정과 단계를 정합니다
이 예제는 Array에 서로 다른 값이 두 개 이상 있다고 가정합니다. 이런 **가정**을 먼저 말하는 것도 알고리즘 설계의 일부입니다.

문제를 풀 때 바로 코드를 쓰기보다 다음을 생각해 보세요.

1. 무엇을 기억해야 하는가?
2. 새 값을 하나 보았을 때 기억을 어떻게 바꿀 것인가?
3. 특별한 입력이나 가정은 무엇인가?

## 조금 바꾸어 보기

@code example2.cpp

## 정답은 하나가 아닙니다
정렬한 뒤 두 번째 값을 보는 방법도 있고, 한 번 훑으면서 두 값을 기억하는 방법도 있습니다. 어떤 방법이 더 단순한지, 데이터가 커지면 어떤 일이 생기는지 비교할 수 있습니다.

여기까지 오면 기본 문법을 아는 것에서 한 단계 넘어와 **알고리즘을 설계하고 비교하는 경험**을 한 것입니다. 다음 Part는 잠깐 방향을 바꾸어 프로그램의 데이터를 파일에 저장하고 다시 불러옵니다.

## Exercise — 두 번째로 작은 값

서로 다른 값이 두 개 이상 있다고 가정하고 두 번째로 작은 값을 찾으세요.

@exercise exercise1_starter.cpp

### Hint

smallest와 second를 기억하고, 새 값이 smallest보다 작을 때 두 값을 함께 갱신하세요.

@solution exercise1_solution.cpp

## Exercise — 가장 큰 값은 몇 번?

Array의 가장 큰 값을 먼저 찾고, 그 값이 몇 번 나타나는지 두 번째 loop에서 세세요.

@exercise exercise2_starter.cpp

### Hint

첫 loop는 largest, 두 번째 loop는 `numbers[i] == largest`인 횟수를 셉니다.

@solution exercise2_solution.cpp
