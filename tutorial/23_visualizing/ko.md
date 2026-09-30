---
title: Visualizing an Algorithm
part: algorithms
part-title: Part III — Thinking with Programs
goal: 정렬 과정을 막대 그림으로 표시해 알고리즘의 상태 변화를 눈으로 봅니다.
related-example: programs/bouncing_ball
---

## 알고리즘을 눈으로 보기
Part II에서 배운 Graphics를 이제 생각을 이해하는 도구로 사용해 봅시다. Array의 값을 막대 높이로 그리면 정렬 과정이 실제로 어떻게 변하는지 볼 수 있습니다.

## 먼저 실행해 보세요

@code example1.cpp

## 한 단계마다 다시 그리기
정렬의 swap이 끝날 때마다 화면을 Clear하고 현재 Array를 다시 그리면 값들이 이동하는 과정을 볼 수 있습니다.

여기서는 일부러 drawing 코드를 함수로 빼지 않습니다. Window를 함수에 효율적으로 전달하는 방법은 reference를 알아야 자연스럽게 설명할 수 있기 때문입니다. **Lesson 31 전까지는 아직 배우지 않은 문법을 마법처럼 사용하지 않습니다.**

## 조금 바꾸어 보기

@code example2.cpp

## 그림은 디버깅 도구이기도 합니다
값을 Print하는 것처럼 그림으로 상태를 표시하면 알고리즘의 행동을 더 쉽게 발견할 수 있습니다. 복잡한 프로그램에서도 visualization은 결과를 예쁘게 보여주는 것뿐 아니라 **무슨 일이 일어나는지 이해하는 방법**이 될 수 있습니다.

## Exercise — 현재 위치 표시

정렬된 위치를 나타내기 위해 현재 i번째 막대를 Red로, 나머지를 Blue로 그리세요.

@exercise exercise1_starter.cpp

### Hint

막대를 그리는 loop 안에서 `j == current` 또는 `j == i`인지 검사해 Color를 선택하세요.

@solution exercise1_solution.cpp

## Exercise — swap 횟수 세기

Selection Sort에서 실제로 swap을 수행한 횟수를 세고 마지막에 출력하세요. 같은 위치끼리는 swap하지 않도록 해도 좋습니다.

@exercise exercise2_starter.cpp

### Hint

`swaps`를 0으로 시작하고 smallest != i일 때만 swap하고 증가시키세요.

@solution exercise2_solution.cpp
