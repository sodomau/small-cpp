---
title: 바이너리 파일 읽고 쓰기
part: files
part-title: 작은 걸음 IV — 저장하고 불러오기
goal: 바이너리 파일 읽고 쓰기
related-example: reference/file
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 숫자를 바이너리로 저장하기

### 이번에 배울 것

**바이너리 파일**은 정한 바이트 형식대로 값을 기록합니다. 숫자를 읽을 수 있는 글자로 바꾸어 저장하는 텍스트 파일과 구분합니다.

### 실행해 보기

@code example1.cpp

WriteBinary로 열고 정수 두 개, 실수 한 개를 순서대로 씁니다. save.dat는 메모장으로 읽기 좋은 문장이 아닙니다.

읽을 때 사용할 값의 타입과 순서를 기억해야 합니다. 이 모드도 기존 파일을 지우므로 연습 파일로 실행하세요.

## 쓴 순서대로 바이너리 읽기

### 이번에 배울 것

바이너리 데이터는 **쓴 타입과 같은 순서**로 읽어야 원래 값을 복원할 수 있습니다.

### 실행해 보기

@code binary_files_2_example2.cpp

앞 수업으로 save.dat를 만든 뒤 같은 소스 폴더에서 실행하세요. read_int, read_int, read_real로 읽어 3, 1250, 42.5를 복원합니다.

바이너리가 언제나 더 좋은 것은 아닙니다. 사람이 확인하거나 오래 교환할 데이터에는 형식과 호환성을 따로 설계해야 합니다.

## Exercise — 게임 상태 저장

`game.dat`에 level=5, score=2300, play_time=18.75를 binary로 저장하세요.

@exercise exercise1_starter.cpp

### Hint

WriteBinary mode에서 write_int 두 번, write_real 한 번을 사용하세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 저장하고 복원하기

`state.dat`에 int 7과 double 3.5를 저장하고, 다시 열어 두 값을 읽어 출력하세요.

@exercise binary_files_2_exercise2_starter.cpp

### Hint

쓰기와 읽기 사이에 close하고, 읽을 때 같은 타입과 순서를 사용하세요.

@solution binary_files_2_exercise2_solution.cpp
