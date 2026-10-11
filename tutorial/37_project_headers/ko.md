---
title: 소스와 헤더로 코드 나누기
part: projects
part-title: 작은 걸음 VIII — 여러 파일로 프로그램 만들기
goal: 소스와 헤더로 코드 나누기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 프로그램을 두 파일로 나누기

### 먼저 한 파일에서 실행하기

@code example.cpp

`say_hello`를 다른 파일로 옮겨 보겠습니다. 새 프로젝트가 아니라 앞 수업의 `Greeting` 프로젝트에서 작업하세요.

### greeting.cpp 만들기

왼쪽 파일 목록의 빈 공간을 우클릭하고 **New Source File…**을 누르세요. 이름을 `greeting.cpp`로 입력하면 파일이 생성되고 탭이 열립니다. 아래 내용을 넣으세요.

### greeting.cpp
```cpp
void say_hello()
{
    print("Hello from another file!");
}
```

이제 `main.cpp`를 아래처럼 바꿉니다. `say_hello`의 함수 내용은 지우고, 첫 줄에 함수 선언을 넣습니다.

### main.cpp
```cpp
void say_hello();

void small_main()
{
    say_hello();
}
```

끝에 세미콜론이 있는 `void say_hello();`는 함수가 있다는 소개입니다. 중괄호가 있는 쪽은 실제 함수 내용입니다. **Run Project**를 누르면 이전과 같은 결과가 나옵니다.

`small_main`은 프로젝트 전체에 하나만 두세요. `.cpp`를 `#include`하지 마세요. IDE가 모든 포함된 `.cpp`를 각각 컴파일하고 합칩니다.

## 함수의 소개장을 만들기

### 소개를 한 곳에 모으기

앞 수업에서는 `main.cpp`에 함수 선언을 직접 썼습니다. 여러 파일에서 같은 함수를 쓸 때는 선언을 헤더에 모아 두면 편합니다.

왼쪽 빈 공간을 우클릭해 **New Header File…**로 `greeting.h`를 만드세요. 처음 들어 있는 `#pragma once`는 그대로 둡니다.

### greeting.h
```cpp
#pragma once

void say_hello();
```

### greeting.cpp
```cpp
#include "greeting.h"

void say_hello()
{
    print("Hello from another file!");
}
```

### main.cpp
```cpp
#include "greeting.h"

void small_main()
{
    say_hello();
}
```

`#include "greeting.h"`는 이 헤더의 내용을 현재 파일에서 읽게 합니다. 같은 폴더의 헤더 이름은 큰따옴표로 감쌉니다. 함수 내용은 `greeting.cpp` 한 곳에만 있습니다. 그 파일도 자기 헤더를 포함해 선언과 정의가 맞는지 확인합니다.

`#pragma once`는 한 소스 파일을 컴파일할 때 헤더 내용이 중복으로 들어오는 것을 막습니다. C++ 표준 기능은 아니지만 Small C++의 컴파일러가 지원합니다. 다른 표준적인 방법인 include guard는 나중에 배워도 됩니다.

### 한 파일에서 다시 확인하기

![세 파일이 들어 있는 Greeting 프로젝트. main.cpp에서 greeting.h를 포함합니다.](project_headers_project.png)

아래는 같은 동작을 한 파일로 모은 코드입니다. **Try This Code**는 이 한 파일을 엽니다. 프로젝트의 세 파일을 자동으로 만들지는 않습니다.

@code project_headers_example.cpp

## 연습 — 직접 확인하기

아래 한 파일 예제에서 인사말을 바꿔 보세요. 다음으로 프로젝트의 greeting.cpp에서 같은 변경을 하고, main.cpp 탭을 닫은 상태에서도 Run Project로 실행해 보세요.

@exercise exercise_starter.cpp

### Hint

위에서 설명한 메뉴를 이용하세요. 아래 코드는 한 파일 연습의 답안입니다. 프로젝트에서는 해당 역할의 파일에 같은 변경을 적용하세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## 연습 — 직접 확인하기

한 파일 연습에서 say_hello를 두 번 호출하세요. 그 다음 프로젝트에서도 main.cpp만 바꿔 같은 결과를 만들어 보세요.

@exercise project_headers_exercise_starter.cpp

### Hint

위에서 설명한 메뉴를 이용하세요. 아래 코드는 한 파일 연습의 답안입니다. 프로젝트에서는 해당 역할의 파일에 같은 변경을 적용하세요.

@solution project_headers_exercise_solution.cpp
