---
title: 반복하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 반복하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 같은 일을 여러 번 하기

### 이번에 배울 것

**반복문**은 한 번 적은 코드 묶음을 여러 번 실행합니다. for에는 시작 준비, 계속할 조건, 다음 값으로 바꾸기를 적습니다.

### 실행해 보기

@code example.cpp

i를 1로 시작합니다. 조건이 참이면 출력한 뒤 i를 1 늘리고 다시 검사합니다. 3을 출력한 뒤 i가 4가 되면 조건이 거짓이라 끝납니다. i는 우리가 정한 변수 이름입니다.

예상 출력:

```text
1
2
3
```

## 조건이 맞는 동안 반복하기

### 이번에 배울 것

**while**은 조건이 참인 동안 중괄호 안을 반복합니다. 실행하기 전에 매번 조건을 확인합니다.

### 실행해 보기

@code while_example.cpp

count가 0이 되면 반복을 끝냅니다. 처음부터 0이면 한 번도 출력하지 않습니다. count를 줄이는 줄을 지우면 끝나지 않으므로, 그런 경우 IDE의 stop으로 멈추세요.

횟수를 세며 반복할 때는 for가 편하고, 조건이 바뀔 때까지 기다릴 때는 while이 편합니다.

예상 출력:

```text
3
2
1
```

## 반복을 멈추거나 건너뛰기

### 이번에 배울 것

**break**는 가장 안쪽 반복문을 끝냅니다. **continue**는 이번 반복의 남은 부분을 건너뛰고 다음 반복으로 갑니다.

### 실행해 보기

@code loop_control_example.cpp

2에서는 print를 건너뜁니다. for는 i를 늘린 뒤 다음 조건을 검사합니다. 4에서는 반복 자체를 끝내므로 4와 5 모두 출력하지 않습니다.

예상 출력:

```text
1
3
```

## 별을 여러 줄 그리기

### 이번에 배울 것

반복문 안에 반복문을 넣을 수 있습니다. 바깥 반복은 줄을 세고, 안쪽 반복은 그 줄에 찍을 별을 셉니다.

### 실행해 보기

@code nested_loops_example.cpp

`write`는 출력 뒤 줄을 바꾸지 않습니다. **print()**는 내용 없이 줄만 바꿉니다. 따라서 별 세 개를 붙여 쓴 뒤 줄을 바꾸는 일을 두 번 합니다.

예상 출력:

```text
***
***
```

## Exercise — 한 가지 바꾸기

1부터 5까지 출력하도록 바꾸세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

5부터 1까지 거꾸로 출력하세요.

@exercise while_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution while_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

2 대신 3을 건너뛰고, 5에서 멈추도록 바꾸세요.

@exercise loop_control_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution loop_control_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

별 네 개씩 세 줄을 그리세요.

@exercise nested_loops_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution nested_loops_exercise_solution.cpp
