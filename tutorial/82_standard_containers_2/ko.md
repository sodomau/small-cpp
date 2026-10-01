---
title: 원소를 추가하고 하나씩 읽기
part: cpp
part-title: 작은 걸음 VI — C++로 성장하기
goal: 원소를 추가하고 하나씩 읽기
related-example: reference/console
---

## 이번에 배울 것

std::vector는 원소를 뒤에 추가할 수 있습니다. **범위 기반 for**는 컨테이너의 원소를 하나씩 꺼내 반복합니다.

## 실행해 보기

@code example2.cpp

push_back(40)은 뒤에 40을 붙입니다. `for (int value : numbers)`는 각 원소 값을 value로 받아 합산합니다. 결과는 Sum: 100입니다.

이 형태의 value는 복사한 정수이므로 value를 바꿔도 배열 원소가 바뀌지 않습니다. size()의 타입은 int와 다를 수 있어 큰 크기를 다룰 때는 타입도 확인해야 합니다.

## Exercise — std::string 함수

`const std::string&`을 받아 길이를 돌려주는 `TextLength` 함수를 만들고 "Small"의 길이를 출력하세요.

@exercise exercise2_starter.cpp

### Hint

`text.size()`는 표준 C++의 unsigned 크기 type을 돌려줍니다. 이 연습의 return type은 int이므로 `static_cast<int>(text.size())`로 명시적으로 바꾸어 반환하세요.

@solution exercise2_solution.cpp
