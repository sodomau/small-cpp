---
title: 텍스트 파일 읽고 쓰기
part: files
part-title: 작은 걸음 IV — 저장하고 불러오기
goal: 텍스트 파일 읽고 쓰기
related-example: reference/file
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 실행이 끝나도 값 남기기

### 이번에 배울 것

**파일**은 프로그램이 끝난 뒤에도 저장 장치에 남겨 둘 수 있는 데이터입니다. 텍스트 파일은 글자로 기록해 메모장으로 읽을 수 있습니다.

### 실행해 보기

@code example1.cpp

소스를 저장한 뒤 실행하세요. score.txt에 Alex와 1200을 한 줄씩 기록합니다. FileMode::Write는 새로 쓰는 모드라서 기존 내용을 지웁니다. 직접 만든 연습 파일을 쓰세요.

Open → 쓰기 → Close 순서입니다. 상대 경로의 파일은 보통 저장한 소스 폴더에 생깁니다. 메모장으로 열어 두 줄을 확인하세요.

## 파일에서 값 다시 읽기

### 이번에 배울 것

저장했던 파일을 열면 이전 실행의 값을 되찾을 수 있습니다. **경로**는 어느 위치의 파일을 사용할지 나타냅니다.

### 실행해 보기

@code text_files_2_example2.cpp

먼저 앞 수업 예제로 score.txt를 만드세요. 이번 소스도 같은 폴더에 저장해야 같은 파일을 읽습니다.

open의 기본 모드는 읽기입니다. input은 첫 줄을 문자열로, input_int는 둘째 줄을 정수로 읽습니다. Alex's score: 1200이 나오는지 보세요. 오류가 나면 파일 위치와 줄 내용을 확인하세요.

## Exercise — 이름과 나이 저장

`profile.txt`에 이름 한 줄과 나이 한 줄을 저장한 뒤 닫으세요.

@exercise exercise1_starter.cpp

### Hint

Write mode로 열고 `file.print`를 두 번 사용하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — high score 저장하고 읽기

`highscore.txt`에 950을 저장한 뒤 다시 열어 int로 읽고 출력하세요.

@exercise text_files_2_exercise2_starter.cpp

### Hint

Write/`close` 후 다시 open하고 `input_int()`를 사용하세요.

@solution text_files_2_exercise2_solution.cpp
