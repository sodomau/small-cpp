---
title: 숫자를 바이너리로 저장하기
part: files
part-title: 작은 걸음 IV — 저장하고 불러오기
goal: 숫자를 바이너리로 저장하기
related-example: reference/file
---

## 이번에 배울 것

**바이너리 파일**은 정한 바이트 형식대로 값을 기록합니다. 숫자를 읽을 수 있는 글자로 바꾸어 저장하는 텍스트 파일과 구분합니다.

## 실행해 보기

@code example1.cpp

WriteBinary로 열고 정수 두 개, 실수 한 개를 순서대로 씁니다. save.dat는 메모장으로 읽기 좋은 문장이 아닙니다.

읽을 때 사용할 값의 타입과 순서를 기억해야 합니다. 이 모드도 기존 파일을 지우므로 연습 파일로 실행하세요.

## Exercise — 게임 상태 저장

`game.dat`에 level=5, score=2300, play_time=18.75를 binary로 저장하세요.

@exercise exercise1_starter.cpp

### Hint

WriteBinary mode에서 write_int 두 번, write_real 한 번을 사용하세요.

@solution exercise1_solution.cpp

