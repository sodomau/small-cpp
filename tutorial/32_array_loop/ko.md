---
title: 배열의 값을 하나씩 보기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 각 점수의 두 배를 출력하세요. 배열에 다시 저장할 필요는 없습니다.
related-example: reference/console
---

## 이번에 배울 것

반복문의 변수를 배열의 위치로 사용하면 원소를 차례로 읽을 수 있습니다. Length()는 원소 개수를 알려 줍니다.

## 실행해 보기

@code example.cpp

i가 0, 1, 2일 때 각각 출력합니다. 3은 원소 개수와 같아서 조건이 거짓이 됩니다. 따라서 조건은 `<=`가 아니라 `<`입니다. 길이가 0이면 반복하지 않습니다.

예상 출력:

```text
80
95
70
```

## Exercise — 한 가지 바꾸기

각 점수의 두 배를 출력하세요. 배열에 다시 저장할 필요는 없습니다.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
