---
title: 파일에서 값 다시 읽기
part: files
part-title: 작은 걸음 IV — 저장하고 불러오기
goal: 파일에서 값 다시 읽기
related-example: reference/file
---

## 이번에 배울 것

저장했던 파일을 열면 이전 실행의 값을 되찾을 수 있습니다. **경로**는 어느 위치의 파일을 사용할지 나타냅니다.

## 실행해 보기

@code example2.cpp

먼저 앞 수업 예제로 score.txt를 만드세요. 이번 소스도 같은 폴더에 저장해야 같은 파일을 읽습니다.

open의 기본 모드는 읽기입니다. input은 첫 줄을 문자열로, input_int는 둘째 줄을 정수로 읽습니다. Alex's score: 1200이 나오는지 보세요. 오류가 나면 파일 위치와 줄 내용을 확인하세요.

## Exercise — high score 저장하고 읽기

`highscore.txt`에 950을 저장한 뒤 다시 열어 int로 읽고 출력하세요.

@exercise exercise2_starter.cpp

### Hint

Write/`close` 후 다시 open하고 `input_int()`를 사용하세요.

@solution exercise2_solution.cpp
