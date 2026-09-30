---
title: Faster and Slower Algorithms
part: algorithms
part-title: Part III — Thinking with Programs
goal: 입력 크기가 커질 때 알고리즘의 작업량이 어떻게 자라는지 비교합니다.
related-example: reference/array
---

## 빠르다는 말보다 중요한 질문
작은 Array에서는 대부분의 알고리즘이 금방 끝납니다. 더 중요한 질문은 **데이터가 10배 커지면 해야 할 일이 얼마나 늘어나는가?**입니다.

Linear Search는 최악의 경우 모든 값을 봅니다. 100개면 100번, 1,000개면 1,000번입니다.

## 먼저 실행해 보세요

@code example1.cpp

## Binary Search는 다르게 자랍니다
Binary Search는 범위를 절반으로 줄입니다. 1,024개도 약 11번이면 범위를 모두 줄일 수 있습니다.

이런 성장 방식을 간단히 표현하는 표기법이 **Big-O**입니다. Linear Search는 `O(n)`, Binary Search는 `O(log n)`이라고 부릅니다. 지금은 수학적 정의를 외울 필요가 없습니다. 입력이 커질 때 작업량이 어떤 모양으로 자라는지를 보는 것이 핵심입니다.

## 조금 바꾸어 보기

@code example2.cpp

## Big-O는 속도계가 아닙니다
`O(log n)`이라고 해서 언제나 특정 프로그램이 몇 초 걸린다는 뜻은 아닙니다. 컴퓨터, 구현, 데이터에 따라 실제 시간은 달라집니다. Big-O는 **문제가 커질 때 필요한 일의 양이 어떻게 증가하는지**를 비교하는 언어입니다.

지금은 O(n), O(log n) 두 이름만 맛보고 넘어갑니다.

## Exercise — Linear 비교 횟수

20개의 값에서 없는 값을 Linear Search한다고 생각하고 실제 comparisons를 세어 출력하세요.

@exercise exercise1_starter.cpp

### Hint

값을 하나 볼 때마다 comparisons를 증가시키고 끝까지 찾지 못하게 하면 됩니다.

@solution exercise1_solution.cpp

## Exercise — 몇 번 반으로 나눌까

n=1000을 시작으로 n이 0이 될 때까지 2로 나누며 몇 단계가 필요한지 세세요.

@exercise exercise2_starter.cpp

### Hint

while 안에서 `n = n / 2`와 count 증가를 함께 하세요.

@solution exercise2_solution.cpp
