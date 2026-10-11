---
title: 외부 라이브러리 선택하고 사용하기
part: libraries
part-title: 작은 걸음 IX — 외부 라이브러리 사용하기
goal: 외부 라이브러리 선택하고 사용하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 다른 사람이 만든 코드 사용하기

### 먼저 알아둘 것

외부 라이브러리는 다른 사람이 만든 코드를 사용하는 방법입니다. 하지만 **Libraries 메뉴, `//@` 설정, `small.project`, 자동 패키지 설치는 C++ 표준 기능이 아니라 Small C++ IDE의 기능**입니다. 다른 IDE에서는 그 환경의 방식으로 라이브러리를 설정합니다.

### 작은 프로그램에서 시작하기

먼저 아래 프로그램을 실행해 보세요. 아직 외부 라이브러리는 필요하지 않습니다.

@code example.cpp

이제 문자열을 편리하게 만드는 **fmt** 라이브러리를 써 봅시다. 편집기에 예제를 연 뒤 아래 코드로 바꿉니다.

```cpp
//@ {
//@     "libraries": ["fmt"]
//@ }

#include <fmt/format.h>

void small_main()
{
    print(fmt::format("Hello, {}!", "Small C++").c_str());
}
```

**Tools → Libraries…**에서 `fmt`를 검색하고 Use를 체크한 뒤 OK를 누르는 방법도 있습니다. 선택은 설정만 저장합니다. **Run**을 눌렀을 때 없는 패키지의 설치를 확인합니다. 동의하면 Library Console에 설치 과정이 나오고, 설치가 끝나면 빌드합니다. 이미 설치되어 있으면 바로 사용합니다. 인터넷이 필요한 것은 설치할 때입니다.

`#include <fmt/format.h>`와 함수 호출은 C++ 코드입니다. 맨 앞의 `//@` 줄은 컴파일러에게는 일반 주석이며, Small IDE가 빌드 설정으로 읽습니다.

### 라이브러리와 패키지

라이브러리는 프로그램에서 사용하는 코드입니다. 패키지는 파일을 설치하고 관리하는 단위입니다. Libraries의 Library 열은 pkg-config 모듈 이름이고, Package 열은 이를 제공하는 MSYS2 패키지 이름입니다. 한 패키지가 여러 모듈을 제공할 수도 있습니다.

**Update List**는 선택 가능한 목록만 갱신합니다. 패키지를 설치하거나 업그레이드하지 않습니다.

## 라이브러리 설정은 어디에 저장될까?

### 한 파일과 프로젝트

아래 기본 프로그램을 저장하고 Tools → Libraries…에서 fmt를 선택하세요. 편집기 맨 앞에 `//@` 설정이 추가됩니다.

@code library_settings_example.cpp

```cpp
//@ {
//@     "libraries": ["fmt"]
//@ }

#include <fmt/format.h>

void small_main()
{
    print(fmt::format("Hello, {}!", "Small C++").c_str());
}
```

**한 파일 모드에서만** 파일 처음의 연속된 `//@` 줄을 읽습니다. 빈 줄이나 일반 줄이 나오면 설정 블록이 끝납니다. 코드 중간의 `//@`는 일반 주석입니다. 이 규칙은 Small IDE의 규칙입니다.

### 프로젝트에서는 small.project

프로젝트를 열고 Libraries에서 선택하면 프로젝트 폴더의 `small.project`에 저장됩니다. 예를 들면 다음과 같습니다.

```json
{
    "version": 1,
    "libraries": ["fmt"]
}
```

기존 파일이 있으면 다른 옵션을 지우지 말고 libraries만 수정하세요. 프로젝트에서는 각 cpp의 `//@` 설정을 무시하고 **small.project 하나의 설정**을 사용합니다. libraries에는 `fmt` 같은 모듈 이름을 넣으며 긴 pacman 패키지 이름을 넣지 않습니다.

설정은 필요한 것을 선언할 뿐입니다. 다른 컴퓨터에서 열어 빌드할 때도 설치 여부를 확인합니다. cpp 하나를 보낼 때는 맨 앞의 설정을, 프로젝트를 보낼 때는 small.project를 함께 보냅니다.

## 연습 — 인사할 대상 바꾸기

기본 예제를 연 뒤 fmt 예제로 바꾸고, 인사할 대상을 `friend`로 바꿔 실행하세요. 아래 해답은 같은 출력의 기본 C++ 버전입니다. fmt 버전에서는 문자열 전체 대신 format의 두 번째 인자를 바꾸세요.

@exercise exercise_starter.cpp

### Hint

fmt 예제의 `"Small C++"`을 `"friend"`로 바꾸세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## 연습 — 선언과 설치 구분하기

기본 프로그램을 열고 Libraries에서 fmt를 선택하세요. OK 후 추가된 주석을 확인하고, 다시 Libraries에서 체크를 해제해 보세요. 선택 해제는 설정을 바꾸며 설치된 패키지를 삭제하지 않습니다. 아래 해답 프로그램은 라이브러리 없이 같은 인사를 출력합니다.

@exercise library_settings_exercise_starter.cpp

### Hint

체크 여부는 이 프로그램이 사용할 라이브러리이고, Installed는 실제 환경에 설치되어 있는지입니다.

@solution library_settings_exercise_solution.cpp
