---
title: 화면에 출력하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 화면에 출력하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 글자를 화면에 보여 주기

### 이번에 배울 것

**프로그램**은 컴퓨터가 할 일을 정한 것입니다. 그 일을 글로 적은 것이 **코드**, 실제로 시키는 것이 **실행**입니다. 오늘은 인사말 하나를 보여 줍니다.

### 실행해 보기

@code example.cpp

**Try This Code**로 코드를 열고 **Run 또는 F5**를 누르세요. 글자는 콘솔 창에 나옵니다.

**문자열**은 글자들이 순서대로 이어진 값입니다. `"Hello!"`의 큰따옴표는 그 시작과 끝을 표시합니다. **함수**는 할 일을 묶어 이름 붙인 것입니다. print는 출력하는 함수이고, `print("Hello!");`는 그 함수에 인사말을 전달해 실행합니다.

small_main은 우리가 할 일을 적는 함수입니다. 지금은 바깥 틀을 유지하고 `{ }` 안의 print만 바꾸세요. 문장 끝의 `;`도 함께 둡니다.

예상 출력:

```text
Hello!
```

## 위에서 아래로 실행하기

### 이번에 배울 것

명령을 여러 개 적으면 위에서 아래로 실행합니다. print는 출력한 뒤 다음 줄로 내려갑니다.

### 실행해 보기

@code lines_example.cpp

첫 print가 끝나면 둘째 print를 실행합니다. 두 줄의 순서를 바꾸면 출력 순서도 바뀝니다.

코드에서 `//`부터 그 줄 끝까지는 **주석**입니다. 사람에게 남기는 메모라서 실행하지 않습니다. 첫 줄 앞에 //를 붙이고 차이를 확인해 보세요.

예상 출력:

```text
Hello!
Small C++
```

## 따옴표와 줄바꿈 넣기

### 이번에 배울 것

문자열 안에 특별한 문자를 넣을 때는 역슬래시로 시작하는 **이스케이프 표기**를 사용합니다.

### 실행해 보기

@code escape_example.cpp

`\n`은 줄바꿈, `\"`는 큰따옴표 하나, `\\`는 역슬래시 하나입니다. 코드에서 두 기호로 적어도 하나의 문자를 나타냅니다.

`""`는 내용이 없는 빈 문자열이고 `" "`는 공백 하나가 있는 문자열입니다. print는 빈 문자열을 출력해도 마지막에 줄을 바꿉니다.

예상 출력:

```text
Hello
Small
"Hi"
```

## Exercise — 한 가지 바꾸기

Hello! 대신 자신의 이름을 출력하세요.

@exercise exercise_starter.cpp

### Hint

큰따옴표 안의 글자만 바꾸세요. `print`의 p는 소문자입니다.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

이름, 좋아하는 것, 만들고 싶은 것을 세 줄로 출력하세요.

@exercise lines_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution lines_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

`print` 한 번으로 A와 B를 서로 다른 줄에 출력하세요.

@exercise escape_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution escape_exercise_solution.cpp
