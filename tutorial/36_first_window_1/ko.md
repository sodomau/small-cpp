---
title: 창 하나 열기
part: making_things
part-title: 작은 걸음 II — 만들며 배우기
goal: 창 하나 열기
related-example: reference/window
---

## 이번에 배울 것

**Window**는 화면의 창을 다루는 타입입니다. **객체**는 그 타입으로 만든 실제 대상입니다. window라는 객체를 만들고 창을 열어 봅니다.

## 실행해 보기

@code example1.cpp

`Open(640, 480)`은 가로 640, 세로 480픽셀의 창을 엽니다. **픽셀**은 화면을 이루는 작은 점입니다. `SetTitle`은 제목을 정합니다.

IsOpen이 참인 동안 Show를 반복합니다. Show는 화면을 보여 주고 닫기 같은 입력도 처리합니다. 창이 반응하려면 이 호출이 필요합니다. 창의 닫기 버튼을 누르면 반복을 끝냅니다.

이후 그림 예제에서도 이 창 열기 틀을 다시 사용합니다.

## Exercise — 내 이름의 창

500 x 300 크기의 Window를 열고 제목을 자신의 이름으로 지정하세요. 창을 닫을 때까지 유지하세요.

@exercise exercise1_starter.cpp

### Hint

`SetTitle`을 `Open` 전에 호출해도 됩니다.

@solution exercise1_solution.cpp

