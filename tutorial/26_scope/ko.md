---
title: 함수 안의 변수는 따로 쓰기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: score를 20으로 시작하면 두 출력이 무엇인지 예상하고 확인하세요.
related-example: reference/console
---

## 이번에 배울 것

함수 안에서 만든 **지역 변수**는 그 범위 안에서 사용합니다. 값으로 전달받은 매개변수도 원본과 별도로 값을 가집니다.

## 실행해 보기

@code example.cpp

number는 score의 값 10을 복사해서 받습니다. number만 바꾸었으므로 돌아온 뒤 score는 여전히 10입니다.

일반적인 지역 변수는 그 범위가 끝나면 수명도 끝납니다. 다음 호출에서 이전 값을 자동으로 기억하지 않습니다. 원본을 바꾸는 방법은 뒤의 참조 수업에서 배웁니다.

예상 출력:

```text
11
10
```

## Exercise — 한 가지 바꾸기

score를 20으로 시작하면 두 출력이 무엇인지 예상하고 확인하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
