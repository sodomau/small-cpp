---
title: 표준 문자열과 배열 만나기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 표준 문자열과 배열 만나기
related-example: reference/console
---

## 이번에 배울 것

**컨테이너**는 여러 값을 담는 도구입니다. std::string과 std::vector는 익숙한 문자열·배열에 대응하는 표준 도구입니다.

## 실행해 보기

@code example1.cpp

길이를 묻는 이름이 length() 대신 size()입니다. 예제는 Hello, Characters: 5, Numbers: 4, First number: 3을 출력합니다.

대괄호의 위치는 여전히 0부터입니다. 표준 컨테이너의 []는 Small처럼 범위 오류를 알려 준다고 기대하면 안 됩니다.

## Exercise — vector에 값 추가

`std::vector<int>`에 5, 10을 넣어 만들고 `push_back(15)`로 하나 더 추가한 뒤 모두 출력하세요.

@exercise exercise1_starter.cpp

### Hint

range-based for를 쓰면 `for (int value : numbers)`로 모든 값을 볼 수 있습니다.

@solution exercise1_solution.cpp

