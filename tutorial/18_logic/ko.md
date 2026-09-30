---
title: 조건 두 개 함께 보기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 나이가 13 미만이거나 19 초과일 때 Outside를 출력하세요. 20으로 시험하세요.
related-example: reference/console
---

## 이번에 배울 것

`&&`는 두 조건이 **모두 참**, `||`는 **하나 이상 참**, `!`는 참과 거짓을 뒤집는 연산자입니다.

## 실행해 보기

@code example.cpp

나이가 13 이상이면서 19 이하인지 확인합니다. 12, 13, 19, 20으로 바꾸어 경계를 확인하세요.

`!ready`는 준비되지 않았는지 묻습니다. &&는 왼쪽이 거짓이면, ||는 왼쪽이 참이면 오른쪽을 검사하지 않습니다.

예상 출력:

```text
Teen
```

## Exercise — 한 가지 바꾸기

나이가 13 미만이거나 19 초과일 때 Outside를 출력하세요. 20으로 시험하세요.

@exercise exercise_starter.cpp

### Hint

두 조건 사이에 ||를 사용하세요.

@solution exercise_solution.cpp
