---
title: 데이터가 많아지면 얼마나 일할까
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 데이터가 많아지면 얼마나 일할까
related-example: reference/array
---

## 이번에 배울 것

**시간 복잡도**는 데이터 개수가 늘 때 필요한 작업량이 어떻게 커지는지 나타냅니다. 실제 초 수와는 다릅니다.

## 실행해 보기

@code example1.cpp

순차 검색은 못 찾는 경우 원소 n개를 모두 검사합니다. n이 10, 100, 1000이면 최악의 비교 횟수도 10, 100, 1000입니다.

이런 증가를 O(n)이라고 씁니다. 이 예제는 시간을 측정하는 대신 작업량을 숫자로 보여 줍니다.

## Exercise — Linear 비교 횟수

20개의 값에서 없는 값을 Linear Search한다고 생각하고 실제 comparisons를 세어 출력하세요.

@exercise exercise1_starter.cpp

### Hint

값을 하나 볼 때마다 comparisons를 증가시키고 끝까지 찾지 못하게 하면 됩니다.

@solution exercise1_solution.cpp

