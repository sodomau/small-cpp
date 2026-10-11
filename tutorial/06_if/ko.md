---
title: 조건에 따라 실행하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 조건에 따라 실행하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 조건에 맞을 때만 실행하기

### 이번에 배울 것

**조건**은 참인지 거짓인지 판단할 수 있는 식입니다. if는 조건이 참일 때만 중괄호 안을 실행하는 **조건문**입니다.

### 실행해 보기

@code example.cpp

`score >= 60`은 점수가 60 이상인지 묻습니다. 80이면 참이라 Pass를 출력합니다. 50으로 바꾸면 Pass는 건너뛰고 Done만 출력합니다.

`>`는 초과, `<`는 미만, `>=`는 이상, `<=`는 이하입니다. if의 닫는 중괄호 뒤에는 ;을 붙이지 않습니다.

예상 출력:

```text
Pass
Done
```

## 조건이 맞지 않으면 다른 일 하기

### 이번에 배울 것

**else**는 if의 조건이 거짓일 때 실행할 일을 적는 부분입니다. 두 갈래 중 하나를 고릅니다.

### 실행해 보기

@code else_example.cpp

같은지 비교할 때는 `==`를 씁니다. 값을 넣는 `=`와 다릅니다. `!=`는 서로 다른지를 비교합니다. answer를 5로 바꾸면 else 쪽만 실행됩니다.

예상 출력:

```text
Correct
```

## 세 갈래 중 하나 고르기

### 이번에 배울 것

선택지가 셋 이상이면 **else if**로 조건을 이어 봅니다. 위에서부터 검사하고, 처음 맞는 갈래 하나만 실행합니다.

### 실행해 보기

@code else_if_example.cpp

0은 양수도 음수도 아니어서 마지막 else로 갑니다. else if 대신 독립된 if를 여러 개 쓰면 각 조건을 따로 검사하므로 여러 갈래가 실행될 수도 있습니다.

예상 출력:

```text
Zero
```

## 참과 거짓도 기억하기

### 이번에 배울 것

**bool**은 참(true) 또는 거짓(false)을 저장하는 타입입니다. 준비되었는지, 게임이 끝났는지 같은 상태를 기억합니다.

### 실행해 보기

@code bool_example.cpp

if에 bool 변수를 바로 넣을 수 있습니다. Small의 print는 true를 1, false를 0으로 출력합니다. `bool passed = score >= 60;`처럼 비교 결과를 저장할 수도 있습니다.

예상 출력:

```text
Start
1
```

## 조건 두 개 함께 보기

### 이번에 배울 것

`&&`는 두 조건이 **모두 참**, `||`는 **하나 이상 참**, `!`는 참과 거짓을 뒤집는 연산자입니다.

### 실행해 보기

@code logic_example.cpp

나이가 13 이상이면서 19 이하인지 확인합니다. 12, 13, 19, 20으로 바꾸어 경계를 확인하세요.

`!ready`는 준비되지 않았는지 묻습니다. &&는 왼쪽이 거짓이면, ||는 왼쪽이 참이면 오른쪽을 검사하지 않습니다.

예상 출력:

```text
Teen
```

## Exercise — 한 가지 바꾸기

number가 0보다 클 때만 Positive를 출력하세요. 먼저 3으로 시험하세요.

@exercise exercise_starter.cpp

### Hint

3을 0과 -1로도 바꾸어 보세요. 그때는 출력하지 않아야 합니다.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

비밀번호가 1234와 같으면 Open, 다르면 Locked를 출력하세요. 1111로 시험하세요.

@exercise else_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution else_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

number를 -2로 바꾸어 어떤 갈래가 실행되는지 확인하세요.

@exercise else_if_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution else_if_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

ready를 false로 바꾸고 출력 차이를 확인하세요.

@exercise bool_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution bool_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

나이가 13 미만이거나 19 초과일 때 Outside를 출력하세요. 20으로 시험하세요.

@exercise logic_exercise_starter.cpp

### Hint

두 조건 사이에 ||를 사용하세요.

@solution logic_exercise_solution.cpp
