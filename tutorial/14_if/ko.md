---
title: 조건에 맞을 때만 실행하기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: number가 0보다 클 때만 Positive를 출력하세요. 먼저 3으로 시험하세요.
related-example: reference/console
---

## 이번에 배울 것

**조건**은 참인지 거짓인지 판단할 수 있는 식입니다. if는 조건이 참일 때만 중괄호 안을 실행하는 **조건문**입니다.

## 실행해 보기

@code example.cpp

`score >= 60`은 점수가 60 이상인지 묻습니다. 80이면 참이라 Pass를 출력합니다. 50으로 바꾸면 Pass는 건너뛰고 Done만 출력합니다.

`>`는 초과, `<`는 미만, `>=`는 이상, `<=`는 이하입니다. if의 닫는 중괄호 뒤에는 ;을 붙이지 않습니다.

예상 출력:

```text
Pass
Done
```

## Exercise — 한 가지 바꾸기

number가 0보다 클 때만 Positive를 출력하세요. 먼저 3으로 시험하세요.

@exercise exercise_starter.cpp

### Hint

3을 0과 -1로도 바꾸어 보세요. 그때는 출력하지 않아야 합니다.

@solution exercise_solution.cpp
