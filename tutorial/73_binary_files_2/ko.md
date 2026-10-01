---
title: 쓴 순서대로 바이너리 읽기
part: files
part-title: 작은 걸음 IV — 저장하고 불러오기
goal: 쓴 순서대로 바이너리 읽기
related-example: reference/file
---

## 이번에 배울 것

바이너리 데이터는 **쓴 타입과 같은 순서**로 읽어야 원래 값을 복원할 수 있습니다.

## 실행해 보기

@code example2.cpp

앞 수업으로 save.dat를 만든 뒤 같은 소스 폴더에서 실행하세요. ReadInt, ReadInt, ReadReal로 읽어 3, 1250, 42.5를 복원합니다.

바이너리가 언제나 더 좋은 것은 아닙니다. 사람이 확인하거나 오래 교환할 데이터에는 형식과 호환성을 따로 설계해야 합니다.

## Exercise — 저장하고 복원하기

`state.dat`에 int 7과 double 3.5를 저장하고, 다시 열어 두 값을 읽어 출력하세요.

@exercise exercise2_starter.cpp

### Hint

쓰기와 읽기 사이에 Close하고, 읽을 때 같은 타입과 순서를 사용하세요.

@solution exercise2_solution.cpp
