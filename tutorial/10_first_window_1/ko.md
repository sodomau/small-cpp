---
title: 창 열고 사용하기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 창 열고 사용하기
related-example: reference/window
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 창 하나 열기

### 이번에 배울 것

**Window**는 화면의 창을 다루는 타입입니다. **객체**는 그 타입으로 만든 실제 대상입니다. window라는 객체를 만들고 창을 열어 봅니다.

### 실행해 보기

@code example1.cpp

`open(640, 480)`은 가로 640, 세로 480픽셀의 창을 엽니다. **픽셀**은 화면을 이루는 작은 점입니다. `set_title`은 제목을 정합니다.

is_open이 참인 동안 show를 반복합니다. show는 화면을 보여 주고 닫기 같은 입력도 처리합니다. 창이 반응하려면 이 호출이 필요합니다. 창의 닫기 버튼을 누르면 반복을 끝냅니다.

이후 그림 예제에서도 이 창 열기 틀을 다시 사용합니다.

## 객체에게 정보 물어보기

### 이번에 배울 것

객체의 점 뒤에 함수 이름을 쓰면 그 객체에 속한 기능을 사용합니다. 이런 함수를 **멤버 함수**라고 합니다.

### 실행해 보기

@code first_window_2_example2.cpp

`window.width()`와 `window.height()`는 창의 가로·세로 크기를 돌려줍니다. 콘솔에 `Size: 400 x 300`이 나오는지 보세요.

객체 만들기와 실제 창 열기는 별개입니다. set_title은 open 전에 해도 됩니다. 프로그램에서 직접 닫으려면 close를 호출합니다.

## Exercise — 내 이름의 창

500 x 300 크기의 Window를 열고 제목을 자신의 이름으로 지정하세요. 창을 닫을 때까지 유지하세요.

@exercise exercise1_starter.cpp

### Hint

`set_title`을 `open` 전에 호출해도 됩니다.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 크기 확인하기

320 x 240 창을 열고 실제 width와 height를 콘솔에 출력한 뒤 창을 유지하세요.

@exercise first_window_2_exercise2_starter.cpp

### Hint

`window.width()`와 `window.height()`를 print에 전달하세요.

@solution first_window_2_exercise2_solution.cpp
