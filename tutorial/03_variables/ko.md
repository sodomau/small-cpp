---
title: 변수와 상수
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 변수와 상수
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 값에 이름 붙이기

### 이번에 배울 것

**변수**는 값을 저장해 두는, 이름이 붙은 공간입니다. 점수를 score라는 이름으로 기억해 봅시다.

### 실행해 보기

@code example.cpp

`int score = 10;`은 score라는 변수를 만들고 처음 값 10을 넣습니다. **int는 정수 타입**입니다. 타입은 저장할 값의 종류이고, 정수는 0, 10, -3처럼 소수 부분이 없는 수입니다.

변수를 만드는 것을 **선언**, 처음 값을 넣는 것을 **초기화**라고 합니다. 이번에는 항상 값을 넣으며 만드세요. `print(score);`는 score라는 글자가 아니라 저장된 값을 출력합니다.

예상 출력:

```text
10
```

## 저장한 값 바꾸기

### 이번에 배울 것

변수의 이름은 그대로 두고, 그 안의 값만 바꿀 수 있습니다. 새 값을 저장하는 일을 **대입**이라고 합니다.

### 실행해 보기

@code assignment_example.cpp

`score = 20;`을 실행하면 이전 값 10 대신 20이 저장됩니다. 이미 만든 변수이므로 int를 다시 쓰지 않습니다. `=`는 오른쪽 값을 왼쪽 변수에 넣는다는 뜻입니다.

예상 출력:

```text
10
20
```

## 기억한 값으로 계산하기

### 이번에 배울 것

변수에 저장한 값도 계산에 사용할 수 있습니다. 계산한 결과를 다시 저장하면 점수를 올릴 수 있습니다.

### 실행해 보기

@code update_example.cpp

`score = score + 5;`는 ① 현재 값 10을 읽고 ② 5를 더하고 ③ 결과 15를 score에 저장합니다. 수학의 등식처럼 양쪽이 같다는 뜻이 아닙니다.

`print(score + 5);`만 실행하면 계산 결과를 보여 줄 뿐, score 자체는 바뀌지 않습니다.

예상 출력:

```text
15
```

## 소수 부분이 있는 값 저장하기

### 이번에 배울 것

길이나 시간에는 소수 부분이 필요합니다. **double**은 이런 수를 표현하는 타입입니다. 정수 개수를 셀 때는 int, 소수 부분이 필요한 값에는 double을 선택합니다.

### 실행해 보기

@code double_example.cpp

변수의 타입은 만들 때 정합니다. int 변수에 나중에 소수를 넣는다고 double 변수로 변하지는 않습니다.

double도 모든 수를 무한히 정확하게 저장하지는 못하지만, 지금은 간단한 길이와 시간부터 다룹니다.

예상 출력:

```text
1.45
```

## 바꾸지 않을 값에 이름 붙이기

### 이번에 배울 것

**const**는 처음 정한 값을 이후에 바꾸지 않겠다는 표시입니다. 게임의 목표 점수처럼 일정한 값에 이름을 붙일 때 사용합니다.

### 실행해 보기

@code constants_example.cpp

goal_score에 나중에 다른 값을 넣으면 컴파일 오류입니다.

이 과정에서는 이름을 영문자로 시작하고 영문자·숫자·밑줄로 만드세요. 공백은 넣지 않습니다. score와 Score는 다르고 int, if 같은 C++ 예약어는 이름으로 사용할 수 없습니다.

예상 출력:

```text
20
```

## 값을 바꾸는 짧은 표기

### 이번에 배울 것

자주 쓰는 계산과 대입을 짧게 쓸 수 있습니다. int나 double에서 `score += 5;`는 `score = score + 5;`와 같은 갱신입니다.

### 실행해 보기

@code short_updates_example.cpp

`++`는 1 증가, `--`는 1 감소입니다. 처음에는 예제처럼 독립된 문장으로 사용하세요. `-=`, `*=`, `/=`도 같은 방식입니다. 정수에는 `%=`도 씁니다. 정수의 /=는 여전히 정수 나눗셈입니다.

예상 출력:

```text
14
```

## Exercise — 한 가지 바꾸기

age라는 int 변수에 10을 저장하고 출력하세요.

@exercise exercise_starter.cpp

### Hint

score 대신 age라는 이름을 사용하세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

점수를 처음에는 3으로, 그다음에는 8로 바꾸어 각각 출력하세요.

@exercise assignment_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution assignment_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

남은 기회 lives를 3으로 만들고, 1을 줄인 뒤 출력하세요.

@exercise update_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution update_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

달리기 시간 12.5를 seconds라는 변수에 저장하고 출력하세요.

@exercise double_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution double_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

목표를 200으로 정하고 현재 점수 80에서 얼마나 더 필요한지 출력하세요.

@exercise constants_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution constants_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

점수를 10으로 시작하고 두 배로 만든 뒤 1 늘려 출력하세요.

@exercise short_updates_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution short_updates_exercise_solution.cpp
