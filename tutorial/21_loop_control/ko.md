---
title: 반복을 멈추거나 건너뛰기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 2 대신 3을 건너뛰고, 5에서 멈추도록 바꾸세요.
related-example: reference/console
---

## 이번에 배울 것

**break**는 가장 안쪽 반복문을 끝냅니다. **continue**는 이번 반복의 남은 부분을 건너뛰고 다음 반복으로 갑니다.

## 실행해 보기

@code example.cpp

2에서는 print를 건너뜁니다. for는 i를 늘린 뒤 다음 조건을 검사합니다. 4에서는 반복 자체를 끝내므로 4와 5 모두 출력하지 않습니다.

예상 출력:

```text
1
3
```

## Exercise — 한 가지 바꾸기

2 대신 3을 건너뛰고, 5에서 멈추도록 바꾸세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
