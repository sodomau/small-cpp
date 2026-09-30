---
title: 세 갈래 중 하나 고르기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: number를 -2로 바꾸어 어떤 갈래가 실행되는지 확인하세요.
related-example: reference/console
---

## 이번에 배울 것

선택지가 셋 이상이면 **else if**로 조건을 이어 봅니다. 위에서부터 검사하고, 처음 맞는 갈래 하나만 실행합니다.

## 실행해 보기

@code example.cpp

0은 양수도 음수도 아니어서 마지막 else로 갑니다. else if 대신 독립된 if를 여러 개 쓰면 각 조건을 따로 검사하므로 여러 갈래가 실행될 수도 있습니다.

예상 출력:

```text
Zero
```

## Exercise — 한 가지 바꾸기

number를 -2로 바꾸어 어떤 갈래가 실행되는지 확인하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
