---
title: 조건이 맞지 않으면 다른 일 하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 비밀번호가 1234와 같으면 Open, 다르면 Locked를 출력하세요. 1111로 시험하세요.
related-example: reference/console
---

## 이번에 배울 것

**else**는 if의 조건이 거짓일 때 실행할 일을 적는 부분입니다. 두 갈래 중 하나를 고릅니다.

## 실행해 보기

@code example.cpp

같은지 비교할 때는 `==`를 씁니다. 값을 넣는 `=`와 다릅니다. `!=`는 서로 다른지를 비교합니다. answer를 5로 바꾸면 else 쪽만 실행됩니다.

예상 출력:

```text
Correct
```

## Exercise — 한 가지 바꾸기

비밀번호가 1234와 같으면 Open, 다르면 Locked를 출력하세요. 1111로 시험하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
