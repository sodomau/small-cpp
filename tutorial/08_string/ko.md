---
title: String
part: basics
part-title: Part I — Programming Basics
goal: String에 글자를 저장하고 길이, 문자, 부분 문자열을 다룹니다.
related-example: reference/string
---

## 글자도 값입니다
지금까지 큰따옴표 안의 글자를 바로 출력했습니다. 글자도 변수에 저장해 두고 계산하듯 다룰 수 있습니다. Small C++에서는 여러 글자를 담는 타입을 `String`이라고 합니다.

String은 `+`로 이어 붙일 수 있고 `Length()`로 몇 글자인지 알 수 있습니다.

## 먼저 실행해 보세요

@code example1.cpp

## 한 글자씩 보기
String의 첫 글자는 `text[0]`, 두 번째 글자는 `text[1]`처럼 읽습니다. 컴퓨터에서는 위치를 셀 때 **0부터 시작**하는 경우가 많습니다.

`Substring(start, length)`는 String의 일부를 새 String으로 만듭니다. 아래에서 `word.Substring(1, 3)`은 위치 1부터 세 글자를 가져옵니다.

String끼리는 `==`, `!=`, `<`, `>` 같은 비교도 할 수 있습니다.

## 조금 바꾸어 보기

@code example2.cpp

## 범위를 벗어나지 않게
길이가 5인 String의 올바른 위치는 0, 1, 2, 3, 4입니다. `text[5]`는 여섯 번째 글자를 뜻하므로 범위를 벗어납니다. Small은 이런 실수를 발견하면 runtime error로 알려줍니다.

String을 함수에 전달하는 것도 다른 값과 똑같이 할 수 있습니다. 지금 단계에서는 `String text`처럼 값으로 받으면 됩니다. reference는 나중에 메모리 모델을 배울 때 함께 살펴봅니다.

## Exercise — 글자를 거꾸로 출력

`String word = "Small";`의 글자를 마지막부터 첫 글자까지 한 줄에 하나씩 출력하세요.

@exercise exercise1_starter.cpp

### Hint

마지막 위치는 `word.Length() - 1`입니다. i를 1씩 줄이는 for를 만들어 보세요.

@solution exercise1_solution.cpp

## Exercise — 첫 글자와 나머지

이름을 Input으로 입력받고 첫 글자를 `First:` 뒤에, 나머지 글자를 `Rest:` 뒤에 출력하세요. 이 문제에서는 두 글자 이상의 이름을 입력한다고 가정합니다.

@exercise exercise2_starter.cpp

### Hint

첫 글자는 `name[0]`입니다. 나머지는 `name.Substring(1)`로 얻을 수 있습니다.

@solution exercise2_solution.cpp
