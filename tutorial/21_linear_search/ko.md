---
title: Linear Search
part: algorithms
part-title: Part III — Thinking with Programs
goal: 앞에서부터 하나씩 비교하는 linear search를 함수로 만듭니다.
related-example: reference/array
---

## 원하는 값은 어디에 있을까요?
가장 단순한 검색은 첫 번째 값부터 차례대로 확인하는 것입니다. 찾으면 그 위치를 즉시 `return`할 수 있습니다.

## 먼저 실행해 보세요

@code example1.cpp

## 못 찾았다는 것도 결과입니다
올바른 index는 0 이상이므로 `-1`을 **찾지 못함**의 표시로 사용할 수 있습니다. 이런 특별한 값을 sentinel이라고 부르기도 합니다.

Linear search는 데이터가 어떤 순서인지 몰라도 사용할 수 있다는 장점이 있습니다.

## 조금 바꾸어 보기

@code example2.cpp

## 검색 비용은 어디에 있나요?
찾는 값이 마지막에 있거나 아예 없다면 모든 값을 확인해야 합니다. Array가 1,000개라면 최대 1,000번 비교할 수 있습니다. 이 사실은 정렬된 데이터에서 더 빠른 검색을 생각하는 출발점이 됩니다.

## Exercise — 마지막 위치 찾기

같은 값이 여러 번 있을 때 마지막으로 나타나는 index를 찾으세요. 없으면 -1을 출력하세요.

@exercise exercise1_starter.cpp

### Hint

찾았다고 바로 return하지 말고 index를 갱신하며 끝까지 보세요.

@solution exercise1_solution.cpp

## Exercise — 문자 찾기

String에서 문자 'a'가 처음 나타나는 위치를 linear search처럼 찾아 출력하세요. 없으면 -1입니다.

@exercise exercise2_starter.cpp

### Hint

String도 Length와 []를 사용할 수 있으므로 Array 검색과 거의 같습니다.

@solution exercise2_solution.cpp
