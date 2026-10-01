---
title: 숫자를 막대로 보여 주기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 숫자를 막대로 보여 주기
related-example: programs/bouncing_ball
---

## 이번에 배울 것

**시각화**는 데이터를 그림으로 표현하는 것입니다. 값이 클수록 높은 막대를 그려 배열을 눈으로 봅니다.

## 실행해 보기

@code example1.cpp

값에 30을 곱해 높이를 정합니다. 화면은 아래로 갈수록 y가 커지므로 막대 위쪽을 `420 - height`로 계산합니다.

배열의 값 하나를 바꾸고 해당 막대의 높이가 달라지는지 확인하세요.

## Exercise — 현재 위치 표시

먼저 정렬 애니메이션에 사용할 위치 표시를 따로 연습합니다. 시작 코드의 current번째 막대를 Red로, 나머지를 Blue로 그리세요. 이 연습 자체는 정렬하지 않는 정적인 그림입니다. current를 0부터 4까지 바꾸어 빨간 막대가 해당 위치로 바뀌는지 확인하세요.

@exercise exercise1_starter.cpp

### Hint

막대를 그리는 loop 안에서 `i == current`인지 검사해 Color를 선택하세요. 앞의 정렬 애니메이션으로 옮길 때에는 current 대신 그 단계에서 확정한 위치를 사용하면 됩니다.

@solution exercise1_solution.cpp

