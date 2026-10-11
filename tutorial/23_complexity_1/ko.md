---
title: 프로그램이 얼마나 일할까? (선택)
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 프로그램이 얼마나 일할까? (선택)
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 데이터가 많아지면 얼마나 일할까

### 이번에 배울 것

**시간 복잡도**는 데이터 개수가 늘 때 필요한 작업량이 어떻게 커지는지 나타냅니다. 실제 초 수와는 다릅니다.

### 실행해 보기

@code example1.cpp

순차 검색은 못 찾는 경우 원소 n개를 모두 검사합니다. n이 10, 100, 1000이면 최악의 비교 횟수도 10, 100, 1000입니다.

이런 증가를 O(n)이라고 씁니다. 이 예제는 시간을 측정하는 대신 작업량을 숫자로 보여 줍니다.

## 반씩 줄이는 일은 얼마나 반복될까

### 이번에 배울 것

범위를 매번 반으로 줄이면 데이터가 커져도 반복 횟수는 천천히 늘어납니다. 이런 증가를 O(log n)이라고 합니다.

### 실행해 보기

@code complexity_2_example2.cpp

1024를 정수 나눗셈으로 계속 반으로 줄입니다. 1024, 512, …, 1을 처리하므로 Steps: 11입니다.

이 수는 예제의 반복 횟수이지 모든 이진 검색의 정확한 비교 횟수는 아닙니다. Big-O는 증가 경향을 요약한 표기입니다.

## Exercise — Linear 비교 횟수

20개의 값에서 없는 값을 Linear Search한다고 생각하고 실제 comparisons를 세어 출력하세요.

@exercise exercise1_starter.cpp

### Hint

값을 하나 볼 때마다 comparisons를 증가시키고 끝까지 찾지 못하게 하면 됩니다.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 몇 번 반으로 나눌까

n=1000을 시작으로 n이 0이 될 때까지 2로 나누며 몇 단계가 필요한지 세세요.

@exercise complexity_2_exercise2_starter.cpp

### Hint

while 안에서 `n = n / 2`와 count 증가를 함께 하세요.

@solution complexity_2_exercise2_solution.cpp
