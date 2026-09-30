---
title: Binary Files
part: files
part-title: Part IV — Saving and Loading
goal: int와 double을 native binary representation 그대로 저장하고 다시 읽습니다.
related-example: reference/file
---

## 숫자를 글자로 바꾸지 않고 저장한다면
Text file에 123을 쓰면 파일에는 문자 `'1'`, `'2'`, `'3'`이 들어갑니다. Binary file에서는 int가 메모리에서 사용하는 **native C++ representation**을 그대로 저장할 수 있습니다.

Small에서는 `WriteInt`, `WriteReal`, `ReadInt`, `ReadReal`만 제공해 binary I/O를 일부러 단순하게 유지합니다.

## 먼저 실행해 보세요

@code example1.cpp

## 읽는 순서는 쓰는 순서와 같아야 합니다
binary file에는 줄이나 `Score:` 같은 설명이 없습니다. 프로그램이 어떤 값이 어떤 순서로 저장됐는지 알고 있어야 합니다.

위에서 int, int, double 순으로 썼다면 읽을 때도 같은 순서로 `ReadInt`, `ReadInt`, `ReadReal`을 호출합니다.

이 방식은 일부러 native representation을 사용합니다. 즉 C++의 int와 double이 현재 컴퓨터에서 사용하는 byte 표현을 그대로 기록합니다. 지금은 **내 프로그램의 간단한 save file** 정도로 생각하면 충분합니다.

## 조금 바꾸어 보기

@code example2.cpp

## binary가 항상 더 좋은 것은 아닙니다
Text file은 사람이 직접 읽고 고치기 쉽고 다른 프로그램과도 다루기 편합니다. Binary file은 값의 표현을 그대로 저장하는 경험을 주고 compact한 save data를 만들기 쉽지만, 사람이 열어 봐도 의미를 알아보기 어렵습니다.

파일 형식의 호환성, byte order, 버전 관리 같은 문제는 더 큰 프로그램에서 중요해집니다. 이 tutorial에서는 binary representation이 실제 byte로 저장된다는 사실까지만 경험합니다.

이제 다시 C++ 자체로 돌아가, 관련된 데이터를 하나의 새로운 type으로 묶는 방법을 배웁니다.

`FileMode::AppendBinary`를 사용하면 기존 binary file의 끝에 새 binary 값을 추가할 수 있습니다. `WriteBinary`는 기존 내용을 지우고 새로 쓰지만, `AppendBinary`는 기존 byte를 유지합니다.

## Exercise — 게임 상태 저장

`game.dat`에 level=5, score=2300, playTime=18.75를 binary로 저장하세요.

@exercise exercise1_starter.cpp

### Hint

WriteBinary mode에서 WriteInt 두 번, WriteReal 한 번을 사용하세요.

@solution exercise1_solution.cpp

## Exercise — 저장하고 복원하기

`state.dat`에 int 7과 double 3.5를 저장하고, 다시 열어 두 값을 읽어 출력하세요.

@exercise exercise2_starter.cpp

### Hint

쓰기와 읽기 사이에 Close하고, 읽을 때 같은 타입과 순서를 사용하세요.

@solution exercise2_solution.cpp
