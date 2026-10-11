---
title: 라이브러리 설정은 어디에 저장될까?
part: libraries
part-title: 작은 걸음 IX — 외부 라이브러리 사용하기
goal: 라이브러리 설정은 어디에 저장될까?
related-example: reference/console
---

## 한 파일과 프로젝트

아래 기본 프로그램을 저장하고 Tools → Libraries…에서 fmt를 선택하세요. 편집기 맨 앞에 `//@` 설정이 추가됩니다.

@code example.cpp

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

## 프로젝트에서는 small.project

프로젝트를 열고 Libraries에서 선택하면 프로젝트 폴더의 `small.project`에 저장됩니다. 예를 들면 다음과 같습니다.

```json
{
    "version": 1,
    "libraries": ["fmt"]
}
```

기존 파일이 있으면 다른 옵션을 지우지 말고 libraries만 수정하세요. 프로젝트에서는 각 cpp의 `//@` 설정을 무시하고 **small.project 하나의 설정**을 사용합니다. libraries에는 `fmt` 같은 모듈 이름을 넣으며 긴 pacman 패키지 이름을 넣지 않습니다.

설정은 필요한 것을 선언할 뿐입니다. 다른 컴퓨터에서 열어 빌드할 때도 설치 여부를 확인합니다. cpp 하나를 보낼 때는 맨 앞의 설정을, 프로젝트를 보낼 때는 small.project를 함께 보냅니다.

## 연습 — 선언과 설치 구분하기

기본 프로그램을 열고 Libraries에서 fmt를 선택하세요. OK 후 추가된 주석을 확인하고, 다시 Libraries에서 체크를 해제해 보세요. 선택 해제는 설정을 바꾸며 설치된 패키지를 삭제하지 않습니다. 아래 해답 프로그램은 라이브러리 없이 같은 인사를 출력합니다.

@exercise exercise_starter.cpp

### Hint

체크 여부는 이 프로그램이 사용할 라이브러리이고, Installed는 실제 환경에 설치되어 있는지입니다.

@solution exercise_solution.cpp
