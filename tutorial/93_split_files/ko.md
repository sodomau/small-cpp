---
title: 프로그램을 두 파일로 나누기
part: projects
part-title: 작은 걸음 VIII — 여러 파일로 프로그램 만들기
goal: 함수 내용을 다른 소스 파일로 옮깁니다.
related-example: reference/console
---

## 먼저 한 파일에서 실행하기

@code example.cpp

`SayHello`를 다른 파일로 옮겨 보겠습니다. 새 프로젝트가 아니라 앞 수업의 `Greeting` 프로젝트에서 작업하세요.

## greeting.cpp 만들기

왼쪽 파일 목록의 빈 공간을 우클릭하고 **New Source File…**을 누르세요. 이름을 `greeting.cpp`로 입력하면 파일이 생성되고 탭이 열립니다. 아래 내용을 넣으세요.

### greeting.cpp
```cpp
void SayHello()
{
    Print("Hello from another file!");
}
```

이제 `main.cpp`를 아래처럼 바꿉니다. `SayHello`의 함수 내용은 지우고, 첫 줄에 함수 선언을 넣습니다.

### main.cpp
```cpp
void SayHello();

void SmallMain()
{
    SayHello();
}
```

끝에 세미콜론이 있는 `void SayHello();`는 함수가 있다는 소개입니다. 중괄호가 있는 쪽은 실제 함수 내용입니다. **Run Project**를 누르면 이전과 같은 결과가 나옵니다.

`SmallMain`은 프로젝트 전체에 하나만 두세요. `.cpp`를 `#include`하지 마세요. IDE가 모든 포함된 `.cpp`를 각각 컴파일하고 합칩니다.

## 연습 — 직접 확인하기

아래 한 파일 예제에서 인사말을 바꿔 보세요. 다음으로 프로젝트의 greeting.cpp에서 같은 변경을 하고, main.cpp 탭을 닫은 상태에서도 Run Project로 실행해 보세요.

@exercise exercise_starter.cpp

### Hint

위에서 설명한 메뉴를 이용하세요. 아래 코드는 한 파일 연습의 답안입니다. 프로젝트에서는 해당 역할의 파일에 같은 변경을 적용하세요.

@solution exercise_solution.cpp
