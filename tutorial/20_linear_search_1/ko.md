---
title: 원하는 값 찾기
part: algorithms
part-title: 작은 걸음 III — 프로그램으로 생각하기
goal: 원하는 값 찾기
related-example: reference/array
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 원하는 값 찾아보기

### 이번에 배울 것

**검색**은 원하는 값이 있는지, 있다면 어디 있는지 찾는 일입니다. 처음부터 하나씩 비교하는 방법을 순차 검색이라고 합니다.

### 실행해 보기

@code example1.cpp

9는 위치 2에 있으므로 Index: 2가 나옵니다. 찾으면 return으로 위치를 돌려주며 함수 전체를 끝냅니다.

끝까지 못 찾으면 -1을 돌려줍니다. 유효한 위치는 0 이상이므로 -1을 못 찾았다는 표시로 정했습니다.

## 못 찾은 경우도 처리하기

### 이번에 배울 것

검색 결과에는 성공과 실패가 모두 있습니다. 프로그램은 두 경우를 구분해 안내해야 합니다.

### 실행해 보기

@code linear_search_2_example2.cpp

콘솔에 9를 입력하면 Found at 2, 8을 입력하면 Not found가 나옵니다.

이번에는 break로 검색 반복만 끝내고, 뒤의 if에서 결과를 출력합니다. return으로 함수 전체를 끝내는 것과 구분하세요.

## Exercise — 마지막 위치 찾기

같은 값이 여러 번 있을 때 마지막으로 나타나는 index를 찾으세요. 없으면 -1을 출력하세요.

@exercise exercise1_starter.cpp

### Hint

찾았다고 바로 return하지 말고 index를 갱신하며 끝까지 보세요.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — 문자 찾기

String에서 문자 'a'가 처음 나타나는 위치를 linear search처럼 찾아 출력하세요. 없으면 -1입니다.

@exercise linear_search_2_exercise2_starter.cpp

### Hint

String도 length와 []를 사용할 수 있으므로 Array 검색과 거의 같습니다.

@solution linear_search_2_exercise2_solution.cpp
