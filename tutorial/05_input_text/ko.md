---
title: 입력받기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 입력받기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 실행 중에 이름 물어보기

### 이번에 배울 것

**입력**은 프로그램 밖에서 값을 받아 오는 일입니다. input 함수는 키보드로 쓴 한 줄을 문자열로 돌려줍니다.

### 실행해 보기

@code example.cpp

Run한 뒤 콘솔 창에 Alex를 쓰고 Enter를 누르세요. input이 기다리는 동안은 고장이 아닙니다. 입력을 마치면 그 문자열을 name에 저장하고 다음 줄을 실행합니다.

`input("Name: ")`처럼 괄호 안에 안내문을 넣을 수도 있습니다.

예상 출력 (입력 안내문 제외):

```text
Hello, Alex
```

## 입력한 숫자로 계산하기

### 이번에 배울 것

input_int는 입력한 내용을 **정수**로 읽어 돌려주는 함수입니다. input이 돌려주는 문자열과 구분해서 사용합니다.

### 실행해 보기

@code input_int_example.cpp

콘솔에 10을 입력하고 Enter를 누르세요. 읽은 정수 10에 1을 더하므로 11이 나옵니다. 한 줄에 정수 하나를 쓰세요. 숫자가 아닌 글자를 쓰면 다시 입력하라는 안내가 나옵니다.

예상 출력 (입력 안내문 제외):

```text
11
```

## 작은 계산기 만들기

### 이번에 배울 것

input_real은 소수 부분이 있는 수를 double 값으로 읽습니다. **입력 → 계산 → 출력**을 연결하면 계산기가 됩니다.

### 실행해 보기

@code input_real_example.cpp

2.5를 쓰고 Enter, 3.5를 쓰고 Enter를 누르세요. 함수를 두 번 호출하므로 두 번 입력합니다. a와 b에 각각 저장한 다음 합을 출력합니다.

예상 출력 (입력 안내문 제외):

```text
6
```

## Exercise — 한 가지 바꾸기

이름을 입력받아 Nice to meet you, 뒤에 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

숫자 하나를 입력받고 두 배를 출력하세요. 7을 넣으면 14가 나와야 합니다.

@exercise input_int_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution input_int_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

가로와 세로를 입력받아 넓이를 출력하세요. 3.5와 2를 넣으면 7입니다.

@exercise input_real_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution input_real_exercise_solution.cpp
