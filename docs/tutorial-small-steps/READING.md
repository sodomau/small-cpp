# Small C++ — 작은 걸음판 읽기 자료

IDE용 tutorial과 같은 한국어 수업입니다. 코드를 복사해 Small IDE에서 실행할 수 있습니다.


# 1. 글자를 화면에 보여 주기


## 이번에 배울 것

**프로그램**은 컴퓨터가 할 일을 정한 것입니다. 그 일을 글로 적은 것이 **코드**, 실제로 시키는 것이 **실행**입니다. 오늘은 인사말 하나를 보여 줍니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print("Hello!");
}
```

**Try This Code**로 코드를 열고 **Run 또는 F5**를 누르세요. 글자는 콘솔 창에 나옵니다.

**문자열**은 글자들이 순서대로 이어진 값입니다. `"Hello!"`의 큰따옴표는 그 시작과 끝을 표시합니다. **함수**는 할 일을 묶어 이름 붙인 것입니다. Print는 출력하는 함수이고, `Print("Hello!");`는 그 함수에 인사말을 전달해 실행합니다.

SmallMain은 우리가 할 일을 적는 함수입니다. 지금은 바깥 틀을 유지하고 `{ }` 안의 Print만 바꾸세요. 문장 끝의 `;`도 함께 둡니다.

예상 출력:

```text
Hello!
```

## Exercise — 한 가지 바꾸기

Hello! 대신 자신의 이름을 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

큰따옴표 안의 글자만 바꾸세요. Print의 P는 대문자입니다.

**정답**

```cpp
void SmallMain()
{
    Print("Alex");
}
```


# 2. 위에서 아래로 실행하기


## 이번에 배울 것

명령을 여러 개 적으면 위에서 아래로 실행합니다. Print는 출력한 뒤 다음 줄로 내려갑니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print("Hello!");
    Print("Small C++");
}
```

첫 Print가 끝나면 둘째 Print를 실행합니다. 두 줄의 순서를 바꾸면 출력 순서도 바뀝니다.

코드에서 `//`부터 그 줄 끝까지는 **주석**입니다. 사람에게 남기는 메모라서 실행하지 않습니다. 첫 줄 앞에 //를 붙이고 차이를 확인해 보세요.

예상 출력:

```text
Hello!
Small C++
```

## Exercise — 한 가지 바꾸기

이름, 좋아하는 것, 만들고 싶은 것을 세 줄로 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Print("Alex");
    Print("Games");
    Print("My game");
}
```


# 3. 숫자를 계산해 보여 주기


## 이번에 배울 것

숫자는 큰따옴표 없이 씁니다. `+`는 더하기, `-`는 빼기를 하는 **연산자**, 즉 계산 기호입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print(3 + 5);
    Print(9 - 2);
    Print("3 + 5");
}
```

`3 + 5`는 계산하여 값 8을 얻는 **식**입니다. `"3 + 5"`는 글자 그대로인 문자열이라서 계산하지 않습니다.

예상 출력:

```text
8
7
3 + 5
```

## Exercise — 한 가지 바꾸기

12 더하기 7과 12 빼기 7을 차례로 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Print(12 + 7);
    Print(12 - 7);
}
```


# 4. 값에 이름 붙이기


## 이번에 배울 것

**변수**는 값을 저장해 두는, 이름이 붙은 공간입니다. 점수를 score라는 이름으로 기억해 봅시다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int score = 10;
    Print(score);
}
```

`int score = 10;`은 score라는 변수를 만들고 처음 값 10을 넣습니다. **int는 정수 타입**입니다. 타입은 저장할 값의 종류이고, 정수는 0, 10, -3처럼 소수 부분이 없는 수입니다.

변수를 만드는 것을 **선언**, 처음 값을 넣는 것을 **초기화**라고 합니다. 이번에는 항상 값을 넣으며 만드세요. `Print(score);`는 score라는 글자가 아니라 저장된 값을 출력합니다.

예상 출력:

```text
10
```

## Exercise — 한 가지 바꾸기

age라는 int 변수에 10을 저장하고 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

score 대신 age라는 이름을 사용하세요.

**정답**

```cpp
void SmallMain()
{
    int age = 10;
    Print(age);
}
```


# 5. 저장한 값 바꾸기


## 이번에 배울 것

변수의 이름은 그대로 두고, 그 안의 값만 바꿀 수 있습니다. 새 값을 저장하는 일을 **대입**이라고 합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int score = 10;
    Print(score);
    score = 20;
    Print(score);
}
```

`score = 20;`을 실행하면 이전 값 10 대신 20이 저장됩니다. 이미 만든 변수이므로 int를 다시 쓰지 않습니다. `=`는 오른쪽 값을 왼쪽 변수에 넣는다는 뜻입니다.

예상 출력:

```text
10
20
```

## Exercise — 한 가지 바꾸기

점수를 처음에는 3으로, 그다음에는 8로 바꾸어 각각 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int score = 3;
    Print(score);
    score = 8;
    Print(score);
}
```


# 6. 기억한 값으로 계산하기


## 이번에 배울 것

변수에 저장한 값도 계산에 사용할 수 있습니다. 계산한 결과를 다시 저장하면 점수를 올릴 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int score = 10;
    score = score + 5;
    Print(score);
}
```

`score = score + 5;`는 ① 현재 값 10을 읽고 ② 5를 더하고 ③ 결과 15를 score에 저장합니다. 수학의 등식처럼 양쪽이 같다는 뜻이 아닙니다.

`Print(score + 5);`만 실행하면 계산 결과를 보여 줄 뿐, score 자체는 바뀌지 않습니다.

예상 출력:

```text
15
```

## Exercise — 한 가지 바꾸기

남은 기회 lives를 3으로 만들고, 1을 줄인 뒤 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int lives = 3;
    lives = lives - 1;
    Print(lives);
}
```


# 7. 소수 부분이 있는 값 저장하기


## 이번에 배울 것

길이나 시간에는 소수 부분이 필요합니다. **double**은 이런 수를 표현하는 타입입니다. 정수 개수를 셀 때는 int, 소수 부분이 필요한 값에는 double을 선택합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    double height = 1.45;
    Print(height);
}
```

변수의 타입은 만들 때 정합니다. int 변수에 나중에 소수를 넣는다고 double 변수로 변하지는 않습니다.

double도 모든 수를 무한히 정확하게 저장하지는 못하지만, 지금은 간단한 길이와 시간부터 다룹니다.

예상 출력:

```text
1.45
```

## Exercise — 한 가지 바꾸기

달리기 시간 12.5를 seconds라는 변수에 저장하고 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    double seconds = 12.5;
    Print(seconds);
}
```


# 8. 곱셈과 계산 순서


## 이번에 배울 것

`*`는 곱하기입니다. 곱셈은 덧셈보다 먼저 계산합니다. 먼저 계산할 부분을 괄호로 묶을 수도 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print(2 + 3 * 4);
    Print((2 + 3) * 4);
}
```

첫 줄은 3 × 4를 먼저 계산합니다. 둘째 줄은 괄호 안의 2 + 3을 먼저 계산합니다. 복잡한 식은 괄호로 순서를 드러내세요.

예상 출력:

```text
14
20
```

## Exercise — 한 가지 바꾸기

가로 3.5, 세로 2.0을 double 변수에 저장하고 넓이를 계산해 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

곱셈 결과가 7.0이어도 화면에는 7로 보일 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    double width = 3.5;
    double height = 2.0;
    Print(width * height);
}
```


# 9. 몫과 나머지


## 이번에 배울 것

`/`는 나누기, `%`는 정수 나눗셈의 나머지입니다. 사탕 17개를 5개씩 담으면 세 봉지를 만들고 2개가 남습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print(17 / 5);
    Print(17 % 5);
    Print(5.0 / 2);
}
```

정수끼리 나누면 소수 부분을 버립니다. `5 / 2`는 2이지만, `5.0 / 2`처럼 한쪽이 double이면 2.5입니다. 결과를 담는 변수만 double로 바꾸어도 먼저 계산한 `5 / 2`는 2입니다.

나누는 수에 0을 넣으면 안 됩니다. /와 %는 곱셈처럼 덧셈보다 먼저 계산합니다.

예상 출력:

```text
3
2
2.5
```

## Exercise — 한 가지 바꾸기

사탕 18개를 5개씩 담을 때 봉지 수와 남는 수를 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Print(18 / 5);
    Print(18 % 5);
}
```


# 10. 문자열도 저장하기


## 이번에 배울 것

이름이나 문장도 변수에 저장할 수 있습니다. **문자열**은 값의 종류이고, **String**은 Small에서 문자열을 저장할 때 쓰는 타입 이름입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    String name = "Alex";
    Print("Hello, ", name);
}
```

`Print("Hello, ", name);`은 인사말과 name의 값을 이어 출력합니다. 쉼표가 화면에 나오거나 공백이 자동으로 생기지는 않습니다. 필요한 공백은 큰따옴표 안에 넣습니다.

`"123"`은 글자로 된 문자열입니다. 숫자 계산에 쓰는 정수 123과는 종류가 다릅니다.

예상 출력:

```text
Hello, Alex
```

## Exercise — 한 가지 바꾸기

좋아하는 음식 이름을 food에 저장하고 Food: 뒤에 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    String food = "Pizza";
    Print("Food: ", food);
}
```


# 11. 실행 중에 이름 물어보기


## 이번에 배울 것

**입력**은 프로그램 밖에서 값을 받아 오는 일입니다. Input 함수는 키보드로 쓴 한 줄을 문자열로 돌려줍니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    String name = Input();
    Print("Hello, ", name);
}
```

Run한 뒤 콘솔 창에 Alex를 쓰고 Enter를 누르세요. Input이 기다리는 동안은 고장이 아닙니다. 입력을 마치면 그 문자열을 name에 저장하고 다음 줄을 실행합니다.

`Input("Name: ")`처럼 괄호 안에 안내문을 넣을 수도 있습니다.

예상 출력 (입력 안내문 제외):

```text
Hello, Alex
```

## Exercise — 한 가지 바꾸기

이름을 입력받아 Nice to meet you, 뒤에 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    String name = Input();
    Print("Nice to meet you, ", name);
}
```


# 12. 입력한 숫자로 계산하기


## 이번에 배울 것

InputInt는 입력한 내용을 **정수**로 읽어 돌려주는 함수입니다. Input이 돌려주는 문자열과 구분해서 사용합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int age = InputInt();
    Print(age + 1);
}
```

콘솔에 10을 입력하고 Enter를 누르세요. 읽은 정수 10에 1을 더하므로 11이 나옵니다. 한 줄에 정수 하나를 쓰세요. 숫자가 아닌 글자를 쓰면 다시 입력하라는 안내가 나옵니다.

예상 출력 (입력 안내문 제외):

```text
11
```

## Exercise — 한 가지 바꾸기

숫자 하나를 입력받고 두 배를 출력하세요. 7을 넣으면 14가 나와야 합니다.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int number = InputInt();
    Print(number * 2);
}
```


# 13. 작은 계산기 만들기


## 이번에 배울 것

InputReal은 소수 부분이 있는 수를 double 값으로 읽습니다. **입력 → 계산 → 출력**을 연결하면 계산기가 됩니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    double a = InputReal();
    double b = InputReal();
    Print(a + b);
}
```

2.5를 쓰고 Enter, 3.5를 쓰고 Enter를 누르세요. 함수를 두 번 호출하므로 두 번 입력합니다. a와 b에 각각 저장한 다음 합을 출력합니다.

예상 출력 (입력 안내문 제외):

```text
6
```

## Exercise — 한 가지 바꾸기

가로와 세로를 입력받아 넓이를 출력하세요. 3.5와 2를 넣으면 7입니다.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    double width = InputReal();
    double height = InputReal();
    Print(width * height);
}
```


# 14. 조건에 맞을 때만 실행하기


## 이번에 배울 것

**조건**은 참인지 거짓인지 판단할 수 있는 식입니다. if는 조건이 참일 때만 중괄호 안을 실행하는 **조건문**입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int score = 80;
    if (score >= 60)
    {
        Print("Pass");
    }
    Print("Done");
}
```

`score >= 60`은 점수가 60 이상인지 묻습니다. 80이면 참이라 Pass를 출력합니다. 50으로 바꾸면 Pass는 건너뛰고 Done만 출력합니다.

`>`는 초과, `<`는 미만, `>=`는 이상, `<=`는 이하입니다. if의 닫는 중괄호 뒤에는 ;을 붙이지 않습니다.

예상 출력:

```text
Pass
Done
```

## Exercise — 한 가지 바꾸기

number가 0보다 클 때만 Positive를 출력하세요. 먼저 3으로 시험하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

3을 0과 -1로도 바꾸어 보세요. 그때는 출력하지 않아야 합니다.

**정답**

```cpp
void SmallMain()
{
    int number = 3;
    if (number > 0)
    {
        Print("Positive");
    }
}
```


# 15. 조건이 맞지 않으면 다른 일 하기


## 이번에 배울 것

**else**는 if의 조건이 거짓일 때 실행할 일을 적는 부분입니다. 두 갈래 중 하나를 고릅니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int answer = 4;
    if (answer == 4)
    {
        Print("Correct");
    }
    else
    {
        Print("Try again");
    }
}
```

같은지 비교할 때는 `==`를 씁니다. 값을 넣는 `=`와 다릅니다. `!=`는 서로 다른지를 비교합니다. answer를 5로 바꾸면 else 쪽만 실행됩니다.

예상 출력:

```text
Correct
```

## Exercise — 한 가지 바꾸기

비밀번호가 1234와 같으면 Open, 다르면 Locked를 출력하세요. 1111로 시험하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int password = 1111;
    if (password == 1234)
    {
        Print("Open");
    }
    else
    {
        Print("Locked");
    }
}
```


# 16. 세 갈래 중 하나 고르기


## 이번에 배울 것

선택지가 셋 이상이면 **else if**로 조건을 이어 봅니다. 위에서부터 검사하고, 처음 맞는 갈래 하나만 실행합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int number = 0;
    if (number > 0)
    {
        Print("Positive");
    }
    else if (number < 0)
    {
        Print("Negative");
    }
    else
    {
        Print("Zero");
    }
}
```

0은 양수도 음수도 아니어서 마지막 else로 갑니다. else if 대신 독립된 if를 여러 개 쓰면 각 조건을 따로 검사하므로 여러 갈래가 실행될 수도 있습니다.

예상 출력:

```text
Zero
```

## Exercise — 한 가지 바꾸기

