---
title: 그림과 글자 그리기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 그림과 글자 그리기
related-example: reference/drawing
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 좌표로 그림 그리기

### 이번에 배울 것

**좌표**는 화면의 위치를 숫자로 나타낸 것입니다. 창의 왼쪽 위가 (0, 0)이고 x는 오른쪽, y는 아래쪽으로 커집니다.

### 실행해 보기

@code example1.cpp

clear는 배경을 지웁니다. `fill_circle(320, 240, 80, Yellow)`는 중심 (320, 240), 반지름 80인 노란 원을 채웁니다. draw_circle은 테두리만 그립니다.

draw_line의 네 숫자는 시작점 x, y와 끝점 x, y입니다. 나중에 그린 것이 먼저 그린 것을 덮습니다. 노란 얼굴이 보이면 원의 위치 하나를 바꾸어 보세요.

예제 끝의 while처럼 실행할 문장이 하나이면 중괄호를 생략하기도 합니다. 직접 쓸 때는 중괄호로 묶어도 됩니다.

## 색과 글자 더하기

### 이번에 배울 것

**rgb**는 빨강·초록·파랑의 세기를 섞어 색을 만드는 방식입니다. 각 값은 0부터 255까지 씁니다.

### 실행해 보기

@code drawing_2_example2.cpp

Color는 색을 저장하는 타입이고 rgb는 그 색을 만들어 돌려주는 함수입니다.

fill_rectangle의 숫자는 왼쪽 위 x, y와 가로·세로 크기입니다. draw_rectangle은 테두리만 그립니다. draw_text는 x, y, 문자열, 색, 글자 크기를 받습니다. 주황 사각형 위에 글자가 보이는지 확인하세요.

## Exercise — 신호등

검은색 또는 Gray 사각형 안에 Red, Yellow, Green 원 세 개가 세로로 들어 있는 신호등을 그리세요.

@exercise exercise1_starter.cpp

### Hint

먼저 fill_rectangle로 몸체를 그리고 fill_circle을 세 번 사용하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 나만의 얼굴

원과 선을 사용해 간단한 얼굴을 그리세요. 눈 두 개와 입이 보이면 됩니다. 색과 위치는 자유입니다.

@exercise drawing_2_exercise2_starter.cpp

### Hint

큰 fill_circle 하나를 얼굴로 만든 뒤 작은 원 두 개와 draw_line을 추가해 보세요.

@solution drawing_2_exercise2_solution.cpp
