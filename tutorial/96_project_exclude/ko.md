---
title: 잠시 사용하지 않을 파일
part: projects
part-title: 작은 걸음 VIII — 여러 파일로 프로그램 만들기
goal: 파일을 삭제하지 않고 빌드에서 제외합니다.
related-example: reference/console
---

## 시작점은 하나

프로젝트의 모든 포함된 `.cpp`는 하나의 프로그램으로 합쳐집니다. 예전 연습 파일에도 `small_main`이 있다면 시작점이 두 개가 되어 실행할 수 없습니다.

앞의 Greeting 프로젝트에 **New Source File…**로 `practice.cpp`를 만들고 아래 코드를 넣어 보세요.

@code example.cpp

Run Project를 누르면 시작 함수가 여러 개라는 안내가 나옵니다. `practice.cpp`를 우클릭하고 **Exclude from Project**를 고르세요. 회색 기울임 글씨와 `(Excluded)` 표시로 바뀌고, 이제 Greeting 프로그램을 실행할 수 있습니다.

## 제외와 삭제는 다릅니다

제외해도 파일은 디스크에 남고 열어서 읽을 수 있습니다. 탭에도 **[Excluded]**가 표시됩니다. **Include in Project**로 다시 포함하면 원래 표시로 돌아갑니다. 다시 포함한 뒤에는 시작점 충돌도 다시 생깁니다.

제외 정보는 IDE가 `small.project`에 저장합니다. 직접 작성할 필요는 없습니다. 프로젝트를 다시 열어도 제외가 유지됩니다.

다른 프로그램을 연습하려면 별도 프로젝트를 쓰는 것이 편합니다. 필요한 함수가 든 파일을 제외하면 그 함수를 찾지 못하는 링크 오류가 생길 수 있습니다.

## 연습 — 직접 확인하기

연습 파일의 메시지를 바꾸고 저장하세요. 프로젝트에서 제외하고 프로젝트를 닫았다가 다시 열어 보세요. 파일과 제외 표시가 모두 남아 있는지 확인하세요.

@exercise exercise_starter.cpp

### Hint

위에서 설명한 메뉴를 이용하세요. 아래 코드는 한 파일 연습의 답안입니다. 프로젝트에서는 해당 역할의 파일에 같은 변경을 적용하세요.

@solution exercise_solution.cpp
