---
title: Text Files
part: files
part-title: Part IV — Saving and Loading
goal: Text file에 값을 저장하고 다시 읽어 프로그램 실행 사이에 데이터를 남깁니다.
related-example: reference/file
---

## 프로그램을 꺼도 기억하게 하기
지금까지 변수의 값은 프로그램이 끝나면 사라졌습니다. 게임의 high score처럼 다음 실행에서도 기억해야 하는 값은 **파일**에 저장할 수 있습니다.

먼저 사람이 메모장으로도 읽을 수 있는 text file을 만들어 봅시다.

## 먼저 실행해 보세요

@code example1.cpp

## Open → 사용 → Close
`FileMode::Write`로 열면 새로 쓰기 위해 기존 내용을 지우고 시작합니다. `Print`는 값을 쓰고 줄을 바꾸며 `Write`는 줄을 바꾸지 않습니다.

읽을 때는 기본 mode가 Read이므로 `file.Open("score.txt");`만 써도 됩니다. `Input`, `InputInt`, `InputReal`로 한 줄의 String, int, double을 읽을 수 있습니다.

File은 scope가 끝날 때 자동으로 닫히기도 하지만, 처음에는 **Open한 파일을 Close한다**는 흐름을 명시적으로 익힙니다.

## 조금 바꾸어 보기

@code example2.cpp

## 파일은 어디에 생길까요?
소스 파일을 저장한 뒤 Run하면 상대 경로의 파일은 보통 그 소스가 있는 폴더에 만들어집니다. 내장 Example을 그대로 실행하면 임시 실행 폴더를 사용하므로 파일을 남기고 싶다면 **Try → 소스 저장 → Run** 순서가 좋습니다.

`Append` mode를 사용하면 기존 내용을 지우지 않고 끝에 새 내용을 추가할 수도 있습니다.

## Exercise — 이름과 나이 저장

`profile.txt`에 이름 한 줄과 나이 한 줄을 저장한 뒤 닫으세요.

@exercise exercise1_starter.cpp

### Hint

Write mode로 열고 `file.Print`를 두 번 사용하세요.

@solution exercise1_solution.cpp

## Exercise — high score 저장하고 읽기

`highscore.txt`에 950을 저장한 뒤 다시 열어 int로 읽고 출력하세요.

@exercise exercise2_starter.cpp

### Hint

Write/Close 후 다시 Open하고 `InputInt()`를 사용하세요.

@solution exercise2_solution.cpp
