---
title: 원하는 값 찾아보기
part: algorithms
part-title: Part III — 프로그램으로 생각하기
goal: 원하는 값 찾아보기
related-example: reference/array
---

## 이번에 배울 것

**검색**은 원하는 값이 있는지, 있다면 어디 있는지 찾는 일입니다. 처음부터 하나씩 비교하는 방법을 순차 검색이라고 합니다.

## 실행해 보기

@code example1.cpp

9는 위치 2에 있으므로 Index: 2가 나옵니다. 찾으면 return으로 위치를 돌려주며 함수 전체를 끝냅니다.

끝까지 못 찾으면 -1을 돌려줍니다. 유효한 위치는 0 이상이므로 -1을 못 찾았다는 표시로 정했습니다.

## Exercise — 마지막 위치 찾기

같은 값이 여러 번 있을 때 마지막으로 나타나는 index를 찾으세요. 없으면 -1을 출력하세요.

@exercise exercise1_starter.cpp

### Hint

찾았다고 바로 return하지 말고 index를 갱신하며 끝까지 보세요.

@solution exercise1_solution.cpp