number를 -2로 바꾸어 어떤 갈래가 실행되는지 확인하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int number = -2;
    if (number > 0)
    {
        Print("Positive");
    }
    else if (number < 0)
    {
        Print("Negative");
    }
    else
    {
        Print("Zero");
    }
}
```


# 17. 참과 거짓도 기억하기


## 이번에 배울 것

**bool**은 참(true) 또는 거짓(false)을 저장하는 타입입니다. 준비되었는지, 게임이 끝났는지 같은 상태를 기억합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    bool ready = true;
    if (ready)
    {
        Print("Start");
    }
    Print(ready);
}
```

if에 bool 변수를 바로 넣을 수 있습니다. Small의 Print는 true를 1, false를 0으로 출력합니다. `bool passed = score >= 60;`처럼 비교 결과를 저장할 수도 있습니다.

예상 출력:

```text
Start
1
```

## Exercise — 한 가지 바꾸기

ready를 false로 바꾸고 출력 차이를 확인하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    bool ready = false;
    if (ready)
    {
        Print("Start");
    }
    Print(ready);
}
```


# 18. 조건 두 개 함께 보기


## 이번에 배울 것

`&&`는 두 조건이 **모두 참**, `||`는 **하나 이상 참**, `!`는 참과 거짓을 뒤집는 연산자입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int age = 15;
    if (age >= 13 && age <= 19)
    {
        Print("Teen");
    }
}
```

나이가 13 이상이면서 19 이하인지 확인합니다. 12, 13, 19, 20으로 바꾸어 경계를 확인하세요.

`!ready`는 준비되지 않았는지 묻습니다. &&는 왼쪽이 거짓이면, ||는 왼쪽이 참이면 오른쪽을 검사하지 않습니다.

예상 출력:

```text
Teen
```

## Exercise — 한 가지 바꾸기

나이가 13 미만이거나 19 초과일 때 Outside를 출력하세요. 20으로 시험하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

두 조건 사이에 ||를 사용하세요.

**정답**

```cpp
void SmallMain()
{
    int age = 20;
    if (age < 13 || age > 19)
    {
        Print("Outside");
    }
}
```


# 19. 같은 일을 여러 번 하기


## 이번에 배울 것

**반복문**은 한 번 적은 코드 묶음을 여러 번 실행합니다. for에는 시작 준비, 계속할 조건, 다음 값으로 바꾸기를 적습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    for (int i = 1; i <= 3; i = i + 1)
    {
        Print(i);
    }
}
```

i를 1로 시작합니다. 조건이 참이면 출력한 뒤 i를 1 늘리고 다시 검사합니다. 3을 출력한 뒤 i가 4가 되면 조건이 거짓이라 끝납니다. i는 우리가 정한 변수 이름입니다.

예상 출력:

```text
1
2
3
```

## Exercise — 한 가지 바꾸기

1부터 5까지 출력하도록 바꾸세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    for (int i = 1; i <= 5; i = i + 1)
    {
        Print(i);
    }
}
```


# 20. 조건이 맞는 동안 반복하기


## 이번에 배울 것

**while**은 조건이 참인 동안 중괄호 안을 반복합니다. 실행하기 전에 매번 조건을 확인합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int count = 3;
    while (count > 0)
    {
        Print(count);
        count = count - 1;
    }
}
```

count가 0이 되면 반복을 끝냅니다. 처음부터 0이면 한 번도 출력하지 않습니다. count를 줄이는 줄을 지우면 끝나지 않으므로, 그런 경우 IDE의 Stop으로 멈추세요.

횟수를 세며 반복할 때는 for가 편하고, 조건이 바뀔 때까지 기다릴 때는 while이 편합니다.

예상 출력:

```text
3
2
1
```

## Exercise — 한 가지 바꾸기

5부터 1까지 거꾸로 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int count = 5;
    while (count > 0)
    {
        Print(count);
        count = count - 1;
    }
}
```


# 21. 반복을 멈추거나 건너뛰기


## 이번에 배울 것

**break**는 가장 안쪽 반복문을 끝냅니다. **continue**는 이번 반복의 남은 부분을 건너뛰고 다음 반복으로 갑니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    for (int i = 1; i <= 5; i = i + 1)
    {
        if (i == 2)
        {
            continue;
        }
        if (i == 4)
        {
            break;
        }
        Print(i);
    }
}
```

2에서는 Print를 건너뜁니다. for는 i를 늘린 뒤 다음 조건을 검사합니다. 4에서는 반복 자체를 끝내므로 4와 5 모두 출력하지 않습니다.

예상 출력:

```text
1
3
```

## Exercise — 한 가지 바꾸기

2 대신 3을 건너뛰고, 5에서 멈추도록 바꾸세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    for (int i = 1; i <= 5; i = i + 1)
    {
        if (i == 3)
        {
            continue;
        }
        if (i == 5)
        {
            break;
        }
        Print(i);
    }
}
```


# 22. 별을 여러 줄 그리기


## 이번에 배울 것

반복문 안에 반복문을 넣을 수 있습니다. 바깥 반복은 줄을 세고, 안쪽 반복은 그 줄에 찍을 별을 셉니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    for (int row = 0; row < 2; row = row + 1)
    {
        for (int col = 0; col < 3; col = col + 1)
        {
            Write("*");
        }
        Print();
    }
}
```

**Write**는 출력 뒤 줄을 바꾸지 않습니다. **Print()**는 내용 없이 줄만 바꿉니다. 따라서 별 세 개를 붙여 쓴 뒤 줄을 바꾸는 일을 두 번 합니다.

예상 출력:

```text
***
***
```

## Exercise — 한 가지 바꾸기

별 네 개씩 세 줄을 그리세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    for (int row = 0; row < 3; row = row + 1)
    {
        for (int col = 0; col < 4; col = col + 1)
        {
            Write("*");
        }
        Print();
    }
}
```


# 23. 내가 만든 일에 이름 붙이기


## 이번에 배울 것

**함수**는 할 일을 묶어 이름 붙인 것입니다. Print를 사용했듯, 이번에는 Greet라는 함수를 직접 만듭니다.

## 실행해 보기

**예제**

```cpp
void Greet()
{
    Print("Hello!");
}

void SmallMain()
{
    Greet();
    Greet();
}
```

위쪽은 Greet가 할 일을 정하는 **정의**, 아래의 `Greet();`는 실제로 시키는 **호출**입니다. 정의만으로 실행되지는 않습니다. SmallMain에서 호출하면 Greet로 갔다가 끝난 뒤 돌아옵니다.

**void**는 호출한 쪽에 결과값을 돌려주지 않는다는 뜻입니다. 화면 출력은 할 수 있습니다. 빈 ()는 전달받는 값이 없다는 뜻입니다.

예상 출력:

```text
Hello!
Hello!
```

## Exercise — 한 가지 바꾸기

Greet를 세 번 호출해 보세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void Greet()
{
    Print("Hello!");
}

void SmallMain()
{
    Greet();
    Greet();
    Greet();
}
```


# 24. 함수에 값 전달하기


## 이번에 배울 것

함수에 값을 전달하면 같은 일을 다른 값으로 할 수 있습니다. 전달받은 값을 담는 변수를 **매개변수**라고 합니다.

## 실행해 보기

**예제**

```cpp
void ShowDouble(int number)
{
    Print(number * 2);
}

void SmallMain()
{
    ShowDouble(3);
    ShowDouble(5);
}
```

첫 호출에서는 number가 3, 둘째 호출에서는 5로 시작합니다. 호출할 때 넣는 값 3과 5를 **인자**라고 합니다. number는 이 함수를 실행하는 동안 쓰는 변수입니다.

예상 출력:

```text
6
10
```

## Exercise — 한 가지 바꾸기

ShowDouble에 7과 10을 전달해 차례로 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void ShowDouble(int number)
{
    Print(number * 2);
}

void SmallMain()
{
    ShowDouble(7);
    ShowDouble(10);
}
```


# 25. 함수의 결과 돌려받기


## 이번에 배울 것

**반환값**은 함수가 호출한 쪽에 돌려주는 값입니다. return은 값을 돌려주고 그 함수의 실행을 끝냅니다.

## 실행해 보기

**예제**

```cpp
int Square(int number)
{
    return number * number;
}

void SmallMain()
{
    int result = Square(4);
    Print(result);
}
```

맨 앞 int는 결과가 정수라는 뜻입니다. Square(4)가 돌려준 16을 result에 저장합니다. 함수는 계산을 맡고, 출력은 SmallMain에서 합니다.

InputInt도 이렇게 읽은 정수를 돌려주는 함수였습니다.

예상 출력:

```text
16
```

## Exercise — 한 가지 바꾸기

Square(6)의 결과를 받아 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
int Square(int number)
{
    return number * number;
}

void SmallMain()
{
    int result = Square(6);
    Print(result);
}
```


# 26. 함수 안의 변수는 따로 쓰기


## 이번에 배울 것

함수 안에서 만든 **지역 변수**는 그 범위 안에서 사용합니다. 값으로 전달받은 매개변수도 원본과 별도로 값을 가집니다.

## 실행해 보기

**예제**

```cpp
void AddOne(int number)
{
    number = number + 1;
    Print(number);
}

void SmallMain()
{
    int score = 10;
    AddOne(score);
    Print(score);
}
```

number는 score의 값 10을 복사해서 받습니다. number만 바꾸었으므로 돌아온 뒤 score는 여전히 10입니다.

일반적인 지역 변수는 그 범위가 끝나면 수명도 끝납니다. 다음 호출에서 이전 값을 자동으로 기억하지 않습니다. 원본을 바꾸는 방법은 뒤의 참조 수업에서 배웁니다.

예상 출력:

```text
11
10
```

## Exercise — 한 가지 바꾸기

score를 20으로 시작하면 두 출력이 무엇인지 예상하고 확인하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void AddOne(int number)
{
    number = number + 1;
    Print(number);
}

void SmallMain()
{
    int score = 20;
    AddOne(score);
    Print(score);
}
```


# 27. 문자열 이어 붙이기


## 이번에 배울 것

String 값에 쓰는 `+`는 숫자 덧셈 대신 **이어 붙이기**를 합니다. 이어 붙인 결과도 String 값입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    String first = "Small";
    String text = first + " C++";
    Print(text);
    Print(text.Length());
}
```

`text.Length()`는 text의 길이를 돌려주는 기능입니다. 점은 text에 속한 기능을 사용한다는 뜻입니다. 여기에는 공백도 포함됩니다.

길이는 **바이트**라는 데이터 크기 단위로 셉니다. 이번 영문 예제에서는 한 글자가 한 바이트입니다. UTF-8 한글 한 글자는 여러 바이트라서 글자 수와 다를 수 있습니다.

예상 출력:

```text
Small C++
9
```

## Exercise — 한 가지 바꾸기

Good과 공백 하나, morning을 이어 붙여 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    String first = "Good";
    String text = first + " morning";
    Print(text);
}
```


# 28. 문자 하나 꺼내 보기


## 이번에 배울 것

**문자**는 글자나 기호 하나입니다. **char**는 문자 값을 담을 때 쓰는 타입입니다. 영문자 하나는 `'A'`처럼 작은따옴표로 씁니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    char grade = 'A';
    Print(grade);
    String word = "Small";
    Print(word[0]);
}
```

`word[0]`은 맨 처음 위치의 문자를 읽습니다. 위치 번호는 0부터 셉니다. Small의 유효한 위치는 0부터 4까지입니다.

`7`은 정수, `'7'`은 문자, `"7"`은 문자열입니다. char는 한 바이트를 담으므로 UTF-8 한글 한 글자를 char 하나에 넣을 수는 없습니다. 여기서는 영문자로 연습하세요.

예상 출력:

```text
A
S
```

## Exercise — 한 가지 바꾸기

Small에서 둘째 문자인 m을 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

둘째 위치의 번호는 1입니다.

**정답**

```cpp
void SmallMain()
{
    String word = "Small";
    Print(word[1]);
}
```


# 29. 문자열의 일부 가져오기


## 이번에 배울 것

**부분 문자열**은 문자열의 연속된 일부입니다. Substring에 시작 위치와 가져올 길이를 전달합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    String word = "Small";
    Print(word.Substring(1, 3));
}
```

위치 1은 m입니다. 여기부터 세 글자를 가져오므로 mal이 됩니다. `Substring(1)`처럼 길이를 생략하면 위치 1부터 끝까지 가져옵니다.

길이가 5인 문자열에서 문자 위치는 0–4입니다. 대괄호로 문자를 읽을 때 범위를 벗어나지 않게 하세요.

예상 출력:

```text
mal
```

## Exercise — 한 가지 바꾸기

Small의 맨 앞 두 글자 Sm을 가져오세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    String word = "Small";
    Print(word.Substring(0, 2));
}
```


# 30. 따옴표와 줄바꿈 넣기


## 이번에 배울 것

문자열 안에 특별한 문자를 넣을 때는 역슬래시로 시작하는 **이스케이프 표기**를 사용합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print("Hello\nSmall");
    Print("\"Hi\"");
}
```

`\n`은 줄바꿈, `\"`는 큰따옴표 하나, `\\`는 역슬래시 하나입니다. 코드에서 두 기호로 적어도 하나의 문자를 나타냅니다.

`""`는 내용이 없는 빈 문자열이고 `" "`는 공백 하나가 있는 문자열입니다. Print는 빈 문자열을 출력해도 마지막에 줄을 바꿉니다.

예상 출력:

```text
Hello
Small
"Hi"
```

## Exercise — 한 가지 바꾸기

Print 한 번으로 A와 B를 서로 다른 줄에 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Print("A\nB");
}
```


# 31. 여러 값을 한곳에 담기


## 이번에 배울 것

**배열**은 같은 타입의 값들을 순서대로 담은 모음입니다. Small의 Array<int>는 여러 정수를 담는 타입입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> scores = {80, 95, 70};
    Print(scores[0]);
    scores[1] = 100;
    Print(scores[1]);
}
```

배열의 값 하나를 **원소**, 위치 번호를 **인덱스**라고 합니다. 문자열처럼 0부터 셉니다. 원소가 셋이면 유효한 번호는 0, 1, 2입니다. 대괄호로 값을 읽거나 바꿀 수 있습니다.

예상 출력:

```text
80
100
```

## Exercise — 한 가지 바꾸기

세 번째 점수를 90으로 바꾸고 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> scores = {80, 95, 70};
    scores[2] = 90;
    Print(scores[2]);
}
```


# 32. 배열의 값을 하나씩 보기


## 이번에 배울 것

반복문의 변수를 배열의 위치로 사용하면 원소를 차례로 읽을 수 있습니다. Length()는 원소 개수를 알려 줍니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> scores = {80, 95, 70};
    for (int i = 0; i < scores.Length(); i = i + 1)
    {
        Print(scores[i]);
    }
}
```

