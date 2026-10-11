---
title: 표준 문자열과 배열 사용하기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 표준 문자열과 배열 사용하기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 표준 문자열과 배열 만나기

### 이번에 배울 것

**컨테이너**는 여러 값을 담는 도구입니다. std::string과 std::vector는 익숙한 문자열·배열에 대응하는 표준 도구입니다.

### 실행해 보기

@code example1.cpp

길이를 묻는 이름이 length() 대신 size()입니다. 예제는 Hello, Characters: 5, Numbers: 4, First number: 3을 출력합니다.

대괄호의 위치는 여전히 0부터입니다. 표준 컨테이너의 []는 Small처럼 범위 오류를 알려 준다고 기대하면 안 됩니다.

## 원소를 추가하고 하나씩 읽기

### 이번에 배울 것

std::vector는 원소를 뒤에 추가할 수 있습니다. **범위 기반 for**는 컨테이너의 원소를 하나씩 꺼내 반복합니다.

### 실행해 보기

@code standard_containers_2_example2.cpp

push_back(40)은 뒤에 40을 붙입니다. `for (int value : numbers)`는 각 원소 값을 value로 받아 합산합니다. 결과는 Sum: 100입니다.

이 형태의 value는 복사한 정수이므로 value를 바꿔도 배열 원소가 바뀌지 않습니다. size()의 타입은 int와 다를 수 있어 큰 크기를 다룰 때는 타입도 확인해야 합니다.

## Exercise — vector에 값 추가

`std::vector<int>`에 5, 10을 넣어 만들고 `push_back(15)`로 하나 더 추가한 뒤 모두 출력하세요.

@exercise exercise1_starter.cpp

### Hint

range-based for를 쓰면 `for (int value : numbers)`로 모든 값을 볼 수 있습니다.

@solution exercise1_solution.cpp

## 더 해 보기 (선택)

## Exercise — std::string 함수

`const std::string&`을 받아 길이를 돌려주는 `text_length` 함수를 만들고 "Small"의 길이를 출력하세요.

@exercise standard_containers_2_exercise2_starter.cpp

### Hint

`text.size()`는 표준 C++의 unsigned 크기 type을 돌려줍니다. 이 연습의 return type은 int이므로 `static_cast<int>(text.size())`로 명시적으로 바꾸어 반환하세요.

@solution standard_containers_2_exercise2_solution.cpp
