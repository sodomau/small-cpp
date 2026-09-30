---
title: 값이 있는 위치 기억하기
part: algorithms
part-title: Part III — Thinking with Programs
goal: 값이 있는 위치 기억하기
related-example: reference/array
---

## 이번에 배울 것

값 대신 **인덱스**를 기억하면 가장 작은 값이 무엇인지와 어디 있는지를 함께 알 수 있습니다.

## 실행해 보기

@code example2.cpp

smallestIndex는 가장 작은 원소의 위치입니다. `numbers[smallestIndex]`로 그 값을 읽습니다. 예제의 최솟값은 1, 위치는 3입니다.

값과 위치를 혼동하지 않게 변수 이름에 Index를 붙였습니다. 같은 최솟값이 여러 개면 현재의 < 비교는 먼저 만난 위치를 남깁니다.

## Exercise — 가장 큰 값의 위치

가장 큰 값의 index를 찾아 값과 index를 함께 출력하세요.

@exercise exercise2_starter.cpp

### Hint

largestIndex를 0으로 시작하고 `numbers[i] > numbers[largestIndex]`를 비교하세요.

@solution exercise2_solution.cpp
