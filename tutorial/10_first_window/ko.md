---
title: Your First Window
part: making_things
part-title: Part II — Making Things
goal: Window를 만들고 열고 닫으며 화면 크기와 제목을 다룹니다.
related-example: reference/window
---

## 콘솔 밖으로 나가 봅시다
지금까지는 글자를 콘솔에 출력했습니다. 이제 직접 창을 하나 열어 봅시다. `Window window;`는 Window 객체를 만들고, `window.Open(640, 480);`은 실제 화면에 640 x 480 크기의 창을 엽니다.

창을 연 뒤에는 사용자가 닫을 때까지 프로그램이 살아 있어야 합니다. 그래서 `while (window.IsOpen())`을 사용합니다.

## 먼저 실행해 보세요

@code example1.cpp

## 객체에게 일을 시키기
`window.Open(...)`, `window.SetTitle(...)`, `window.Width()`처럼 점 뒤에 이름을 붙여 Window에게 일을 시키거나 정보를 물어볼 수 있습니다. 아직 class를 배우지 않았지만 이런 사용법에는 먼저 익숙해질 수 있습니다.

`SetTitle`은 Open 전에도, 열린 뒤에도 사용할 수 있습니다. 제목은 Window가 가진 상태이고 Open은 실제 창을 여는 동작이기 때문입니다.

## 조금 바꾸어 보기

@code example2.cpp

## Window를 닫으면 반복도 끝납니다
창 오른쪽 위의 닫기 버튼을 누르면 `IsOpen()`이 false가 되어 while을 빠져나옵니다. `window.Close()`를 호출해서 프로그램이 직접 닫을 수도 있습니다.

지금은 Window의 내부 구현을 알 필요가 없습니다. 뒤에서 class를 배울 때 `Window window;`와 점을 사용하는 코드가 왜 이런 모습인지 다시 만나게 됩니다.

## Exercise — 내 이름의 창

500 x 300 크기의 Window를 열고 제목을 자신의 이름으로 지정하세요. 창을 닫을 때까지 유지하세요.

@exercise exercise1_starter.cpp

### Hint

`SetTitle`을 `Open` 전에 호출해도 됩니다.

@solution exercise1_solution.cpp

## Exercise — 크기 확인하기

320 x 240 창을 열고 실제 Width와 Height를 콘솔에 출력한 뒤 창을 유지하세요.

@exercise exercise2_starter.cpp

### Hint

`window.Width()`와 `window.Height()`를 Print에 전달하세요.

@solution exercise2_solution.cpp
