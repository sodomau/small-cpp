---
title: 복사 없이 읽기만 하기
part: types
part-title: 작은 걸음 V — 나만의 자료형 만들기
goal: 복사 없이 읽기만 하기
related-example: reference/array
---

## 이번에 배울 것

**const 참조**는 원본을 복사하지 않고 읽되, 그 참조를 통해 바꾸지는 않겠다는 뜻입니다.

## 실행해 보기

@code example2.cpp

`const Array<int>& numbers`의 &는 원본 참조, const는 읽기 전용입니다. 출력은 Sum: 25입니다.

배열 전체를 복사할 필요 없이 합계를 구합니다. 값을 바꾸려 하면 컴파일 오류입니다. 앞에서 쓴 Array<int> 매개변수도 올바르지만 배열이 크면 복사 비용이 커질 수 있습니다.

## Exercise — FindLargest 개선하기

앞에서 배운 `FindLargest(Array<int> numbers)`를 `const Array<int>&`를 사용하도록 바꾸세요. 함수는 Array를 수정하지 않습니다.

@exercise exercise2_starter.cpp

### Hint

parameter만 `const Array<int>& numbers`로 바꾸고 나머지 알고리즘은 그대로 사용할 수 있습니다.

@solution exercise2_solution.cpp