i가 0, 1, 2일 때 각각 출력합니다. 3은 원소 개수와 같아서 조건이 거짓이 됩니다. 따라서 조건은 `<=`가 아니라 `<`입니다. 길이가 0이면 반복하지 않습니다.

예상 출력:

```text
80
95
70
```

## Exercise — 한 가지 바꾸기

각 점수의 두 배를 출력하세요. 배열에 다시 저장할 필요는 없습니다.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> scores = {80, 95, 70};
    for (int i = 0; i < scores.Length(); i = i + 1)
    {
        Print(scores[i] * 2);
    }
}
```


# 33. 자리 수부터 정해서 배열 만들기


## 이번에 배울 것

처음 값을 나열하는 대신 필요한 자리 수를 먼저 정할 수도 있습니다. Array<int>(3)은 정수를 담을 자리 세 개를 만듭니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers(3);
    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        numbers[i] = i + 1;
        Print(numbers[i]);
    }
}
```

`Array<int> numbers(3);`은 세 자리이고, `Array<int> numbers = {3};`은 값 3이 든 한 자리입니다. 구분하세요.

Small Array는 만든 뒤 길이를 늘리는 기능이 없습니다. 각 원소의 값은 바꿀 수 있습니다.

예상 출력:

```text
1
2
3
```

## Exercise — 한 가지 바꾸기

다섯 자리를 만들고 1부터 5까지 저장하며 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers(5);
    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        numbers[i] = i + 1;
        Print(numbers[i]);
    }
}
```


# 34. 바꾸지 않을 값에 이름 붙이기


## 이번에 배울 것

**const**는 처음 정한 값을 이후에 바꾸지 않겠다는 표시입니다. 게임의 목표 점수처럼 일정한 값에 이름을 붙일 때 사용합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    const int GoalScore = 100;
    int score = 80;
    Print(GoalScore - score);
}
```

GoalScore에 나중에 다른 값을 넣으면 컴파일 오류입니다.

이 과정에서는 이름을 영문자로 시작하고 영문자·숫자·밑줄로 만드세요. 공백은 넣지 않습니다. score와 Score는 다르고 int, if 같은 C++ 예약어는 이름으로 사용할 수 없습니다.

예상 출력:

```text
20
```

## Exercise — 한 가지 바꾸기

목표를 200으로 정하고 현재 점수 80에서 얼마나 더 필요한지 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    const int GoalScore = 200;
    int score = 80;
    Print(GoalScore - score);
}
```


# 35. 값을 바꾸는 짧은 표기


## 이번에 배울 것

자주 쓰는 계산과 대입을 짧게 쓸 수 있습니다. int나 double에서 `score += 5;`는 `score = score + 5;`와 같은 갱신입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int score = 10;
    score += 5;
    score--;
    Print(score);
}
```

`++`는 1 증가, `--`는 1 감소입니다. 처음에는 예제처럼 독립된 문장으로 사용하세요. `-=`, `*=`, `/=`도 같은 방식입니다. 정수에는 `%=`도 씁니다. 정수의 /=는 여전히 정수 나눗셈입니다.

예상 출력:

```text
14
```

## Exercise — 한 가지 바꾸기

점수를 10으로 시작하고 두 배로 만든 뒤 1 늘려 출력하세요.

연습은 위 예제를 복사해 시작하세요.

### Hint

위 예제에서 필요한 부분을 바꾸어 보세요.

**정답**

```cpp
void SmallMain()
{
    int score = 10;
    score *= 2;
    score++;
    Print(score);
}
```


# 36. 창 하나 열기


## 이번에 배울 것

**Window**는 화면의 창을 다루는 타입입니다. **객체**는 그 타입으로 만든 실제 대상입니다. window라는 객체를 만들고 창을 열어 봅니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.SetTitle("My First Window");
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Show();
    }
}
```

`Open(640, 480)`은 가로 640, 세로 480픽셀의 창을 엽니다. **픽셀**은 화면을 이루는 작은 점입니다. `SetTitle`은 제목을 정합니다.

IsOpen이 참인 동안 Show를 반복합니다. Show는 화면을 보여 주고 닫기 같은 입력도 처리합니다. 창이 반응하려면 이 호출이 필요합니다. 창의 닫기 버튼을 누르면 반복을 끝냅니다.

이후 그림 예제에서도 이 창 열기 틀을 다시 사용합니다.

## Exercise — 내 이름의 창

500 x 300 크기의 Window를 열고 제목을 자신의 이름으로 지정하세요. 창을 닫을 때까지 유지하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;

    // Set a title and open a 500 x 300 window.
}
```

### Hint

`SetTitle`을 `Open` 전에 호출해도 됩니다.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.SetTitle("Alex");
    window.Open(500, 300);

    while (window.IsOpen())
        window.Show();
}
```



# 37. 객체에게 정보 물어보기


## 이번에 배울 것

객체의 점 뒤에 함수 이름을 쓰면 그 객체에 속한 기능을 사용합니다. 이런 함수를 **멤버 함수**라고 합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;

    window.SetTitle("Small Window");
    window.Open(400, 300);

    Print("Size: ", window.Width(), " x ", window.Height());

    while (window.IsOpen())
    {
        window.Show();
    }
}
```

`window.Width()`와 `window.Height()`는 창의 가로·세로 크기를 돌려줍니다. 콘솔에 `Size: 400 x 300`이 나오는지 보세요.

객체 만들기와 실제 창 열기는 별개입니다. SetTitle은 Open 전에 해도 됩니다. 프로그램에서 직접 닫으려면 Close를 호출합니다.

## Exercise — 크기 확인하기

320 x 240 창을 열고 실제 Width와 Height를 콘솔에 출력한 뒤 창을 유지하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(320, 240);

    // Print the size, then keep the window alive.
}
```

### Hint

`window.Width()`와 `window.Height()`를 Print에 전달하세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(320, 240);

    Print(window.Width(), " x ", window.Height());

    while (window.IsOpen())
        window.Show();
}
```


# 38. 좌표로 그림 그리기


## 이번에 배울 것

**좌표**는 화면의 위치를 숫자로 나타낸 것입니다. 창의 왼쪽 위가 (0, 0)이고 x는 오른쪽, y는 아래쪽으로 커집니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    window.Clear(White);
    window.FillCircle(320, 240, 80, Yellow);
    window.DrawCircle(290, 220, 10, Black);
    window.DrawCircle(350, 220, 10, Black);
    window.DrawLine(285, 275, 355, 275, Black);
    window.Show();

    while (window.IsOpen())
        window.Show();
}
```

Clear는 배경을 지웁니다. `FillCircle(320, 240, 80, Yellow)`는 중심 (320, 240), 반지름 80인 노란 원을 채웁니다. DrawCircle은 테두리만 그립니다.

DrawLine의 네 숫자는 시작점 x, y와 끝점 x, y입니다. 나중에 그린 것이 먼저 그린 것을 덮습니다. 노란 얼굴이 보이면 원의 위치 하나를 바꾸어 보세요.

예제 끝의 while처럼 실행할 문장이 하나이면 중괄호를 생략하기도 합니다. 직접 쓸 때는 중괄호로 묶어도 됩니다.

## Exercise — 신호등

검은색 또는 Gray 사각형 안에 Red, Yellow, Green 원 세 개가 세로로 들어 있는 신호등을 그리세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(300, 500);

    window.Clear(White);

    // Draw a traffic light here.

    window.Show();
    while (window.IsOpen())
        window.Show();
}
```

### Hint

먼저 FillRectangle로 몸체를 그리고 FillCircle을 세 번 사용하세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(300, 500);

    window.Clear(White);
    window.FillRectangle(75, 30, 150, 420, Gray);
    window.FillCircle(150, 110, 50, Red);
    window.FillCircle(150, 240, 50, Yellow);
    window.FillCircle(150, 370, 50, Green);
    window.Show();

    while (window.IsOpen())
        window.Show();
}
```



# 39. 색과 글자 더하기


## 이번에 배울 것

**RGB**는 빨강·초록·파랑의 세기를 섞어 색을 만드는 방식입니다. 각 값은 0부터 255까지 씁니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    Color orange = RGB(255, 140, 0);

    window.Clear(White);
    window.FillRectangle(60, 80, 180, 120, orange);
    window.DrawRectangle(60, 80, 180, 120, Black);
    window.DrawText(80, 110, "Small C++", Blue, 24);
    window.Show();

    while (window.IsOpen())
        window.Show();
}
```

Color는 색을 저장하는 타입이고 RGB는 그 색을 만들어 돌려주는 함수입니다.

FillRectangle의 숫자는 왼쪽 위 x, y와 가로·세로 크기입니다. DrawRectangle은 테두리만 그립니다. DrawText는 x, y, 문자열, 색, 글자 크기를 받습니다. 주황 사각형 위에 글자가 보이는지 확인하세요.

## Exercise — 나만의 얼굴

원과 선을 사용해 간단한 얼굴을 그리세요. 눈 두 개와 입이 보이면 됩니다. 색과 위치는 자유입니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(500, 500);

    window.Clear(White);

    // Draw your face here.

    window.Show();
    while (window.IsOpen())
        window.Show();
}
```

### Hint

큰 FillCircle 하나를 얼굴로 만든 뒤 작은 원 두 개와 DrawLine을 추가해 보세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(500, 500);

    window.Clear(White);
    window.FillCircle(250, 250, 160, Yellow);
    window.FillCircle(195, 210, 18, Black);
    window.FillCircle(305, 210, 18, Black);
    window.DrawLine(190, 315, 310, 315, Black);
    window.Show();

    while (window.IsOpen())
        window.Show();
}
```


# 40. 키를 누르는 동안 움직이기


## 이번에 배울 것

**키 입력 상태**는 지금 어떤 키가 눌려 있는지 알려 줍니다. KeyDown은 키를 누르고 있는 동안 참입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    double y = 240;

    while (window.IsOpen())
    {
        if (window.KeyDown(Key::Left))
            x = x - 2;
        if (window.KeyDown(Key::Right))
            x = x + 2;
        if (window.KeyDown(Key::Up))
            y = y - 2;
        if (window.KeyDown(Key::Down))
            y = y + 2;

        window.Clear(Black);
        window.FillCircle(x, y, 20, Yellow);
        window.Show();
    }
}
```

방향키로 x와 y를 바꾸고 그 위치에 원을 다시 그립니다. 한 번의 반복에서 만든 화면을 **프레임**이라고 합니다.

`Key::Left`는 왼쪽 방향키를 가리키는 이름입니다. 왼쪽·오른쪽 키를 길게 눌러 원이 계속 움직이는지 보세요.

## Exercise — WASD로 움직이기

방향키 대신 W, A, S, D를 사용해 원을 위, 왼쪽, 아래, 오른쪽으로 움직이세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    double y = 240;

    while (window.IsOpen())
    {
        // Move with W, A, S, D.

        window.Clear(Black);
        window.FillCircle(x, y, 20, Cyan);
        window.Show();
    }
}
```

### Hint

문자 키는 `window.KeyDown('W')`처럼 확인할 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 320;
    double y = 240;

    while (window.IsOpen())
    {
        if (window.KeyDown('A')) x = x - 2;
        if (window.KeyDown('D')) x = x + 2;
        if (window.KeyDown('W')) y = y - 2;
        if (window.KeyDown('S')) y = y + 2;

        window.Clear(Black);
        window.FillCircle(x, y, 20, Cyan);
        window.Show();
    }
}
```



# 41. 한 번 누를 때 한 번 바꾸기


## 이번에 배울 것

**KeyPressed**는 새로 누른 순간을 알려 줍니다. 길게 눌러도 매 프레임 참이 되는 KeyDown과 구분합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    bool red = true;

    while (window.IsOpen())
    {
        if (window.KeyPressed(Key::Space))
            red = !red;

        window.Clear(Black);

        if (red)
            window.FillCircle(320, 240, 60, Red);
        else
            window.FillCircle(320, 240, 60, Blue);

        window.Show();
    }
}
```

Space를 새로 누를 때 `red = !red;`로 참과 거짓을 뒤집습니다. 그 값에 따라 빨강과 파랑을 고릅니다. Space를 길게 눌렀다가 떼고 다시 눌러 보세요.

KeyReleased는 키를 뗀 순간을 알려 줍니다. 이동에는 Down, 한 번 바꾸는 동작에는 Pressed가 편합니다.

## Exercise — Space로 크기 바꾸기

Space를 누를 때마다 원의 radius가 20과 60 사이에서 바뀌게 하세요. 누르고 있는 동안 계속 바뀌면 안 됩니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    bool big = false;

    while (window.IsOpen())
    {
        // Toggle big when Space is pressed.

        window.Clear(Black);

        if (big)
            window.FillCircle(320, 240, 60, Yellow);
        else
            window.FillCircle(320, 240, 20, Yellow);

        window.Show();
    }
}
```

### Hint

`KeyPressed(Key::Space)`와 bool 변수를 사용해 두 상태를 번갈아 보세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    bool big = false;

    while (window.IsOpen())
    {
        if (window.KeyPressed(Key::Space))
            big = !big;

        window.Clear(Black);

        if (big)
            window.FillCircle(320, 240, 60, Yellow);
        else
            window.FillCircle(320, 240, 20, Yellow);

        window.Show();
    }
}
```


# 42. 마우스를 따라가는 원


## 이번에 배울 것

**마우스 위치**도 창 안의 x, y 좌표로 읽을 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);
        window.FillCircle(window.MouseX(), window.MouseY(), 12, Red);
        window.Show();
    }
}
```

MouseX와 MouseY가 돌려준 위치를 원의 중심으로 사용합니다. 매번 배경을 지우고 새 위치에 그리므로 원 하나가 마우스를 따라갑니다. 창 안에서 마우스를 움직여 보세요.

## Exercise — 클릭 위치 표시

왼쪽 버튼을 누르고 있는 동안 마우스 위치에 Yellow 원을 표시하고, 누르지 않을 때는 작은 Gray 원을 표시하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(Black);

        // Draw a different circle while the left button is down.

        window.Show();
    }
}
```

### Hint

`MouseDown(MouseButton::Left)`로 두 경우를 나누세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(Black);

        if (window.MouseDown(MouseButton::Left))
            window.FillCircle(window.MouseX(), window.MouseY(), 25, Yellow);
        else
            window.FillCircle(window.MouseX(), window.MouseY(), 8, Gray);

        window.Show();
    }
}
```



# 43. 마우스 버튼에 반응하기


## 이번에 배울 것

마우스의 **위치**와 **버튼 상태**는 별개입니다. 둘을 함께 읽으면 클릭한 곳에서 행동할 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);

        if (window.MouseDown(MouseButton::Left))
            window.FillCircle(window.MouseX(), window.MouseY(), 30, Blue);
        else
            window.DrawCircle(window.MouseX(), window.MouseY(), 30, Black);

        window.Show();
    }
}
```

