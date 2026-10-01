---
title: 실행이 끝나도 값 남기기
part: files
part-title: 작은 걸음 IV — 저장하고 불러오기
goal: 실행이 끝나도 값 남기기
related-example: reference/file
---

## 이번에 배울 것

**파일**은 프로그램이 끝난 뒤에도 저장 장치에 남겨 둘 수 있는 데이터입니다. 텍스트 파일은 글자로 기록해 메모장으로 읽을 수 있습니다.

## 실행해 보기

@code example1.cpp

소스를 저장한 뒤 실행하세요. score.txt에 Alex와 1200을 한 줄씩 기록합니다. FileMode::Write는 새로 쓰는 모드라서 기존 내용을 지웁니다. 직접 만든 연습 파일을 쓰세요.

Open → 쓰기 → Close 순서입니다. 상대 경로의 파일은 보통 저장한 소스 폴더에 생깁니다. 메모장으로 열어 두 줄을 확인하세요.

## Exercise — 이름과 나이 저장

`profile.txt`에 이름 한 줄과 나이 한 줄을 저장한 뒤 닫으세요.

@exercise exercise1_starter.cpp

### Hint

Write mode로 열고 `file.Print`를 두 번 사용하세요.

@solution exercise1_solution.cpp

