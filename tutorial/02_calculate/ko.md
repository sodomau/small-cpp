---
title: 숫자 계산하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 숫자 계산하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 숫자를 계산해 보여 주기

### 이번에 배울 것

숫자는 큰따옴표 없이 씁니다. `+`는 더하기, `-`는 빼기를 하는 **연산자**, 즉 계산 기호입니다.

### 실행해 보기

@code example.cpp

`3 + 5`는 계산하여 값 8을 얻는 **식**입니다. `"3 + 5"`는 글자 그대로인 문자열이라서 계산하지 않습니다.

예상 출력:

```text
8
7
3 + 5
```

## 곱셈과 계산 순서

### 이번에 배울 것

`*`는 곱하기입니다. 곱셈은 덧셈보다 먼저 계산합니다. 먼저 계산할 부분을 괄호로 묶을 수도 있습니다.

### 실행해 보기

@code multiply_example.cpp

첫 줄은 3 × 4를 먼저 계산합니다. 둘째 줄은 괄호 안의 2 + 3을 먼저 계산합니다. 복잡한 식은 괄호로 순서를 드러내세요.

예상 출력:

```text
14
20
```

## 몫과 나머지

### 이번에 배울 것

`/`는 나누기, `%`는 정수 나눗셈의 나머지입니다. 사탕 17개를 5개씩 담으면 세 봉지를 만들고 2개가 남습니다.

### 실행해 보기

@code division_example.cpp

정수끼리 나누면 소수 부분을 버립니다. `5 / 2`는 2이지만, `5.0 / 2`처럼 한쪽이 double이면 2.5입니다. 결과를 담는 변수만 double로 바꾸어도 먼저 계산한 `5 / 2`는 2입니다.

나누는 수에 0을 넣으면 안 됩니다. /와 %는 곱셈처럼 덧셈보다 먼저 계산합니다.

예상 출력:

```text
3
2
2.5
```

## Exercise — 한 가지 바꾸기

12 더하기 7과 12 빼기 7을 차례로 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

가로 3.5, 세로 2.0을 double 변수에 저장하고 넓이를 계산해 출력하세요.

@exercise multiply_exercise_starter.cpp

### Hint

곱셈 결과가 7.0이어도 화면에는 7로 보일 수 있습니다.

@solution multiply_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

사탕 18개를 5개씩 담을 때 봉지 수와 남는 수를 출력하세요.

@exercise division_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution division_exercise_solution.cpp
