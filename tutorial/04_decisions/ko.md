---
title: Making Decisions — if
part: basics
part-title: Part I — Programming Basics
goal: if와 else로 조건에 따라 다른 문장을 실행합니다.
related-example: reference/console
---

## 결과에 따라 다르게 행동하기
 게임에서 점수가 충분하면 승리 메시지를 보여주고 싶습니다. 조건이 맞을 때만 코드를 실행하려면 `if`를 사용합니다.

 아래 예제에서 120을 입력했을 때와 50을 입력했을 때를 비교해 보세요.

## 먼저 실행해 보세요

@code example1.cpp

## 조건은 true 또는 false
 `score >= 100`은 점수가 100 이상인지 비교합니다. 조건이 true일 때만 중괄호 안을 실행합니다. false일 때 할 일은 `else`에 적습니다.

 `<`는 작다, `>`는 크다, `<=`와 `>=`는 같을 때도 포함합니다. 두 값이 같은지는 `==`로, 다른지는 `!=`로 비교합니다. **`=`는 저장, `==`는 비교**이므로 구분하세요.

 `if (조건)` 뒤에는 `;`를 붙이지 않고 실행할 블록을 둡니다. 선택지가 세 개 이상이면 아래처럼 `else if`를 이어 쓸 수 있습니다. 위에서부터 검사해 처음 맞는 갈래만 실행합니다.

## 조금 바꾸어 보기

@code example2.cpp

## 경계의 값도 시험해 보세요
 조건을 만들면 양쪽 경우를 모두 실행해 보세요. 첫 예제의 99와 100처럼 조건이 바뀌는 경계가 특히 유용합니다.

 두 번째 예제에서 0일 때 무엇이 출력되는지 설명해 볼 수 있나요? 예상하고 실행해서 확인하는 것이 코드를 이해하는 좋은 연습입니다.

## Exercise — 양수일 때만

정수 하나를 입력받고, 0보다 클 때만 `Positive`를 출력하세요. 0이나 음수일 때는 추가 메시지를 출력하지 않습니다.

@exercise exercise1_starter.cpp

### Hint

`number > 0`을 if의 조건으로 쓰세요. 이 문제에는 else가 없어도 됩니다.

@solution exercise1_solution.cpp

## Exercise — 세 가지 안내

나이를 입력받으세요. 0~12는 `Child`, 13~19는 `Teenager`, 20 이상은 `Adult`를 출력합니다. 여기서는 나이를 0 이상의 정수로 입력한다고 약속합니다.

@exercise exercise2_starter.cpp

### Hint

먼저 age <= 12를 검사하고, 아니면 age <= 19를 검사하세요. 나머지는 Adult입니다.

@solution exercise2_solution.cpp
