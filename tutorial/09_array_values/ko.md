---
title: 배열 사용하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 배열 사용하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 여러 값을 한곳에 담기

### 이번에 배울 것

**배열**은 같은 타입의 값들을 순서대로 담은 모음입니다. Small의 Array<int>는 여러 정수를 담는 타입입니다.

### 실행해 보기

@code example.cpp

배열의 값 하나를 **원소**, 위치 번호를 **인덱스**라고 합니다. 문자열처럼 0부터 셉니다. 원소가 셋이면 유효한 번호는 0, 1, 2입니다. 대괄호로 값을 읽거나 바꿀 수 있습니다.

예상 출력:

```text
80
100
```

## 배열의 값을 하나씩 보기

### 이번에 배울 것

반복문의 변수를 배열의 위치로 사용하면 원소를 차례로 읽을 수 있습니다. length()는 원소 개수를 알려 줍니다.

### 실행해 보기

@code array_loop_example.cpp

i가 0, 1, 2일 때 각각 출력합니다. 3은 원소 개수와 같아서 조건이 거짓이 됩니다. 따라서 조건은 `<=`가 아니라 `<`입니다. 길이가 0이면 반복하지 않습니다.

예상 출력:

```text
80
95
70
```

## 자리 수부터 정해서 배열 만들기

### 이번에 배울 것

처음 값을 나열하는 대신 필요한 자리 수를 먼저 정할 수도 있습니다. Array<int>(3)은 정수를 담을 자리 세 개를 만듭니다.

### 실행해 보기

@code array_create_example.cpp

`Array<int> numbers(3);`은 세 자리이고, `Array<int> numbers = {3};`은 값 3이 든 한 자리입니다. 구분하세요.

Small Array는 만든 뒤 길이를 늘리는 기능이 없습니다. 각 원소의 값은 바꿀 수 있습니다.

예상 출력:

```text
1
2
3
```

## Exercise — 한 가지 바꾸기

세 번째 점수를 90으로 바꾸고 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

각 점수의 두 배를 출력하세요. 배열에 다시 저장할 필요는 없습니다.

@exercise array_loop_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution array_loop_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

다섯 자리를 만들고 1부터 5까지 저장하며 출력하세요.

@exercise array_create_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution array_create_exercise_solution.cpp
