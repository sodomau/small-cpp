---
title: Repeating with for
part: basics
part-title: Part I — Programming Basics
goal: for를 이용해 정해진 횟수만큼 반복합니다.
related-example: reference/console
---

## 같은 코드를 계속 쓰지 않기
 숫자 1부터 5까지 출력하려면 Print를 다섯 번 쓸 수도 있습니다. 그런데 100까지 출력해야 한다면요? **반복문**으로 같은 일을 여러 번 시킬 수 있습니다.

 아래에서는 반복할 때마다 변수 i가 바뀝니다. 실행하기 전에 나올 숫자를 순서대로 적어 보세요.

## 먼저 실행해 보세요

@code example1.cpp

## for의 세 부분
 괄호 안은 `처음 값; 계속할 조건; 다음으로 바꾸기`입니다.

 `int i = 1`은 처음 한 번만 실행합니다. 매번 `i <= 5`를 검사해 true이면 블록을 실행하고, 그 뒤 `i = i + 1`로 값을 늘립니다. 조건이 false가 되면 반복을 끝냅니다. 이 예제에서는 1부터 5까지 다섯 번 출력합니다.

 다음 예제에서는 Write로 별을 같은 줄에 이어 출력합니다. 반복문 뒤의 Print는 한 번만 실행합니다.

## 조금 바꾸어 보기

@code example2.cpp

## 시작과 끝을 확인하세요
 0부터 시작해서 `i < count`를 검사하는 방법과, 1부터 시작해서 `i <= count`를 검사하는 방법은 둘 다 count번 반복할 수 있습니다. 처음 값과 조건을 함께 읽어야 합니다.

 i를 바꾸는 부분을 빼면 조건이 계속 참이 되어 끝나지 않을 수도 있습니다. 예상과 다르게 끝없이 실행되면 IDE의 **Stop**으로 멈추고 코드를 확인하세요. 실제 실험에서는 작은 수부터 시작합시다.

## Exercise — 1부터 10까지

for 하나를 사용해 1부터 10까지 한 줄에 하나씩 출력하세요.

@exercise exercise1_starter.cpp

### Hint

시작은 1, 조건은 i <= 10, 다음 값은 i + 1입니다.

@solution exercise1_solution.cpp

## Exercise — 구구단 한 단

2부터 9 사이의 정수를 입력받아 그 수의 구구단을 1부터 9까지 출력하세요. 예를 들어 3을 입력하면 `3 x 1 = 3`부터 `3 x 9 = 27`까지 출력합니다.

@exercise exercise2_starter.cpp

### Hint

i를 1부터 9까지 바꾸며 `Print(number, " x ", i, " = ", number * i);`를 실행하세요.

@solution exercise2_solution.cpp
