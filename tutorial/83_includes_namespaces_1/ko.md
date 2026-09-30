---
title: 필요한 도구를 코드에 적기
part: cpp
part-title: Part VI — Growing into C++
goal: 필요한 도구를 코드에 적기
related-example: reference/console
---

## 이번에 배울 것

**헤더**는 다른 코드의 도구를 사용할 수 있도록 선언을 알려 주는 파일입니다. #include는 그 헤더를 포함하는 지시문입니다.

## 실행해 보기

@code example1.cpp

iostream은 표준 입출력, string은 std::string을 위해 포함합니다. std::cout << 값은 출력, std::getline(std::cin, name)은 한 줄 입력입니다. Alex를 넣으면 Hello, Alex가 나옵니다.

이번에는 SmallMain을 유지하며 입출력 도구만 바꿉니다.

## Exercise — std::cout 사용하기

`#include <iostream>`을 적고 `std::cout`으로 `Hello C++`과 줄바꿈을 출력하세요. `SmallMain()`은 아직 그대로 사용합니다.

@exercise exercise1_starter.cpp

### Hint

`std::cout << "Hello C++" << "\n";`처럼 값을 output stream으로 보낼 수 있습니다.

@solution exercise1_solution.cpp

