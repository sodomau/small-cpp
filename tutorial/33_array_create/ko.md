---
title: 자리 수부터 정해서 배열 만들기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 다섯 자리를 만들고 1부터 5까지 저장하며 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

처음 값을 나열하는 대신 필요한 자리 수를 먼저 정할 수도 있습니다. Array<int>(3)은 정수를 담을 자리 세 개를 만듭니다.

## 실행해 보기

@code example.cpp

`Array<int> numbers(3);`은 세 자리이고, `Array<int> numbers = {3};`은 값 3이 든 한 자리입니다. 구분하세요.

Small Array는 만든 뒤 길이를 늘리는 기능이 없습니다. 각 원소의 값은 바꿀 수 있습니다.

예상 출력:

```text
1
2
3
```

## Exercise — 한 가지 바꾸기

다섯 자리를 만들고 1부터 5까지 저장하며 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
