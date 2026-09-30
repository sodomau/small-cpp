---
title: 값을 바꾸는 짧은 표기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 점수를 10으로 시작하고 두 배로 만든 뒤 1 늘려 출력하세요.
related-example: reference/console
---

## 이번에 배울 것

자주 쓰는 계산과 대입을 짧게 쓸 수 있습니다. int나 double에서 `score += 5;`는 `score = score + 5;`와 같은 갱신입니다.

## 실행해 보기

@code example.cpp

`++`는 1 증가, `--`는 1 감소입니다. 처음에는 예제처럼 독립된 문장으로 사용하세요. `-=`, `*=`, `/=`도 같은 방식입니다. 정수에는 `%=`도 씁니다. 정수의 /=는 여전히 정수 나눗셈입니다.

예상 출력:

```text
14
```

## Exercise — 한 가지 바꾸기

점수를 10으로 시작하고 두 배로 만든 뒤 1 늘려 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
