---
title: 문자열 이어 붙이기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: Good과 공백 하나, morning을 이어 붙여 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

String 값에 쓰는 `+`는 숫자 덧셈 대신 **이어 붙이기**를 합니다. 이어 붙인 결과도 String 값입니다.

## 실행해 보기

@code example.cpp

`text.length()`는 text의 길이를 돌려주는 기능입니다. 점은 text에 속한 기능을 사용한다는 뜻입니다. 여기에는 공백도 포함됩니다.

길이는 **바이트**라는 데이터 크기 단위로 셉니다. 이번 영문 예제에서는 한 글자가 한 바이트입니다. UTF-8 한글 한 글자는 여러 바이트라서 글자 수와 다를 수 있습니다.

예상 출력:

```text
Small C++
9
```

## Exercise — 한 가지 바꾸기

Good과 공백 하나, morning을 이어 붙여 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
