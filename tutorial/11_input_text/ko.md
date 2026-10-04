---
title: 실행 중에 이름 물어보기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 이름을 입력받아 Nice to meet you, 뒤에 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

**입력**은 프로그램 밖에서 값을 받아 오는 일입니다. input 함수는 키보드로 쓴 한 줄을 문자열로 돌려줍니다.

## 실행해 보기

@code example.cpp

Run한 뒤 콘솔 창에 Alex를 쓰고 Enter를 누르세요. input이 기다리는 동안은 고장이 아닙니다. 입력을 마치면 그 문자열을 name에 저장하고 다음 줄을 실행합니다.

`input("Name: ")`처럼 괄호 안에 안내문을 넣을 수도 있습니다.

예상 출력 (입력 안내문 제외):

```text
Hello, Alex
```

## Exercise — 한 가지 바꾸기

이름을 입력받아 Nice to meet you, 뒤에 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
