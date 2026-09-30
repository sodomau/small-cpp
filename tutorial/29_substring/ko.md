---
title: 문자열의 일부 가져오기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: Small의 맨 앞 두 글자 Sm을 가져오세요.
related-example: reference/console
---

## 이번에 배울 것

**부분 문자열**은 문자열의 연속된 일부입니다. Substring에 시작 위치와 가져올 길이를 전달합니다.

## 실행해 보기

@code example.cpp

위치 1은 m입니다. 여기부터 세 글자를 가져오므로 mal이 됩니다. `Substring(1)`처럼 길이를 생략하면 위치 1부터 끝까지 가져옵니다.

길이가 5인 문자열에서 문자 위치는 0–4입니다. 대괄호로 문자를 읽을 때 범위를 벗어나지 않게 하세요.

예상 출력:

```text
mal
```

## Exercise — 한 가지 바꾸기

Small의 맨 앞 두 글자 Sm을 가져오세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
