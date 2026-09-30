---
title: References — Sharing Without Copying
part: types
part-title: Part V — Making Your Own Types
goal: value copy, reference, const reference를 메모리 모델과 함께 이해하고 큰 값을 복사하지 않고 전달합니다.
related-example: reference/array
---

## 지금까지 함수 parameter는 어떻게 동작했을까요?
우리는 지금까지 일부러 parameter를 단순하게 **값으로** 받았습니다.

`AddOne(n)`을 호출하면 parameter x에는 n의 값이 복사됩니다. 그래서 함수 안에서 x를 바꾸어도 원래 n은 바뀌지 않습니다.

`n: [10]  → copy →  x: [10]`

이 단순한 규칙 덕분에 앞의 lesson에서는 함수 자체에 집중할 수 있었습니다. 이제 실제 메모리에서 이 차이가 왜 중요한지 열어 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## 같은 값을 함께 사용하려면 reference
원본을 함수에서 바꾸고 싶다면 parameter를 `int& x`처럼 **reference**로 만들 수 있습니다.

이때 새로운 int copy가 생기는 것이 아니라 x를 통해 원래 n을 사용합니다.

`n: [10]  ← x refers to this value`

그래서 x를 바꾸면 n도 바뀝니다.

이제 Array를 생각해 봅시다. Lesson 19의 `Sum(Array<int> numbers)`는 올바른 C++이지만 함수 호출 때 Array 값 전체를 복사합니다. 다섯 개라면 별 문제 없지만 백만 개라면 굳이 복사할 이유가 없습니다.

## 복사하지 않고 읽기

@code example2.cpp

## `const T&`는 복사하지 않는 read-only input
`Array<int>&`만 사용하면 원래 Array를 함께 사용하므로 복사는 피할 수 있지만 함수가 원본을 수정할 수도 있습니다. Sum은 읽기만 해야 합니다.

`const Array<int>& numbers`는 두 뜻을 합칩니다.

- `&` — 새로운 Array를 복사하지 않고 원래 값을 사용합니다.
- `const` — 이 reference를 통해서는 값을 바꾸지 않겠다는 약속입니다.

그래서 큰 read-only input에 흔히 쓰입니다.

`T x` = 값을 복사해서 받음  
`T& x` = 원래 값을 함께 사용하며 수정 가능  
`const T& x` = 원래 값을 함께 사용하지만 수정하지 않음

`const int MaxScore = 100;`처럼 const는 값 자체를 변경하지 못하게 하는 데도 쓰입니다. 하지만 여기서는 **함수의 read-only input contract**가 가장 중요한 사용입니다.

이 lesson 이후에는 큰 String과 Array를 읽기만 하는 parameter에 일반적인 C++ style인 `const T&`를 사용합니다.

## Exercise — Swap 만들기

두 int의 원래 값을 서로 바꾸는 `Swap(int& a, int& b)` 함수를 만드세요.

@exercise exercise1_starter.cpp

### Hint

temp에 a를 잠깐 저장한 뒤 a=b, b=temp 순서로 바꾸세요.

@solution exercise1_solution.cpp

## Exercise — FindLargest 개선하기

앞에서 배운 `FindLargest(Array<int> numbers)`를 `const Array<int>&`를 사용하도록 바꾸세요. 함수는 Array를 수정하지 않습니다.

@exercise exercise2_starter.cpp

### Hint

parameter만 `const Array<int>& numbers`로 바꾸고 나머지 알고리즘은 그대로 사용할 수 있습니다.

@solution exercise2_solution.cpp
