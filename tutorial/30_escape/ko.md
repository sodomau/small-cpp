---
title: 따옴표와 줄바꿈 넣기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: Print 한 번으로 A와 B를 서로 다른 줄에 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

문자열 안에 특별한 문자를 넣을 때는 역슬래시로 시작하는 **이스케이프 표기**를 사용합니다.

## 실행해 보기

@code example.cpp

`\n`은 줄바꿈, `\"`는 큰따옴표 하나, `\\`는 역슬래시 하나입니다. 코드에서 두 기호로 적어도 하나의 문자를 나타냅니다.

`""`는 내용이 없는 빈 문자열이고 `" "`는 공백 하나가 있는 문자열입니다. Print는 빈 문자열을 출력해도 마지막에 줄을 바꿉니다.

예상 출력:

```text
Hello
Small
"Hi"
```

## Exercise — 한 가지 바꾸기

Print 한 번으로 A와 B를 서로 다른 줄에 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
