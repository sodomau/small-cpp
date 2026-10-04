---
title: 색과 글자 더하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 색과 글자 더하기
related-example: reference/drawing
---

## 이번에 배울 것

**rgb**는 빨강·초록·파랑의 세기를 섞어 색을 만드는 방식입니다. 각 값은 0부터 255까지 씁니다.

## 실행해 보기

@code example2.cpp

Color는 색을 저장하는 타입이고 rgb는 그 색을 만들어 돌려주는 함수입니다.

fill_rectangle의 숫자는 왼쪽 위 x, y와 가로·세로 크기입니다. draw_rectangle은 테두리만 그립니다. draw_text는 x, y, 문자열, 색, 글자 크기를 받습니다. 주황 사각형 위에 글자가 보이는지 확인하세요.

## Exercise — 나만의 얼굴

원과 선을 사용해 간단한 얼굴을 그리세요. 눈 두 개와 입이 보이면 됩니다. 색과 위치는 자유입니다.

@exercise exercise2_starter.cpp

### Hint

큰 fill_circle 하나를 얼굴로 만든 뒤 작은 원 두 개와 draw_line을 추가해 보세요.

@solution exercise2_solution.cpp