MouseDown(MouseButton::Left)은 왼쪽 버튼을 누르고 있는지 묻습니다. 누르는 동안 파란 원, 떼면 검은 테두리를 그립니다.

MousePressed는 누른 순간, MouseReleased는 뗀 순간입니다. 위치를 한 번 기억하려면 Pressed를 사용할 수 있습니다.

## Exercise — 두 버튼 두 색

왼쪽 버튼을 누르면 마우스 위치에 Red 원, 오른쪽 버튼을 누르면 Blue 원을 표시하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);

        // Left = red, Right = blue.

        window.Show();
    }
}
```

### Hint

Left와 Right에 대해 각각 MouseDown을 검사하면 됩니다.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    while (window.IsOpen())
    {
        window.Clear(White);

        if (window.MouseDown(MouseButton::Left))
            window.FillCircle(window.MouseX(), window.MouseY(), 30, Red);

        if (window.MouseDown(MouseButton::Right))
            window.FillCircle(window.MouseX(), window.MouseY(), 30, Blue);

        window.Show();
    }
}
```


# 44. 위치를 바꾸며 다시 그리기


## 이번에 배울 것

**애니메이션**은 상태를 조금씩 바꾸며 그림을 연속해서 보여 주는 것입니다. 이번에는 원의 x 위치를 바꿉니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 50;

    while (window.IsOpen())
    {
        x = x + 2;

        if (x > 640)
            x = 0;

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Yellow);
        window.Show();
        Sleep(0.01);
    }
}
```

반복할 때마다 x를 2 늘리고, 배경을 지우고, 원을 그려 보여 줍니다. 오른쪽을 넘으면 x를 0으로 되돌립니다.

Sleep(0.01)은 약 0.01초 기다립니다. 원이 오른쪽으로 움직이다 왼쪽에서 다시 나타나는지 보세요.

## Exercise — 위아래로 움직이기

원을 화면 중앙 x=320에 두고 y 방향으로 움직이게 하세요. 위와 아래 끝에 닿으면 방향을 바꾸세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 3;

    while (window.IsOpen())
    {
        // Update y and bounce.

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
        Sleep(0.01);
    }
}
```

### Hint

y와 speed를 만들고, `y > 460 || y < 20`이면 speed의 부호를 바꾸세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 3;

    while (window.IsOpen())
    {
        y = y + speed;

        if (y > 460 || y < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
        Sleep(0.01);
    }
}
```



# 45. 방향 바꾸어 튕기기


## 이번에 배울 것

움직이는 방향을 속도 값의 부호로 나타낼 수 있습니다. 양수이면 오른쪽, 음수이면 왼쪽으로 갑니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 100;
    double speed = 3;

    while (window.IsOpen())
    {
        x = x + speed;

        if (x > 620 || x < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Cyan);
        window.Show();
        Sleep(0.01);
    }
}
```

경계에 닿으면 `speed = -speed;`로 부호를 뒤집습니다. 반지름 20을 고려해 중심이 20과 620 사이에 머무르게 합니다.

지금의 속도는 반복 한 번당 이동량입니다. 컴퓨터마다 반복 속도가 달라질 수 있어 다음에는 실제 시간을 사용합니다.

## Exercise — 두 공 움직이기

서로 다른 x 위치와 속도를 가진 공 두 개를 같은 화면에서 움직이세요. 둘 다 오른쪽 끝을 지나면 왼쪽에서 다시 시작하게 하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x1 = 50;
    double x2 = 200;
    double speed1 = 2;
    double speed2 = 4;

    while (window.IsOpen())
    {
        // Update both balls.

        window.Clear(Black);
        window.FillCircle(x1, 180, 15, Yellow);
        window.FillCircle(x2, 300, 15, Cyan);
        window.Show();
        Sleep(0.01);
    }
}
```

### Hint

x1, x2와 speed1, speed2를 각각 만들면 됩니다.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x1 = 50;
    double x2 = 200;
    double speed1 = 2;
    double speed2 = 4;

    while (window.IsOpen())
    {
        x1 = x1 + speed1;
        x2 = x2 + speed2;

        if (x1 > 655) x1 = -15;
        if (x2 > 655) x2 = -15;

        window.Clear(Black);
        window.FillCircle(x1, 180, 15, Yellow);
        window.FillCircle(x2, 300, 15, Cyan);
        window.Show();
        Sleep(0.01);
    }
}
```


# 46. 지난 시간 재기


## 이번에 배울 것

**StopWatch**는 경과 시간을 재는 도구입니다. 객체를 만들 때부터 시간을 재고 Elapsed는 지난 초 수를 알려 줍니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    StopWatch watch;

    Sleep(1.0);
    Print("About one second: ", watch.Elapsed());

    watch.Reset();
    Sleep(0.5);
    Print("About half a second: ", watch.Elapsed());
}
```

Sleep(1.0) 뒤에는 약 1초, Reset 후 Sleep(0.5) 뒤에는 약 0.5초가 나옵니다. 읽기만 한다고 시계가 0으로 돌아가지는 않습니다. Reset이 다시 재는 동작입니다.

실행 환경 때문에 정확히 1.000이나 0.500이 아니어도 정상입니다.

## Exercise — 2초 재기

StopWatch를 만들고 Sleep(2.0) 뒤 Elapsed 값을 출력하세요. 정확히 2.000...이 아니어도 정상입니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    StopWatch watch;

    // Wait two seconds and print the elapsed time.
}
```

### Hint

StopWatch는 생성되는 순간 시작하므로 별도의 Start가 필요 없습니다.

**정답**

```cpp
void SmallMain()
{
    StopWatch watch;

    Sleep(2.0);
    Print("Elapsed: ", watch.Elapsed());
}
```



# 47. 실제 시간에 맞춰 움직이기


## 이번에 배울 것

이동 거리 = 속도 × 시간입니다. 초당 속도를 정하고, 지난 시간만큼 이동하면 반복 속도가 달라도 움직임을 맞출 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double x = 50;
    double speed = 200;

    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        x = x + speed * dt;

        if (x > 620 || x < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(x, 240, 20, Yellow);
        window.Show();
    }
}
```

dt는 지난 반복부터 흐른 시간을 담는 변수입니다. Elapsed로 읽은 뒤 Reset하고 `speed * dt`를 위치에 더합니다.

속도가 초당 200픽셀이면 0.01초에는 2픽셀, 0.02초에는 4픽셀 움직입니다. dt는 새 문법이 아닙니다. speed를 100으로 바꾸어 비교하세요.

## Exercise — 시간 기준으로 움직이기

수업 44의 위아래 움직이는 공을 고쳐서 speed를 초당 150 pixel로 만들고 dt를 사용하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 150;
    StopWatch watch;

    while (window.IsOpen())
    {
        // Measure dt and move using seconds.

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
    }
}
```

### Hint

loop마다 `double dt = watch.Elapsed(); watch.Reset();`을 하고 `y = y + speed * dt;`로 이동하세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);

    double y = 100;
    double speed = 150;
    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        y = y + speed * dt;

        if (y > 460 || y < 20)
            speed = -speed;

        window.Clear(Black);
        window.FillCircle(320, y, 20, Green);
        window.Show();
    }
}
```


# 48. 효과음 재생하기


## 이번에 배울 것

**소리 재생**은 시간이 걸리는 작업입니다. 함수를 호출한 뒤 소리가 끝나기 전에 프로그램이 다음 일을 할 수도 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Print("Pop!");
    PlaySound(Sound::Pop);

    Sleep(0.5);

    Print("Coin!");
    PlaySound(Sound::Coin);

    Sleep(1.0);
}
```

PlaySound는 재생을 시작하고 바로 돌아옵니다. Sound::Pop과 Sound::Coin은 준비된 효과음 이름입니다.

예제에서는 프로그램이 바로 끝나지 않도록 Sleep으로 기다립니다. 두 효과음이 순서대로 시작되는지 들어 보세요.

## Exercise — 세 가지 효과음

Click, Coin, Win 효과음을 순서대로 들려주세요. 각 소리가 끝난 뒤 다음 소리가 시작되도록 하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // Play Click, Coin, and Win in order.
}
```

### Hint

`PlaySoundAndWait`를 세 번 사용하세요.

**정답**

```cpp
void SmallMain()
{
    PlaySoundAndWait(Sound::Click);
    PlaySoundAndWait(Sound::Coin);
    PlaySoundAndWait(Sound::Win);
}
```



# 49. 소리가 끝날 때까지 기다리기


## 이번에 배울 것

**AndWait**이 붙은 함수는 소리가 끝날 때까지 기다렸다가 돌아옵니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    BeepAndWait(440, 0.25);
    BeepAndWait(550, 0.25);
    BeepAndWait(660, 0.4);

    PlaySoundAndWait(Sound::Win);
}
```

BeepAndWait의 첫 값은 음의 높이를 정하는 주파수(Hz), 둘째 값은 초 단위 길이입니다. 440, 550, 660으로 높아지는 세 음 뒤에 효과음이 납니다.

게임 화면도 계속 움직여야 할 때는 기다리지 않는 PlaySound나 Beep이 편합니다.

## Exercise — 세 음 만들기

BeepAndWait를 사용해 서로 다른 주파수의 음 세 개를 차례대로 재생하세요. 주파수와 길이는 자유입니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // Make a three-note sound.
}
```

### Hint

예를 들어 440, 550, 660 Hz를 각각 0.2초 정도 사용할 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    BeepAndWait(440, 0.2);
    BeepAndWait(550, 0.2);
    BeepAndWait(660, 0.3);
}
```


# 50. 시간이 되면 함수 실행하기


## 이번에 배울 것

**이벤트**는 프로그램이 반응할 사건이고, **콜백**은 그 사건 때 실행하도록 맡겨 둔 함수입니다. Timer로 약 1초마다 함수를 실행합니다.

## 실행해 보기

**예제**

```cpp
int ticks = 0;

void OnTimer()
{
    ticks = ticks + 1;
    Print("Tick ", ticks);
}

void SmallMain()
{
    Timer timer;

    timer.Start(1.0, OnTimer);
    Sleep(3.2);
    timer.Stop();
}
```

Start(1.0, OnTimer)에서 OnTimer 뒤에 ()가 없는 이유는 지금 실행하는 대신 실행할 함수를 지정하기 때문입니다.

모든 함수 밖의 ticks는 여러 함수가 사용하는 **전역 변수**입니다. 콜백마다 1을 더합니다. Sleep 중에도 타이머가 처리되고 Stop하면 멈춥니다. 시간 예약이므로 정확한 호출 횟수를 보장하지는 않습니다.

## Exercise — 0.5초마다 세기

0.5초마다 호출되는 callback을 만들고 count를 1씩 증가시키며 출력하세요. 약 2.2초 뒤 Timer를 멈추세요.

**연습 시작 코드**

```cpp
int count = 0;

void OnTimer()
{
    // Increase and print count.
}

void SmallMain()
{
    Timer timer;

    // Start the timer, wait about 2.2 seconds, then stop it.
}
```

### Hint

`timer.Start(0.5, OnTimer)`를 사용하고 callback에서 count를 증가시키세요.

**정답**

```cpp
int count = 0;

void OnTimer()
{
    count = count + 1;
    Print("Count: ", count);
}

void SmallMain()
{
    Timer timer;
    timer.Start(0.5, OnTimer);

    Sleep(2.2);

    timer.Stop();
}
```



# 51. 타이머의 값을 화면에 표시하기


## 이번에 배울 것

콜백에서는 값을 바꾸고, 창의 반복문에서는 그 값을 읽어 그림을 그릴 수 있습니다.

## 실행해 보기

**예제**

```cpp
int seconds = 0;

void OnSecond()
{
    seconds = seconds + 1;
}

void SmallMain()
{
    Window window;
    window.Open(500, 250);

    Timer timer;
    timer.Start(1.0, OnSecond);

    while (window.IsOpen())
    {
        window.Clear(Black);
        window.DrawText(30, 80, Format("Seconds: ", seconds), White, 28);
        window.Show();
    }

    timer.Stop();
}
```

OnSecond가 전역 seconds를 늘리고 DrawText가 현재 값을 표시합니다. **Format**은 글자와 값을 이어 붙인 String을 돌려줍니다. Print와 달리 직접 출력하지 않습니다.

Timer는 별도 계산 스레드가 아닙니다. Show나 Sleep이 이벤트를 처리할 때 콜백을 실행하므로 긴 계산은 호출을 늦출 수 있습니다. 정확한 시간 측정은 StopWatch로 하세요.

## Exercise — 창의 제목 바꾸기

Timer callback이 1초마다 level을 1씩 증가시키게 하세요. Window loop에서는 현재 level을 `SetTitle("Level ", level)`로 제목에 표시하세요.

**연습 시작 코드**

```cpp
int level = 1;

void OnSecond()
{
    // Increase level.
}

void SmallMain()
{
    Window window;
    window.Open(500, 300);

    Timer timer;
    timer.Start(1.0, OnSecond);

    while (window.IsOpen())
    {
        // Show level in the title.
        window.Clear(Black);
        window.Show();
    }

    timer.Stop();
}
```

### Hint

callback에서는 전역 int level만 바꾸고, Window title은 main loop에서 갱신하면 간단합니다.

**정답**

```cpp
int level = 1;

void OnSecond()
{
    level = level + 1;
}

void SmallMain()
{
    Window window;
    window.Open(500, 300);

    Timer timer;
    timer.Start(1.0, OnSecond);

    while (window.IsOpen())
    {
        window.SetTitle("Level ", level);
        window.Clear(Black);
        window.Show();
    }

    timer.Stop();
}
```


# 52. 배운 것을 묶어 작은 게임 만들기


## 이번에 배울 것

