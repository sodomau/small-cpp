---
title: 문자열 다루기
part: basics
part-title: 작은 걸음 I — 글자와 숫자로 만들기
goal: 문자열 다루기
related-example: reference/console
---

한 주제 안에서 차근차근 배워 봅니다. 예제를 하나씩 실행하고, 중간에 쉬었다가 이어서 해도 좋습니다. 마지막의 추가 연습은 원하는 만큼 해 보세요.

## 문자열도 저장하기

### 이번에 배울 것

이름이나 문장도 변수에 저장할 수 있습니다. **문자열**은 값의 종류이고, **String**은 Small에서 문자열을 저장할 때 쓰는 타입 이름입니다.

### 실행해 보기

@code example.cpp

`print("Hello, ", name);`은 인사말과 name의 값을 이어 출력합니다. 쉼표가 화면에 나오거나 공백이 자동으로 생기지는 않습니다. 필요한 공백은 큰따옴표 안에 넣습니다.

`"123"`은 글자로 된 문자열입니다. 숫자 계산에 쓰는 정수 123과는 종류가 다릅니다.

예상 출력:

```text
Hello, Alex
```

## 문자열 이어 붙이기

### 이번에 배울 것

String 값에 쓰는 `+`는 숫자 덧셈 대신 **이어 붙이기**를 합니다. 이어 붙인 결과도 String 값입니다.

### 실행해 보기

@code string_join_example.cpp

`text.length()`는 text의 길이를 돌려주는 기능입니다. 점은 text에 속한 기능을 사용한다는 뜻입니다. 여기에는 공백도 포함됩니다.

길이는 **바이트**라는 데이터 크기 단위로 셉니다. 이번 영문 예제에서는 한 글자가 한 바이트입니다. UTF-8 한글 한 글자는 여러 바이트라서 글자 수와 다를 수 있습니다.

예상 출력:

```text
Small C++
9
```

## 문자 하나 꺼내 보기

### 이번에 배울 것

**문자**는 글자나 기호 하나입니다. **char**는 문자 값을 담을 때 쓰는 타입입니다. 영문자 하나는 `'A'`처럼 작은따옴표로 씁니다.

### 실행해 보기

@code characters_example.cpp

`word[0]`은 맨 처음 위치의 문자를 읽습니다. 위치 번호는 0부터 셉니다. Small의 유효한 위치는 0부터 4까지입니다.

`7`은 정수, `'7'`은 문자, `"7"`은 문자열입니다. char는 한 바이트를 담으므로 UTF-8 한글 한 글자를 char 하나에 넣을 수는 없습니다. 여기서는 영문자로 연습하세요.

예상 출력:

```text
A
S
```

## 문자열의 일부 가져오기

### 이번에 배울 것

**부분 문자열**은 문자열의 연속된 일부입니다. substring에 시작 위치와 가져올 길이를 전달합니다.

### 실행해 보기

@code substring_example.cpp

위치 1은 m입니다. 여기부터 세 글자를 가져오므로 mal이 됩니다. `substring(1)`처럼 길이를 생략하면 위치 1부터 끝까지 가져옵니다.

길이가 5인 문자열에서 문자 위치는 0–4입니다. 대괄호로 문자를 읽을 때 범위를 벗어나지 않게 하세요.

예상 출력:

```text
mal
```

## Exercise — 한 가지 바꾸기

좋아하는 음식 이름을 food에 저장하고 Food: 뒤에 출력하세요.

@exercise exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution exercise_solution.cpp

## 더 해 보기 (선택)

## Exercise — 한 가지 바꾸기

Good과 공백 하나, morning을 이어 붙여 출력하세요.

@exercise string_join_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution string_join_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

Small에서 둘째 문자인 m을 출력하세요.

@exercise characters_exercise_starter.cpp

### Hint

둘째 위치의 번호는 1입니다.

@solution characters_exercise_solution.cpp

## Exercise — 한 가지 바꾸기

Small의 맨 앞 두 글자 Sm을 가져오세요.

@exercise substring_exercise_starter.cpp

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

@solution substring_exercise_solution.cpp
