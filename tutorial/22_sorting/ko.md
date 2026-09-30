---
title: Sorting
part: algorithms
part-title: Part III — Thinking with Programs
goal: Selection Sort를 직접 구현하며 정렬을 절차로 설명하는 방법을 익힙니다.
related-example: reference/array
---

## 정렬을 컴퓨터에게 설명한다면
사람은 숫자를 보고 금방 작은 순서로 놓을 수 있지만 컴퓨터에게는 정확한 절차가 필요합니다. Selection Sort는 아직 정리되지 않은 부분에서 가장 작은 값을 찾아 앞쪽에 놓는 일을 반복합니다.

## 먼저 실행해 보세요

@code example1.cpp

## 바깥 반복과 안쪽 반복
바깥쪽 i는 **이번에 확정할 위치**입니다. 안쪽 j는 i 뒤의 값들을 훑으며 가장 작은 위치를 찾습니다. 마지막 세 줄은 두 값을 서로 바꾸는 swap입니다.

빠른 정렬을 배우는 것이 이 lesson의 목적은 아닙니다. 정렬이라는 말을 컴퓨터가 실행할 수 있는 작은 단계로 바꾸는 것이 목적입니다.

## 조금 바꾸어 보기

@code example2.cpp

## 작은 변화로 순서가 뒤집힙니다
가장 작은 값을 찾던 비교를 가장 큰 값을 찾도록 바꾸면 내림차순 정렬이 됩니다. 알고리즘을 이해하면 외운 코드를 복사하는 대신 원하는 동작에 맞게 변형할 수 있습니다.

## Exercise — 오름차순 정렬

`{10, 3, 8, 1, 6}`을 Selection Sort로 작은 순서로 정렬하세요.

@exercise exercise1_starter.cpp

### Hint

Lesson의 smallest index 패턴을 그대로 적용하세요.

@solution exercise1_solution.cpp

## Exercise — 큰 순서로 바꾸기

Selection Sort를 수정해 큰 값부터 작은 값 순서로 정렬하세요.

@exercise exercise2_starter.cpp

### Hint

smallest 대신 largest를 찾고 비교 방향을 `>`로 바꾸세요.

@solution exercise2_solution.cpp