**게임**은 입력을 받아 상태를 바꾸고 그 상태를 그림으로 보여 주는 프로그램입니다. 이번은 새 문법 수업이 아니라 조립 활동입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.SetTitle("Mini Pong");
    window.Open(800, 500);

    double paddleY = 210;
    double ballX = 400;
    double ballY = 250;
    double ballVX = 260;
    double ballVY = 180;

    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Up))
            paddleY = paddleY - 300 * dt;
        if (window.KeyDown(Key::Down))
            paddleY = paddleY + 300 * dt;

        ballX = ballX + ballVX * dt;
        ballY = ballY + ballVY * dt;

        if (ballY < 10)
        {
            ballY = 10;
            ballVY = -ballVY;
        }

        if (ballY > 490)
        {
            ballY = 490;
            ballVY = -ballVY;
        }

        if (ballX < 50 && ballX > 30 &&
            ballY > paddleY && ballY < paddleY + 80)
        {
            ballX = 50;
            ballVX = -ballVX;
            PlaySound(Sound::Hit);
        }

        if (ballX > 790)
        {
            ballX = 790;
            ballVX = -ballVX;
        }

        if (ballX < 0)
        {
            ballX = 400;
            ballY = 250;
            ballVX = 260;
            PlaySound(Sound::Lose);
        }

        window.Clear(Black);
        window.FillRectangle(30, paddleY, 15, 80, White);
        window.FillCircle(ballX, ballY, 10, Yellow);
        window.Show();
    }
}
```

예제를 실행하고 방향키 위·아래로 막대를 움직이세요. 코드는 ① 시간·입력 읽기 ② 위치 바꾸기 ③ 충돌 처리 ④ 그리기 순서입니다.

충돌은 물체가 서로 닿았는지 판단하는 일입니다. 벽을 넘었을 때 방향만 바꾸지 않고 위치도 경계로 돌려놓습니다. 한 번에 전체를 고치지 말고 막대 이동 부분부터 찾으세요.

## Exercise — paddle이 화면 밖으로 못 나가게

시작 코드는 첫 Pong 예제에서 paddle 이동만 분리한 것입니다. paddleY가 0보다 작아지거나 420보다 커지지 않도록 제한하는 코드를 추가하세요. 위아래 방향키를 오래 눌러도 paddle 전체가 창 안에 남아 있어야 합니다. 확인한 제한 코드는 첫 Pong 예제에도 옮겨 사용할 수 있습니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(800, 500);

    double paddleY = 210;
    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Up))
            paddleY = paddleY - 300 * dt;
        if (window.KeyDown(Key::Down))
            paddleY = paddleY + 300 * dt;

        // Keep paddleY between 0 and 420.

        window.Clear(Black);
        window.FillRectangle(30, paddleY, 15, 80, White);
        window.Show();
    }
}
```

### Hint

입력으로 paddleY를 바꾼 뒤 두 개의 if로 0과 420 범위에 맞추세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(800, 500);

    double paddleY = 210;
    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Up))
            paddleY = paddleY - 300 * dt;
        if (window.KeyDown(Key::Down))
            paddleY = paddleY + 300 * dt;

        if (paddleY < 0) paddleY = 0;
        if (paddleY > 420) paddleY = 420;

        window.Clear(Black);
        window.FillRectangle(30, paddleY, 15, 80, White);
        window.Show();
    }
}
```



# 53. 게임에 점수 붙이기


## 이번에 배울 것

**게임 규칙**은 어떤 사건이 일어났을 때 상태를 어떻게 바꿀지 정한 것입니다. 공을 받아 냈을 때만 점수를 늘립니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.SetTitle("Catch the Ball");
    window.Open(640, 480);

    double playerX = 320;
    double ballX = 100;
    double ballY = 80;
    double ballVX = 180;
    double ballVY = 140;
    int score = 0;

    StopWatch watch;

    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();

        if (window.KeyDown(Key::Left)) playerX = playerX - 250 * dt;
        if (window.KeyDown(Key::Right)) playerX = playerX + 250 * dt;

        ballX = ballX + ballVX * dt;
        ballY = ballY + ballVY * dt;

        if (ballX < 15)
        {
            ballX = 15;
            ballVX = -ballVX;
        }

        if (ballX > 625)
        {
            ballX = 625;
            ballVX = -ballVX;
        }

        if (ballY < 15)
        {
            ballY = 15;
            ballVY = -ballVY;
        }

        if (ballY > 430 && ballY < 460 &&
            ballX > playerX - 60 && ballX < playerX + 60)
        {
            ballY = 430;
            ballVY = -ballVY;
            score = score + 1;
            PlaySound(Sound::Coin);
        }

        if (ballY > 500)
        {
            ballX = 100;
            ballY = 80;
        }

        window.SetTitle("Score: ", score);
        window.Clear(Black);
        window.FillRectangle(playerX - 60, 450, 120, 12, White);
        window.FillCircle(ballX, ballY, 15, Cyan);
        window.Show();
    }
}
```

좌우 키로 막대를 움직이세요. 공이 막대의 범위에 닿으면 튕기고 score가 1 증가합니다. SetTitle은 현재 점수를 창 제목에 보여 줍니다.

놓쳤을 때는 공만 시작 위치로 돌립니다. 적중과 실패를 각각 시험하세요. 문제가 있으면 위치 갱신·조건·점수 변경 중 어느 단계인지 나누어 확인합니다.

## Exercise — score를 제목에 표시

시작 코드의 paddle을 좌우 방향키로 움직여 보세요. 공이 paddle에 맞을 때만 score를 1 증가시키고 `window.SetTitle("Score: ", score)`로 창 제목에 표시하세요. paddle을 옆으로 치워 공을 놓쳤을 때에는 점수가 늘어나면 안 됩니다. 충돌 검사는 시작 코드에 제공되어 있습니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);
    int score = 0;
    double paddleX = 320;
    double ballX = 320;
    double ballY = 100;
    double ballVY = 180;
    StopWatch watch;
    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();
        if (window.KeyDown(Key::Left)) { paddleX = paddleX - 250 * dt; }
        if (window.KeyDown(Key::Right)) { paddleX = paddleX + 250 * dt; }
        if (paddleX < 70) { paddleX = 70; }
        if (paddleX > 570) { paddleX = 570; }
        double previousY = ballY;
        ballY = ballY + ballVY * dt;
        if (ballVY > 0 && previousY <= 430 && ballY >= 430 &&
            ballX >= paddleX - 70 && ballX <= paddleX + 70)
        {
            ballY = 430;
            ballVY = -ballVY;
            // Increase score only on a paddle hit.
            PlaySound(Sound::Hit);
        }
        if (ballY < 20) { ballY = 20; ballVY = -ballVY; }
        if (ballY > 500) { ballY = 100; ballVY = 180; }
        // Show score in the window title.
        window.Clear(Black);
        window.FillRectangle(paddleX - 70, 450, 140, 10, White);
        window.FillCircle(ballX, ballY, 20, Yellow);
        window.Show();
    }
}
```

### Hint

score는 loop 밖에서 0으로 만들고 충돌 if 안에서 증가시키세요.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(640, 480);
    int score = 0;
    double paddleX = 320;
    double ballX = 320;
    double ballY = 100;
    double ballVY = 180;
    StopWatch watch;
    while (window.IsOpen())
    {
        double dt = watch.Elapsed();
        watch.Reset();
        if (window.KeyDown(Key::Left)) { paddleX = paddleX - 250 * dt; }
        if (window.KeyDown(Key::Right)) { paddleX = paddleX + 250 * dt; }
        if (paddleX < 70) { paddleX = 70; }
        if (paddleX > 570) { paddleX = 570; }
        double previousY = ballY;
        ballY = ballY + ballVY * dt;
        if (ballVY > 0 && previousY <= 430 && ballY >= 430 &&
            ballX >= paddleX - 70 && ballX <= paddleX + 70)
        {
            ballY = 430;
            ballVY = -ballVY;
            score = score + 1;
            PlaySound(Sound::Hit);
        }
        if (ballY < 20) { ballY = 20; ballVY = -ballVY; }
        if (ballY > 500) { ballY = 100; ballVY = 180; }
        window.SetTitle("Score: ", score);
        window.Clear(Black);
        window.FillRectangle(paddleX - 70, 450, 140, 10, White);
        window.FillCircle(ballX, ballY, 20, Yellow);
        window.Show();
    }
}
```


# 54. 값을 차례로 더하기


## 이번에 배울 것

**알고리즘**은 답을 구하는 절차입니다. 합계는 지금까지 더한 값을 기억하면서 다음 값을 더해 구합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 9, 4};
    int total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        total = total + numbers[i];

    Print("Sum: ", total);
}
```

total은 0 → 3 → 10 → 12 → 21 → 25로 바뀝니다. 예상 출력은 Sum: 25입니다.

아직 더한 값이 없을 때의 합은 0이므로 시작값도 0입니다. 반복문 안에서 total을 매번 0으로 만들면 누적되지 않습니다.

## Exercise — 평균 구하기

Array의 합계를 구한 뒤 값의 개수로 나누어 평균을 출력하세요. 실수 나눗셈이 되도록 total을 double로 만들어 보세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {10, 20, 30, 40};
    double total = 0;

    // Add the values and print the average.
}
```

### Hint

`double total = 0;`으로 시작하고 마지막에 `total / numbers.Length()`를 계산하세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {10, 20, 30, 40};
    double total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        total = total + numbers[i];

    Print("Average: ", total / numbers.Length());
}
```



# 55. 조건에 맞는 값 세기


## 이번에 배울 것

개수를 셀 때는 조건에 맞는 원소를 만날 때만 1을 더합니다.

## 실행해 보기

**예제**

```cpp
int CountEven(Array<int> numbers)
{
    int count = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] % 2 == 0)
            count = count + 1;

    return count;
}

void SmallMain()
{
    Array<int> numbers = {3, 8, 4, 7, 10};
    Print("Even: ", CountEven(numbers));
}
```

`numbers[i] % 2 == 0`은 2로 나눈 나머지가 0, 즉 짝수인지 묻습니다. 8, 4, 10이 해당해 Even: 3이 나옵니다. 0도 이 조건을 만족합니다.

CountEven은 배열을 매개변수로 받습니다. 지금은 Array<int> 값을 복사해서 받으며, 복사를 피하는 방법은 뒤의 참조 수업에서 배웁니다.

## Exercise — 양수 개수 세기

Array에서 0보다 큰 값이 몇 개인지 세어 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {-2, 5, 0, 8, -1, 3};
    int count = 0;

    // Count positive values.

    Print(count);
}
```

### Hint

각 값에 대해 `numbers[i] > 0`인지 검사하고 count를 1 증가시키세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {-2, 5, 0, 8, -1, 3};
    int count = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] > 0)
            count = count + 1;

    Print(count);
}
```


# 56. 지금까지 가장 큰 값 기억하기


## 이번에 배울 것

**최댓값 찾기**는 지금까지 본 가장 큰 값을 기억하고, 더 큰 값을 만나면 바꾸는 절차입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    Print("Largest: ", largest);
}
```

첫 원소 7을 시작값으로 정합니다. 2는 작아서 그대로, 9는 커서 바꿉니다. 결과는 Largest: 9입니다.

0으로 시작하면 모든 값이 음수일 때 잘못될 수 있습니다. 이 예제는 원소가 하나 이상인 배열을 사용합니다.

## Exercise — 가장 작은 값

Array에서 가장 작은 값을 찾아 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {8, -3, 5, 2, -1};

    // Find and print the smallest value.
}
```

### Hint

첫 번째 값을 smallest로 두고 index 1부터 비교하세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {8, -3, 5, 2, -1};
    int smallest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] < smallest)
            smallest = numbers[i];

    Print(smallest);
}
```



# 57. 값이 있는 위치 기억하기


## 이번에 배울 것

값 대신 **인덱스**를 기억하면 가장 작은 값이 무엇인지와 어디 있는지를 함께 알 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 1, 5};
    int smallestIndex = 0;

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] < numbers[smallestIndex])
            smallestIndex = i;

    Print("Smallest: ", numbers[smallestIndex]);
    Print("Index: ", smallestIndex);
}
```

smallestIndex는 가장 작은 원소의 위치입니다. `numbers[smallestIndex]`로 그 값을 읽습니다. 예제의 최솟값은 1, 위치는 3입니다.

값과 위치를 혼동하지 않게 변수 이름에 Index를 붙였습니다. 같은 최솟값이 여러 개면 현재의 < 비교는 먼저 만난 위치를 남깁니다.

## Exercise — 가장 큰 값의 위치

가장 큰 값의 index를 찾아 값과 index를 함께 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {4, 11, 6, 20, 9};

    // Find the index of the largest value.
}
```

### Hint

largestIndex를 0으로 시작하고 `numbers[i] > numbers[largestIndex]`를 비교하세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {4, 11, 6, 20, 9};
    int largestIndex = 0;

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > numbers[largestIndex])
            largestIndex = i;

    Print("Value: ", numbers[largestIndex]);
    Print("Index: ", largestIndex);
}
```


# 58. 원하는 값 찾아보기


## 이번에 배울 것

**검색**은 원하는 값이 있는지, 있다면 어디 있는지 찾는 일입니다. 처음부터 하나씩 비교하는 방법을 순차 검색이라고 합니다.

## 실행해 보기

**예제**

```cpp
int Find(Array<int> numbers, int value)
{
    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == value)
            return i;

    return -1;
}

void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    Print("Index: ", Find(numbers, 9));
}
```

9는 위치 2에 있으므로 Index: 2가 나옵니다. 찾으면 return으로 위치를 돌려주며 함수 전체를 끝냅니다.

끝까지 못 찾으면 -1을 돌려줍니다. 유효한 위치는 0 이상이므로 -1을 못 찾았다는 표시로 정했습니다.

## Exercise — 마지막 위치 찾기

같은 값이 여러 번 있을 때 마지막으로 나타나는 index를 찾으세요. 없으면 -1을 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 7, 5, 7};
    int value = 7;
    int index = -1;

    // Find the last position.

    Print(index);
}
```

### Hint

찾았다고 바로 return하지 말고 index를 갱신하며 끝까지 보세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 7, 5, 7};
    int value = 7;
    int index = -1;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == value)
            index = i;

    Print(index);
}
```



# 59. 못 찾은 경우도 처리하기


## 이번에 배울 것

검색 결과에는 성공과 실패가 모두 있습니다. 프로그램은 두 경우를 구분해 안내해야 합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int value = InputInt("Find: ");
    int index = -1;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == value)
        {
            index = i;
            break;
        }

    if (index == -1)
        Print("Not found");
    else
        Print("Found at ", index);
}
```

콘솔에 9를 입력하면 Found at 2, 8을 입력하면 Not found가 나옵니다.

이번에는 break로 검색 반복만 끝내고, 뒤의 if에서 결과를 출력합니다. return으로 함수 전체를 끝내는 것과 구분하세요.

## Exercise — 문자 찾기

String에서 문자 'a'가 처음 나타나는 위치를 linear search처럼 찾아 출력하세요. 없으면 -1입니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    String text = "Small C++";
    int index = -1;

    // Find the first 'a'.

    Print(index);
}
```

### Hint

String도 Length와 []를 사용할 수 있으므로 Array 검색과 거의 같습니다.

**정답**

```cpp
void SmallMain()
{
    String text = "Small C++";
    int index = -1;

    for (int i = 0; i < text.Length(); i = i + 1)
        if (text[i] == 'a')
        {
            index = i;
            break;
        }

    Print(index);
}
```


# 60. 작은 수부터 순서 정하기


## 이번에 배울 것

**정렬**은 정한 기준에 맞게 순서를 바꾸는 일입니다. 이번 방법은 남은 값 중 최솟값을 찾아 앞자리부터 채웁니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int smallest = i;

        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        int temp = numbers[i];
        numbers[i] = numbers[smallest];
        numbers[smallest] = temp;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}
```

