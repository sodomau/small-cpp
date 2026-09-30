---
title: 못 찾은 경우도 처리하기
part: algorithms
part-title: Part III — Thinking with Programs
goal: 못 찾은 경우도 처리하기
related-example: reference/array
---

## 이번에 배울 것

검색 결과에는 성공과 실패가 모두 있습니다. 프로그램은 두 경우를 구분해 안내해야 합니다.

## 실행해 보기

@code example2.cpp

콘솔에 9를 입력하면 Found at 2, 8을 입력하면 Not found가 나옵니다.

이번에는 break로 검색 반복만 끝내고, 뒤의 if에서 결과를 출력합니다. return으로 함수 전체를 끝내는 것과 구분하세요.

## Exercise — 문자 찾기

String에서 문자 'a'가 처음 나타나는 위치를 linear search처럼 찾아 출력하세요. 없으면 -1입니다.

@exercise exercise2_starter.cpp

### Hint

String도 Length와 []를 사용할 수 있으므로 Array 검색과 거의 같습니다.

@solution exercise2_solution.cpp
