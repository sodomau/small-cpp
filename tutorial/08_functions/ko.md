---
title: 함수 만들기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 함수 만들기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 내가 만든 일에 이름 붙이기

### 이번에 배울 것

**함수**는 할 일을 묶어 이름 붙인 것입니다. print를 사용했듯, 이번에는 greet라는 함수를 직접 만듭니다.

### 실행해 보기

@code example.cpp

위쪽은 greet가 할 일을 정하는 **정의**, 아래의 `greet();`는 실제로 시키는 **호출**입니다. 정의만으로 실행되지는 않습니다. small_main에서 호출하면 greet로 갔다가 끝난 뒤 돌아옵니다.

**void**는 호출한 쪽에 결과값을 돌려주지 않는다는 뜻입니다. 화면 출력은 할 수 있습니다. 빈 ()는 전달받는 값이 없다는 뜻입니다.

예상 출력:

```text
Hello!
Hello!
```

## 함수에 값 전달하기

### 이번에 배울 것

함수에 값을 전달하면 같은 일을 다른 값으로 할 수 있습니다. 전달받은 값을 담는 변수를 **매개변수**라고 합니다.

### 실행해 보기

@code parameters_example.cpp

첫 호출에서는 number가 3, 둘째 호출에서는 5로 시작합니다. 호출할 때 넣는 값 3과 5를 **인자**라고 합니다. number는 이 함수를 실행하는 동안 쓰는 변수입니다.

예상 출력:

```text
6
10
```

## 함수의 결과 돌려받기

### 이번에 배울 것

**반환값**은 함수가 호출한 쪽에 돌려주는 값입니다. return은 값을 돌려주고 그 함수의 실행을 끝냅니다.

### 실행해 보기

@code return_value_example.cpp

맨 앞 int는 결과가 정수라는 뜻입니다. square(4)가 돌려준 16을 result에 저장합니다. 함수는 계산을 맡고, 출력은 small_main에서 합니다.

input_int도 이렇게 읽은 정수를 돌려주는 함수였습니다.

예상 출력:

```text
16
```

## 함수 안의 변수는 따로 쓰기

### 이번에 배울 것

함수 안에서 만든 **지역 변수**는 그 범위 안에서 사용합니다. 값으로 전달받은 매개변수도 원본과 별도로 값을 가집니다.

### 실행해 보기

@code scope_example.cpp

number는 score의 값 10을 복사해서 받습니다. number만 바꾸었으므로 돌아온 뒤 score는 여전히 10입니다.

일반적인 지역 변수는 그 범위가 끝나면 수명도 끝납니다. 다음 호출에서 이전 값을 자동으로 기억하지 않습니다. 원본을 바꾸는 방법은 뒤의 참조 수업에서 배웁니다.

예상 출력:

```text
11
10
```

## Exercise — 한 가지 바꾸기

greet를 세 번 호출해 보세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

show_double에 7과 10을 전달해 차례로 출력하세요.

@exercise parameters_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution parameters_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

square(6)의 결과를 받아 출력하세요.

@exercise return_value_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution return_value_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

score를 20으로 시작하면 두 출력이 무엇인지 예상하고 확인하세요.

@exercise scope_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution scope_exercise_solution.cpp