바깥 반복은 채울 자리 i, 안쪽 반복은 남은 부분의 최솟값 위치를 찾습니다.

두 값을 바꿀 때 temp에 한 값을 잠시 보관합니다. 곧바로 덮어쓰면 원래 값을 잃기 때문입니다. 출력이 2, 4, 5, 7, 9 순서인지 보세요.

## Exercise — 오름차순 정렬

`{10, 3, 8, 1, 6}`을 Selection Sort로 작은 순서로 정렬하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {10, 3, 8, 1, 6};

    // Selection Sort here.

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}
```

### Hint

Lesson의 smallest index 패턴을 그대로 적용하세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {10, 3, 8, 1, 6};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int smallest = i;
        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        int temp = numbers[i];
        numbers[i] = numbers[smallest];
        numbers[smallest] = temp;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}
```



# 61. 큰 수부터 순서 정하기


## 이번에 배울 것

같은 절차에서 비교 기준을 바꾸면 순서도 바뀝니다. 큰 수부터 나열하는 것을 **내림차순**이라고 합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int largest = i;

        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] > numbers[largest])
                largest = j;

        int temp = numbers[i];
        numbers[i] = numbers[largest];
        numbers[largest] = temp;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}
```

이번에는 남은 값 중 최댓값을 찾습니다. 비교가 <에서 >로 바뀌고 출력은 9, 7, 5, 4, 2가 됩니다.

정렬 방향을 바꾸려고 반복문 전체를 다시 만들 필요는 없습니다. 어떤 값을 먼저 고르는지 바꾸면 됩니다.

## Exercise — 큰 순서로 바꾸기

Selection Sort를 수정해 큰 값부터 작은 값 순서로 정렬하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {10, 3, 8, 1, 6};

    // Sort from largest to smallest.

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}
```

### Hint

smallest 대신 largest를 찾고 비교 방향을 `>`로 바꾸세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {10, 3, 8, 1, 6};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int largest = i;
        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] > numbers[largest])
                largest = j;

        int temp = numbers[i];
        numbers[i] = numbers[largest];
        numbers[largest] = temp;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
        Print(numbers[i]);
}
```


# 62. 숫자를 막대로 보여 주기


## 이번에 배울 것

**시각화**는 데이터를 그림으로 표현하는 것입니다. 값이 클수록 높은 막대를 그려 배열을 눈으로 봅니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};

    window.Clear(White);

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        double height = numbers[i] * 30;
        window.FillRectangle(40 + i * 70, 420 - height, 50, height, Blue);
    }

    window.Show();

    while (window.IsOpen())
        window.Show();
}
```

값에 30을 곱해 높이를 정합니다. 화면은 아래로 갈수록 y가 커지므로 막대 위쪽을 `420 - height`로 계산합니다.

배열의 값 하나를 바꾸고 해당 막대의 높이가 달라지는지 확인하세요.

## Exercise — 현재 위치 표시

먼저 정렬 애니메이션에 사용할 위치 표시를 따로 연습합니다. 시작 코드의 current번째 막대를 Red로, 나머지를 Blue로 그리세요. 이 연습 자체는 정렬하지 않는 정적인 그림입니다. current를 0부터 4까지 바꾸어 빨간 막대가 해당 위치로 바뀌는지 확인하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Window window;
    window.Open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};
    int current = 2;

    window.Clear(White);

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        double height = numbers[i] * 30;
        Color color = Blue;

        // Make current red.

        window.FillRectangle(40 + i * 70, 420 - height, 50, height, color);
    }

    window.Show();

    while (window.IsOpen())
        window.Show();
}
```

### Hint

막대를 그리는 loop 안에서 `i == current`인지 검사해 Color를 선택하세요. 앞의 정렬 애니메이션으로 옮길 때에는 current 대신 그 단계에서 확정한 위치를 사용하면 됩니다.

**정답**

```cpp
void SmallMain()
{
    Window window;
    window.Open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};
    int current = 2;

    window.Clear(White);

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        double height = numbers[i] * 30;
        Color color = Blue;

        if (i == current)
            color = Red;

        window.FillRectangle(40 + i * 70, 420 - height, 50, height, color);
    }

    window.Show();

    while (window.IsOpen())
        window.Show();
}
```



# 63. 정렬 과정을 눈으로 보기


## 이번에 배울 것

완성된 답뿐 아니라 **중간 상태**를 그리면 알고리즘의 동작도 볼 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Window window;
    window.Open(450, 450);

    Array<int> numbers = {7, 2, 9, 4, 5};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int smallest = i;

        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        int temp = numbers[i];
        numbers[i] = numbers[smallest];
        numbers[smallest] = temp;

        window.Clear(White);

        for (int j = 0; j < numbers.Length(); j = j + 1)
        {
            double height = numbers[j] * 30;
            Color color = Blue;
            if (j == i)
                color = Red;

            window.FillRectangle(40 + j * 70, 420 - height, 50, height, color);
        }

        window.Show();
        Sleep(0.5);
    }

    while (window.IsOpen())
        window.Show();
}
```

자리 하나를 정한 뒤 전체 막대를 다시 그리고 0.5초 기다립니다. 이번에 정한 자리는 빨강입니다.

바뀐 배열을 보고 정렬이 어디까지 진행됐는지 말해 보세요. 그림을 그리는 부분과 정렬하는 부분을 구분해 읽습니다.

## Exercise — swap 횟수 세기

Selection Sort에서 실제로 swap을 수행한 횟수를 세고 마지막에 출력하세요. 같은 위치끼리는 swap하지 않도록 해도 좋습니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int swaps = 0;

    // Sort and count real swaps.

    Print("Swaps: ", swaps);
}
```

### Hint

`swaps`를 0으로 시작하고 smallest != i일 때만 swap하고 증가시키세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {7, 2, 9, 4, 5};
    int swaps = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        int smallest = i;

        for (int j = i + 1; j < numbers.Length(); j = j + 1)
            if (numbers[j] < numbers[smallest])
                smallest = j;

        if (smallest != i)
        {
            int temp = numbers[i];
            numbers[i] = numbers[smallest];
            numbers[smallest] = temp;
            swaps = swaps + 1;
        }
    }

    Print("Swaps: ", swaps);
}
```


# 64. 찾을 범위를 반으로 줄이기


## 이번에 배울 것

**이진 검색**은 가운데 값과 비교하여 가능한 범위를 반씩 줄이는 방법입니다. 배열이 먼저 작은 순서로 정렬되어 있어야 합니다.

## 실행해 보기

**예제**

```cpp
int BinarySearch(Array<int> numbers, int value)
{
    int left = 0;
    int right = numbers.Length() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (numbers[middle] == value)
            return middle;

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    return -1;
}

void SmallMain()
{
    Array<int> numbers = {1, 3, 5, 7, 9, 11, 13};
    Print(BinarySearch(numbers, 11));
}
```

left와 right는 남은 범위의 양 끝입니다. 가운데보다 찾는 값이 작으면 오른쪽 절반을, 크면 왼쪽 절반을 제외합니다.

11의 위치는 5입니다. 못 찾으면 -1을 돌려줍니다. 가운데 위치도 검사했으므로 다음 범위에서는 middle을 빼고 시작합니다.

## Exercise — Binary Search 완성

정렬된 `{4, 8, 15, 16, 23, 42}`에서 23을 찾아 index를 출력하는 Binary Search를 작성하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {4, 8, 15, 16, 23, 42};
    int value = 23;
    int index = -1;

    // Binary Search here.

    Print(index);
}
```

### Hint

left, right, middle 세 변수를 사용하고 매번 범위를 절반으로 줄이세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {4, 8, 15, 16, 23, 42};
    int value = 23;
    int index = -1;
    int left = 0;
    int right = numbers.Length() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (numbers[middle] == value)
        {
            index = middle;
            break;
        }

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    Print(index);
}
```



# 65. 어떤 값을 비교했는지 보기


## 이번에 배울 것

중간에 값을 출력하면 프로그램이 답을 찾는 과정을 추적할 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {2, 5, 8, 12, 16, 23, 38, 56};
    int value = 23;

    int left = 0;
    int right = numbers.Length() - 1;
    int comparisons = 0;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        comparisons = comparisons + 1;
        Print("Checking ", numbers[middle]);

        if (numbers[middle] == value)
            break;

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    Print("Comparisons: ", comparisons);
}
```

예제는 23을 찾으며 Checking 12, Checking 23을 출력합니다. 비교 횟수는 2입니다.

이번 예제는 비교 과정을 관찰하는 용도입니다. value를 없는 값으로 바꾸면 범위가 비어 끝나지만, 별도의 성공 안내는 출력하지 않습니다.

## Exercise — 비교 횟수 세기

Binary Search가 값을 찾을 때 몇 번 비교했는지 count를 추가해 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    int value = 17;
    int comparisons = 0;

    // Binary Search and count comparisons.

    Print("Comparisons: ", comparisons);
}
```

### Hint

while을 한 번 돌 때마다 comparisons를 1 증가시키세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    int value = 17;
    int comparisons = 0;
    int left = 0;
    int right = numbers.Length() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        comparisons = comparisons + 1;

        if (numbers[middle] == value)
            break;

        if (value < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }

    Print("Comparisons: ", comparisons);
}
```


# 66. 데이터가 많아지면 얼마나 일할까


## 이번에 배울 것

**시간 복잡도**는 데이터 개수가 늘 때 필요한 작업량이 어떻게 커지는지 나타냅니다. 실제 초 수와는 다릅니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> sizes = {10, 100, 1000};

    for (int i = 0; i < sizes.Length(); i = i + 1)
    {
        int n = sizes[i];
        int linear = n;
        Print("n = ", n, ", linear worst case = ", linear);
    }
}
```

순차 검색은 못 찾는 경우 원소 n개를 모두 검사합니다. n이 10, 100, 1000이면 최악의 비교 횟수도 10, 100, 1000입니다.

이런 증가를 O(n)이라고 씁니다. 이 예제는 시간을 측정하는 대신 작업량을 숫자로 보여 줍니다.

## Exercise — Linear 비교 횟수

20개의 값에서 없는 값을 Linear Search한다고 생각하고 실제 comparisons를 세어 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers(20);
    int comparisons = 0;

    // Search for 99 and count comparisons.

    Print(comparisons);
}
```

### Hint

값을 하나 볼 때마다 comparisons를 증가시키고 끝까지 찾지 못하게 하면 됩니다.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers(20);
    int comparisons = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        comparisons = comparisons + 1;
        if (numbers[i] == 99)
            break;
    }

    Print(comparisons);
}
```



# 67. 반씩 줄이는 일은 얼마나 반복될까


## 이번에 배울 것

범위를 매번 반으로 줄이면 데이터가 커져도 반복 횟수는 천천히 늘어납니다. 이런 증가를 O(log n)이라고 합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int n = 1024;
    int steps = 0;

    while (n > 0)
    {
        Print(n);
        n = n / 2;
        steps = steps + 1;
    }

    Print("Steps: ", steps);
}
```

1024를 정수 나눗셈으로 계속 반으로 줄입니다. 1024, 512, …, 1을 처리하므로 Steps: 11입니다.

이 수는 예제의 반복 횟수이지 모든 이진 검색의 정확한 비교 횟수는 아닙니다. Big-O는 증가 경향을 요약한 표기입니다.

## Exercise — 몇 번 반으로 나눌까

n=1000을 시작으로 n이 0이 될 때까지 2로 나누며 몇 단계가 필요한지 세세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    int n = 1000;
    int steps = 0;

    // Keep dividing by 2.

    Print(steps);
}
```

### Hint

while 안에서 `n = n / 2`와 count 증가를 함께 하세요.

**정답**

```cpp
void SmallMain()
{
    int n = 1000;
    int steps = 0;

    while (n > 0)
    {
        n = n / 2;
        steps = steps + 1;
    }

    Print(steps);
}
```


# 68. 두 번째로 큰 값 찾기


## 이번에 배울 것

새 문제를 풀기 전에 **무엇을 답으로 할지와 입력의 가정**을 정합니다. 이번에는 두 자리의 후보를 기억합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {8, 3, 12, 5, 10};

    int largest = numbers[0];
    int second = numbers[1];

    if (second > largest)
    {
        int temp = largest;
        largest = second;
        second = temp;
    }

    for (int i = 2; i < numbers.Length(); i = i + 1)
    {
        if (numbers[i] > largest)
        {
            second = largest;
            largest = numbers[i];
        }
        else if (numbers[i] > second)
        {
            second = numbers[i];
        }
    }

    Print("Second largest: ", second);
}
```

예제는 원소가 적어도 두 개이며, 두 번째 순위에 중복도 포함합니다. {9, 9, 3}이라면 답은 9입니다. 서로 다른 값 중 둘째라는 뜻은 아닙니다.

새 최댓값을 만나면 이전 최댓값을 second로 옮깁니다. 8, 3, 12, 5, 10에서는 답이 10입니다.

## Exercise — 두 번째로 작은 값

서로 다른 값이 두 개 이상 있다고 가정하고 두 번째로 작은 값을 찾으세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {8, 3, 12, 5, 10};

    // Find the second smallest value.
}
```

### Hint

smallest와 second를 기억하고, 새 값이 smallest보다 작을 때 두 값을 함께 갱신하세요.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {8, 3, 12, 5, 10};

    int smallest = numbers[0];
    int second = numbers[1];

    if (second < smallest)
    {
        int temp = smallest;
        smallest = second;
        second = temp;
    }

    for (int i = 2; i < numbers.Length(); i = i + 1)
    {
        if (numbers[i] < smallest)
        {
            second = smallest;
            smallest = numbers[i];
        }
        else if (numbers[i] < second)
        {
            second = numbers[i];
        }
    }

    Print(second);
}
```



# 69. 가장 큰 값이 몇 개인지 세기


## 이번에 배울 것

이미 아는 절차 두 개를 이어 붙이면 새 문제를 해결할 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {4, 9, 2, 9, 7};

    int largest = numbers[0];
    int countLargest = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == largest)
            countLargest = countLargest + 1;

    Print("Largest: ", largest);
    Print("How many: ", countLargest);
}
```

먼저 최댓값을 찾고, 두 번째 반복에서 그 값과 같은 원소를 셉니다. 출력은 Largest: 9, How many: 2입니다.

두 반복을 억지로 하나로 합치기보다 각 단계가 맡은 일을 먼저 분명히 하세요. 배열에는 원소가 하나 이상 있어야 합니다.

