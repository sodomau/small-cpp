---
title: 참조로 원본 사용하기
part: types
part-title: 작은 걸음 V — 나만의 자료형 만들기
goal: 참조로 원본 사용하기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 복사 대신 원본에 이름 붙이기

### 이번에 배울 것

**참조(reference)**는 기존 대상에 붙이는 다른 이름입니다. int& 매개변수는 전달한 정수의 원본을 가리킵니다.

### 실행해 보기

@code example1.cpp

먼저 예제를 실행하면 Inside: 11, Outside: 10입니다. `add_one(int x)`를 `add_one(int& x)`로 바꾸어 다시 실행하세요. 이번에는 둘 다 11입니다.

처음에는 x가 복사본이었고, &를 붙인 뒤에는 n의 다른 이름이기 때문입니다. 원본을 바꾸겠다는 의도가 있을 때 사용합니다.

## 복사 없이 읽기만 하기

### 이번에 배울 것

**const 참조**는 원본을 복사하지 않고 읽되, 그 참조를 통해 바꾸지는 않겠다는 뜻입니다.

### 실행해 보기

@code references_2_example2.cpp

`const Array<int>& numbers`의 &는 원본 참조, const는 읽기 전용입니다. 출력은 Sum: 25입니다.

배열 전체를 복사할 필요 없이 합계를 구합니다. 값을 바꾸려 하면 컴파일 오류입니다. 앞에서 쓴 Array<int> 매개변수도 올바르지만 배열이 크면 복사 비용이 커질 수 있습니다.

## Exercise — Swap 만들기

두 int의 원래 값을 서로 바꾸는 `swap(int& a, int& b)` 함수를 만드세요.

@exercise exercise1_starter.cpp

### Hint

temp에 a를 잠깐 저장한 뒤 a=b, b=temp 순서로 바꾸세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — find_largest 개선하기

앞에서 배운 `find_largest(Array<int> numbers)`를 `const Array<int>&`를 사용하도록 바꾸세요. 함수는 Array를 수정하지 않습니다.

@exercise references_2_exercise2_starter.cpp

### Hint

parameter만 `const Array<int>& numbers`로 바꾸고 나머지 알고리즘은 그대로 사용할 수 있습니다.

@solution references_2_exercise2_solution.cpp
