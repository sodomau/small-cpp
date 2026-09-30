---
title: Input and Output
part: basics
part-title: Part I — Programming Basics
goal: 콘솔에서 글자와 숫자를 입력받아 결과를 출력합니다.
related-example: reference/console
---

## 실행할 때 값을 정하기
 이름이나 숫자를 바꿀 때마다 코드를 수정하지 않고, 실행 중에 직접 입력해 봅시다.

 아래 예제를 Run한 뒤 **콘솔 창**에서 이름을 쓰고 **Enter**를 누르세요. 입력을 기다리는 동안은 프로그램이 멈춘 것이 아닙니다. `Input`은 한 줄을 글자 값으로 돌려줍니다. `String`은 그 글자를 담는 타입입니다.

## 먼저 실행해 보세요

@code example1.cpp

## 무엇을 입력받을까요?
 `Input()`은 한 줄의 글자를, `InputInt()`는 정수를, `InputReal()`은 double 값을 읽습니다. 괄호 안에 안내문을 넣을 수도 있습니다.

 `Write`는 출력한 뒤 줄을 바꾸지 않습니다. `Write("Age: ");` 다음에 `InputInt()`를 쓰면 같은 줄에서 입력할 수 있습니다. `Print()`를 인자 없이 사용하면 줄만 바꿉니다.

 숫자 입력에는 한 줄에 숫자 하나를 쓰세요. 숫자가 아닌 것을 넣으면 올바른 숫자를 다시 입력하라고 안내합니다.

## 조금 바꾸어 보기

@code example2.cpp

## 입력과 계산 연결하기
 입력한 값도 직접 코드에 쓴 값처럼 계산에 사용할 수 있습니다. 두 값을 따로 입력받으려면 입력 함수도 두 번 호출합니다.

 아래의 문제를 풀 때 소수도 입력하고 싶으면 InputReal과 double을 선택하세요. `Input`이 읽은 글자가 자동으로 숫자가 되는 것은 아닙니다.

## Exercise — 이름을 물어보기

이름을 입력받고 `Nice to meet you, 이름!`처럼 인사하세요.

@exercise exercise1_starter.cpp

### Hint

String 변수에 Input의 결과를 저장한 뒤, Print의 쉼표 사이에 그 변수를 넣으세요.

@solution exercise1_solution.cpp

## Exercise — 두 수의 합

두 숫자를 한 번씩 입력받고 합을 출력하세요. 2.5와 3.5를 넣으면 6이 나와야 합니다.

@exercise exercise2_starter.cpp

### Hint

double 변수 두 개를 InputReal로 채우고 `Print(a + b);`처럼 계산을 출력하세요.

@solution exercise2_solution.cpp
