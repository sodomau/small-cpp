---
title: 객체에게 정보 물어보기
part: making_things
part-title: Part II — 만들며 배우기
goal: 객체에게 정보 물어보기
related-example: reference/window
---

## 이번에 배울 것

객체의 점 뒤에 함수 이름을 쓰면 그 객체에 속한 기능을 사용합니다. 이런 함수를 **멤버 함수**라고 합니다.

## 실행해 보기

@code example2.cpp

`window.Width()`와 `window.Height()`는 창의 가로·세로 크기를 돌려줍니다. 콘솔에 `Size: 400 x 300`이 나오는지 보세요.

객체 만들기와 실제 창 열기는 별개입니다. SetTitle은 Open 전에 해도 됩니다. 프로그램에서 직접 닫으려면 Close를 호출합니다.

## Exercise — 크기 확인하기

320 x 240 창을 열고 실제 Width와 Height를 콘솔에 출력한 뒤 창을 유지하세요.

@exercise exercise2_starter.cpp

### Hint

`window.Width()`와 `window.Height()`를 Print에 전달하세요.

@solution exercise2_solution.cpp
