---
title: 내가 만든 일에 이름 붙이기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: greet를 세 번 호출해 보세요.
related-example: reference/console
---

## 이번에 배울 것

**함수**는 할 일을 묶어 이름 붙인 것입니다. print를 사용했듯, 이번에는 greet라는 함수를 직접 만듭니다.

## 실행해 보기

@code example.cpp

위쪽은 greet가 할 일을 정하는 **정의**, 아래의 `greet();`는 실제로 시키는 **호출**입니다. 정의만으로 실행되지는 않습니다. small_main에서 호출하면 greet로 갔다가 끝난 뒤 돌아옵니다.

**void**는 호출한 쪽에 결과값을 돌려주지 않는다는 뜻입니다. 화면 출력은 할 수 있습니다. 빈 ()는 전달받는 값이 없다는 뜻입니다.

예상 출력:

```text
Hello!
Hello!
```

## Exercise — 한 가지 바꾸기

greet를 세 번 호출해 보세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp
