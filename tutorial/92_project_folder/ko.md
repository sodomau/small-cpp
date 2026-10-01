---
title: 폴더 하나가 프로젝트
part: projects
part-title: 작은 걸음 VIII — 여러 파일로 프로그램 만들기
goal: 프로젝트를 만들고 전체 프로그램을 실행합니다.
related-example: reference/console
---

## 코드가 길어졌다면

한 파일로 충분하면 그대로 써도 됩니다. 함수가 많아져서 역할별로 나누고 싶을 때 프로젝트를 사용하세요. **폴더 하나가 프로젝트 하나**입니다.

## 첫 프로젝트 만들기

1. **File → New Project…**를 누릅니다.
2. 프로젝트를 둘 위치를 고르고 이름을 `Greeting`으로 입력합니다.
3. 만들어진 `main.cpp`의 내용을 아래 코드로 바꾸고 저장합니다.

@code example.cpp

**Run Project**를 누르면 `Hello, project!`가 나옵니다. 왼쪽 PROJECT 아래의 이름은 폴더 이름입니다. 창 제목과 아래 상태 표시줄에서도 프로젝트를 확인할 수 있습니다.

이미 폴더가 있다면 **File → Open Project (Folder)…**에서 그 폴더 안으로 들어간 뒤 **Open This Folder**를 누르세요. `small.project`가 없어도 열립니다.

## 탭과 프로젝트는 다릅니다

탭은 지금 읽고 고치는 파일입니다. Run Project는 선택한 탭 하나가 아니라 프로젝트의 모든 포함된 `.cpp`를 함께 사용합니다. 탭을 닫아도 파일은 프로젝트에 남습니다. 다른 폴더의 파일을 열면 탭에 **[Outside Project]**가 표시되고 프로젝트 실행에는 들어가지 않습니다.

**File → Close Project**는 프로젝트를 닫습니다. 파일을 삭제하지는 않습니다.

## 연습 — 직접 확인하기

메시지를 바꾸고 저장하세요. 프로젝트를 닫았다가 같은 폴더를 다시 열어 실행해 보세요.

@exercise exercise_starter.cpp

### Hint

위에서 설명한 메뉴를 이용하세요. 아래 코드는 한 파일 연습의 답안입니다. 프로젝트에서는 해당 역할의 파일에 같은 변경을 적용하세요.

@solution exercise_solution.cpp
