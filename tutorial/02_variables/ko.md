---
title: Variables and Values
part: basics
part-title: Part I — Programming Basics
goal: 값을 변수에 저장하고, 계산하거나 새로운 값으로 바꿉니다.
related-example: reference/console
---

## 이름을 붙여 기억하기
 게임의 점수는 계속 바뀝니다. 숫자를 기억하고 다시 쓰려면 **변수**를 사용하면 편리합니다.

 `int score = 10;`은 정수를 저장할 변수 score를 만들고 처음 값으로 10을 넣습니다. 아래 코드를 실행하기 전에 두 번째 출력이 얼마일지 예상해 보세요.

## 먼저 실행해 보세요

@code example1.cpp

## = 는 값을 저장한다는 뜻
 `score = score + 5;`에서는 오른쪽을 먼저 계산하고 그 결과를 왼쪽 변수에 저장합니다. 수학의 등식과는 다릅니다. score의 값을 출력할 때에는 큰따옴표를 쓰지 않습니다. `"score"`라고 쓰면 변수의 값이 아니라 글자 score가 나옵니다.

 `int`는 정수에, `double`은 소수 부분이 있는 수에도 사용합니다. `+`, `-`, `*`, `/`로 계산할 수 있습니다. 두 정수의 나눗셈은 소수 부분을 버리므로 `5 / 2`는 2이고, `5.0 / 2.0`은 2.5입니다. double도 모든 실수를 정확히 저장하는 것은 아닙니다.

 `bool`은 `true` 또는 `false`를, `char`는 `'A'`처럼 작은따옴표로 쓴 문자 하나를 담습니다. 아래에서 bool은 Print로 1 또는 0으로 출력됩니다.

## 조금 바꾸어 보기

@code example2.cpp

## 글자와 값을 함께 출력하기
 `Print("Area: ", area);`처럼 쉼표로 나누어 주면 순서대로 이어서 출력합니다. 필요한 공백은 큰따옴표 안에 직접 넣습니다.

 변수는 처음 만들 때 값을 넣고 시작하세요. 선언할 때 쓴 타입 이름은 값을 바꿀 때 다시 쓰지 않습니다. 이름은 `score`, `width`처럼 무엇을 담는지 알아보기 쉽게 지어 봅시다.

## Exercise — 나이 변수

int 변수 age에 자신의 나이를 넣고 `Age: ` 뒤에 출력하세요.

@exercise exercise1_starter.cpp

### Hint

`int age = 10;`처럼 만든 뒤 `Print("Age: ", age);`를 사용합니다.

@solution exercise1_solution.cpp

## Exercise — 사각형 넓이

double 변수 width와 height에 3.5와 2.0을 넣으세요. 곱한 값을 area에 저장하고 출력하세요. 값을 바꾸어 다시 실행해 보세요.

@exercise exercise2_starter.cpp

### Hint

넓이는 가로 * 세로입니다. 계산 결과를 담을 변수도 double로 만드세요.

@solution exercise2_solution.cpp
