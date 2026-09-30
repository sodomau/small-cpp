---
title: 문자 하나 꺼내 보기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: Small에서 둘째 문자인 m을 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

**문자**는 글자나 기호 하나입니다. **char**는 문자 값을 담을 때 쓰는 타입입니다. 영문자 하나는 `'A'`처럼 작은따옴표로 씁니다.

## 실행해 보기

@code example.cpp

`word[0]`은 맨 처음 위치의 문자를 읽습니다. 위치 번호는 0부터 셉니다. Small의 유효한 위치는 0부터 4까지입니다.

`7`은 정수, `'7'`은 문자, `"7"`은 문자열입니다. char는 한 바이트를 담으므로 UTF-8 한글 한 글자를 char 하나에 넣을 수는 없습니다. 여기서는 영문자로 연습하세요.

예상 출력:

```text
A
S
```

## Exercise — 한 가지 바꾸기

Small에서 둘째 문자인 m을 출력하세요.

@exercise exercise_starter.cpp

### Hint

둘째 위치의 번호는 1입니다.

@solution exercise_solution.cpp
