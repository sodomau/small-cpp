---
title: Array
part: basics
part-title: Part I — Programming Basics
goal: Array에 같은 타입의 여러 값을 모아 저장하고 반복해서 처리합니다.
related-example: reference/array
---

## 값이 많아지면 한곳에 모으기
점수 다섯 개를 `score1`, `score2`, `score3`처럼 따로 만들 수도 있습니다. 하지만 값이 많아질수록 반복해서 처리하기 어렵습니다. **Array**는 같은 타입의 여러 값을 순서대로 모아 둡니다.

`Array<int>`는 int 여러 개를 담는 Array입니다. String처럼 위치는 0부터 시작합니다.

## 먼저 실행해 보세요

@code example1.cpp

## 읽고 바꿀 수 있습니다
`scores[0]`은 첫 번째 값입니다. Array의 한 칸에는 새 값을 대입할 수도 있습니다. `Length()`는 Array에 몇 개의 값이 있는지 알려줍니다.

Array 전체도 하나의 값처럼 함수에 전달할 수 있습니다. 지금은 다른 parameter와 똑같이 `Array<int> numbers`라고 쓰겠습니다. 이렇게 하면 함수가 Array 값을 받습니다.

실제로 큰 Array를 전달할 때 복사를 피하는 방법은 Lesson 31에서 **reference와 메모리 모델**을 배울 때 다룹니다.

## 조금 바꾸어 보기

@code example2.cpp

## Array의 범위
길이가 5인 Array의 올바른 index는 0부터 4까지입니다. 범위를 벗어난 index를 사용하면 Small이 runtime error로 알려줍니다.

Array와 반복문은 매우 자주 함께 사용됩니다. 다음 Part에서는 그래픽과 입력으로 실제 프로그램을 만들어 보고, 그 뒤에는 Array를 이용해 검색과 정렬 같은 알고리즘을 직접 만들어 봅니다.

## Exercise — 모든 값의 두 배

`{2, 4, 6, 8, 10}`이 들어 있는 Array의 모든 값을 for로 돌면서 두 배로 바꾼 뒤 모두 출력하세요.

@exercise exercise1_starter.cpp

### Hint

각 위치에서 `numbers[i] = numbers[i] * 2;`처럼 같은 칸에 새 값을 넣을 수 있습니다.

@solution exercise1_solution.cpp

## Exercise — Array의 합을 함수로

`Array<int>`를 값으로 받는 `Sum` 함수를 만들고 `{5, 10, 15, 20}`의 합을 출력하세요. 지금은 reference를 사용하지 않습니다.

@exercise exercise2_starter.cpp

### Hint

`int Sum(Array<int> numbers)`로 시작하고 for로 모든 값을 total에 더해 보세요.

@solution exercise2_solution.cpp
