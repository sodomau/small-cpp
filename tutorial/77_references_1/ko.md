---
title: 복사 대신 원본에 이름 붙이기
part: types
part-title: 작은 걸음 V — 나만의 자료형 만들기
goal: 복사 대신 원본에 이름 붙이기
related-example: reference/array
---

## 이번에 배울 것

**참조(reference)**는 기존 대상에 붙이는 다른 이름입니다. int& 매개변수는 전달한 정수의 원본을 가리킵니다.

## 실행해 보기

@code example1.cpp

먼저 예제를 실행하면 Inside: 11, Outside: 10입니다. `AddOne(int x)`를 `AddOne(int& x)`로 바꾸어 다시 실행하세요. 이번에는 둘 다 11입니다.

처음에는 x가 복사본이었고, &를 붙인 뒤에는 n의 다른 이름이기 때문입니다. 원본을 바꾸겠다는 의도가 있을 때 사용합니다.

## Exercise — Swap 만들기

두 int의 원래 값을 서로 바꾸는 `Swap(int& a, int& b)` 함수를 만드세요.

@exercise exercise1_starter.cpp

### Hint

temp에 a를 잠깐 저장한 뒤 a=b, b=temp 순서로 바꾸세요.

@solution exercise1_solution.cpp

