---
title: 순서 정하기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 순서 정하기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 작은 수부터 순서 정하기

### 이번에 배울 것

**정렬**은 정한 기준에 맞게 순서를 바꾸는 일입니다. 이번 방법은 남은 값 중 최솟값을 찾아 앞자리부터 채웁니다.

### 실행해 보기

@code example1.cpp

바깥 반복은 채울 자리 i, 안쪽 반복은 남은 부분의 최솟값 위치를 찾습니다.

두 값을 바꿀 때 temp에 한 값을 잠시 보관합니다. 곧바로 덮어쓰면 원래 값을 잃기 때문입니다. 출력이 2, 4, 5, 7, 9 순서인지 보세요.

## 큰 수부터 순서 정하기

### 이번에 배울 것

같은 절차에서 비교 기준을 바꾸면 순서도 바뀝니다. 큰 수부터 나열하는 것을 **내림차순**이라고 합니다.

### 실행해 보기

@code sorting_2_example2.cpp

이번에는 남은 값 중 최댓값을 찾습니다. 비교가 <에서 >로 바뀌고 출력은 9, 7, 5, 4, 2가 됩니다.

정렬 방향을 바꾸려고 반복문 전체를 다시 만들 필요는 없습니다. 어떤 값을 먼저 고르는지 바꾸면 됩니다.

## 숫자를 막대로 보여 주기

### 이번에 배울 것

**시각화**는 데이터를 그림으로 표현하는 것입니다. 값이 클수록 높은 막대를 그려 배열을 눈으로 봅니다.

### 실행해 보기

@code visualizing_1_example1.cpp

값에 30을 곱해 높이를 정합니다. 화면은 아래로 갈수록 y가 커지므로 막대 위쪽을 `420 - height`로 계산합니다.

배열의 값 하나를 바꾸고 해당 막대의 높이가 달라지는지 확인하세요.

## 정렬 과정을 눈으로 보기

### 이번에 배울 것

완성된 답뿐 아니라 **중간 상태**를 그리면 알고리즘의 동작도 볼 수 있습니다.

### 실행해 보기

@code visualizing_2_example2.cpp

자리 하나를 정한 뒤 전체 막대를 다시 그리고 0.5초 기다립니다. 이번에 정한 자리는 빨강입니다.

바뀐 배열을 보고 정렬이 어디까지 진행됐는지 말해 보세요. 그림을 그리는 부분과 정렬하는 부분을 구분해 읽습니다.

## Exercise — 오름차순 정렬

`{10, 3, 8, 1, 6}`을 Selection Sort로 작은 순서로 정렬하세요.

@exercise exercise1_starter.cpp

### Hint

Lesson의 smallest index 패턴을 그대로 적용하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 큰 순서로 바꾸기

Selection Sort를 수정해 큰 값부터 작은 값 순서로 정렬하세요.

@exercise sorting_2_exercise2_starter.cpp

### Hint

smallest 대신 largest를 찾고 비교 방향을 `>`로 바꾸세요.

@solution sorting_2_exercise2_solution.cpp

## Exercise — 현재 위치 표시

먼저 정렬 애니메이션에 사용할 위치 표시를 따로 연습합니다. 시작 코드의 current번째 막대를 Red로, 나머지를 Blue로 그리세요. 이 연습 자체는 정렬하지 않는 정적인 그림입니다. current를 0부터 4까지 바꾸어 빨간 막대가 해당 위치로 바뀌는지 확인하세요.

@exercise visualizing_1_exercise1_starter.cpp

### Hint

막대를 그리는 loop 안에서 `i == current`인지 검사해 Color를 선택하세요. 앞의 정렬 애니메이션으로 옮길 때에는 current 대신 그 단계에서 확정한 위치를 사용하면 됩니다.

@solution visualizing_1_exercise1_solution.cpp

## Exercise — swap 횟수 세기

Selection Sort에서 실제로 swap을 수행한 횟수를 세고 마지막에 출력하세요. 같은 위치끼리는 swap하지 않도록 해도 좋습니다.

@exercise visualizing_2_exercise2_starter.cpp

### Hint

`swaps`를 0으로 시작하고 smallest != i일 때만 swap하고 증가시키세요.

@solution visualizing_2_exercise2_solution.cpp
