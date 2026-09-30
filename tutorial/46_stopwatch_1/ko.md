---
title: 지난 시간 재기
part: making_things
part-title: Part II — Making Things
goal: 지난 시간 재기
related-example: reference/stopwatch
---

## 이번에 배울 것

**StopWatch**는 경과 시간을 재는 도구입니다. 객체를 만들 때부터 시간을 재고 Elapsed는 지난 초 수를 알려 줍니다.

## 실행해 보기

@code example1.cpp

Sleep(1.0) 뒤에는 약 1초, Reset 후 Sleep(0.5) 뒤에는 약 0.5초가 나옵니다. 읽기만 한다고 시계가 0으로 돌아가지는 않습니다. Reset이 다시 재는 동작입니다.

실행 환경 때문에 정확히 1.000이나 0.500이 아니어도 정상입니다.

## Exercise — 2초 재기

StopWatch를 만들고 Sleep(2.0) 뒤 Elapsed 값을 출력하세요. 정확히 2.000...이 아니어도 정상입니다.

@exercise exercise1_starter.cpp

### Hint

StopWatch는 생성되는 순간 시작하므로 별도의 Start가 필요 없습니다.

@solution exercise1_solution.cpp