## Exercise — 가장 큰 값은 몇 번?

Array의 가장 큰 값을 먼저 찾고, 그 값이 몇 번 나타나는지 두 번째 loop에서 세세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {5, 9, 2, 9, 9, 4};

    // Find largest, then count it.
}
```

### Hint

첫 loop는 largest, 두 번째 loop는 `numbers[i] == largest`인 횟수를 셉니다.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {5, 9, 2, 9, 9, 4};
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    int count = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        if (numbers[i] == largest)
            count = count + 1;

    Print("Largest: ", largest);
    Print("Count: ", count);
}
```


# 70. 실행이 끝나도 값 남기기


## 이번에 배울 것

**파일**은 프로그램이 끝난 뒤에도 저장 장치에 남겨 둘 수 있는 데이터입니다. 텍스트 파일은 글자로 기록해 메모장으로 읽을 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    File file;

    file.Open("score.txt", FileMode::Write);
    file.Print("Alex");
    file.Print(1200);
    file.Close();

    Print("Saved score.txt");
}
```

소스를 저장한 뒤 실행하세요. score.txt에 Alex와 1200을 한 줄씩 기록합니다. FileMode::Write는 새로 쓰는 모드라서 기존 내용을 지웁니다. 직접 만든 연습 파일을 쓰세요.

Open → 쓰기 → Close 순서입니다. 상대 경로의 파일은 보통 저장한 소스 폴더에 생깁니다. 메모장으로 열어 두 줄을 확인하세요.

## Exercise — 이름과 나이 저장

`profile.txt`에 이름 한 줄과 나이 한 줄을 저장한 뒤 닫으세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    File file;

    // Save a name and age to profile.txt.
}
```

### Hint

Write mode로 열고 `file.Print`를 두 번 사용하세요.

**정답**

```cpp
void SmallMain()
{
    File file;

    file.Open("profile.txt", FileMode::Write);
    file.Print("Alex");
    file.Print(12);
    file.Close();

    Print("Saved");
}
```



# 71. 파일에서 값 다시 읽기


## 이번에 배울 것

저장했던 파일을 열면 이전 실행의 값을 되찾을 수 있습니다. **경로**는 어느 위치의 파일을 사용할지 나타냅니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    File file;

    file.Open("score.txt");

    String name = file.Input();
    int score = file.InputInt();

    file.Close();

    Print(name, "'s score: ", score);
}
```

먼저 앞 수업 예제로 score.txt를 만드세요. 이번 소스도 같은 폴더에 저장해야 같은 파일을 읽습니다.

Open의 기본 모드는 읽기입니다. Input은 첫 줄을 문자열로, InputInt는 둘째 줄을 정수로 읽습니다. Alex's score: 1200이 나오는지 보세요. 오류가 나면 파일 위치와 줄 내용을 확인하세요.

## Exercise — high score 저장하고 읽기

`highscore.txt`에 950을 저장한 뒤 다시 열어 int로 읽고 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    File file;

    // Save 950, close the file, then read it back.
}
```

### Hint

Write/Close 후 다시 Open하고 `InputInt()`를 사용하세요.

**정답**

```cpp
void SmallMain()
{
    File file;

    file.Open("highscore.txt", FileMode::Write);
    file.Print(950);
    file.Close();

    file.Open("highscore.txt");
    int score = file.InputInt();
    file.Close();

    Print("High score: ", score);
}
```


# 72. 숫자를 바이너리로 저장하기


## 이번에 배울 것

**바이너리 파일**은 정한 바이트 형식대로 값을 기록합니다. 숫자를 읽을 수 있는 글자로 바꾸어 저장하는 텍스트 파일과 구분합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    File file;

    file.Open("save.dat", FileMode::WriteBinary);
    file.WriteInt(3);
    file.WriteInt(1250);
    file.WriteReal(42.5);
    file.Close();

    Print("Binary save written");
}
```

WriteBinary로 열고 정수 두 개, 실수 한 개를 순서대로 씁니다. save.dat는 메모장으로 읽기 좋은 문장이 아닙니다.

읽을 때 사용할 값의 타입과 순서를 기억해야 합니다. 이 모드도 기존 파일을 지우므로 연습 파일로 실행하세요.

## Exercise — 게임 상태 저장

`game.dat`에 level=5, score=2300, playTime=18.75를 binary로 저장하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    int level = 5;
    int score = 2300;
    double playTime = 18.75;

    File file;

    // Save the three values to game.dat.
}
```

### Hint

WriteBinary mode에서 WriteInt 두 번, WriteReal 한 번을 사용하세요.

**정답**

```cpp
void SmallMain()
{
    int level = 5;
    int score = 2300;
    double playTime = 18.75;

    File file;
    file.Open("game.dat", FileMode::WriteBinary);
    file.WriteInt(level);
    file.WriteInt(score);
    file.WriteReal(playTime);
    file.Close();

    Print("Saved");
}
```



# 73. 쓴 순서대로 바이너리 읽기


## 이번에 배울 것

바이너리 데이터는 **쓴 타입과 같은 순서**로 읽어야 원래 값을 복원할 수 있습니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    File file;

    file.Open("save.dat", FileMode::ReadBinary);

    int level = file.ReadInt();
    int score = file.ReadInt();
    double playTime = file.ReadReal();

    file.Close();

    Print("Level: ", level);
    Print("Score: ", score);
    Print("Play time: ", playTime);
}
```

앞 수업으로 save.dat를 만든 뒤 같은 소스 폴더에서 실행하세요. ReadInt, ReadInt, ReadReal로 읽어 3, 1250, 42.5를 복원합니다.

바이너리가 언제나 더 좋은 것은 아닙니다. 사람이 확인하거나 오래 교환할 데이터에는 형식과 호환성을 따로 설계해야 합니다.

## Exercise — 저장하고 복원하기

`state.dat`에 int 7과 double 3.5를 저장하고, 다시 열어 두 값을 읽어 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    File file;

    // Write 7 and 3.5, then read them back.
}
```

### Hint

쓰기와 읽기 사이에 Close하고, 읽을 때 같은 타입과 순서를 사용하세요.

**정답**

```cpp
void SmallMain()
{
    File file;

    file.Open("state.dat", FileMode::WriteBinary);
    file.WriteInt(7);
    file.WriteReal(3.5);
    file.Close();

    file.Open("state.dat", FileMode::ReadBinary);
    int number = file.ReadInt();
    double value = file.ReadReal();
    file.Close();

    Print(number);
    Print(value);
}
```


# 74. 관련된 값 묶기


## 이번에 배울 것

**struct**는 관련된 값들을 묶는 새 타입을 정의합니다. Player 하나에 이름과 점수를 함께 담아 봅니다.

## 실행해 보기

**예제**

```cpp
struct Player
{
    String name;
    int score;
};

void SmallMain()
{
    Player player;

    player.name = "Alex";
    player.score = 1200;

    Print(player.name, ": ", player.score);
}
```

String과 int가 이미 있던 타입이라면 Player는 우리가 만든 타입입니다. player.name처럼 점으로 안의 값에 접근합니다.

예제는 Alex: 1200을 출력합니다. struct 정의의 닫는 중괄호 뒤에는 ;이 필요합니다.

## Exercise — Point 만들기

x와 y를 double로 가지는 `Point` struct를 만들고 (3.5, 7.0)을 저장해 출력하세요.

**연습 시작 코드**

```cpp
struct Point
{
    // Add x and y here.
    double x;
    double y;
};

void SmallMain()
{
    Point point;
    point.x = 3.5;
    point.y = 7.0;

    Print(point.x, ", ", point.y);
}
```

### Hint

`struct Point { double x; double y; };`로 시작하세요.

**정답**

```cpp
struct Point
{
    double x;
    double y;
};

void SmallMain()
{
    Point point;
    point.x = 3.5;
    point.y = 7.0;

    Print(point.x, ", ", point.y);
}
```



# 75. 묶은 값을 여러 개 담기


## 이번에 배울 것

직접 만든 타입도 배열의 원소가 될 수 있습니다. Array<Player>는 여러 선수의 정보를 담습니다.

## 실행해 보기

**예제**

```cpp
struct Player
{
    String name;
    int score;
};

void SmallMain()
{
    Array<Player> players = {
        {"Alex", 800},
        {"Mina", 1200},
        {"Sam", 950}
    };

    int best = 0;

    for (int i = 1; i < players.Length(); i = i + 1)
        if (players[i].score > players[best].score)
            best = i;

    Print("Winner: ", players[best].name);
}
```

players[i].score는 i번째 선수의 점수입니다. 최댓값 위치를 찾던 방법을 그대로 쓰고, 마지막에는 그 선수의 이름을 출력합니다.

예상 결과는 Winner: Mina입니다. 점수를 바꾸어 우승자가 달라지는지 보세요.

## Exercise — 최고 점수 찾기

name과 score를 가진 Player 세 명을 Array에 넣고 가장 높은 score의 Player 이름을 출력하세요.

**연습 시작 코드**

```cpp
struct Player
{
    String name;
    int score;
};

void SmallMain()
{
    Array<Player> players = {
        {"A", 10},
        {"B", 35},
        {"C", 20}
    };

    // Find and print the best player's name.
}
```

### Hint

Lesson의 best index 패턴을 사용하세요.

**정답**

```cpp
struct Player
{
    String name;
    int score;
};

void SmallMain()
{
    Array<Player> players = {
        {"A", 10},
        {"B", 35},
        {"C", 20}
    };

    int best = 0;

    for (int i = 1; i < players.Length(); i = i + 1)
        if (players[i].score > players[best].score)
            best = i;

    Print(players[best].name);
}
```


# 76. 데이터와 기능 함께 묶기


## 이번에 배울 것

**class**는 데이터와 그 데이터를 다루는 기능을 묶는 타입입니다. **객체**는 그 타입으로 만든 실제 대상입니다. 이런 도구도 직접 만들 수 있다는 정도로 살펴봅니다.

## 실행해 보기

**예제**

```cpp
class Counter
{
public:
    void AddOne()
    {
        value = value + 1;
    }

    int Value()
    {
        return value;
    }

private:
    int value = 0;
};

void SmallMain()
{
    Counter counter;

    counter.AddOne();
    counter.AddOne();

    Print(counter.Value());
}
```

Counter 객체는 자신이 센 값 value를 가집니다. AddOne을 두 번 호출하고 Value를 읽으면 2입니다.

public은 사용하는 쪽에 공개한 부분, private은 바깥에서 직접 접근하지 못하게 한 부분입니다. String이나 Window도 데이터와 관련 기능을 가진 객체로 사용해 왔습니다. 이번에는 생성자나 상속까지 배우지 않습니다.

## Exercise — Counter에 Reset 추가

Counter class에 값을 0으로 만드는 public `Reset()`을 추가하고 동작을 확인하세요.

**연습 시작 코드**

```cpp
class Counter
{
public:
    void AddOne()
    {
        value = value + 1;
    }

    void Reset()
    {
        // Reset value.
    }

    int Value()
    {
        return value;
    }

private:
    int value = 0;
};

void SmallMain()
{
    Counter counter;
    counter.AddOne();
    counter.AddOne();
    counter.Reset();
    Print(counter.Value());
}
```

### Hint

Reset 안에서 private value에 0을 대입하세요.

**정답**

```cpp
class Counter
{
public:
    void AddOne()
    {
        value = value + 1;
    }

    void Reset()
    {
        value = 0;
    }

    int Value()
    {
        return value;
    }

private:
    int value = 0;
};

void SmallMain()
{
    Counter counter;
    counter.AddOne();
    counter.AddOne();
    counter.Reset();
    Print(counter.Value());
}
```



# 77. 복사 대신 원본에 이름 붙이기


## 이번에 배울 것

**참조(reference)**는 기존 대상에 붙이는 다른 이름입니다. int& 매개변수는 전달한 정수의 원본을 가리킵니다.

## 실행해 보기

**예제**

```cpp
void AddOne(int x)
{
    x = x + 1;
    Print("Inside: ", x);
}

void SmallMain()
{
    int n = 10;

    AddOne(n);

    Print("Outside: ", n);
}
```

먼저 예제를 실행하면 Inside: 11, Outside: 10입니다. `AddOne(int x)`를 `AddOne(int& x)`로 바꾸어 다시 실행하세요. 이번에는 둘 다 11입니다.

처음에는 x가 복사본이었고, &를 붙인 뒤에는 n의 다른 이름이기 때문입니다. 원본을 바꾸겠다는 의도가 있을 때 사용합니다.

## Exercise — Swap 만들기

두 int의 원래 값을 서로 바꾸는 `Swap(int& a, int& b)` 함수를 만드세요.

**연습 시작 코드**

```cpp
void Swap(int& a, int& b)
{
    // Swap the original values.
}

void SmallMain()
{
    int x = 3;
    int y = 7;

    Swap(x, y);

    Print(x, ", ", y);
}
```

### Hint

temp에 a를 잠깐 저장한 뒤 a=b, b=temp 순서로 바꾸세요.

**정답**

```cpp
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SmallMain()
{
    int x = 3;
    int y = 7;

    Swap(x, y);

    Print(x, ", ", y);
}
```



# 78. 복사 없이 읽기만 하기


## 이번에 배울 것

**const 참조**는 원본을 복사하지 않고 읽되, 그 참조를 통해 바꾸지는 않겠다는 뜻입니다.

## 실행해 보기

**예제**

```cpp
int Sum(const Array<int>& numbers)
{
    int total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
        total = total + numbers[i];

    return total;
}

void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 9, 4};

    Print("Sum: ", Sum(numbers));
}
```

`const Array<int>& numbers`의 &는 원본 참조, const는 읽기 전용입니다. 출력은 Sum: 25입니다.

배열 전체를 복사할 필요 없이 합계를 구합니다. 값을 바꾸려 하면 컴파일 오류입니다. 앞에서 쓴 Array<int> 매개변수도 올바르지만 배열이 크면 복사 비용이 커질 수 있습니다.

## Exercise — FindLargest 개선하기

앞에서 배운 `FindLargest(Array<int> numbers)`를 `const Array<int>&`를 사용하도록 바꾸세요. 함수는 Array를 수정하지 않습니다.

**연습 시작 코드**

```cpp
int FindLargest(Array<int> numbers)
{
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    return largest;
}

void SmallMain()
{
    Array<int> numbers = {4, 12, 3, 9};
    Print(FindLargest(numbers));
}
```

### Hint

parameter만 `const Array<int>& numbers`로 바꾸고 나머지 알고리즘은 그대로 사용할 수 있습니다.

**정답**

