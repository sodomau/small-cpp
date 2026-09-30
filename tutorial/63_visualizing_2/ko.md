---
title: 정렬 과정을 눈으로 보기
part: algorithms
part-title: Part III — Thinking with Programs
goal: 정렬 과정을 눈으로 보기
related-example: programs/bouncing_ball
---

## 이번에 배울 것

완성된 답뿐 아니라 **중간 상태**를 그리면 알고리즘의 동작도 볼 수 있습니다.

## 실행해 보기

@code example2.cpp

자리 하나를 정한 뒤 전체 막대를 다시 그리고 0.5초 기다립니다. 이번에 정한 자리는 빨강입니다.

바뀐 배열을 보고 정렬이 어디까지 진행됐는지 말해 보세요. 그림을 그리는 부분과 정렬하는 부분을 구분해 읽습니다.

## Exercise — swap 횟수 세기

Selection Sort에서 실제로 swap을 수행한 횟수를 세고 마지막에 출력하세요. 같은 위치끼리는 swap하지 않도록 해도 좋습니다.

@exercise exercise2_starter.cpp

### Hint

`swaps`를 0으로 시작하고 smallest != i일 때만 swap하고 증가시키세요.

@solution exercise2_solution.cpp
