---
title: 글자를 화면에 보여 주기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: Hello! 대신 자신의 이름을 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

**프로그램**은 컴퓨터가 할 일을 정한 것입니다. 그 일을 글로 적은 것이 **코드**, 실제로 시키는 것이 **실행**입니다. 오늘은 인사말 하나를 보여 줍니다.

## 실행해 보기

@code example.cpp

**Try This Code**로 코드를 열고 **Run 또는 F5**를 누르세요. 글자는 콘솔 창에 나옵니다.

**문자열**은 글자들이 순서대로 이어진 값입니다. `"Hello!"`의 큰따옴표는 그 시작과 끝을 표시합니다. **함수**는 할 일을 묶어 이름 붙인 것입니다. print는 출력하는 함수이고, `print("Hello!");`는 그 함수에 인사말을 전달해 실행합니다.

small_main은 우리가 할 일을 적는 함수입니다. 지금은 바깥 틀을 유지하고 `{ }` 안의 print만 바꾸세요. 문장 끝의 `;`도 함께 둡니다.

예상 출력:

```text
Hello!
```

## Exercise — 한 가지 바꾸기

Hello! 대신 자신의 이름을 출력하세요.

@exercise exercise_starter.cpp

### Hint

큰따옴표 안의 글자만 바꾸세요. `print`의 p는 소문자입니다.

@solution exercise_solution.cpp