```cpp
int FindLargest(const Array<int>& numbers)
{
    int largest = numbers[0];

    for (int i = 1; i < numbers.Length(); i = i + 1)
        if (numbers[i] > largest)
            largest = numbers[i];

    return largest;
}

void SmallMain()
{
    Array<int> numbers = {4, 12, 3, 9};
    Print(FindLargest(numbers));
}
```


# 79. 이미 만들어진 도구 사용하기


## 이번에 배울 것

**라이브러리**는 프로그램에서 쓸 수 있도록 만든 도구들의 모음입니다. C++ 표준 라이브러리는 여러 환경에서 공통으로 사용하는 도구를 제공합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    Array<int> numbers = {8, 3, 12, 5};

    int smallest = std::min(8, 3);
    int largest = std::max(8, 12);

    Print("Min: ", smallest);
    Print("Max: ", largest);
}
```

std::min은 두 값 중 작은 값, std::max는 큰 값을 돌려줍니다. 예상 출력은 Min: 3, Max: 12입니다.

std::는 표준 라이브러리에 속한 이름이라는 표시입니다. 지금은 Small IDE가 필요한 기본 헤더를 준비해 줍니다.

## Exercise — min과 max

두 int 17과 42에 대해 `std::min`과 `std::max`를 사용해 작은 값과 큰 값을 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // Print the smaller and larger values using std::min and std::max.
}
```

### Hint

`Print(std::min(17, 42));`처럼 표준 함수를 Print 안에서도 바로 사용할 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    Print(std::min(17, 42));
    Print(std::max(17, 42));
}
```



# 80. 음수의 크기 구하기


## 이번에 배울 것

**절댓값**은 수직선에서 0까지의 거리입니다. std::abs로 구합니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    int a = -12;
    int b = 7;

    Print("Absolute: ", std::abs(a));
    Print("Smaller: ", std::min(a, b));
}
```

-12의 절댓값은 12입니다. 예상 출력은 Absolute: 12, Smaller: -12입니다.

함수의 이름과 입력·결과를 알면 내부 구현을 다시 만들지 않고 사용할 수 있습니다. 값의 범위에는 한계가 있으므로 여기서는 작은 정수로 연습합니다.

## Exercise — 절댓값

-25의 절댓값을 `std::abs`로 구해 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // Use a Standard Library function.
}
```

### Hint

`std::abs(-25)`의 결과는 int 25입니다.

**정답**

```cpp
void SmallMain()
{
    Print(std::abs(-25));
}
```


# 81. 표준 문자열과 배열 만나기


## 이번에 배울 것

**컨테이너**는 여러 값을 담는 도구입니다. std::string과 std::vector는 익숙한 문자열·배열에 대응하는 표준 도구입니다.

## 실행해 보기

**예제**

```cpp
void SmallMain()
{
    std::string text = "Hello";
    std::vector<int> numbers = {3, 7, 2, 9};

    Print(text);
    Print("Characters: ", text.size());
    Print("Numbers: ", numbers.size());
    Print("First number: ", numbers[0]);
}
```

길이를 묻는 이름이 Length() 대신 size()입니다. 예제는 Hello, Characters: 5, Numbers: 4, First number: 3을 출력합니다.

대괄호의 위치는 여전히 0부터입니다. 표준 컨테이너의 []는 Small처럼 범위 오류를 알려 준다고 기대하면 안 됩니다.

## Exercise — vector에 값 추가

`std::vector<int>`에 5, 10을 넣어 만들고 `push_back(15)`로 하나 더 추가한 뒤 모두 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    std::vector<int> numbers = {5, 10};

    // Add 15 and print every value.
}
```

### Hint

range-based for를 쓰면 `for (int value : numbers)`로 모든 값을 볼 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    std::vector<int> numbers = {5, 10};
    numbers.push_back(15);

    for (int value : numbers)
        Print(value);
}
```



# 82. 원소를 추가하고 하나씩 읽기


## 이번에 배울 것

std::vector는 원소를 뒤에 추가할 수 있습니다. **범위 기반 for**는 컨테이너의 원소를 하나씩 꺼내 반복합니다.

## 실행해 보기

**예제**

```cpp
int Sum(const std::vector<int>& numbers)
{
    int total = 0;

    for (int value : numbers)
        total = total + value;

    return total;
}

void SmallMain()
{
    std::vector<int> numbers = {10, 20, 30};
    numbers.push_back(40);

    Print("Sum: ", Sum(numbers));
}
```

push_back(40)은 뒤에 40을 붙입니다. `for (int value : numbers)`는 각 원소 값을 value로 받아 합산합니다. 결과는 Sum: 100입니다.

이 형태의 value는 복사한 정수이므로 value를 바꿔도 배열 원소가 바뀌지 않습니다. size()의 타입은 int와 다를 수 있어 큰 크기를 다룰 때는 타입도 확인해야 합니다.

## Exercise — std::string 함수

`const std::string&`을 받아 길이를 돌려주는 `TextLength` 함수를 만들고 "Small"의 길이를 출력하세요.

**연습 시작 코드**

```cpp
int TextLength(const std::string& text)
{
    // Return the length.
    return 0;
}

void SmallMain()
{
    std::string text = "Small";
    Print(TextLength(text));
}
```

### Hint

`text.size()`는 표준 C++의 unsigned 크기 type을 돌려줍니다. 이 연습의 return type은 int이므로 `static_cast<int>(text.size())`로 명시적으로 바꾸어 반환하세요.

**정답**

```cpp
int TextLength(const std::string& text)
{
    return static_cast<int>(text.size());
}

void SmallMain()
{
    std::string text = "Small";
    Print(TextLength(text));
}
```


# 83. 필요한 도구를 코드에 적기


## 이번에 배울 것

**헤더**는 다른 코드의 도구를 사용할 수 있도록 선언을 알려 주는 파일입니다. #include는 그 헤더를 포함하는 지시문입니다.

## 실행해 보기

**예제**

```cpp
#include <iostream>
#include <string>

void SmallMain()
{
    std::string name;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Hello, " << name << "\n";
}
```

iostream은 표준 입출력, string은 std::string을 위해 포함합니다. std::cout << 값은 출력, std::getline(std::cin, name)은 한 줄 입력입니다. Alex를 넣으면 Hello, Alex가 나옵니다.

이번에는 SmallMain을 유지하며 입출력 도구만 바꿉니다.

## Exercise — std::cout 사용하기

`#include <iostream>`을 적고 `std::cout`으로 `Hello C++`과 줄바꿈을 출력하세요. `SmallMain()`은 아직 그대로 사용합니다.

**연습 시작 코드**

```cpp
#include <iostream>

void SmallMain()
{
    // Print Hello C++ with std::cout.
}
```

### Hint

`std::cout << "Hello C++" << "\n";`처럼 값을 output stream으로 보낼 수 있습니다.

**정답**

```cpp
#include <iostream>

void SmallMain()
{
    std::cout << "Hello C++" << "\n";
}
```



# 84. 어디에 속한 이름인지 표시하기


## 이번에 배울 것

**이름 공간(namespace)**은 이름들을 묶어 구별하는 영역입니다. ::로 어느 영역의 이름인지 표시합니다.

## 실행해 보기

**예제**

```cpp
#include <iostream>
#include <string>

void SmallMain()
{
    Small::String smallText = "Small namespace";
    Small::Print(smallText);

    std::string standardText = "Standard namespace";
    std::cout << standardText << "\n";
}
```

Small::Print와 std::cout은 서로 다른 도구입니다. 예제는 Small namespace와 Standard namespace를 차례로 출력합니다.

이름 공간은 객체가 아닙니다. window.Show()의 점과 Small::Print의 ::를 구분하세요.

## Exercise — 표준 입출력으로 이름 읽기

`std::string name`을 만들고 `std::getline(std::cin, name)`으로 한 줄을 입력받아 `std::cout`으로 다시 출력하세요.

**연습 시작 코드**

```cpp
#include <iostream>
#include <string>

void SmallMain()
{
    std::string name;

    // Ask for a name, read a line, and print it.
}
```

### Hint

`<iostream>`과 `<string>`을 include하고, 먼저 prompt를 cout으로 출력한 뒤 getline을 호출하세요.

**정답**

```cpp
#include <iostream>
#include <string>

void SmallMain()
{
    std::string name;

    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "\n";
}
```


# 85. 진짜 시작 함수 main 쓰기


## 이번에 배울 것

**main**은 C++ 프로그램의 시작 함수입니다. 지금까지는 Small이 준비한 main이 SmallMain을 호출했습니다. 이제 준비와 종료까지 직접 적습니다.

## 실행해 보기

**예제**

```cpp
#include <small.h>

int main()
{
    Small::InitializeSmall();

    Small::Print("Hello from main!");

    Small::ShutdownSmall();
    return 0;
}
```

이 IDE에서 직접 main을 쓰면 자동 헤더·이름 공간 지원도 끝납니다. 그래서 small.h를 포함하고 Small::를 씁니다.

InitializeSmall → 내 작업 → ShutdownSmall 순서입니다. return 0은 정상 종료를 나타냅니다. Hello from main!이 출력되는지 확인하세요.

## Exercise — main으로 옮기기

`SmallMain` Hello 프로그램을 진짜 `main()`으로 바꾸세요. `#include <small.h>`를 직접 적고 `Small::InitializeSmall()`, `Small::Print`, `Small::ShutdownSmall()`을 사용하세요.

**연습 시작 코드**

```cpp
#include <small.h>

int main()
{
    // Initialize Small, print a message, shut Small down, and return 0.
}
```

### Hint

함수 이름을 main으로 바꾸는 것만이 아니라 return type을 `int`로 하고 끝나기 전에 `Small::ShutdownSmall();`을 호출한 뒤 `return 0;`을 적어 보세요.

**정답**

```cpp
#include <small.h>

int main()
{
    Small::InitializeSmall();

    Small::Print("Hello from main!");

    Small::ShutdownSmall();
    return 0;
}
```



# 86. 창을 정리한 뒤 런타임 끝내기


## 이번에 배울 것

**런타임**은 창·소리 같은 실행 기능을 지원하는 기반입니다. 그 기능을 쓰는 객체를 먼저 정리한 뒤 기반을 종료해야 합니다.

## 실행해 보기

**예제**

```cpp
#include <small.h>

int main(int argc, char* argv[])
{
    Small::InitializeSmall(argc, argv);

    {
        Small::Window window;
        window.SetTitle("Real main()");
        window.Open(500, 300);

        while (window.IsOpen())
        {
            window.Clear(Small::Black);
            window.DrawText(30, 80, "This is ordinary C++ main()");
            window.Show();
        }
    } // Destroy Window before shutting down the runtime.
    Small::ShutdownSmall();
    return 0;
}
```

안쪽 중괄호 범위가 끝나면 Window 객체가 정리됩니다. 그 뒤 ShutdownSmall을 호출합니다. 창을 닫는 것과 객체 수명이 끝나는 것은 다릅니다.

argc와 argv는 명령줄로 전달된 정보를 받는 형태입니다. 이번은 선택 심화입니다. 포인터 표기를 지금 모두 외울 필요는 없습니다.

## Exercise — argc와 argv 넘기기

`#include <small.h>`와 `int main(int argc, char* argv[])`를 작성하고 argc, argv를 `Small::InitializeSmall`에 전달한 뒤 argc를 출력하고 프로그램을 끝내기 전에 `Small::ShutdownSmall()`을 호출하세요.

**연습 시작 코드**

```cpp
#include <small.h>

int main(int argc, char* argv[])
{
    // Initialize Small with argc and argv.
    // Print argc, then shut Small down before returning.

    return 0;
}
```

### Hint

`Small::InitializeSmall(argc, argv);` 다음에 `Small::Print("argc: ", argc);`를 사용하고 `return 0;` 전에 `Small::ShutdownSmall();`을 호출하세요.

**정답**

```cpp
#include <small.h>

int main(int argc, char* argv[])
{
    Small::InitializeSmall(argc, argv);

    Small::Print("argc: ", argc);

    Small::ShutdownSmall();
    return 0;
}
```


# 87. Small 없이 인사하기


## 이번에 배울 것

이미 배운 표준 도구만 사용하면 Small 없이도 같은 일을 할 수 있습니다.

## 실행해 보기

**예제**

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Hello, " << name << "\n";

    return 0;
}
```

SmallMain 대신 main, String 대신 std::string, Input 대신 getline, Print 대신 cout을 씁니다. Alex를 입력하면 Hello, Alex가 나옵니다.

Small 기능을 쓰지 않으므로 small.h나 InitializeSmall, ShutdownSmall도 필요 없습니다.

## Exercise — Small 없는 합계

Small API 없이 `std::vector<int>`의 값을 모두 더해 `std::cout`으로 출력하는 main 프로그램을 작성하세요.

**연습 시작 코드**

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {10, 20, 30};
    int total = 0;

    // Sum and print using only standard C++.

    return 0;
}
```

### Hint

`#include <iostream>`과 `#include <vector>`를 직접 적으세요.

**정답**

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {10, 20, 30};
    int total = 0;

    for (int value : numbers)
        total = total + value;

    std::cout << total << "\n";

    return 0;
}
```



# 88. 표준 C++에서도 같은 절차 쓰기


## 이번에 배울 것

도구의 표기가 바뀌어도 **값을 저장하고 반복하며 합산하는 절차**는 그대로입니다.

## 실행해 보기

**예제**

```cpp
#include <iostream>
#include <vector>

int Sum(const std::vector<int>& numbers)
{
    int total = 0;

    for (int value : numbers)
        total = total + value;

    return total;
}

int main()
{
    std::vector<int> numbers = {3, 7, 2, 9, 4};

    std::cout << "Sum: " << Sum(numbers) << "\n";

    return 0;
}
```

vector의 값을 범위 기반 for로 더하고, 함수가 돌려준 값을 cout으로 출력합니다. 결과는 Sum: 25입니다.

지금까지의 변수·조건·반복·함수는 모두 일반 C++에서도 사용됩니다. 이후에는 만들고 싶은 것에 필요한 도구를 조금씩 더 배우면 됩니다.

## Exercise — 첫 standard C++ 함수

`const std::string&`을 받아 `Hello, 이름!`을 std::cout으로 출력하는 `Greet` 함수를 만들고 main에서 호출하세요.

**연습 시작 코드**

```cpp
#include <iostream>
#include <string>

// Write Greet here.

int main()
{
    std::string name = "Alex";

    // Call Greet.

    return 0;
}
```

### Hint

`#include <iostream>`과 `#include <string>`이 필요합니다.

**정답**

```cpp
#include <iostream>
#include <string>

void Greet(const std::string& name)
{
    std::cout << "Hello, " << name << "!\n";
}

int main()
{
    std::string name = "Alex";

    Greet(name);

    return 0;
}
```
