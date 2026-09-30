# 상세 설명 참고서

이 파일은 기존 38강의 설명과 코드를 보존한 참고서입니다. 본문의 장 번호는 **기존 38강 번호**이며 작은 걸음 수업 번호가 아닙니다. 짧은 수업을 마친 뒤 질문이 생길 때 찾아보세요.


# 기존 1강 — Hello, Small C++!


## 프로그램과 코드는 무엇인가요?

**프로그램**은 컴퓨터가 할 일을 정해 놓은 것입니다. 그 일을 C++ 같은 프로그래밍 언어의 규칙에 맞춰 글로 적은 것을 **소스 코드**, 줄여서 코드라고 합니다. 이 튜토리얼에서는 글자를 출력하는 작은 프로그램부터 시작합니다.

**실행**은 그 코드에 적힌 일을 실제로 시키는 것입니다. Small IDE에서 Run을 누르면 코드를 검사하고 실행 가능한 프로그램으로 만드는 **컴파일** 과정을 거친 뒤 실행합니다. IDE는 코드를 쓰고 실행하는 일을 도와주는 개발 도구입니다.

규칙에 맞지 않아 프로그램을 만들지 못하면 컴파일 오류이고, 만들어진 프로그램을 실행하다 문제가 생기면 실행 중 오류입니다. 처음에는 이 둘을 구분하고 Diagnostics의 설명을 읽는 것부터 익히면 됩니다.

## 컴퓨터에게 첫 인사를 시켜 봅시다
 화면에 내가 쓴 말이 나타나게 해 볼까요? 아래 **Try This Code**를 누르면 코드가 새 편집 탭으로 복사됩니다. IDE의 **Run** 또는 **F5**를 누르세요.

 글자는 별도의 **콘솔 창**에 나타납니다. IDE 아래의 Diagnostics는 컴파일이나 실행 중 문제가 생겼을 때 읽는 곳입니다. 튜토리얼 창은 열어 둔 채 편집기로 돌아갈 수 있습니다.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
 {
     Print("Hello, Small C++!");
 }
```

## 문자열은 글자들이 순서대로 이어진 데이터입니다

**문자열(string)**은 글자들이 순서대로 이어진 데이터입니다. 이름이나 인사말, 문장 등을 나타낼 때 사용합니다. 공백, 숫자 모양의 글자, 쉼표와 느낌표 같은 기호도 문자열에 들어갈 수 있습니다.

C++ 코드에서는 `"Hello, Small C++!"`처럼 **큰따옴표**로 문자열을 나타냅니다. 따옴표는 문자열의 시작과 끝을 표시하며, 실제 내용에 포함되지 않습니다. 단어 사이의 공백과 마지막 느낌표는 내용의 일부입니다.

`"A"`처럼 글자 하나만 들어 있어도 문자열입니다. `""`는 글자가 하나도 없는 **빈 문자열**이고, `" "`는 공백 하나가 들어 있는 문자열이므로 서로 다릅니다. `"123"`도 숫자 모양의 글자로 된 문자열입니다. 계산에 사용하는 수와의 차이는 다음 장에서 배웁니다.

## 한 줄씩 읽어 봅시다

`Print("Hello, Small C++!");`는 이 문자열을 Print에 전달하여 화면에 출력한 다음 줄을 바꾸는 문장입니다. 문장 끝에는 `;`를 붙입니다. 큰따옴표 자체는 화면에 나오지 않습니다.

직접 확인: 큰따옴표 안의 내용만 `A`, `123`, 빈 내용으로 차례로 바꾸어 실행해 보세요. 각각 A, 123, 빈 줄이 출력됩니다. Print는 내용이 없어도 출력 뒤에 줄을 바꿉니다. 따옴표를 지우는 것은 빈 문자열을 만드는 것과 다릅니다.

## 함수는 이름으로 부탁하는 일입니다

**함수는 특정한 일을 수행하는 코드 묶음에 이름을 붙인 것입니다.** 방금 사용한 Print는 화면에 글자를 출력하는 함수입니다. 출력에 필요한 세부 코드는 Small이 준비해 두었으므로, 우리는 Print라는 이름으로 그 일을 시킬 수 있습니다.

`Print("Hello");`처럼 함수 이름 뒤에 괄호를 붙여 그 일을 실행시키는 것을 **함수 호출**이라고 합니다. 괄호 안의 `"Hello"`는 출력할 내용입니다. 함수에 일을 부탁하면서 필요한 값을 함께 전달한 것입니다.

지금은 “Print를 호출하면 글자가 출력된다”는 정도를 이해하면 충분합니다. 함수 안에서 출력이 어떻게 구현되어 있는지까지 알 필요는 없습니다.

## SmallMain은 우리가 할 일을 적는 함수입니다

Print가 이미 준비된 함수라면, `SmallMain`은 우리가 내용을 채우는 함수입니다. `void SmallMain()`과 그 뒤의 중괄호는 SmallMain이라는 함수가 할 일을 **정의하는 부분**입니다. `{`와 `}` 사이에 실행할 명령을 적습니다.

프로그램을 실행하면 Small이 준비를 마친 뒤 SmallMain을 호출합니다. 그러면 중괄호 안의 명령이 위에서 아래로 실행됩니다. 그 안에서 Print를 호출하면 글자가 출력되고, 출력이 끝나면 다음 명령으로 넘어갑니다.

즉, SmallMain은 우리가 프로그램의 일을 적어 두는 곳이고, Print는 그 일을 하는 중에 사용하는 도구입니다. 지금은 SmallMain의 틀을 유지하며 안쪽 명령을 바꾸어 보세요. 직접 다른 함수를 만드는 방법은 9장에서 배웁니다.

 아래 코드는 Print를 세 번 사용합니다. 어떤 순서로 나올지 먼저 예상해 보세요.

## 조금 바꾸어 보기

**예제**

```cpp
void SmallMain()
 {
     Print("***************");
     Print("* Hello!      *");
     Print("***************");
 }
```

## 한 곳만 바꾸어 보세요
 `Hello!`를 다른 말로 바꾼 뒤 다시 Run을 눌러 보세요. 코드를 저장하려면 **Ctrl+S**를 사용합니다. Try로 연 코드는 자신의 복사본이므로 튜토리얼 원본은 바뀌지 않습니다.

 `Print`의 대문자 P와 큰따옴표를 확인하세요. 오류가 나면 Diagnostics에서 설명을 읽고 고친 뒤 다시 실행하면 됩니다. 실패해도 괜찮습니다.

## 처음 보이는 기호는 어디까지 알면 될까요?

`void SmallMain()`에서 SmallMain은 Small이 준비를 마친 뒤 호출하는 함수 이름입니다. `void`는 이 함수가 호출한 쪽에 결과값을 돌려주지 않는다는 뜻입니다. 화면에 글자를 출력하지 못한다는 뜻은 아닙니다. 함수와 반환값은 9장에서 자세히 배웁니다.

빈 `()`는 이 함수가 전달받는 값이 없다는 표시이고, `{}`는 실행할 문장들을 묶습니다. 지금은 이 틀을 유지하고 중괄호 안의 명령을 바꾸면 됩니다. `Print("Hello");`의 괄호 안에는 출력할 글자를 전달합니다.

C++은 대소문자를 구분합니다. `Print`와 `print`는 서로 다른 이름입니다. 들여쓰기는 사람이 코드의 묶음을 보기 쉽게 합니다. 문자열 밖의 줄바꿈과 공백은 대체로 배치를 위한 것이지만, 이름을 중간에서 나누거나 문자열 안의 공백을 지우면 의미가 달라집니다.

앞으로 단순한 대입이나 함수 호출 문장 끝에는 `;`을 붙입니다. 모든 줄 끝에 붙이는 것은 아닙니다. 중괄호로 묶은 if와 반복문은 뒤에서 따로 배웁니다.

## 코드에 메모를 남기는 `//`

`//` 뒤에 쓰는 글은 **comment(주석)** 입니다. 컴퓨터가 실행하는 명령이 아니라 코드를 읽는 사람에게 남기는 메모입니다.

예를 들어 `// 화면에 인사말을 출력합니다.`처럼 적을 수 있습니다. `//`부터 그 줄의 끝까지만 주석이 됩니다.

주석은 코드를 설명할 때뿐 아니라 코드를 잠깐 실행하지 않고 시험해 볼 때도 편리합니다. `// Print("잠시 실행하지 않음");`처럼 앞에 `//`를 붙이면 그 줄은 실행되지 않습니다.

앞으로 Examples에서도 코드가 이미 말해 주는 내용을 반복하기보다, 코드 덩어리의 목적이나 중요한 이유를 설명하는 주석을 만나게 됩니다.

## Exercise — 이름 출력하기

자신의 이름을 한 줄로 출력하세요. 예를 들어 `Alex`라고 쓸 수 있습니다.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      // Print your name here.
  }
```

### Hint

`Print("Alex");`에서 큰따옴표 안을 자신의 이름으로 바꿔 보세요.

**정답**

```cpp
void SmallMain()
  {
      Print("Alex");
  }
```

## Exercise — 세 줄 자기소개

이름, 좋아하는 것, 만들고 싶은 프로그램을 각각 한 줄씩 출력하세요. 내용에는 정답이 없습니다.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      // Print three lines about yourself.
  }
```

### Hint

Print를 세 번 쓰면 세 줄을 만들 수 있습니다.

**정답**

```cpp
void SmallMain()
  {
      Print("My name is Alex.");
      Print("I like drawing.");
      Print("I want to make a game.");
  }
```


# 기존 2강 — Variables and Values


## 변수는 무엇인가요?

게임은 현재 점수를 기억해야 하고, 계산기는 입력한 숫자를 기억해야 합니다. 이처럼 프로그램이 실행되는 동안 값을 저장하고 다시 사용하려면 **변수**를 만듭니다.

변수는 **값을 저장해 두는, 이름이 붙은 공간**이라고 생각하면 됩니다. 이름으로 저장된 값을 읽을 수 있고, 새 값을 저장해 내용을 바꿀 수도 있습니다. 값이 들어 있는 이름표 붙은 상자를 떠올려 보세요. 실제로 컴퓨터에서는 실행 중 사용하는 값을 보관하는 **메모리**에 값을 저장합니다.

이름과 값은 다릅니다. score라는 변수에 10을 저장했다가 20으로 바꾸어도 이름은 여전히 score입니다. 바뀌는 것은 그 안의 값입니다.

## 먼저 정수를 담아 보기

변수를 만들 때는 담을 값의 종류인 **데이터 타입**을 함께 적습니다. 이번 장에서는 **int**, 즉 정수를 저장하는 타입을 사용합니다. 정수는 0, 10, -3처럼 소수 부분이 없는 수입니다. 다른 종류의 값과 타입은 다음 장에서 배웁니다.

## 변수를 만들고 처음 값을 넣기

`int score = 10;`을 부분별로 읽어 봅시다.

- `int`: 정수를 저장하겠다는 뜻입니다.
- `score`: 새로 만드는 변수의 이름입니다.
- `= 10`: 처음 값으로 10을 넣습니다.
- `;`: 이 문장이 끝났음을 나타냅니다.

변수를 사용할 수 있도록 이름과 타입을 알려 주는 것을 **선언**이라고 하고, 처음 값을 넣는 것을 **초기화**라고 합니다. 이 문장은 변수를 만들면서 초기화도 합니다. 이 과정에서는 변수를 만들 때 반드시 처음 값을 넣으세요. 초기화하지 않은 지역 int의 값을 읽으면 안 됩니다.

## 이름으로 값을 읽고 바꾸기

**예제**

```cpp
void SmallMain()
{
    int score = 10;
    Print(score);
    Print("score");
    score = 20;
    Print(score);
}
```

출력은 10, score, 20 순서입니다. `Print(score);`는 score에 저장된 값을 읽어 출력합니다. `Print("score");`는 큰따옴표 안의 글자 score를 그대로 출력합니다.

`score = 20;`은 이미 만든 변수의 값을 바꾸는 **대입**입니다. 이전 값 10은 새 값 20으로 바뀝니다. 기존 변수에 값을 대입할 때는 int를 다시 적지 않습니다. 같은 범위에서 `int score`를 또 적으면 새 변수를 같은 이름으로 만들려는 것이 되어 오류가 납니다.

## 변수 이름과 바뀌지 않는 값

이 과정에서는 이름에 영문자·숫자·밑줄을 사용하고, 영문자로 시작하세요. 공백은 넣지 않습니다. `playerScore`와 `playerscore`는 다르고, `int`나 `if` 같은 C++ 예약어는 이름으로 쓸 수 없습니다.

`const int MaxScore = 100;`은 바꾸지 않을 값에 이름을 붙입니다. 이후 MaxScore에 다른 값을 대입하면 컴파일 오류입니다. 변수는 사용할 값을 정해 초기화하고 시작하세요.

## 글자와 값을 함께 출력하기

`Print("Age: ", age);`는 문자열과 변수 값을 순서대로 이어 출력합니다. 쉼표가 화면에 나오거나 공백을 자동으로 넣어 주는 것은 아닙니다. 필요한 공백은 큰따옴표 안에 넣습니다. age에 10이 들어 있다면 `Age: 10`이 출력됩니다.

## Exercise — 나이 변수

int 변수 age에 자신의 나이를 넣고 `Age: ` 뒤에 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      // Create age, then print it.
  }
```

### Hint

`int age = 10;`처럼 만든 뒤 `Print("Age: ", age);`를 사용합니다.

**정답**

```cpp
void SmallMain()
  {
      int age = 10;
      Print("Age: ", age);
  }
```



# 기존 3강 — Data Types


## 값에는 종류가 있습니다 — 데이터 타입

프로그램은 점수 10, 길이 3.5, 참·거짓, 글자처럼 여러 종류의 값을 다룹니다. **데이터 타입(data type)**은 값의 종류와 그 값에 사용할 수 있는 연산 등을 정하는 규칙입니다. 변수를 만들 때 어떤 타입의 값을 저장할지 함께 적습니다.

**int는 정수를 저장하는 타입입니다.** 정수는 0, 1, 10, -3처럼 소수 부분이 없는 수입니다. 사람 수, 점수, 남은 기회처럼 하나씩 세는 값에 사용합니다. 예를 들어 `int lives = 3;`은 남은 기회 3을 저장합니다. int도 저장 범위가 무한하지는 않습니다.

**double은 소수 부분이 있는 수를 표현하는 데 사용하는 타입입니다.** `double height = 1.75;`처럼 키나 길이, 시간, 속도 등에 사용합니다. 2.0처럼 정수와 같은 값도 저장할 수 있습니다. 다만 모든 실수를 정확히 저장하는 것은 아니며, 표현할 수 있는 범위와 정밀도에 한계가 있습니다.

int 변수가 값을 바꿀 때마다 double이나 다른 타입으로 변하는 것은 아닙니다. 변수의 타입은 선언할 때 정해집니다. 소수 부분이 필요한 값에는 처음부터 double을 선택하세요.

## 참·거짓과 문자에도 타입이 있습니다

**bool은 참 또는 거짓을 저장하는 타입입니다.** 값은 `true`와 `false` 두 가지입니다. `bool ready = true;`는 준비되었다는 상태를 기억합니다. 6장에서 조건에 따라 행동을 바꿀 때 사용합니다. 지금 Small의 Print는 true를 1, false를 0으로 출력합니다.

## 문자 하나와 문자열을 구분하기 — char

**문자**는 글자나 기호 하나를 나타냅니다. 이 장에서는 영문자 A, 숫자 모양의 글자 7, 기호 !처럼 char로 표현할 수 있는 문자부터 시작합니다. C++ 코드에서는 `'A'`, `'7'`, `'!'`처럼 **작은따옴표**로 이런 문자 값을 씁니다.

**char는 이런 문자 값을 저장할 때 사용하는 타입입니다.** `char grade = 'A';`는 char 타입의 변수 grade를 만들고 문자 값 'A'를 저장합니다. `Print(grade);`를 실행하면 A가 출력됩니다. `grade = 'B';`로 바꾸면 이후에는 B가 출력됩니다.

다음 표기들은 모양이 비슷해도 의미가 다릅니다.

- `7`: 계산에 사용하는 정수입니다. `7 + 1`은 8입니다.
- `'7'`: 숫자 모양의 문자 하나입니다. 수량 7을 저장하려는 표기가 아닙니다.
- `"7"`: 문자 하나가 들어 있는 문자열입니다.
- `'A'`와 `"A"`: 각각 문자 값과 문자열입니다. 둘 다 A로 출력되어도 같은 종류의 값은 아닙니다.

`char grade = "A";`처럼 큰따옴표의 문자열을 char에 그대로 넣을 수는 없습니다. char 변수에 영문자 A를 저장하려면 작은따옴표를 사용하세요. char에 산술 연산을 하면 문자의 내부 숫자 표현을 사용하는 정수 계산이 일어날 수 있으므로, 글자 '7'을 수량 7로 자동 변환한다고 생각하면 안 됩니다.

한글까지 모든 글자 하나를 char 하나에 담을 수 있는 것은 아닙니다. char는 **한 바이트**를 저장하며, 바이트는 컴퓨터의 데이터 크기 단위입니다. UTF-8에서 한글 한 글자는 여러 바이트로 표현됩니다. 이 장의 char 연습은 영문자와 기본 기호로 진행하세요. 한글 이름처럼 문자열 전체를 저장하고 다루는 String 타입은 5장에서 사용하고 10장에서 더 배웁니다.

직접 확인: 아래 예제의 grade를 'B'로 바꾸면 Grade: B가 출력됩니다. 7, '7', "7"을 각각 정수·문자·문자열로 구별해 보세요.

## 타입을 골라 사용해 보기

**예제**

```cpp
void SmallMain()
{
    int students = 20;
    double seconds = 12.5;
    bool ready = true;
    char grade = 'A';
    Print("Students: ", students);
    Print("Seconds: ", seconds);
    Print("Ready: ", ready);
    Print("Grade: ", grade);
}
```

학생 수 students는 정수이므로 int, 달리기 시간 seconds는 소수 부분이 필요하므로 double입니다. 준비 여부 ready는 bool, 영문 등급 grade는 char입니다.

예상 출력은 `Students: 20`, `Seconds: 12.5`, `Ready: 1`, `Grade: A`입니다. double에 2.0을 저장해도 출력은 2로 보일 수 있습니다. 출력 모양만으로 타입을 판단하지 마세요.

직접 확인: seconds를 13.2로, ready를 false로 바꾸고 결과를 예측해 보세요.

## Exercise — 값에 맞는 타입

남은 기회 3, 키 1.45, 준비 여부 true, 영문 등급 'B'를 각각 lives, height, ready, grade라는 변수에 저장하고 출력하세요. 값마다 어떤 타입을 골랐는지 설명해 보세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // 값에 맞는 타입으로 네 변수를 만들고 출력하세요.
}
```

### Hint

하나씩 세는 값은 int, 소수 부분이 필요한 값은 double, 참·거짓은 bool, 영문자 하나는 char를 사용합니다.

**정답**

```cpp
void SmallMain()
{
    int lives = 3;
    double height = 1.45;
    bool ready = true;
    char grade = 'B';
    Print(lives);
    Print(height);
    Print(ready);
    Print(grade);
}
```


# 기존 4강 — Calculations and Operators


## 연산자는 무엇인가요?

**연산자**는 값에 계산이나 비교 같은 일을 시키는 기호입니다. 이번 장에서는 숫자를 계산하는 연산자를 배웁니다. `2 + 3`에서 +는 더하기 연산자이고, 2와 3은 계산의 대상인 **피연산자**입니다. 이렇게 계산하여 하나의 값을 얻는 코드 조각을 **식**이라고 합니다.

## 계산 기호와 계산 순서

`+`는 더하기, `-`는 빼기, `*`는 곱하기, `/`는 나누기입니다. `%`는 정수 나눗셈의 나머지입니다. 예를 들어 `17 / 5`는 3이고 `17 % 5`는 2입니다. 이 장에서는 나머지를 계산할 수로 0 이상의 정수와 양의 나누는 수를 사용합니다. 0으로 나누거나 0으로 나머지를 구하면 안 됩니다.

곱셈·나눗셈·나머지는 덧셈·뺄셈보다 먼저 묶입니다. `2 + 3 * 4`는 14, `(2 + 3) * 4`는 20입니다. 복잡한 식은 괄호로 의도를 분명히 하세요.

**예제**

```cpp
void SmallMain()
{
    Print(2 + 3 * 4);
    Print((2 + 3) * 4);
    Print(17 / 5);
    Print(17 % 5);
    double truncated = 5 / 2;
    Print(truncated);
    Print(5.0 / 2);
}
```

예상 출력은 14, 20, 3, 2, 2, 2.5입니다. 마지막 두 결과에 주목하세요. `double result = 5 / 2;`도 먼저 정수 나눗셈을 하므로 2가 저장됩니다. 결과를 담는 변수만 double로 바꾸어도 이미 버린 소수 부분은 돌아오지 않습니다. `5.0 / 2`처럼 피연산자 중 하나를 실수로 만들면 실수 나눗셈을 합니다.

## 기존 값으로 계산해 다시 저장하기

**예제**

```cpp
void SmallMain()
 {
     int score = 10;
     Print(score);

     score = score + 5;
     Print(score);
 }
```

출력은 10과 15입니다. `score = score + 5;`를 다음 순서로 읽으세요.

1. 오른쪽 score에서 현재 값 10을 읽습니다.
2. 10에 5를 더하여 15를 계산합니다.
3. 계산한 15를 왼쪽 score에 저장합니다.

수학의 등식처럼 양쪽이 같다는 주장이 아닙니다. C++의 `=`는 오른쪽의 값을 왼쪽 변수에 저장하라는 뜻입니다. 같은지 비교하는 방법은 6장에서 배웁니다.

`score + 5`처럼 계산하여 하나의 값을 얻는 코드 조각을 **식(expression)**이라고 합니다. 계산 기호인 +는 **연산자(operator)**입니다. 저장하지 않고 `Print(score + 5);`처럼 계산한 값을 곧바로 출력할 수도 있습니다. 이렇게 출력만 하면 score 자체는 바뀌지 않습니다.

## 값을 바꾸는 짧은 표현

int나 double 변수에서 `score += 5;`는 `score = score + 5;`와 같은 갱신을 합니다. `-=`, `*=`, `/=`도 같은 방식이고 정수에는 `%=`도 사용할 수 있습니다. 정수의 `/=` 역시 정수 나눗셈입니다.

`score++;`는 1 증가, `score--;`는 1 감소입니다. 처음에는 독립된 문장으로만 사용하세요. 이 튜토리얼의 긴 형태도 계속 올바른 C++입니다.

직접 확인: 17을 18로 바꾸어 몫과 나머지를 예측하세요. 점수 10에 5를 더한 뒤 1을 줄이면 14가 되어야 합니다.

## Exercise — 사각형 넓이

double 변수 width와 height에 3.5와 2.0을 넣으세요. 곱한 값을 area에 저장하고 출력하세요. 값을 바꾸어 다시 실행해 보세요.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      double width = 3.5;
      double height = 2.0;
      // Calculate and print area.
  }
```

### Hint

넓이는 가로 * 세로입니다. 계산 결과를 담을 변수도 double로 만드세요.

**정답**

```cpp
void SmallMain()
  {
      double width = 3.5;
      double height = 2.0;
      double area = width * height;
      Print("Area: ", area);
  }
```

## Exercise — 몫과 나머지

사탕 17개를 한 봉지에 5개씩 담습니다. 봉지 수와 남은 사탕 수를 각각 출력하세요. 예상 결과는 3과 2입니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    int candies = 17;
    int perBag = 5;
    // Complete the task described in the tutorial.
}
```

### Hint

정수 나눗셈 /와 나머지 %를 사용하세요.

**정답**

```cpp
void SmallMain()
{
    int candies = 17;
    int perBag = 5;
    Print(candies / perBag);
    Print(candies % perBag);
}
```


# 기존 5강 — Input and Output


## 입력·처리·출력은 무엇인가요?

1장에서 큰따옴표로 문자열을 코드에 직접 적었습니다. 이번에는 사용자가 입력한 문자열을 변수에 저장합니다. **문자열은 데이터의 개념이고, String은 Small에서 문자열을 저장하고 다루도록 제공하는 타입의 이름**입니다. `String name`은 “문자열을 저장할 name이라는 변수”로 읽으세요.

**입력**은 프로그램 밖에서 값을 받아 오는 일이고, **출력**은 프로그램의 값이나 결과를 밖으로 보여 주는 일입니다. 지금은 콘솔에 키보드로 입력하고 글자로 결과를 출력합니다. **콘솔**은 글자를 주고받는 창입니다.

계산기를 생각해 보세요. 두 숫자를 입력받고, 더하는 처리를 하고, 합계를 출력합니다. 프로그램도 이 세 단계를 연결합니다. 2장에서는 초기값을 코드에 직접 썼지만, 입력을 사용하면 프로그램을 고치지 않고도 매번 다른 값으로 실행할 수 있습니다.

`String name = Input("Name: ");`은 먼저 Input 함수를 호출합니다. 안내문 Name: 이 표시되고 사용자가 한 줄을 입력하여 Enter를 누르면, Input이 그 글자를 돌려줍니다. 그 값을 name에 저장합니다. `String`은 여러 글자로 된 **문자열**을 저장하는 타입입니다. 화면에서 읽은 값을 프로그램 안에 보관하는 것이 변수의 역할입니다.

입력받는 값의 종류와 변수의 타입을 맞추세요. InputInt는 int, InputReal은 double, Input은 String을 돌려줍니다. 숫자처럼 보이는 문자열 `"12"`와 정수 `12`는 타입이 다릅니다. 이름의 12라는 글자가 자동으로 계산용 정수가 되는 것은 아닙니다.

## 실행할 때 값을 정하기
 이름이나 숫자를 바꿀 때마다 코드를 수정하지 않고, 실행 중에 직접 입력해 봅시다.

 아래 예제를 Run한 뒤 **콘솔 창**에서 이름을 쓰고 **Enter**를 누르세요. 입력을 기다리는 동안은 프로그램이 멈춘 것이 아닙니다. `Input`은 한 줄을 글자 값으로 돌려줍니다. `String`은 그 글자를 담는 타입입니다.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
 {
     String name = Input("Name: ");
     Print("Hello, ", name, "!");
 }
```

## 무엇을 입력받을까요?
 `Input()`은 한 줄의 글자를, `InputInt()`는 정수를, `InputReal()`은 double 값을 읽습니다. 괄호 안에 안내문을 넣을 수도 있습니다.

 `Write`는 출력한 뒤 줄을 바꾸지 않습니다. `Write("Age: ");` 다음에 `InputInt()`를 쓰면 같은 줄에서 입력할 수 있습니다. `Print()`를 인자 없이 사용하면 줄만 바꿉니다.

 숫자 입력에는 한 줄에 숫자 하나를 쓰세요. 숫자가 아닌 것을 넣으면 올바른 숫자를 다시 입력하라고 안내합니다.

## 조금 바꾸어 보기

**예제**

```cpp
void SmallMain()
 {
     Write("Age: ");
     int age = InputInt();
     double height = InputReal("Height in meters: ");

     Print();
     Print("Age: ", age);
     Print("Height: ", height);
 }
```

## 입력과 계산 연결하기
 입력한 값도 직접 코드에 쓴 값처럼 계산에 사용할 수 있습니다. 두 값을 따로 입력받으려면 입력 함수도 두 번 호출합니다.

 아래의 문제를 풀 때 소수도 입력하고 싶으면 InputReal과 double을 선택하세요. `Input`이 읽은 글자가 자동으로 숫자가 되는 것은 아닙니다.

## Exercise — 이름을 물어보기

이름을 입력받고 `Nice to meet you, 이름!`처럼 인사하세요.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      // Read a name, then greet the person.
  }
```

### Hint

String 변수에 Input의 결과를 저장한 뒤, Print의 쉼표 사이에 그 변수를 넣으세요.

**정답**

```cpp
void SmallMain()
  {
      String name = Input("Name: ");
      Print("Nice to meet you, ", name, "!");
  }
```

## Exercise — 두 수의 합

두 숫자를 한 번씩 입력받고 합을 출력하세요. 2.5와 3.5를 넣으면 6이 나와야 합니다.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      // Read two real numbers, then print their sum.
  }
```

### Hint

double 변수 두 개를 InputReal로 채우고 `Print(a + b);`처럼 계산을 출력하세요.

**정답**

```cpp
void SmallMain()
  {
      double a = InputReal("First: ");
      double b = InputReal("Second: ");
      Print("Sum: ", a + b);
  }
```


# 기존 6강 — Making Decisions — if


## 조건문은 실행할 길을 고릅니다

**조건문**은 어떤 조건이 참인지에 따라 실행할 코드를 선택하는 문장입니다. 모든 명령을 무조건 실행하는 대신, “점수가 100 이상이면 축하하기”처럼 상황에 맞게 행동합니다.

**조건**은 참 또는 거짓으로 판단할 수 있는 식입니다. `score >= 100`에서 >=는 두 값을 비교하는 연산자입니다. score가 120이면 결과는 true, 50이면 false입니다. 이 결과의 타입이 3장에서 배운 bool입니다.

`if (조건)`은 조건을 검사하고, true이면 뒤의 `{ }` 안을 실행합니다. 이처럼 중괄호로 묶은 문장들을 **블록**이라고 합니다. false이면 해당 블록을 건너뜁니다. 어느 경우든 선택한 일을 마친 뒤에는 조건문 다음 코드로 이어집니다.

**else는 조건이 거짓일 때 실행할 대안**입니다. 반드시 붙일 필요는 없습니다. 첫 예제에는 else가 없으므로 점수가 100 미만이면 축하 메시지를 출력하지 않을 뿐입니다. **else if는 앞 조건이 거짓일 때 다른 조건을 이어서 검사**합니다. 두 번째 예제에서 0을 넣으면 양수 검사는 실패하고, 0인지 검사는 성공하여 Zero만 출력합니다.

## 결과에 따라 다르게 행동하기
 게임에서 점수가 충분하면 승리 메시지를 보여주고 싶습니다. 조건이 맞을 때만 코드를 실행하려면 `if`를 사용합니다.

 아래 예제에서 120을 입력했을 때와 50을 입력했을 때를 비교해 보세요.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
 {
     int score = InputInt("Score: ");
     if (score >= 100)
     {
         Print("You win!");
     }
 }
```

## 조건은 true 또는 false
 `score >= 100`은 점수가 100 이상인지 비교합니다. 조건이 true일 때만 중괄호 안을 실행합니다. false일 때 할 일은 `else`에 적습니다.

 `<`는 작다, `>`는 크다, `<=`와 `>=`는 같을 때도 포함합니다. 두 값이 같은지는 `==`로, 다른지는 `!=`로 비교합니다. **`=`는 저장, `==`는 비교**이므로 구분하세요.

 `if (조건)` 뒤에는 `;`를 붙이지 않고 실행할 블록을 둡니다. 선택지가 세 개 이상이면 아래처럼 `else if`를 이어 쓸 수 있습니다. 위에서부터 검사해 처음 맞는 갈래만 실행합니다.

## 조금 바꾸어 보기

**예제**

```cpp
void SmallMain()
 {
     int number = InputInt("Number: ");
     if (number > 0)
     {
         Print("Positive");
     }
     else if (number == 0)
     {
         Print("Zero");
     }
     else
     {
         Print("Negative");
     }
 }
```

## 경계의 값도 시험해 보세요
 조건을 만들면 양쪽 경우를 모두 실행해 보세요. 첫 예제의 99와 100처럼 조건이 바뀌는 경계가 특히 유용합니다.

 두 번째 예제에서 0일 때 무엇이 출력되는지 설명해 볼 수 있나요? 예상하고 실행해서 확인하는 것이 코드를 이해하는 좋은 연습입니다.

## 여러 조건을 조합하기

`&&`는 두 조건이 모두 참일 때, `||`는 적어도 하나가 참일 때 true입니다. `!`는 true와 false를 뒤집습니다. `bool ready = false;` 뒤에 `ready = !ready;`를 실행하면 true가 됩니다.

`age >= 13 && age <= 19`는 13 이상이면서 19 이하라는 뜻입니다. 수학처럼 `13 <= age <= 19`라고 쓰면 원하는 범위 검사가 되지 않습니다. 각각 비교한 뒤 &&로 연결하세요.

**예제**

```cpp
void SmallMain()
{
    int age = 15;
    bool ready = false;
    if (age >= 13 && age <= 19) { Print("Teen"); }
    ready = !ready;
    if (ready || age >= 20) { Print("Ready"); }
    if (age > 0) { Print("First"); }
    if (age < 20) { Print("Second"); }
    if (age > 0) { Print("Only first"); }
    else if (age < 20) { Print("Not reached"); }
    bool hasKey = true;
    if (hasKey)
    {
        if (ready) { Print("Enter"); }
    }
}
```

예상 출력은 Teen, Ready, First, Second, Only first, Enter입니다. First와 Second를 출력하는 두 if는 서로 독립적이므로 둘 다 실행될 수 있지만, 그 뒤의 if–else if 묶음은 처음 맞는 갈래 하나만 실행됩니다.

예제 끝의 if 안에 있는 if를 **중첩 if**라고 합니다. 바깥 조건을 통과해야 안쪽 조건도 검사합니다. 중괄호와 들여쓰기로 어느 조건에 속하는지 확인하세요.

`&&`와 `||`는 왼쪽부터 검사하며 결과가 결정되면 오른쪽을 검사하지 않습니다. 이를 단락 평가라고 합니다. `divisor != 0 && total / divisor > 2`는 divisor가 0이면 나눗셈을 하지 않습니다.

처음에는 혼합 조건을 `(hasKey && doorOpen) || isAdmin`처럼 괄호로 묶으세요. 서로 다른 조건의 경계를 읽기 쉽습니다. 한 문장뿐이면 중괄호를 생략할 수도 있지만, 직접 작성할 때는 중괄호를 붙이는 습관을 권합니다.

직접 확인: age를 12, 13, 19, 20으로 바꾸고 Teen이 13과 19에서만 출력되는지 확인하세요. hasKey를 false로 바꾸면 Enter가 나오지 않아야 합니다.

## Exercise — 양수일 때만

정수 하나를 입력받고, 0보다 클 때만 `Positive`를 출력하세요. 0이나 음수일 때는 추가 메시지를 출력하지 않습니다.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      int number = InputInt("Number: ");
      // Print Positive only when number is greater than zero.
  }
```

### Hint

`number > 0`을 if의 조건으로 쓰세요. 이 문제에는 else가 없어도 됩니다.

**정답**

```cpp
void SmallMain()
  {
      int number = InputInt("Number: ");
      if (number > 0)
      {
          Print("Positive");
      }
  }
```

## Exercise — 세 가지 안내

나이를 입력받으세요. 0~12는 `Child`, 13~19는 `Teenager`, 20 이상은 `Adult`를 출력합니다. 여기서는 나이를 0 이상의 정수로 입력한다고 약속합니다.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      int age = InputInt("Age: ");
      // Choose Child, Teenager or Adult.
  }
```

### Hint

먼저 age <= 12를 검사하고, 아니면 age <= 19를 검사하세요. 나머지는 Adult입니다.

**정답**

```cpp
void SmallMain()
  {
      int age = InputInt("Age: ");
      if (age <= 12)
      {
          Print("Child");
      }
      else if (age <= 19)
      {
          Print("Teenager");
      }
      else
      {
          Print("Adult");
      }
  }
```

## Exercise — 입장 조건 조합

나이가 13 이상 19 이하이고 표가 있을 때만 Enter, 아니면 Wait를 출력하세요. 시작 값에서는 Enter여야 합니다. 12세 또는 표가 없는 경우는 Wait여야 합니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    int age = 15;
    bool hasTicket = true;
    // Complete the task described in the tutorial.
}
```

### Hint

두 비교와 hasTicket을 &&로 연결하세요.

**정답**

```cpp
void SmallMain()
{
    int age = 15;
    bool hasTicket = true;
    if (age >= 13 && age <= 19 && hasTicket)
    {
        Print("Enter");
    }
    else
    {
        Print("Wait");
    }
}
```


# 기존 7강 — Repeating with for


## 반복문은 같은 명령을 다시 실행합니다

**반복문**은 코드 묶음을 여러 번 실행하는 문장입니다. 코드 자체를 여러 번 복사하는 대신, 한 번 적은 명령을 정한 규칙에 따라 다시 실행합니다. 한 번 실행하는 동안의 과정을 **한 번의 반복**이라고 부릅니다.

1부터 5까지 출력하려면 출력할 숫자가 매번 달라져야 합니다. 그래서 현재 숫자를 기억하는 변수 i를 두고, 출력한 다음 i를 1 늘립니다. 같은 Print(i)를 실행해도 i에 저장된 값이 달라지므로 출력도 달라집니다.

for는 **시작 준비, 계속할 조건, 한 번 실행한 뒤의 갱신**을 괄호 안에 모아 적는 반복문입니다. i는 C++의 특별한 단어가 아니라 우리가 정한 변수 이름입니다.

첫 예제를 따라가면 i=1에서 조건 검사 → 1 출력 → i=2로 갱신합니다. 이 과정을 계속하여 i=5도 출력합니다. 그 뒤 i=6이 되면 조건이 false라서 출력하지 않고 반복문 다음으로 넘어갑니다. 처음부터 조건이 false라면 본문을 한 번도 실행하지 않습니다.

## 같은 코드를 계속 쓰지 않기
 숫자 1부터 5까지 출력하려면 Print를 다섯 번 쓸 수도 있습니다. 그런데 100까지 출력해야 한다면요? **반복문**으로 같은 일을 여러 번 시킬 수 있습니다.

 아래에서는 반복할 때마다 변수 i가 바뀝니다. 실행하기 전에 나올 숫자를 순서대로 적어 보세요.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
 {
     for (int i = 1; i <= 5; i = i + 1)
     {
         Print(i);
     }
 }
```

## for의 세 부분
 괄호 안은 `처음 값; 계속할 조건; 다음으로 바꾸기`입니다.

 `int i = 1`은 처음 한 번만 실행합니다. 매번 `i <= 5`를 검사해 true이면 블록을 실행하고, 그 뒤 `i = i + 1`로 값을 늘립니다. 조건이 false가 되면 반복을 끝냅니다. 이 예제에서는 1부터 5까지 다섯 번 출력합니다.

 다음 예제에서는 Write로 별을 같은 줄에 이어 출력합니다. 반복문 뒤의 Print는 한 번만 실행합니다.

## 조금 바꾸어 보기

**예제**

```cpp
void SmallMain()
 {
     int count = 5;
     for (int i = 0; i < count; i = i + 1)
     {
         Write("*");
     }
     Print();
 }
```

## 시작과 끝을 확인하세요
 0부터 시작해서 `i < count`를 검사하는 방법과, 1부터 시작해서 `i <= count`를 검사하는 방법은 둘 다 count번 반복할 수 있습니다. 처음 값과 조건을 함께 읽어야 합니다.

 i를 바꾸는 부분을 빼면 조건이 계속 참이 되어 끝나지 않을 수도 있습니다. 예상과 다르게 끝없이 실행되면 IDE의 **Stop**으로 멈추고 코드를 확인하세요. 실제 실험에서는 작은 수부터 시작합시다.

## Exercise — 1부터 10까지

for 하나를 사용해 1부터 10까지 한 줄에 하나씩 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      // Print the numbers from 1 to 10 with a for loop.
  }
```

### Hint

시작은 1, 조건은 i <= 10, 다음 값은 i + 1입니다.

**정답**

```cpp
void SmallMain()
  {
      for (int i = 1; i <= 10; i = i + 1)
      {
          Print(i);
      }
  }
```

## Exercise — 구구단 한 단

2부터 9 사이의 정수를 입력받아 그 수의 구구단을 1부터 9까지 출력하세요. 예를 들어 3을 입력하면 `3 x 1 = 3`부터 `3 x 9 = 27`까지 출력합니다.

**연습 시작 코드**

```cpp
void SmallMain()
  {
      int number = InputInt("Table (2 to 9): ");
      // Repeat from 1 to 9 and print each multiplication.
  }
```

### Hint

i를 1부터 9까지 바꾸며 `Print(number, " x ", i, " = ", number * i);`를 실행하세요.

**정답**

```cpp
void SmallMain()
  {
      int number = InputInt("Table (2 to 9): ");
      for (int i = 1; i <= 9; i = i + 1)
      {
          Print(number, " x ", i, " = ", number * i);
      }
  }
```


# 기존 8강 — Repeating with while


## while은 조건을 다시 확인하는 반복문입니다

**while 반복문**은 조건이 참인 동안 본문을 반복합니다. 조건 검사 → 본문 실행 → 조건 재검사의 순서입니다. if는 그 위치에서 조건을 한 번 검사하지만, while은 본문이 끝나면 돌아가서 다시 검사합니다.

첫 예제에서 number는 1로 시작합니다. number가 5 이하인지 확인하고 출력한 뒤 1을 더합니다. 5를 출력한 후에는 6이 되므로 다음 조건 검사에서 끝납니다. 값이 바뀌지 않으면 같은 조건이 계속 참이 될 수도 있습니다.

두 번째 예제의 0은 **그만 입력하겠다는 약속된 값**입니다. 처음부터 0을 입력하면 본문을 건너뛰고 Done!을 출력합니다. 7을 입력한 뒤 0을 입력하면 7에 대한 안내를 한 번 출력하고 끝납니다. 몇 번 입력할지는 실행 중에 결정됩니다.

for도 조건으로 반복하고 while도 정해진 횟수만큼 반복할 수 있습니다. 둘은 가능한 일의 종류가 다른 것이 아니라, 반복 규칙을 표현하는 모양이 다릅니다. 이 과정에서는 횟수·위치가 뚜렷하면 for, 입력이나 상태를 기다리면 while을 먼저 선택합니다.

## 몇 번 반복할지 미리 모를 때
`for`는 반복 횟수가 분명할 때 편했습니다. 하지만 사용자가 언제 0을 입력할지는 미리 알 수 없습니다. 이럴 때는 **조건이 참인 동안 계속하는** `while`을 사용할 수 있습니다.

아래 코드는 숫자가 5 이하인 동안 반복합니다. 실행하기 전에 어떤 숫자가 나올지 예상해 보세요.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
{
    int number = 1;

    while (number <= 5)
    {
        Print(number);
        number = number + 1;
    }
}
```

## while은 조건을 먼저 확인합니다
`while (number <= 5)`는 반복을 시작하기 전에 조건을 검사합니다. true이면 `{`와 `}` 안을 실행하고 다시 조건으로 돌아갑니다. false가 되는 순간 반복을 끝냅니다.

따라서 반복 안에서 조건에 영향을 주는 값이 바뀌는지 확인하는 습관이 중요합니다. 다음 예제는 사용자가 0을 입력할 때까지 계속 숫자를 받습니다.

## 조금 바꾸어 보기

**예제**

```cpp
void SmallMain()
{
    int number = InputInt("Number (0 to stop): ");

    while (number != 0)
    {
        Print("You entered ", number);
        number = InputInt("Number (0 to stop): ");
    }

    Print("Done!");
}
```

## for와 while 중 무엇을 쓸까요?
`1부터 10까지`처럼 횟수가 분명하면 보통 `for`가 읽기 쉽습니다. `0을 입력할 때까지`, `게임 창이 열려 있는 동안`처럼 **언제 끝날지가 조건으로 정해진 경우**에는 `while`이 자연스럽습니다.

조건이 영원히 true이면 반복도 끝나지 않습니다. 실수로 무한 반복이 생기면 IDE의 **Stop**을 누르고, 반복 안에서 조건이 언젠가 false가 될 수 있는지 확인하세요.

## 매번 다른 값을 만들기
게임이나 간단한 simulation에서는 실행할 때마다 다른 값이 필요할 때가 많습니다. Small은 두 함수를 제공합니다.

`RandomInt(1, 6)`은 1부터 6까지의 정수 중 하나를 고릅니다. 양 끝인 1과 6도 포함됩니다.

`RandomReal(0.0, 1.0)`은 0.0 이상 1.0 미만의 real number를 만듭니다.

예를 들어 숫자 맞히기 게임의 정답은 `int secret = RandomInt(1, 100);`처럼 정할 수 있습니다. 자세한 사용법은 Examples의 **Random Numbers**와 **Number Guessing**에서 바로 실행해볼 수 있습니다.

## 반복을 끝내거나 한 번 건너뛰기

`break;`는 가장 안쪽의 반복문을 즉시 끝냅니다. `continue;`는 이번 반복의 남은 문장만 건너뜁니다. for에서는 다음 값으로 바꾸는 부분으로, while에서는 조건 검사로 이동합니다.

**예제**

```cpp
void SmallMain()
{
    for (int i = 1; i <= 5; i = i + 1)
    {
        if (i == 4) { break; }
        Print(i);
    }
    Print("---");
    for (int i = 1; i <= 5; i = i + 1)
    {
        if (i == 3) { continue; }
        Print(i);
    }
}
```

첫 반복은 1, 2, 3을 출력하고 끝납니다. 두 번째 반복은 3만 건너뛰어 1, 2, 4, 5를 출력합니다. while에서 continue를 쓸 때에는 값 갱신까지 건너뛰어 무한 반복이 되지 않는지 확인하세요.

## 반복 안에 반복 넣기

격자의 각 행마다 여러 칸을 그리려면 반복 안에 반복을 넣을 수 있습니다.

**예제**

```cpp
void SmallMain()
{
    for (int row = 0; row < 2; row = row + 1)
    {
        for (int column = 0; column < 3; column = column + 1)
        {
            Write("*");
        }
        Print();
    }
}
```

별 세 개로 된 줄이 두 줄 출력됩니다. 바깥 반복 한 번마다 안쪽 반복이 처음부터 끝까지 실행됩니다. 마지막 Print는 안쪽 반복 밖에 있어서 한 행이 끝날 때 한 번 줄바꿈합니다.

직접 확인: 행을 3, 열을 4로 바꾸면 별 12개가 세 줄에 나뉘어 나와야 합니다. 중첩 반복 안의 break는 전체 반복이 아니라 가장 안쪽 반복 하나만 끝냅니다.

## Exercise — 10부터 1까지

`while` 하나를 사용해 10부터 1까지 한 줄에 하나씩 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    int number = 10;

    // Use while to print 10 down to 1.
}
```

### Hint

`number`를 10으로 시작하고, `number >= 1`인 동안 출력한 뒤 1씩 줄여 보세요.

**정답**

```cpp
void SmallMain()
{
    int number = 10;

    while (number >= 1)
    {
        Print(number);
        number = number - 1;
    }
}
```

## Exercise — 비밀번호 다시 묻기

정수 비밀번호를 입력받으세요. `1234`가 아니면 `Try again.`을 출력하고 다시 입력받습니다. `1234`를 입력하면 반복을 끝내고 `Welcome!`을 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    int password = InputInt("Password: ");

    // Keep asking while the password is wrong.

    Print("Welcome!");
}
```

### Hint

먼저 password를 한 번 입력받고 `while (password != 1234)` 안에서 다시 입력받아 보세요.

**정답**

```cpp
void SmallMain()
{
    int password = InputInt("Password: ");

    while (password != 1234)
    {
        Print("Try again.");
        password = InputInt("Password: ");
    }

    Print("Welcome!");
}
```

## Exercise — 건너뛰고 멈추기

1부터 10까지 반복하되 3은 출력하지 않고 6을 만나면 끝내세요. 출력은 1, 2, 4, 5입니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // Complete the task described in the tutorial.
}
```

### Hint

3에서는 continue, 6에서는 break를 사용하고 나머지를 출력하세요.

**정답**

```cpp
void SmallMain()
{
    for (int i = 1; i <= 10; i = i + 1)
    {
        if (i == 3) { continue; }
        if (i == 6) { break; }
        Print(i);
    }
}
```


# 기존 9강 — Functions


## 우리는 이미 함수를 사용하고 있습니다

1장에서 함수는 **특정한 일을 수행하는 코드 묶음에 이름을 붙인 것**이라고 배웠습니다. `Print("Hello");`는 Print라는 함수에 출력할 글자를 전달하여 실행시키는 **호출**입니다. 출력의 세부 구현을 몰라도 그 기능을 사용할 수 있었습니다.

5장에서 사용한 `InputInt()`도 함수입니다. 정수를 입력받는 일을 하고, 읽은 값을 호출한 쪽에 돌려줍니다. 그래서 `int age = InputInt();`처럼 그 결과를 변수에 저장할 수 있습니다.

함수에 값을 **전달하는 것**, 화면에 **출력하는 것**, 호출한 쪽에 값을 **돌려주는 것**은 서로 다릅니다. Print는 전달받은 내용을 화면에 출력하고, InputInt는 읽은 정수를 돌려줍니다. 함수마다 맡은 일이 다르며, 모든 함수가 값을 전달받거나 돌려주어야 하는 것은 아닙니다.

## 이제 우리도 함수를 만들어 봅시다

프로그램 여러 곳에서 구분선을 출력하고 싶다고 생각해 봅시다. 그 일을 하는 코드를 PrintLine이라는 이름으로 묶어 두면, 필요한 곳에서 `PrintLine();`으로 실행할 수 있습니다. 나중에 구분선 모양을 바꾸려면 함수의 내용 한 곳을 고치면 됩니다.

이처럼 함수가 할 일을 적는 것이 **정의**, 만들어 둔 함수를 실행시키는 것이 **호출**입니다. SmallMain도 우리가 정의하고 Small이 호출해 주는 함수입니다. 이제 PrintLine은 우리가 정의하고 SmallMain 안에서 직접 호출해 봅니다.

## 먼저 실행해 보세요

**예제**

```cpp
void PrintLine()
{
    Print("**********");
}

void SmallMain()
{
    PrintLine();
    Print("Small C++");
    PrintLine();
}
```

위쪽 `void PrintLine()`과 중괄호는 함수를 정의합니다. 그 부분을 적었다고 별표가 바로 출력되는 것은 아닙니다. SmallMain 안의 `PrintLine();`을 만날 때 PrintLine의 본문을 실행하고, 끝나면 돌아와 그다음 문장을 실행합니다.

먼저 출력 순서를 예상한 뒤 실행해 보세요. PrintLine 안의 별표를 다른 기호로 바꾸면 그 함수를 호출하는 곳들의 출력이 함께 바뀝니다.

## `void`는 돌려주는 값이 없다는 뜻입니다
함수 이름 앞에는 그 함수가 어떤 종류의 값을 돌려주는지가 적힙니다. 이것을 **return type**이라고 합니다.

`void PrintLine()`에서 `void`는 **이 함수가 결과값을 돌려주지 않는다**는 뜻입니다. `PrintLine`은 별표를 출력하는 일을 하고 그대로 끝납니다.

함수의 기본 모양에서 `void`는 돌려주는 값이 없음을, `PrintLine`은 함수의 이름을, `()`는 호출할 때 전달받을 값이 없음을, `{ ... }`는 함수를 호출했을 때 실행할 코드를 나타냅니다.

사실 첫 lesson부터 계속 썼던 `void SmallMain()`의 `void`도 정확히 같은 뜻입니다. `SmallMain`은 프로그램의 일을 실행하지만 결과값을 돌려주지는 않습니다.

조금 뒤에는 `void` 대신 `int`처럼 실제 값을 돌려주는 함수도 만들어 봅니다.

## 입력을 받고 결과를 돌려주기
**매개변수(parameter)**는 함수를 호출할 때 전달한 값을 받아 함수 안에서 사용하는 변수입니다. `int Square(int x)`에서 괄호 안의 int x가 매개변수입니다. `Square(5)`로 호출하면 x에 5를 받아 사용하고, `Square(6)`으로 호출하면 그 호출에서는 x에 6을 받습니다. 호출할 때 전달하는 5나 6을 **인자(argument)**라고 합니다.

함수가 계산한 값을 돌려주려면 `return`을 사용합니다. `int Square(...)`의 앞쪽 `int`는 이 함수가 int 값을 돌려준다는 뜻입니다.

앞에서 본 `void PrintLine()`은 값을 돌려주지 않고, `int Square(int x)`는 int 값을 하나 돌려줍니다. 둘 다 함수이고, 앞의 return type이 함수가 어떤 결과를 돌려주는지 알려줍니다.

지금은 parameter를 **값으로 받는다**고 생각하면 충분합니다. Array처럼 큰 값을 전달할 때 실제 메모리에서 어떤 일이 일어나는지는 훨씬 뒤에서 자세히 살펴봅니다.

## 조금 바꾸어 보기

**예제**

```cpp
int Square(int x)
{
    return x * x;
}

int Max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void SmallMain()
{
    Print("Square: ", Square(6));
    Print("Larger: ", Max(7, 12));
}
```

예제의 `Square(6)`은 x에 6을 전달하고 x * x로 36을 계산한 뒤 return으로 36을 돌려줍니다. 그 결과가 바깥 Print에 전달되어 `Square: 36`이 출력됩니다. Square가 직접 글자를 출력한 것은 아닙니다.

`Max(7, 12)`는 a에 7, b에 12를 전달합니다. a > b가 false여서 b를 반환하므로 `Larger: 12`가 출력됩니다. 여기서 함수 이름 앞의 int는 **반환 타입**, 괄호 안의 int는 **매개변수 타입**입니다. 돌려주는 값과 받는 값의 타입을 각각 나타내는 것입니다.

직접 확인: Square(6)을 Square(3)으로 바꾸면 9를 돌려줍니다. PrintLine은 화면에 출력하지만 값을 돌려주지 않고, Square는 값을 돌려주지만 그 함수 안에서 출력하지 않는다는 차이를 말로 설명해 보세요.

## 함수는 작은 문제 하나를 맡게 하세요
좋은 함수 이름은 코드를 읽는 사람에게 **무슨 일을 하는지** 알려줍니다. 같은 계산이 여러 번 필요하거나, 여러 줄의 코드에 이름을 붙이면 이해하기 쉬워질 때 함수를 만들어 보세요.

처음부터 모든 코드를 함수로 나눌 필요는 없습니다. `SmallMain`에 간단히 쓰다가 반복되거나 의미 있는 한 덩어리가 보일 때 함수로 꺼내도 됩니다.



## 정의와 호출, 돌아오는 위치

함수 정의를 적었다고 그 본문이 바로 실행되지는 않습니다. `Square(5)`처럼 호출하면 해당 함수로 가서 실행하고, 끝나면 호출한 위치로 돌아옵니다. 이 과정에서는 직접 만든 함수를 사용하는 코드보다 위에 정의하세요.

매개변수가 둘이면 전달하는 값의 순서도 중요합니다. `Add(3, 7)`은 첫 매개변수에 3, 두 번째에 7을 전달합니다. 반환값은 변수에 저장하거나 다른 계산에 사용할 수 있습니다.

`return`을 실행하면 함수는 즉시 끝납니다. 반복 안에서 사용해도 함수 전체를 끝냅니다. break가 반복 하나만 끝내는 것과 다릅니다. void 함수에서는 `return;`으로 일찍 끝낼 수 있습니다. int처럼 값을 돌려주는 함수는 실행되는 각 경로에서 값을 반환해야 합니다.

## 변수의 범위와 수명

함수나 중괄호 안에 선언한 지역 변수는 그 범위 안에서만 이름으로 사용할 수 있습니다. 함수의 매개변수도 그 함수 안에서만 사용합니다. 다른 함수에서 같은 이름을 사용해도 같은 변수가 아닙니다.

**예제**

```cpp
void AddOne(int x)
{
    x = x + 1;
    Print(x);
}
void SmallMain()
{
    int n = 10;
    AddOne(n);
    Print(n);
    int total = 0;
    for (int i = 0; i < 3; i = i + 1)
    {
        int temporary = 0;
        temporary = temporary + 1;
        total = total + 1;
        Print(temporary);
    }
    Print(total);
}
```

예상 출력은 11, 10, 1, 1, 1, 3입니다. AddOne의 x는 전달된 n의 값을 복사해서 받으므로 x를 바꾸어도 n은 10입니다. 원본을 바꾸는 참조는 33장에서 배웁니다.

loop 안의 temporary는 반복할 때마다 새로 만들어져 0으로 초기화됩니다. 반면 loop 밖의 total은 반복 사이에도 값을 유지합니다. 점수나 누적 합계를 어디에 선언해야 하는지 이 차이로 판단하세요.

모든 함수 바깥에 선언한 변수는 전역 변수이며, 선언 뒤의 여러 함수에서 접근할 수 있습니다. 19장의 Timer에서 공유 상태를 표현할 때 사용합니다. 평소에는 지역 변수와 매개변수로 필요한 값을 전달하고, 여러 함수가 함부로 같은 전역 값을 바꾸지 않도록 하세요.

## 여러 줄을 주석으로 만들기

여러 줄에 걸쳐 메모를 남기고 싶다면 `/*`와 `*/` 사이를 주석으로 만들 수 있습니다. 예를 들어 `/* 이 부분은 점수에 보너스를 더하는 규칙을 설명합니다. */`처럼 사용할 수 있습니다.

보통 짧은 메모에는 `//`가 가장 편합니다. `/* ... */`는 여러 줄 설명이 정말 필요할 때 사용하면 됩니다.

좋은 주석은 `x = x + 1;`을 “x에 1을 더한다”라고 그대로 번역하기보다, **왜 이 코드가 필요한지** 또는 **이 코드 덩어리가 어떤 역할을 하는지** 알려줍니다.

## Exercise — 두 수의 합

두 int를 parameter로 받아 합을 돌려주는 `Add` 함수를 만들고, `SmallMain`에서 `Add(3, 7)`의 결과를 출력하세요.

**연습 시작 코드**

```cpp
int Add(int a, int b)
{
    // Replace this with the correct result.
    return 0;
}

void SmallMain()
{
    Print(Add(3, 7));
}
```

### Hint

함수의 시작을 `int Add(int a, int b)`로 쓰고 `return a + b;`를 사용해 보세요.

**정답**

```cpp
int Add(int a, int b)
{
    return a + b;
}

void SmallMain()
{
    Print(Add(3, 7));
}
```

## Exercise — 가장 큰 수

int 세 개를 받아 가장 큰 값을 돌려주는 `Max3` 함수를 만드세요. `Max3(8, 3, 12)`를 출력해 확인하세요.

**연습 시작 코드**

```cpp
int Max3(int a, int b, int c)
{
    // Find the largest of a, b, and c.
    return 0;
}

void SmallMain()
{
    Print(Max3(8, 3, 12));
}
```

### Hint

먼저 `largest`에 a를 넣고, b와 c가 더 큰지 각각 if로 확인해 보세요.

**정답**

```cpp
int Max3(int a, int b, int c)
{
    int largest = a;

    if (b > largest)
        largest = b;

    if (c > largest)
        largest = c;

    return largest;
}

void SmallMain()
{
    Print(Max3(8, 3, 12));
}
```

## Exercise — 반복 사이의 값 기억하기

1부터 3까지의 합계를 구해 마지막에 한 번 출력하세요. 답은 6입니다. total을 반복 안에서 매번 0으로 만들면 왜 안 되는지도 설명해 보세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    // Complete the task described in the tutorial.
}
```

### Hint

total은 반복문 밖에서 만들고 반복문 안에서 i를 더하세요.

**정답**

```cpp
void SmallMain()
{
    int total = 0;
    for (int i = 1; i <= 3; i = i + 1)
    {
        total = total + i;
    }
    Print(total);
}
```


# 기존 10강 — String


## 문자열은 글자들이 순서대로 이어진 값입니다

1장에서 문자열 자체와 큰따옴표를, 3장에서 char 문자 값과 작은따옴표를 배웠습니다. 5장에서는 입력받은 문자열을 String 변수에 저장했습니다. 이 장은 그 문자열을 이어 붙이거나 일부를 읽는 방법으로 확장합니다. 문자열이라는 개념과 대문자로 시작하는 Small의 타입 이름 String을 구분하세요.

이름, 인사말, 파일 이름처럼 여러 문자가 이어진 데이터를 **문자열(string)**이라고 합니다. Small의 `String`은 그 문자열을 저장하는 타입입니다. String name에서 String은 타입, name은 변수 이름입니다. int score와 같은 “타입과 변수”의 관계입니다.

`String word = "Small";`은 Small이라는 문자열을 word에 저장합니다. `Print(word);`는 저장된 문자열을 출력합니다. `"word"`를 출력하는 것과 다릅니다. `'A'`는 char 값이고 `"A"`는 문자열 표기입니다.

문자열에도 연산이 있습니다. String 값 사이의 +는 숫자 덧셈이 아니라 **이어 붙이기**입니다. 첫 예제의 first + " " + second는 Small, 공백, C++을 순서대로 붙여 Small C++이라는 새 문자열을 만듭니다. first와 second 자체가 바뀌는 것은 아닙니다.

String은 내부에 데이터를 담고 관련 기능도 제공하는 **객체**로 사용할 수 있습니다. `word.Length()`의 점은 word에 속한 기능을 사용한다는 표시입니다. Length()를 호출하면 길이를 정수로 돌려줍니다. 객체를 만드는 원리는 뒤에서 배우고, 지금은 특정 문자열에 기능을 요청한다는 뜻으로 읽으면 됩니다.

## 글자도 값입니다
지금까지 큰따옴표 안의 글자를 바로 출력했습니다. 글자도 변수에 저장해 두고 계산하듯 다룰 수 있습니다. Small C++에서는 여러 글자를 담는 타입을 `String`이라고 합니다.

String은 `+`로 이어 붙일 수 있고 `Length()`로 바이트 길이를 알 수 있습니다. 이 장에서는 한 글자가 한 바이트인 영문 예제로 시작합니다.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
{
    String first = "Small";
    String second = "C++";
    String name = first + " " + second;

    Print(name);
    Print("Length: ", name.Length());
}
```

## 한 글자씩 보기
String의 첫 글자는 `text[0]`, 두 번째 글자는 `text[1]`처럼 읽습니다. 컴퓨터에서는 위치를 셀 때 **0부터 시작**하는 경우가 많습니다.

`Substring(start, length)`는 String의 일부를 새 String으로 만듭니다. 아래에서 `word.Substring(1, 3)`은 위치 1부터 세 글자를 가져옵니다.

String끼리는 `==`, `!=`, `<`, `>` 같은 비교도 할 수 있습니다.

## 조금 바꾸어 보기

**예제**

```cpp
void SmallMain()
{
    String word = "Small";

    Print("First: ", word[0]);
    Print("Middle: ", word.Substring(1, 3));

    for (int i = 0; i < word.Length(); i = i + 1)
    {
        Print(i, ": ", word[i]);
    }
}
```

## 범위를 벗어나지 않게
길이가 5인 String의 올바른 위치는 0, 1, 2, 3, 4입니다. `text[5]`는 여섯 번째 글자를 뜻하므로 범위를 벗어납니다. Small은 이런 실수를 발견하면 runtime error로 알려줍니다.

String을 함수에 전달하는 것도 다른 값과 똑같이 할 수 있습니다. 지금 단계에서는 `String text`처럼 값으로 받으면 됩니다. reference는 나중에 메모리 모델을 배울 때 함께 살펴봅니다.

## 점과 괄호 읽기

`word.Length()`의 점은 word가 가진 기능을 사용한다는 뜻입니다. 괄호 안이 비어 있으면 추가로 전달할 값이 없고, Length가 돌려준 정수를 계산에 쓸 수 있습니다. `word.Substring(1, 3)`은 word에게 시작 위치 1과 길이 3을 전달합니다. `Substring(1)`은 위치 1부터 끝까지 가져옵니다.

## 따옴표와 줄바꿈을 문자열에 넣기

문자열 안의 `\n`은 줄바꿈, `\t`는 탭, `\"`는 큰따옴표, `\\`는 역슬래시입니다. 따옴표 안의 내용을 끝내지 않고 특수한 문자를 나타내는 이 표기를 이스케이프라고 합니다. 예를 들어 `Print("A\nB");`는 A와 B를 두 줄로 출력합니다.

## 한글을 다룰 때의 주의

Small의 String은 바이트 단위로 길이와 위치를 셉니다. 이 장의 영문 예제에서는 한 글자와 한 바이트가 같지만, UTF-8 한글은 그렇지 않습니다. `Length()`가 화면에 보이는 글자 수와 다를 수 있고, `[]`와 Substring으로 한글 중간을 자르면 글자가 깨질 수 있습니다.

한글 이름을 통째로 입력받아 출력하는 것은 가능하지만, 이 장의 글자 분리 연습은 영문으로 진행하세요. `char`도 임의의 한글 한 글자를 담는 타입은 아닙니다. String의 비교는 저장된 바이트 순서에 따른 비교이며, 자연어 사전 정렬과 같다고 가정하지 마세요.

## Exercise — 글자를 거꾸로 출력

`String word = "Small";`의 글자를 마지막부터 첫 글자까지 한 줄에 하나씩 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    String word = "Small";

    // Print the characters from last to first.
}
```

### Hint

마지막 위치는 `word.Length() - 1`입니다. i를 1씩 줄이는 for를 만들어 보세요.

**정답**

```cpp
void SmallMain()
{
    String word = "Small";

    for (int i = word.Length() - 1; i >= 0; i = i - 1)
    {
        Print(word[i]);
    }
}
```

## Exercise — 첫 글자와 나머지

영문 이름을 Input으로 입력받고 첫 글자를 `First:` 뒤에, 나머지 글자를 `Rest:` 뒤에 출력하세요. 이 문제에서는 영문자 두 개 이상인 이름(예: Alex)을 입력한다고 가정합니다. 한글 이름을 분리하는 문제는 아닙니다.

**연습 시작 코드**

```cpp
void SmallMain()
{
    String name = Input("Name: ");

    // Print the first character and the rest.
}
```

### Hint

첫 글자는 `name[0]`입니다. 나머지는 `name.Substring(1)`로 얻을 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    String name = Input("Name: ");

    Print("First: ", name[0]);
    Print("Rest: ", name.Substring(1));
}
```


# 기존 11강 — Array


## 배열은 번호로 찾아 쓰는 값들의 모음입니다

**배열(array)**은 같은 타입의 여러 값을 순서대로 모아 둔 것입니다. 각각의 값을 **원소(element)**, 원소의 위치 번호를 **인덱스(index)**라고 합니다. 변수 다섯 개에 별개의 이름을 붙이는 대신, 배열 하나와 위치 번호로 다섯 값을 다룰 수 있습니다.

`Array<int> scores = {80, 95, 70, 100, 85};`에서 Array<int>는 int 원소들을 담는 타입이고 scores는 그 배열의 이름입니다. 중괄호 안은 처음 저장할 값의 목록입니다. scores 전체는 배열이고 scores[0]은 그 안의 int 한 개입니다.

인덱스는 0부터 시작하므로 scores[0]은 80, scores[1]은 95입니다. 배열의 **길이**는 원소 개수이며 여기서는 5입니다. 마지막 인덱스는 5가 아니라 4입니다. 길이와 마지막 위치를 구분하세요.

`scores[1] = 90;`은 두 번째 원소만 90으로 바꿉니다. 배열의 길이나 다른 원소가 함께 바뀌지는 않습니다. 반복문의 i를 인덱스로 사용하면 같은 코드로 모든 원소를 하나씩 읽거나 바꿀 수 있습니다. 첫 예제는 Count: 5 뒤에 다섯 점수를 순서대로 출력합니다.

## 값이 많아지면 한곳에 모으기
점수 다섯 개를 `score1`, `score2`, `score3`처럼 따로 만들 수도 있습니다. 하지만 값이 많아질수록 반복해서 처리하기 어렵습니다. **Array**는 같은 타입의 여러 값을 순서대로 모아 둡니다.

`Array<int>`는 int 여러 개를 담는 Array입니다. String처럼 위치는 0부터 시작합니다.

## 먼저 실행해 보세요

**예제**

```cpp
void SmallMain()
{
    Array<int> scores = {80, 95, 70, 100, 85};

    Print("Count: ", scores.Length());

    for (int i = 0; i < scores.Length(); i = i + 1)
    {
        Print(scores[i]);
    }
}
```

## 읽고 바꿀 수 있습니다
`scores[0]`은 첫 번째 값입니다. Array의 한 칸에는 새 값을 대입할 수도 있습니다. `Length()`는 Array에 몇 개의 값이 있는지 알려줍니다.

Array 전체도 하나의 값처럼 함수에 전달할 수 있습니다. 지금은 다른 parameter와 똑같이 `Array<int> numbers`라고 쓰겠습니다. 이렇게 하면 함수가 Array 값을 받습니다.

실제로 큰 Array를 전달할 때 복사를 피하는 방법은 Lesson 33에서 **reference와 메모리 모델**을 배울 때 다룹니다.

## 조금 바꾸어 보기

**예제**

```cpp
int Sum(Array<int> numbers)
{
    int total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        total = total + numbers[i];
    }

    return total;
}

void SmallMain()
{
    Array<int> numbers = {3, 7, 2, 9, 4};

    numbers[2] = 10;

    Print("Third: ", numbers[2]);
    Print("Sum: ", Sum(numbers));
}
```

## Array의 범위
길이가 5인 Array의 올바른 index는 0부터 4까지입니다. 범위를 벗어난 index를 사용하면 Small이 runtime error로 알려줍니다.

Array와 반복문은 매우 자주 함께 사용됩니다. 다음 Part에서는 그래픽과 입력으로 실제 프로그램을 만들어 보고, 그 뒤에는 Array를 이용해 검색과 정렬 같은 알고리즘을 직접 만들어 봅니다.

## 배열을 만드는 두 가지 방법

`Array<int> values = {2, 4, 6};`은 초기값 세 개로 길이 3인 배열을 만듭니다. `Array<int> values(3);`은 길이를 지정해 만들고, 각 칸에 값을 넣어 사용할 수 있습니다. int 칸의 초기값은 0입니다. 두 선언은 같은 범위에 동시에 쓰지 말고 하나를 선택하세요.

Array<int>의 꺾쇠는 원소가 int라는 뜻이지, 비교 연산자가 아닙니다. 중괄호 안의 값 목록은 초기값을 모은 것이며, if의 실행 블록과 역할이 다릅니다.

Small Array는 만든 뒤 길이를 늘리는 기능이 없습니다. 크기가 변하는 목록은 35장의 std::vector에서 배웁니다. 길이가 0인 배열도 가능하므로 첫 원소를 읽기 전에는 원소가 있는지 확인해야 합니다.

## Exercise — 모든 값의 두 배

`{2, 4, 6, 8, 10}`이 들어 있는 Array의 모든 값을 for로 돌면서 두 배로 바꾼 뒤 모두 출력하세요.

**연습 시작 코드**

```cpp
void SmallMain()
{
    Array<int> numbers = {2, 4, 6, 8, 10};

    // Double every value, then print them.
}
```

### Hint

각 위치에서 `numbers[i] = numbers[i] * 2;`처럼 같은 칸에 새 값을 넣을 수 있습니다.

**정답**

```cpp
void SmallMain()
{
    Array<int> numbers = {2, 4, 6, 8, 10};

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        numbers[i] = numbers[i] * 2;
    }

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        Print(numbers[i]);
    }
}
```

## Exercise — Array의 합을 함수로

`Array<int>`를 값으로 받는 `Sum` 함수를 만들고 `{5, 10, 15, 20}`의 합을 출력하세요. 지금은 reference를 사용하지 않습니다.

**연습 시작 코드**

```cpp
int Sum(Array<int> numbers)
{
    // Add every value in numbers.
    return 0;
}

void SmallMain()
{
    Array<int> numbers = {5, 10, 15, 20};
    Print(Sum(numbers));
}
```

### Hint

`int Sum(Array<int> numbers)`로 시작하고 for로 모든 값을 total에 더해 보세요.

**정답**

```cpp
int Sum(Array<int> numbers)
{
    int total = 0;

    for (int i = 0; i < numbers.Length(); i = i + 1)
    {
        total = total + numbers[i];
    }

    return total;
}

void SmallMain()
{
    Array<int> numbers = {5, 10, 15, 20};
    Print(Sum(numbers));
}
```


# 기존 12강 — Your First Window


## 창 객체와 화면의 창은 구분합니다

**Window는 화면의 창을 다루는 타입**입니다. `Window window;`는 그 타입의 객체를 만들고 window라는 이름을 붙입니다. 객체는 자신의 상태와 그 상태를 다루는 기능을 함께 가진 대상으로 생각하면 됩니다. 변수에 값을 담았던 것처럼 이 객체는 제목·크기 등 창에 관한 정보를 관리합니다.

객체를 만들었다고 화면에 창이 열리는 것은 아닙니다. `window.Open(640, 480);`이라는 동작을 요청해야 실제 창을 엽니다. `window.SetTitle("My Window");`는 상태를 바꾸고, `window.Width()`는 가로 크기를 돌려줍니다. 점 뒤의 함수는 그 객체에 속한 기능인 **멤버 함수**입니다.

창은 화면에 나타나 있다고 해서 프로그램을 저절로 계속 실행시켜 주지 않습니다. while 안에서 Show를 반복해 창이 반응하도록 유지하고, 사용자가 닫으면 반복을 끝냅니다. 자세한 class 구현은 지금 알 필요가 없습니다.

## 콘솔 밖으로 나가 봅시다
지금까지는 글자를 콘솔에 출력했습니다. 이제 직접 창을 하나 열어 봅시다. `Window window;`는 Window 객체를 만들고, `window.Open(640, 480);`은 실제 화면에 640 x 480 크기의 창을 엽니다.

창을 연 뒤에는 사용자가 닫을 때까지 프로그램이 살아 있어야 합니다. 그래서 `while (window.IsOpen())`을 사용합니다.

## 먼저 실행해 보세요

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

## 객체에게 일을 시키기
`window.Open(...)`, `window.SetTitle(...)`, `window.Width()`처럼 점 뒤에 이름을 붙여 Window에게 일을 시키거나 정보를 물어볼 수 있습니다. 아직 class를 배우지 않았지만 이런 사용법에는 먼저 익숙해질 수 있습니다.

`SetTitle`은 Open 전에도, 열린 뒤에도 사용할 수 있습니다. 제목은 Window가 가진 상태이고 Open은 실제 창을 여는 동작이기 때문입니다.

## 조금 바꾸어 보기

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

## Window를 닫으면 반복도 끝납니다
창 오른쪽 위의 닫기 버튼을 누르면 `IsOpen()`이 false가 되어 while을 빠져나옵니다. `window.Close()`를 호출해서 프로그램이 직접 닫을 수도 있습니다.

지금은 Window의 내부 구현을 알 필요가 없습니다. 뒤에서 class를 배울 때 `Window window;`와 점을 사용하는 코드가 왜 이런 모습인지 다시 만나게 됩니다.

## Show는 창의 반응도 진행시킵니다

`window.Show();`는 준비한 그림을 보여주고 창 닫기·키보드·마우스 등의 이벤트도 처리합니다. 반복 안에서 계속 호출해야 창이 반응합니다. IsOpen만 검사하면서 Show를 빼지 마세요. 창 생성과 열기, 반복 중 표시, 종료라는 전체 흐름을 먼저 익히면 됩니다.

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


# 기존 13강 — Drawing


## 그림은 좌표와 크기로 지정합니다

**좌표**는 위치를 숫자로 나타내는 방법입니다. 창 안의 위치를 가로 방향 x와 세로 방향 y 두 값으로 지정합니다. **픽셀(pixel)**은 화면 이미지를 이루는 작은 칸입니다. 이 과정에서는 위치와 길이를 픽셀 단위로 생각합니다.

사각형을 그리려면 어디에서 시작하는지와 얼마나 큰지를 알려야 합니다. 왼쪽 위 위치 (20, 30), 가로 100, 세로 50인 사각형에서 100과 50은 오른쪽 아래 좌표가 아니라 길이입니다. 원은 중심 위치와 반지름으로 정합니다.

Clear는 배경을 지정한 색으로 지우고, drawing 함수들은 보여 줄 그림을 준비하며, Show가 그 결과를 표시합니다. 지우기 → 그리기 → 보여 주기는 역할이 서로 다릅니다. 같은 위치에 도형을 겹치면 나중에 그린 것이 앞에 보입니다.

## 화면을 직접 채워 봅시다
Window는 단순히 빈 창만 여는 것이 아닙니다. 배경을 지우고, 선과 도형과 글자를 그릴 수 있습니다.

그림을 모두 준비한 뒤 `Show()`를 호출하면 그 결과가 화면에 나타납니다.

## 먼저 실행해 보세요

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

## 좌표와 색
화면의 왼쪽 위가 `(0, 0)`입니다. x는 오른쪽으로, y는 아래쪽으로 커집니다. `RGB(red, green, blue)`로 직접 색을 만들 수도 있고 `Red`, `Blue`, `Yellow` 같은 기본 색을 사용할 수도 있습니다.

`DrawRectangle`은 테두리만, `FillRectangle`은 안쪽까지 채웁니다. Circle도 같은 방식입니다.

## 조금 바꾸어 보기

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

## 그리는 순서도 중요합니다
나중에 그린 도형은 먼저 그린 도형 위에 나타납니다. 그래서 보통 배경을 먼저 Clear하고 큰 도형부터 그린 뒤 세부 요소와 글자를 그립니다.

다음 lesson부터는 매 frame마다 화면을 다시 그리면서 키보드와 마우스에 반응하게 됩니다.

## 도형 함수의 숫자는 무엇일까요?

`FillRectangle(x, y, width, height, color)`에서 x와 y는 왼쪽 위 위치, width와 height는 가로·세로 길이입니다. `FillCircle(x, y, radius, color)`에서 x와 y는 중심이고 radius는 반지름입니다. `DrawLine(x1, y1, x2, y2, color)`는 두 끝점을 연결합니다.

RGB의 각 성분은 0부터 255까지입니다. `RGB(255, 0, 0)`은 빨강입니다. 처음에는 위치·크기·색 중 하나만 바꾸어 결과를 비교하세요. 그래야 어떤 숫자가 무엇을 바꾸는지 확인하기 쉽습니다.

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


# 기존 14강 — Keyboard


## 키 입력은 상태와 변화로 나눕니다

**상태**는 지금 어떤 상황인지를 나타내는 값입니다. “키가 눌려 있다”는 상태는 키를 누르는 동안 계속 유지됩니다. 반면 “방금 눌렸다”는 것은 눌리지 않은 상태에서 눌린 상태로 바뀐 사건입니다.

`window.KeyDown(Key::Left)`는 왼쪽 키가 눌려 있는지 bool로 알려 줍니다. if에 넣으면 true인 동안 위치를 바꾸게 할 수 있습니다. KeyPressed는 누르기 시작한 순간을 감지하므로 색 전환처럼 한 번만 할 일에 사용합니다.

`Key::Left`는 키 종류 중 Left라는 이름을 고른 표기입니다. 뺄셈이나 함수 호출이 아닙니다. 지금은 Small이 준비한 선택값으로 사용하면 됩니다. 마우스 버튼과 효과음에서도 같은 형태를 만납니다.

현재 예제는 loop가 한 번 돌 때마다 화면 한 장을 만듭니다. 이 한 장을 frame이라고 부르며, 16장에서 움직임과 연결합니다. 키를 길게 눌렀을 때 Down은 여러 frame에서 참이고 Pressed는 해당 누름의 시작을 알리는 frame에서 참입니다.

## 프로그램이 내 입력에 반응하게
게임에서는 사용자가 키를 누르는 동안 계속 움직이기도 하고, 한 번 누른 순간에만 어떤 일이 일어나기도 합니다.

`KeyDown`은 키가 **지금 눌려 있는 동안** true입니다. 먼저 방향키로 원을 움직여 봅시다.

## 먼저 실행해 보세요

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

## Down과 Pressed의 차이
`KeyDown`은 키를 누르고 있는 여러 frame 동안 true가 될 수 있습니다. `KeyPressed`는 **눌리지 않은 상태에서 눌린 상태로 바뀐 순간**에 한 번만 true가 됩니다. 색을 한 번씩 바꾸거나 총알을 한 발 발사할 때 유용합니다.

특수 키는 `Key::Space`, `Key::Escape`처럼 쓰고 글자 키는 `'A'`처럼 쓸 수도 있습니다.

## 조금 바꾸어 보기

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

## 같은 입력이라도 원하는 행동이 다릅니다
계속 움직여야 하면 `KeyDown`, 한 번만 일어나야 하면 `KeyPressed`가 자연스럽습니다. 키를 놓은 순간이 필요할 때는 `KeyReleased`도 있습니다.

다음에는 같은 방식으로 마우스의 위치와 버튼 상태를 읽어 봅니다.

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


# 기존 15강 — Mouse


## 마우스는 위치와 버튼 정보를 줍니다

키보드에서는 어떤 키인지를 물었다면, 마우스에서는 **어디를 가리키는지**와 **어떤 버튼 상태인지**를 함께 묻습니다. MouseX와 MouseY가 돌려주는 좌표를 도형 위치로 사용하면 도형이 커서를 따라갑니다.

클릭한 위치에 점을 계속 남기는 프로그램은 매번 현재 위치만 읽는 것으로는 부족합니다. 이전에 찍은 위치들도 데이터로 기억하고 다음 frame에 다시 그려야 합니다. “현재 입력 읽기”와 “과거 상태 저장하기”가 서로 다른 일이라는 점을 생각해 보세요.

## 마우스는 좌표를 알려 줍니다
Window 안에서 마우스가 있는 위치를 `MouseX()`와 `MouseY()`로 읽을 수 있습니다. 매 frame 그 위치에 원을 그리면 원이 마우스를 따라다닙니다.

## 먼저 실행해 보세요

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

## 버튼도 키보드와 같은 세 가지 상태가 있습니다
`MouseDown`은 버튼을 누르고 있는 동안, `MousePressed`는 방금 누른 순간, `MouseReleased`는 방금 놓은 순간에 true입니다.

버튼은 `MouseButton::Left`, `MouseButton::Right`, `MouseButton::Middle`로 지정합니다.

## 조금 바꾸어 보기

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

## 위치와 상태를 함께 사용하기
마우스 입력의 재미있는 점은 **어디에서** 일어났는지와 **무슨 버튼을 눌렀는지**를 함께 알 수 있다는 것입니다. 그래서 그림 그리기, 버튼, 간단한 drag 같은 interaction을 만들 수 있습니다.

지금 Window는 매 frame Clear하고 다시 그리는 방식이므로, 계속 남는 그림을 만들 때는 점들의 위치를 Array 등에 저장해 다시 그리는 방법도 생각할 수 있습니다.

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


# 기존 16강 — Animation


## 애니메이션은 상태를 바꾸며 다시 그리는 것입니다

**애니메이션(animation)**은 조금씩 다른 그림을 빠르게 보여 주어 움직임을 만드는 것입니다. 각 그림을 frame이라고 합니다. 공을 표현하는 x는 현재 위치라는 상태이고, 그 값을 바꾸어 같은 원을 다른 위치에 다시 그립니다.

예를 들어 x가 50이고 매번 2씩 더하면 그릴 위치는 52, 54, 56으로 바뀝니다. 변수는 움직임을 기억하고, 반복문은 그 변화와 그리기를 계속합니다. 이전 그림을 Clear하지 않으면 이동한 자리에 흔적이 남을 수 있습니다.

속도의 부호는 방향을 나타낼 수 있습니다. 양수이면 x가 커져 오른쪽으로, 음수이면 x가 작아져 왼쪽으로 움직입니다. speed = -speed는 크기는 유지하고 방향을 바꾸는 계산입니다. 이 장의 speed는 frame당 이동량이고, 다음 장에서는 초당 이동량으로 바꿉니다.

## 움직임은 여러 장의 그림입니다
컴퓨터 animation은 한 장의 그림이 실제로 움직이는 것이 아닙니다. 아주 짧은 시간마다 위치를 조금 바꾸어 다시 그립니다. 각각의 화면을 **frame**이라고 부릅니다.

먼저 x를 frame마다 2씩 증가시켜 원을 움직여 봅시다.

## 먼저 실행해 보세요

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

## update한 뒤 draw하기
animation loop에서는 보통 먼저 위치나 상태를 **update**하고, 그 결과를 **draw**합니다. `Clear`로 이전 frame을 지우고 새 위치에 다시 그린 뒤 `Show`합니다.

하지만 지금 코드는 한 가지 문제가 있습니다. `x = x + 2`는 **frame당** 이동량입니다. 컴퓨터가 더 많은 frame을 그리면 공도 더 빨라집니다.

## 조금 바꾸어 보기

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

## 다음 lesson에서 고칠 문제
`Sleep(0.01)`로 속도를 대충 맞출 수는 있지만 정확한 해결은 아닙니다. 실제로 frame 하나에 얼마나 시간이 걸렸는지를 측정하면 **초당 몇 pixel**처럼 속도를 표현할 수 있습니다.

그래서 다음에는 StopWatch로 시간을 재고, animation을 컴퓨터 속도와 분리합니다.

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


# 기존 17강 — Measuring Time — StopWatch


## 경과 시간으로 움직임을 계산합니다

**경과 시간**은 어떤 시점부터 지금까지 지난 시간입니다. StopWatch는 이를 측정하는 도구입니다. Elapsed는 시간을 읽어 돌려주고, Reset은 측정의 시작점을 지금으로 바꿉니다. 읽기만 한다고 자동으로 0이 되지는 않습니다.

초당 200픽셀 속도로 0.01초 동안 움직이면 2픽셀, 0.02초 동안 움직이면 4픽셀 이동합니다. 이것이 거리 = 속도 × 시간입니다. `double dt = watch.Elapsed();`로 시간을 읽고 Reset한 뒤, speed * dt를 현재 위치에 더합니다.

한 번의 loop가 느렸다면 더 멀리, 빨랐다면 덜 이동시켜 실제 시간에 맞춥니다. dt는 새 문법이 아니라 경과 시간 조각을 저장하는 변수 이름입니다.

## 현실의 스톱워치처럼
`StopWatch`는 만들어지는 순간부터 시간이 흐릅니다. `Elapsed()`는 몇 초가 지났는지 알려주고 `Reset()`은 다시 0부터 재기 시작합니다.

먼저 단순히 시간을 재어 봅시다.

## 먼저 실행해 보세요

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

## frame time을 이용하기
animation loop의 시작에서 지난 frame 이후 걸린 시간을 `dt`로 구할 수 있습니다. 속도가 `200`이면 **초당 200 pixel**이라는 뜻으로 사용할 수 있습니다.

`x = x + speed * dt`라고 하면 frame이 빠른 컴퓨터에서는 dt가 작아지고, 느린 컴퓨터에서는 dt가 커져서 같은 실제 시간 동안 비슷한 거리를 움직입니다.

## 조금 바꾸어 보기

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

## dt는 elapsed time의 작은 조각입니다
`dt`는 delta time의 흔한 이름입니다. 특별한 Small 문법이 아니라 우리가 정한 변수 이름일 뿐입니다.

StopWatch는 animation뿐 아니라 reaction time, 코드가 걸린 시간, 게임 플레이 시간처럼 현실의 시간을 측정할 때도 그대로 사용할 수 있습니다.

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

## Exercise — 시간 기준으로 움직이기

Lesson 16의 위아래 움직이는 공을 고쳐서 speed를 초당 150 pixel로 만들고 dt를 사용하세요.

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


# 기존 18강 — Sound


## 함수가 끝나는 때와 소리가 끝나는 때

소리 재생에는 **시작시키고 바로 다음 명령으로 가기**와 **재생이 끝날 때까지 기다리기**가 있습니다. PlaySound는 소리를 시작시킨 뒤 프로그램이 계속 진행하게 합니다. PlaySoundAndWait는 소리가 끝나야 다음 명령으로 넘어갑니다.

화면을 계속 그리는 게임에서 기다리는 함수를 쓰면 그동안 그림 갱신이 멈출 수 있습니다. 반대로 음을 차례로 들려주려면 기다리는 재생이 간단합니다. “함수를 호출했다”와 “그 함수가 시작한 작업이 모두 끝났다”를 구분하세요.

Beep의 주파수는 음의 높이, seconds는 재생 길이를 정합니다. 작은 소리로 짧게 시험하고, 소리가 들리지 않으면 장치의 음량도 확인하세요.

## 프로그램에 소리를 더하기
Small C++에는 바로 사용할 수 있는 몇 가지 효과음이 있습니다. `PlaySound`는 소리를 시작하고 프로그램은 바로 다음 줄로 진행합니다. 게임처럼 화면도 계속 움직여야 할 때 편합니다.

## 먼저 실행해 보세요

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

## 기다릴 것인가, 계속할 것인가
`PlaySoundAndWait`는 소리가 끝날 때까지 기다린 뒤 다음 줄을 실행합니다. 여러 소리를 순서대로 들려줄 때 이해하기 쉽습니다.

`Beep(frequency, seconds)`는 주파수와 길이를 직접 지정한 간단한 음을 재생합니다. `BeepAndWait`도 같은 방식으로 기다립니다.

## 조금 바꾸어 보기

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

## 게임에서는 보통 기다리지 않습니다
공이 벽에 부딪힐 때 효과음 때문에 animation이 멈추면 어색합니다. 이런 경우에는 `PlaySound`처럼 프로그램을 멈추지 않는 재생이 자연스럽습니다.

반대로 짧은 멜로디를 순서대로 들려주려면 AndWait 버전이 간단합니다.

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


# 기존 19강 — Events — Timer and Callbacks


## 이벤트와 콜백은 무엇인가요?

**이벤트(event)**는 키 누름이나 시간 경과처럼 프로그램이 반응할 사건입니다. **콜백(callback)**은 그 사건에 반응하도록 다른 기능에 맡겨 두는 함수입니다. “지금 실행”하는 대신 “해당 사건이 일어나면 이 함수를 실행”하도록 등록합니다.

Timer는 정해진 간격의 시간 경과를 알려 주는 도구입니다. `timer.Start(1.0, OnTimer);`는 약 1초 간격으로 OnTimer를 호출하도록 등록합니다. `OnTimer()`는 지금 호출하는 표기이지만, 여기의 OnTimer는 나중에 호출할 함수를 지정하는 표기입니다.

Start가 끝났다고 콜백을 한 번 실행하고 끝나는 것이 아닙니다. 타이머를 멈추기 전까지 사건이 반복됩니다. 첫 예제는 ticks를 공유하여 호출할 때마다 1 늘리고, 약 3.2초 동안 기다린 뒤 Stop합니다. 시간 예약은 정확한 횟수나 정밀한 시각을 보장하는 시계로 생각하지 마세요.

## 시간이 되면 어떤 일을 시키기
지금까지 프로그램의 흐름은 대부분 `SmallMain`의 위에서 아래로 진행되었습니다. 하지만 어떤 일은 **1초마다**, 또는 **일정한 간격마다** 일어나게 하고 싶습니다.

`Timer`는 정해진 시간이 지날 때마다 우리가 지정한 함수를 호출할 수 있습니다. 이런 함수를 **callback**이라고 부릅니다.

## 먼저 실행해 보세요

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

## 함수 자체를 전달하기
`timer.Start(1.0, OnTimer);`에서 `OnTimer` 뒤에는 괄호가 없습니다. 지금 OnTimer를 실행하는 것이 아니라, **나중에 Timer가 호출할 함수**로 알려주는 것입니다.

callback은 parameter가 없고 return type이 void인 간단한 함수로 시작합니다. Timer가 실행되는 동안 SmallMain도 자기 일을 계속할 수 있습니다.

## 조금 바꾸어 보기

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

## Event-based programming의 첫 맛
Timer는 프로그램이 계속 실행되는 동안 특정 사건이 생겼을 때 callback을 호출합니다. GUI, 게임, 네트워크 프로그램에서도 이런 **event** 개념을 많이 만납니다.

지금은 callback이 전역 함수이고 공유하는 변수도 간단히 바깥에 두었습니다. 뒤에서 class를 배우면 관련된 상태와 행동을 한 객체에 묶는 방법도 이해할 수 있습니다.

## 출력할 문자열 만들기

`Format("Seconds: ", seconds)`는 Print와 달리 화면에 출력하지 않고, 글자와 값을 이어 붙인 String을 돌려줍니다. DrawText에 숫자가 포함된 문장을 전달할 때 사용합니다.

이 예제의 전역 seconds는 SmallMain과 OnSecond가 함께 사용하는 상태입니다. 함수 안에서 다시 seconds를 선언하면 별도 변수가 되므로 같은 값이 갱신되지 않습니다.

Timer는 별도 계산 스레드를 만드는 기능이 아닙니다. Small의 이벤트 처리 시점에 callback을 실행하므로 Show나 Sleep 같은 이벤트를 처리하는 호출 없이 긴 계산만 계속하면 callback도 늦어질 수 있습니다. callback은 짧게 끝내고, 정확한 경과 시간은 StopWatch로 측정하세요.

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


# 기존 20강 — Make a Game


## 게임은 상태를 규칙에 따라 바꾸는 프로그램입니다

게임의 **상태**는 공의 위치·속도, paddle 위치, 점수처럼 현재 상황을 나타내는 값들입니다. **규칙**은 입력이나 충돌이 있을 때 이 값을 어떻게 바꿀지 정합니다. 화면은 그 상태를 눈으로 보여 주는 결과입니다.

예를 들어 오른쪽 키가 눌리면 paddle 위치를 바꾸고, 공이 벽을 넘으면 위치를 경계로 되돌린 뒤 속도의 부호를 바꿉니다. 충돌 판정은 그림을 보고 판단하는 것이 아니라 좌표·크기를 비교하는 조건식입니다.

긴 코드를 한 번에 외우지 말고 상태를 저장하는 변수, 상태를 바꾸는 코드, 그 상태를 그리는 코드를 찾아보세요. 게임을 만든다는 것은 이미 배운 변수·조건·반복·함수를 이 역할들에 배치하는 일입니다.

## 지금까지 배운 것을 하나로 묶기
게임은 새로운 마법 기능 하나가 아니라 우리가 이미 배운 작은 아이디어들의 조합입니다. Window에 그리고, 키보드를 읽고, frame마다 위치를 바꾸고, StopWatch로 실제 시간을 측정하고, 사건이 생기면 소리를 냅니다.

간단한 Pong의 한쪽 paddle과 공을 만들어 봅시다.

## 먼저 실행해 보세요

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

## 게임 loop를 네 부분으로 읽기
긴 코드도 역할로 나누어 보면 단순합니다.

1. **Time** — dt를 측정합니다.
2. **Input** — 키보드를 읽습니다.
3. **Update** — paddle과 공의 위치, 충돌을 계산합니다.
4. **Draw** — 현재 상태를 화면에 그립니다.

아직 class가 없어도 변수와 함수만으로 작은 게임을 충분히 만들 수 있습니다.

## 충돌에서는 위치도 함께 고칩니다
공이 한 frame에 벽을 조금 넘어갈 수 있기 때문에 속도의 방향만 바꾸면 다음 frame에도 여전히 벽 밖에 있을 수 있습니다. 그러면 방향이 다시 뒤집혀 공이 벽에 붙은 것처럼 보일 수 있습니다.

그래서 이 예제는 충돌을 발견하면 **먼저 공을 경계 위치로 되돌리고, 그다음 속도의 방향을 바꿉니다.**

`collision → position correction → velocity response`

Paddle 충돌과 벽 충돌 모두 같은 원칙을 사용합니다.

## 조금 바꾸어 보기

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

## 완성보다 바꾸어 보는 것이 중요합니다
게임 코드는 정답 하나가 있는 문제가 아닙니다. 속도, 크기, 색, 규칙을 조금씩 바꾸면 전혀 다른 느낌이 납니다. 기존 코드를 이해한 뒤 한 가지 규칙을 추가하는 것이 좋은 다음 단계입니다.

Part II는 여기서 끝납니다. 다음 Part에서는 새로운 화면 기능보다, 지금까지 배운 변수·반복·함수·Array를 사용해 **문제를 해결하는 알고리즘**을 만들어 봅니다.

## 긴 프로그램에서 오류 찾기

먼저 컴파일 오류, 실행 중 오류, 실행은 되지만 결과가 틀린 논리 오류를 구분하세요. Diagnostics의 첫 오류부터 읽고 표시된 줄 주변의 괄호·이름·타입을 확인합니다.

논리 오류라면 `Print("ballX: ", ballX);`처럼 값을 출력해서 예상과 비교할 수 있습니다. 게임 loop에서는 출력이 너무 많아지므로 충돌이 일어날 때만 출력하는 식으로 범위를 좁히세요.

IDE의 디버깅 기능으로 관심 있는 줄에 중단점을 설정하고 디버그 실행하면 그 지점의 변수 값을 살펴볼 수 있습니다. 한 단계씩 진행하며 입력 → 위치 변경 → 충돌 → 그리기 순서를 확인하세요. 실행을 잠시 멈추었다가 재개하면 dt가 커질 수 있다는 점도 유의하세요.

충돌 예제는 간단한 위치 기반 판정입니다. 매우 빠른 공은 한 frame에 패들을 통과할 수 있습니다. 속도를 과하게 키운 경우까지 완전한 물리 시뮬레이션을 보장하는 예제는 아닙니다.

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


# 기존 21강 — Counting and Summing


## 알고리즘은 답을 구하는 절차입니다

**알고리즘(algorithm)**은 원하는 결과를 얻기 위한 구체적인 절차입니다. “모두 더한다”는 목표를 컴퓨터가 실행할 수 있도록, 어느 값부터 보고 무엇을 기억하며 언제 끝낼지 정합니다.

합계를 구하는 절차는 total을 0으로 만들고, 원소 하나를 읽어 total에 더하고, 모든 원소를 볼 때까지 반복하는 것입니다. `{3, 7, 2, 9, 4}`를 읽는 동안 total은 0에서 3, 10, 12, 21, 25로 바뀝니다. 매 단계의 total은 **지금까지 본 값들의 합**입니다.

개수 세기도 비슷합니다. 다만 원소의 값을 더하는 대신 조건을 만족할 때마다 1을 더합니다. “값들의 합”과 “값이 몇 개인가”는 다른 질문입니다. 누적 변수는 반복문 밖에 만들어 이전 단계의 결과를 유지합니다.

## 반복하면서 답을 만들어 가기
Array의 모든 값을 한 번씩 보면서 하나의 답을 만들어 낼 수 있습니다. 합계를 구할 때는 `total`을 0에서 시작하고 값을 하나씩 더합니다. 이런 변수를 **accumulator**라고 부르기도 합니다.

## 먼저 실행해 보세요

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

## 나머지로 짝수 판별하기

두 번째 예제의 `numbers[i] % 2 == 0`은 4장에서 배운 나머지와 6장의 비교를 결합합니다. 2로 나눈 나머지가 0이면 짝수입니다. 값이 0인 경우도 이 조건을 만족합니다.

## 세는 것도 같은 패턴입니다
조건에 맞는 값을 만날 때마다 `count = count + 1`을 하면 개수를 셀 수 있습니다. 합계와 개수는 이후 평균, 검색, 통계 같은 많은 알고리즘의 재료가 됩니다.

지금은 Array를 함수에 전달할 때도 `Array<int> numbers`처럼 값으로 받습니다. reference는 Lesson 33에서 다룹니다.

## 조금 바꾸어 보기

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

## 알고리즘은 작은 단계의 조합입니다
처음에는 `for`, `if`, 변수만 보이지만, 이제 이 도구들을 조합해 **문제를 푸는 절차**를 만들고 있습니다. 앞으로는 같은 Array를 어떻게 더 영리하게 살펴볼지 생각합니다.

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


# 기존 22강 — Finding the Largest and Smallest


## 최댓값을 찾는 동안 무엇을 기억할까요?

**최댓값**은 주어진 값 중 가장 큰 값입니다. 모든 값을 한꺼번에 판단하기보다, 하나씩 보면서 **지금까지 본 것 중 가장 큰 값**을 기억할 수 있습니다.

첫 예제의 값은 7, 2, 9, 4, 5입니다. largest를 7로 시작합니다. 2는 작으니 그대로, 9는 크니 9로 바꾸고, 4와 5에서는 유지합니다. 끝났을 때 largest는 전체에서 가장 큰 9입니다.

값과 위치는 다릅니다. 9는 최댓값이고 2는 그 값이 있는 인덱스입니다. 위치를 기억하면 해당 원소의 다른 정보도 찾아갈 수 있습니다. 빈 배열에는 첫 원소가 없으므로, 이 장에서는 원소가 하나 이상이라는 조건을 먼저 정합니다.

## 지금까지 본 것 중 가장 큰 값 기억하기
가장 큰 값을 찾으려면 첫 번째 값을 `largest`로 기억한 뒤 나머지를 하나씩 비교합니다. 더 큰 값을 만나면 기억을 바꿉니다.

## 먼저 실행해 보세요

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

## 값뿐 아니라 위치도 기억할 수 있습니다
때로는 가장 작은 값 자체보다 **어디에 있는지**가 필요합니다. 그럴 때는 `smallestIndex`를 기억하고 비교할 때 `numbers[smallestIndex]`를 사용합니다.

첫 값을 시작점으로 쓰기 때문에 이 lesson의 Array는 비어 있지 않다고 가정합니다.

## 조금 바꾸어 보기

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

## 좋은 초기값은 데이터에서 가져옵니다
`largest = 0`으로 시작하면 모든 값이 음수일 때 틀립니다. 첫 번째 실제 값을 초기 답으로 삼으면 그런 특별한 가정이 필요 없습니다. 이 패턴은 앞으로 정렬에서도 다시 사용합니다.

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


# 기존 23강 — Linear Search


## 검색은 원하는 값의 위치를 찾는 일입니다

**검색(search)**은 데이터에서 원하는 것을 찾는 과정입니다. 이 장에서는 배열에서 특정 값이 있는 위치를 구합니다. 값 자체를 이미 알고 있어도 “몇 번째에 있는가”는 별도의 정보입니다.

**선형 검색(linear search)**은 앞에서부터 하나씩 확인합니다. 첫 예제에서 9를 찾을 때 인덱스 0의 7은 다르고, 1의 2도 다르고, 2의 9가 같습니다. 따라서 Find는 2를 반환합니다. 같은 값이 여러 개면 이 함수는 처음 만난 위치를 돌려줍니다.

찾지 못한 경우도 결과로 표현해야 합니다. 유효한 인덱스에 없는 -1을 사용하기로 약속합니다. -1은 배열에서 읽을 위치가 아니라 실패 표시입니다. 찾은 결과로 원소에 접근하려면 먼저 -1이 아닌지 확인해야 합니다.

## 원하는 값은 어디에 있을까요?
가장 단순한 검색은 첫 번째 값부터 차례대로 확인하는 것입니다. 찾으면 그 위치를 즉시 `return`할 수 있습니다.

## 먼저 실행해 보세요

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

## 못 찾았다는 것도 결과입니다
올바른 index는 0 이상이므로 `-1`을 **찾지 못함**의 표시로 사용할 수 있습니다. 이런 특별한 값을 sentinel이라고 부르기도 합니다.

Linear search는 데이터가 어떤 순서인지 몰라도 사용할 수 있다는 장점이 있습니다.

## 조금 바꾸어 보기

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

## return과 break를 구별하세요

첫 예제는 검색 함수에서 return하여 위치를 돌려주고 함수 전체를 끝냅니다. 두 번째 예제의 break는 검색 loop만 끝냅니다. 따라서 loop 뒤에서 결과를 출력할 수 있습니다. 8장에서 배운 반복 종료와 9장에서 배운 함수 종료를 연결해 보세요.

## 검색 비용은 어디에 있나요?
찾는 값이 마지막에 있거나 아예 없다면 모든 값을 확인해야 합니다. Array가 1,000개라면 최대 1,000번 비교할 수 있습니다. 이 사실은 정렬된 데이터에서 더 빠른 검색을 생각하는 출발점이 됩니다.

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


# 기존 24강 — Sorting


## 정렬은 정한 기준에 맞게 순서를 바꿉니다

**정렬(sorting)**은 원소들을 정한 순서로 재배치하는 일입니다. 숫자가 작은 것부터 나열하면 **오름차순**, 큰 것부터면 **내림차순**입니다. 원소를 삭제하는 것이 아니라 위치를 바꿉니다.

이 장의 **선택 정렬(selection sort)**은 남은 부분에서 가장 작은 값을 골라 앞에 둡니다. `{7, 2, 9, 4, 5}`에서 먼저 2를 찾아 첫 값 7과 바꾸면 `{2, 7, 9, 4, 5}`가 됩니다. 다음에는 첫 칸을 제외한 부분에서 4를 골라 두 번째 칸에 놓습니다.

두 값을 서로 바꾸는 일을 **교환(swap)**이라고 합니다. a에 b를 넣고 곧바로 b에 a를 넣으면 원래 a를 잃습니다. 그래서 임시 변수 temp에 원래 값을 보관한 뒤 두 위치에 옮깁니다. 바깥 반복은 확정할 위치, 안쪽 반복은 남은 후보를 찾는 역할입니다.

## 정렬을 컴퓨터에게 설명한다면
사람은 숫자를 보고 금방 작은 순서로 놓을 수 있지만 컴퓨터에게는 정확한 절차가 필요합니다. Selection Sort는 아직 정리되지 않은 부분에서 가장 작은 값을 찾아 앞쪽에 놓는 일을 반복합니다.

## 먼저 실행해 보세요

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

## 바깥 반복과 안쪽 반복
바깥쪽 i는 **이번에 확정할 위치**입니다. 안쪽 j는 i 뒤의 값들을 훑으며 가장 작은 위치를 찾습니다. 마지막 세 줄은 두 값을 서로 바꾸는 swap입니다.

빠른 정렬을 배우는 것이 이 lesson의 목적은 아닙니다. 정렬이라는 말을 컴퓨터가 실행할 수 있는 작은 단계로 바꾸는 것이 목적입니다.

## 조금 바꾸어 보기

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

## 작은 변화로 순서가 뒤집힙니다
가장 작은 값을 찾던 비교를 가장 큰 값을 찾도록 바꾸면 내림차순 정렬이 됩니다. 알고리즘을 이해하면 외운 코드를 복사하는 대신 원하는 동작에 맞게 변형할 수 있습니다.

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


# 기존 25강 — Visualizing an Algorithm


## 시각화는 데이터를 그림으로 표현합니다

**시각화(visualization)**는 값이나 처리 과정을 위치·길이·색 같은 눈에 보이는 표현으로 바꾸는 일입니다. 여기서는 배열의 값을 막대 높이로, 인덱스를 가로 위치로 나타냅니다.

값이 7이고 배율이 30이면 높이는 210입니다. 화면에서 y가 아래로 커지므로 바닥을 420에 맞추려면 막대의 위쪽 y를 420 - height로 정합니다. 숫자를 그림으로 옮길 때에도 좌표 계산이 필요합니다.

첫 예제는 배열의 현재 모습 한 장이고, 두 번째 예제는 정렬로 배열이 바뀔 때마다 그 모습을 다시 그립니다. 빨간색은 지금 선택한 위치를 나타내는 표시입니다. 그림이 정렬을 하는 것이 아니라, 정렬 알고리즘이 바꾼 데이터를 그림이 보여 줍니다.

## 알고리즘을 눈으로 보기
Part II에서 배운 Graphics를 이제 생각을 이해하는 도구로 사용해 봅시다. Array의 값을 막대 높이로 그리면 정렬 과정이 실제로 어떻게 변하는지 볼 수 있습니다.

## 먼저 실행해 보세요

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

## 한 단계마다 다시 그리기
정렬의 swap이 끝날 때마다 화면을 Clear하고 현재 Array를 다시 그리면 값들이 이동하는 과정을 볼 수 있습니다.

여기서는 일부러 drawing 코드를 함수로 빼지 않습니다. Window를 함수에 효율적으로 전달하는 방법은 reference를 알아야 자연스럽게 설명할 수 있기 때문입니다. **Lesson 33 전까지는 아직 배우지 않은 문법을 마법처럼 사용하지 않습니다.**

## 조금 바꾸어 보기

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

## 그림은 디버깅 도구이기도 합니다
값을 Print하는 것처럼 그림으로 상태를 표시하면 알고리즘의 행동을 더 쉽게 발견할 수 있습니다. 복잡한 프로그램에서도 visualization은 결과를 예쁘게 보여주는 것뿐 아니라 **무슨 일이 일어나는지 이해하는 방법**이 될 수 있습니다.

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


# 기존 26강 — Binary Search


## 이진 검색은 가능한 범위를 반씩 줄입니다

**이진 검색(binary search)**은 정렬된 데이터에서 가운데 값을 보고 찾을 범위를 줄이는 방법입니다. 선형 검색처럼 모두 차례로 확인하지 않습니다. 정렬되어 있기 때문에 가운데 값보다 작은 목표는 오른쪽에 있을 수 없다고 판단할 수 있습니다.

첫 예제의 `{1, 3, 5, 7, 9, 11, 13}`에서 11을 찾습니다. 처음 가운데 인덱스 3의 값은 7입니다. 11은 더 크므로 인덱스 0부터 3까지는 후보에서 제외합니다. 남은 범위 4부터 6의 가운데 인덱스 5에서 11을 찾습니다. 결과는 값 11이 아니라 인덱스 5입니다.

left와 right는 남아 있는 후보 범위의 양 끝입니다. 가운데까지 확인했으므로 다음 범위에서는 middle을 다시 넣지 않고 +1 또는 -1로 제외합니다. 범위가 줄어들지 않으면 반복이 끝나지 않을 수 있습니다.

## 정렬되어 있다면 더 영리하게 찾을 수 있습니다
Linear Search는 앞에서부터 하나씩 봅니다. 하지만 숫자가 정렬되어 있다면 가운데 값을 보고 찾는 값이 왼쪽에 있을지 오른쪽에 있을지 결정할 수 있습니다.

한 번 비교할 때마다 필요 없는 절반을 버리는 것이 Binary Search의 핵심입니다.

## 먼저 실행해 보세요

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

## left와 right가 남은 범위입니다
처음에는 Array 전체가 후보입니다. middle을 확인한 뒤 찾는 값이 더 작으면 right를 왼쪽으로, 더 크면 left를 오른쪽으로 옮깁니다. `left > right`가 되면 남은 후보가 없다는 뜻입니다.

중요한 전제는 **Array가 정렬되어 있어야 한다**는 것입니다. 정렬되지 않은 데이터에서는 어느 절반을 버려도 되는지 알 수 없습니다.

## 조금 바꾸어 보기

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

## 절반씩 줄어드는 힘
1,000개 중 하나를 찾는다고 해도 범위는 대략 1000 → 500 → 250 → 125처럼 빠르게 줄어듭니다. 다음 lesson에서는 Linear Search와 실제 비교 횟수를 나란히 측정해 봅니다.

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


# 기존 27강 — Faster and Slower Algorithms


## 작업량이 자라는 속도를 비교합니다

**입력 크기**는 처리할 데이터의 양이며 여기서는 배열 원소 수 n입니다. **시간 복잡도**는 입력 크기가 커질 때 필요한 작업량이 어떻게 증가하는지 설명하는 개념입니다. 실제로 몇 초 걸리는지를 그대로 뜻하지는 않습니다.

찾는 값이 없을 때 선형 검색은 원소를 끝까지 확인합니다. 원소가 10배면 확인할 원소 수도 10배입니다. 이진 검색은 남은 후보를 계속 반으로 줄이므로 데이터가 두 배가 되어도 범위를 줄이는 단계는 대략 한 번만 늘어납니다.

Big-O는 이런 증가 방식의 상한을 표현하는 표기입니다. 여기서는 최악의 경우를 비교하며, O(n)은 n에 비례하여 늘어나는 규모, O(log n)은 반으로 줄이는 단계 수처럼 늘어나는 규모로 이해하면 됩니다. 정확한 수학적 정의는 뒤의 알고리즘 학습에서 다룹니다.

이 장의 비교 횟수라는 말은 예제에서 센 원소 검사나 반복 단계 수를 뜻합니다. 한 단계 안에서 C++ 비교 연산자가 여러 번 실행될 수 있으므로 연산자 하나하나를 센 수와 구분하세요.

## 빠르다는 말보다 중요한 질문
작은 Array에서는 대부분의 알고리즘이 금방 끝납니다. 더 중요한 질문은 **데이터가 10배 커지면 해야 할 일이 얼마나 늘어나는가?**입니다.

Linear Search는 최악의 경우 모든 값을 봅니다. 100개면 100번, 1,000개면 1,000번입니다.

## 먼저 실행해 보세요

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

## Binary Search는 다르게 자랍니다
Binary Search는 범위를 절반으로 줄입니다. 1,024개도 약 11번이면 범위를 모두 줄일 수 있습니다.

이런 성장 방식을 간단히 표현하는 표기법이 **Big-O**입니다. Linear Search는 `O(n)`, Binary Search는 `O(log n)`이라고 부릅니다. 지금은 수학적 정의를 외울 필요가 없습니다. 입력이 커질 때 작업량이 어떤 모양으로 자라는지를 보는 것이 핵심입니다.

## 조금 바꾸어 보기

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

## Big-O는 속도계가 아닙니다
`O(log n)`이라고 해서 언제나 특정 프로그램이 몇 초 걸린다는 뜻은 아닙니다. 컴퓨터, 구현, 데이터에 따라 실제 시간은 달라집니다. Big-O는 **문제가 커질 때 필요한 일의 양이 어떻게 증가하는지**를 비교하는 언어입니다.

지금은 O(n), O(log n) 두 이름만 맛보고 넘어갑니다.

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


# 기존 28강 — Algorithm Challenge


## 문제의 뜻과 가정을 먼저 정합니다

“두 번째로 큰 값”이라는 말은 같은 값이 반복될 때 뜻이 모호할 수 있습니다. 예를 들어 9, 9, 5에서 두 번째 자리를 말하면 9지만, 서로 다른 값 중 두 번째를 말하면 5입니다. 이 장은 **서로 다른 값이 두 개 이상**이라는 가정을 두어 이를 피합니다.

첫 예제에서는 지금까지 본 가장 큰 값 largest와 두 번째 값 second를 기억합니다. 8과 3으로 시작해서 12를 만나면, 기존 1등 8이 2등이 되고 12가 1등이 됩니다. 다음 5는 둘보다 작아 그대로 두고, 10을 만나면 2등만 10으로 바꿉니다.

이처럼 “어떤 정보를 기억해야 다음 원소를 처리할 수 있는가”를 정하는 것이 알고리즘 설계의 핵심입니다. 코드에 들어가기 전에 작은 입력으로 이 갱신 과정을 직접 따라가 보세요.

## 이제 문제를 먼저 봅니다
이번 lesson에는 새로운 문법이나 API가 없습니다. 목표는 문제를 읽고 이미 아는 도구를 조합하는 것입니다.

문제: **서로 다른 숫자들이 들어 있는 Array에서 두 번째로 큰 값을 찾아라.**

한 가지 방법은 largest와 second를 함께 기억하면서 Array를 한 번 훑는 것입니다.

## 먼저 실행해 보세요

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

## 먼저 가정과 단계를 정합니다
이 예제는 Array에 서로 다른 값이 두 개 이상 있다고 가정합니다. 이런 **가정**을 먼저 말하는 것도 알고리즘 설계의 일부입니다.

문제를 풀 때 바로 코드를 쓰기보다 다음을 생각해 보세요.

1. 무엇을 기억해야 하는가?
2. 새 값을 하나 보았을 때 기억을 어떻게 바꿀 것인가?
3. 특별한 입력이나 가정은 무엇인가?

## 조금 바꾸어 보기

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

## 정답은 하나가 아닙니다
정렬한 뒤 두 번째 값을 보는 방법도 있고, 한 번 훑으면서 두 값을 기억하는 방법도 있습니다. 어떤 방법이 더 단순한지, 데이터가 커지면 어떤 일이 생기는지 비교할 수 있습니다.

여기까지 오면 기본 문법을 아는 것에서 한 단계 넘어와 **알고리즘을 설계하고 비교하는 경험**을 한 것입니다. 다음 Part는 잠깐 방향을 바꾸어 프로그램의 데이터를 파일에 저장하고 다시 불러옵니다.

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


# 기존 29강 — Text Files


## 파일은 실행이 끝난 뒤에도 남기는 데이터입니다

변수에 저장한 값은 보통 프로그램 실행이 끝나면 사라집니다. **파일(file)**은 이름과 경로를 가지고 저장 장치에 남겨 둘 수 있는 데이터입니다. 저장한 점수를 다음 실행에서 다시 읽는 데 사용할 수 있습니다.

**텍스트 파일**은 문자로 내용을 기록하므로 메모장 같은 도구로 읽을 수 있습니다. 첫 예제는 Alex와 1200을 각각 한 줄에 기록합니다. 파일 안의 1200은 정수 변수 자체가 아니라 숫자를 나타내는 문자들입니다. 읽을 때 InputInt가 이를 정수로 해석합니다.

File 객체를 만드는 것, 파일을 여는 것, 내용을 읽거나 쓰는 것, 닫는 것은 별개의 단계입니다. **모드(mode)**는 읽기·새로 쓰기·덧붙이기 중 무엇을 할지 지정합니다. **경로(path)**는 어느 파일인지를 나타내는 위치 정보입니다. 같은 score.txt라도 기준 폴더가 다르면 다른 파일입니다.

## 프로그램을 꺼도 기억하게 하기
지금까지 변수의 값은 프로그램이 끝나면 사라졌습니다. 게임의 high score처럼 다음 실행에서도 기억해야 하는 값은 **파일**에 저장할 수 있습니다.

먼저 사람이 메모장으로도 읽을 수 있는 text file을 만들어 봅시다.

## 먼저 실행해 보세요

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

## Open → 사용 → Close
`FileMode::Write`로 열면 새로 쓰기 위해 기존 내용을 지우고 시작합니다. `Print`는 값을 쓰고 줄을 바꾸며 `Write`는 줄을 바꾸지 않습니다.

읽을 때는 기본 mode가 Read이므로 `file.Open("score.txt");`만 써도 됩니다. `Input`, `InputInt`, `InputReal`로 한 줄의 String, int, double을 읽을 수 있습니다.

File은 scope가 끝날 때 자동으로 닫히기도 하지만, 처음에는 **Open한 파일을 Close한다**는 흐름을 명시적으로 익힙니다.

## 조금 바꾸어 보기

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

## 파일은 어디에 생길까요?
소스 파일을 저장한 뒤 Run하면 상대 경로의 파일은 보통 그 소스가 있는 폴더에 만들어집니다. 내장 Example을 그대로 실행하면 임시 실행 폴더를 사용하므로 파일을 남기고 싶다면 **Try → 소스 저장 → Run** 순서가 좋습니다.

`Append` mode를 사용하면 기존 내용을 지우지 않고 끝에 새 내용을 추가할 수도 있습니다.

## 읽기 전에 파일을 준비하세요

두 번째 예제는 첫 번째 예제로 score.txt를 만든 뒤 실행하세요. 두 소스를 같은 폴더에 저장해야 같은 상대 경로의 파일을 읽을 수 있습니다. 없는 파일을 읽거나 숫자가 있어야 할 줄에 글자가 있으면 정상적인 입력으로 처리할 수 없습니다. 오류가 나면 파일 위치와 내용을 먼저 확인하세요.

Write는 기존 내용을 지우므로 직접 만든 연습용 파일로만 실험하세요. 텍스트 파일을 메모장으로 열어 저장된 줄과 값을 확인하면 프로그램의 결과를 쉽게 검증할 수 있습니다.

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


# 기존 30강 — Binary Files


## 바이너리 파일도 바이트의 모음입니다

컴퓨터는 데이터를 **바이트(byte)** 단위로 저장합니다. 한 바이트는 8개의 비트로 이루어지며, 비트는 0 또는 1을 나타내는 단위입니다. 숫자도 메모리 안에서는 여러 바이트의 특정 패턴으로 표현됩니다.

텍스트로 123을 저장하면 숫자를 읽을 수 있도록 1, 2, 3이라는 문자 표현을 저장합니다. 이 장의 **바이너리 저장**은 숫자를 문자로 바꾸지 않고 int나 double의 메모리 표현을 기록합니다. 텍스트 파일도 물리적으로는 바이트로 저장되지만 그 바이트를 해석하는 약속이 다릅니다.

ReadInt는 다음 바이트들을 int로 읽습니다. 파일 자체가 “여기는 level, 다음은 score”라고 자동으로 알려 주지는 않습니다. 쓰는 쪽과 읽는 쪽이 타입과 순서를 맞추는 약속을 **파일 형식**이라고 생각하면 됩니다. 이 장의 간단한 형식은 서로 다른 컴퓨터 환경 사이의 호환성을 보장하지 않습니다.

## 숫자를 글자로 바꾸지 않고 저장한다면
Text file에 123을 쓰면 파일에는 문자 `'1'`, `'2'`, `'3'`이 들어갑니다. Binary file에서는 int가 메모리에서 사용하는 **native C++ representation**을 그대로 저장할 수 있습니다.

Small에서는 `WriteInt`, `WriteReal`, `ReadInt`, `ReadReal`만 제공해 binary I/O를 일부러 단순하게 유지합니다.

## 먼저 실행해 보세요

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

## 읽는 순서는 쓰는 순서와 같아야 합니다
binary file에는 줄이나 `Score:` 같은 설명이 없습니다. 프로그램이 어떤 값이 어떤 순서로 저장됐는지 알고 있어야 합니다.

위에서 int, int, double 순으로 썼다면 읽을 때도 같은 순서로 `ReadInt`, `ReadInt`, `ReadReal`을 호출합니다.

이 방식은 일부러 native representation을 사용합니다. 즉 C++의 int와 double이 현재 컴퓨터에서 사용하는 byte 표현을 그대로 기록합니다. 지금은 **내 프로그램의 간단한 save file** 정도로 생각하면 충분합니다.

## 조금 바꾸어 보기

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

## binary가 항상 더 좋은 것은 아닙니다
Text file은 사람이 직접 읽고 고치기 쉽고 다른 프로그램과도 다루기 편합니다. Binary file은 값의 표현을 그대로 저장하는 경험을 주고 compact한 save data를 만들기 쉽지만, 사람이 열어 봐도 의미를 알아보기 어렵습니다.

파일 형식의 호환성, byte order, 버전 관리 같은 문제는 더 큰 프로그램에서 중요해집니다. 이 tutorial에서는 binary representation이 실제 byte로 저장된다는 사실까지만 경험합니다.

이제 다시 C++ 자체로 돌아가, 관련된 데이터를 하나의 새로운 type으로 묶는 방법을 배웁니다.

`FileMode::AppendBinary`를 사용하면 기존 binary file의 끝에 새 binary 값을 추가할 수 있습니다. `WriteBinary`는 기존 내용을 지우고 새로 쓰지만, `AppendBinary`는 기존 byte를 유지합니다.

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


# 기존 31강 — struct — Make Your Own Value


## struct는 관련된 값들을 묶는 새 타입입니다

한 명의 플레이어는 이름과 점수를 함께 가집니다. **struct(구조체)**는 이렇게 관련된 여러 값을 한 묶음으로 다루도록 만드는 타입입니다. 각각의 항목을 **멤버(member)**라고 합니다.

`struct Player`의 정의는 Player가 어떤 항목들로 구성되는지를 정합니다. 이 정의 자체가 특정 플레이어 한 명을 만드는 것은 아닙니다. `Player player;`를 실행할 때 그 타입의 객체 하나를 만듭니다. int가 타입이고 score가 변수였던 것처럼, Player는 타입이고 player는 객체의 이름입니다.

`player.score = 1200;`은 그 플레이어의 score 멤버에 값을 저장합니다. 다른 Player 객체를 만들면 그 객체는 별도의 name과 score를 갖습니다. 첫 예제의 score에는 초기값이 없으므로 반드시 값을 대입한 뒤 읽습니다. 타입 정의를 마치는 중괄호 뒤에는 세미콜론도 필요합니다.

## 서로 관련된 값을 하나로 묶기
게임의 player에는 x, y, score처럼 함께 다니는 값이 많습니다. 변수를 따로 만들 수도 있지만, 이 값들이 **한 명의 Player**에 속한다는 사실을 코드에 표현하면 더 이해하기 쉽습니다.

`struct`를 사용하면 내가 직접 새로운 type을 만들 수 있습니다.

## 먼저 실행해 보세요

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

## struct도 하나의 값입니다
`Player player;`는 우리가 만든 Player type의 값을 하나 만듭니다. 점을 사용해 `player.name`, `player.score`처럼 안의 값을 사용합니다.

Array의 element type도 내가 만든 struct가 될 수 있습니다. 그러면 여러 player를 하나의 Array에 모아 알고리즘을 적용할 수 있습니다.

## 조금 바꾸어 보기

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

## type은 프로그램의 생각을 표현합니다
`int x`, `int y`, `int score`만 보면 이 값들이 무엇을 이루는지 사람이 추측해야 합니다. `Player`, `Point`, `Enemy` 같은 type을 만들면 프로그램이 다루는 개념 자체를 코드에 넣을 수 있습니다.

다음 lesson에서는 data뿐 아니라 그 data가 할 수 있는 **behavior**도 같은 type 안에 넣습니다.

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


# 기존 32강 — class — Data and Behavior


## class는 데이터와 그 데이터를 다루는 기능을 묶습니다

**class**는 객체가 어떤 데이터를 가지고 어떤 일을 할 수 있는지 정의하는 타입입니다. **객체(object)**는 그 타입으로 만든 실제 대상입니다. Counter라는 class를 한 번 정의하고 Counter 객체를 여러 개 만들면, 각 객체가 자신이 센 횟수를 따로 관리할 수 있습니다. 이 예제에서는 그 내부 변수 이름이 value입니다.

Counter의 AddOne은 해당 객체의 값을 바꾸는 기능이고 Value는 현재 값을 돌려주는 기능입니다. `Counter counter;`로 객체를 만든 뒤 AddOne을 두 번 호출하면 그 객체의 값은 0에서 1, 2로 바뀝니다. Value를 호출해 출력하면 2가 나옵니다.

이 장은 새 기능이 많은 OOP 이론을 배우는 것이 아니라, 이미 사용한 Window나 StopWatch처럼 **데이터와 관련 동작을 하나의 대상으로 묶을 수 있다**는 것을 이해하는 단계입니다. struct에도 멤버 함수를 둘 수 있습니다. 여기서는 데이터를 간단히 묶을 때 struct, 내부 상태를 감추고 동작으로 사용하게 할 때 class라는 사용 방식을 보여 줍니다.

## data가 할 수 있는 일까지 묶기
Player의 위치를 바꾸는 코드를 프로그램 곳곳에서 직접 작성하는 대신 Player에게 `Move`라는 행동을 줄 수 있습니다.

`class`는 data와 function을 같은 type 안에 넣을 수 있습니다. class 안의 함수를 **member function**이라고 부릅니다.

## 먼저 실행해 보세요

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

## public은 사용하는 쪽, private은 내부
`public` 아래의 member는 object를 사용하는 코드에서 호출할 수 있습니다. `private` 아래의 data는 class 안의 함수만 직접 사용할 수 있습니다.

Counter를 사용하는 사람은 value가 내부에서 어떻게 저장되는지 몰라도 `AddOne()`과 `Value()`만 알면 됩니다. 이것이 class가 구현의 세부사항을 감추는 기본적인 방법입니다.

우리가 이미 사용한 `Window`, `String`, `StopWatch`, `File`도 이런 class입니다.

## 조금 바꾸어 보기

**예제**

```cpp
class Ball
{
public:
    void Move()
    {
        x = x + speed;
    }

    void Draw(Window& window)
    {
        window.FillCircle(x, 200, 20, Yellow);
    }

private:
    double x = 50;
    double speed = 2;
};

void SmallMain()
{
    Window window;
    window.Open(640, 400);

    Ball ball;

    while (window.IsOpen())
    {
        ball.Move();

        window.Clear(Black);
        ball.Draw(window);
        window.Show();
        Sleep(0.01);
    }
}
```

## 여기서 처음 보이는 `Window&`
Ball의 `Draw`는 이미 열려 있는 **같은 Window**에 그려야 합니다. Window는 복사할 수 없는 객체이므로 여기서는 `Window&`를 사용합니다.

지금은 `&`를 “기존 Window를 그대로 사용한다”는 표지 정도로만 보고 넘어갑니다. 바로 다음 Lesson 33에서 **왜 필요한지, 메모리에서 무엇이 다른지**를 처음부터 설명합니다. 이 한 곳은 다음 개념으로 넘어가기 위한 의도적인 예고입니다.

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

## Exercise — 움직이는 Ball

Ball class에 x와 speed를 private data로 두고 Move와 X member function을 만드세요. Move를 세 번 호출한 뒤 X를 출력하세요.

**연습 시작 코드**

```cpp
class Ball
{
public:
    void Move()
    {
        // Move x.
    }

    double X()
    {
        return 0;
    }

private:
    double x = 10;
    double speed = 5;
};

void SmallMain()
{
    Ball ball;
    ball.Move();
    ball.Move();
    ball.Move();

    Print(ball.X());
}
```

### Hint

Move에서는 x에 speed를 더하고 X에서는 `return x;`를 사용하세요.

**정답**

```cpp
class Ball
{
public:
    void Move()
    {
        x = x + speed;
    }

    double X()
    {
        return x;
    }

private:
    double x = 10;
    double speed = 5;
};

void SmallMain()
{
    Ball ball;
    ball.Move();
    ball.Move();
    ball.Move();

    Print(ball.X());
}
```


# 기존 33강 — References — Sharing Without Copying


## 복사와 참조는 다른 대상을 사용합니다

**값 복사**는 원래 값과 같은 내용을 가진 별도 값을 만드는 것입니다. 첫 예제에서 n은 10이고 AddOne의 x는 그 값을 복사해서 받습니다. x를 11로 바꾸어도 n은 10입니다. 출력은 Inside: 11, Outside: 10입니다.

**참조(reference)**는 기존 객체를 가리켜 그 객체를 다른 이름으로 사용하는 방법입니다. 매개변수를 `int& x`로 바꾸면 AddOne(n)의 x는 별도 복사본이 아니라 원래 n을 사용합니다. 그때 x를 바꾸면 n도 바뀝니다. 먼저 이 한 글자 차이를 바꾸어 실행해 비교해 보세요.

복사가 “내용이 같은 다른 칸”이라면 참조는 “같은 칸을 부르는 다른 이름”입니다. 참조를 통한 변경은 원본에도 영향을 미치므로 함수가 원본을 바꾸는지 분명히 해야 합니다.

`const T&`는 복사하지 않고 기존 값을 읽되, 이 참조를 통해 바꾸지는 않겠다는 뜻입니다. 여기서 T는 int나 Array<int> 같은 실제 타입을 대신 적은 설명용 자리표시자입니다. 지금 코드에 T라는 이름을 그대로 쓰라는 뜻은 아닙니다. const 참조를 만들었다고 원본 자체가 모든 곳에서 변경 불가능해지는 것은 아닙니다.

## 지금까지 함수 parameter는 어떻게 동작했을까요?
우리는 지금까지 일부러 parameter를 단순하게 **값으로** 받았습니다.

`AddOne(n)`을 호출하면 parameter x에는 n의 값이 복사됩니다. 그래서 함수 안에서 x를 바꾸어도 원래 n은 바뀌지 않습니다.

`n: [10]  → copy →  x: [10]`

이 단순한 규칙 덕분에 앞의 lesson에서는 함수 자체에 집중할 수 있었습니다. 이제 실제 메모리에서 이 차이가 왜 중요한지 열어 봅시다.

## 먼저 실행해 보세요

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

## 같은 값을 함께 사용하려면 reference
원본을 함수에서 바꾸고 싶다면 parameter를 `int& x`처럼 **reference**로 만들 수 있습니다.

이때 새로운 int copy가 생기는 것이 아니라 x를 통해 원래 n을 사용합니다.

`n: [10]  ← x refers to this value`

그래서 x를 바꾸면 n도 바뀝니다.

이제 Array를 생각해 봅시다. Lesson 21의 `Sum(Array<int> numbers)`는 올바른 C++이지만 함수 호출 때 Array 값 전체를 복사합니다. 다섯 개라면 별 문제 없지만 백만 개라면 굳이 복사할 이유가 없습니다.

## 복사하지 않고 읽기

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

## `const T&`는 복사하지 않는 read-only input
`Array<int>&`만 사용하면 원래 Array를 함께 사용하므로 복사는 피할 수 있지만 함수가 원본을 수정할 수도 있습니다. Sum은 읽기만 해야 합니다.

`const Array<int>& numbers`는 두 뜻을 합칩니다.

- `&` — 새로운 Array를 복사하지 않고 원래 값을 사용합니다.
- `const` — 이 reference를 통해서는 값을 바꾸지 않겠다는 약속입니다.

그래서 큰 read-only input에 흔히 쓰입니다.

`T x` = 값을 복사해서 받음  
`T& x` = 원래 값을 함께 사용하며 수정 가능  
`const T& x` = 원래 값을 함께 사용하지만 수정하지 않음

`const int MaxScore = 100;`처럼 const는 값 자체를 변경하지 못하게 하는 데도 쓰입니다. 하지만 여기서는 **함수의 read-only input contract**가 가장 중요한 사용입니다.

이 lesson 이후에는 큰 String과 Array를 읽기만 하는 parameter에 일반적인 C++ style인 `const T&`를 사용합니다.

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


# 기존 34강 — Meet the Standard Library


## 라이브러리는 이미 만들어 둔 도구들의 모음입니다

**라이브러리(library)**는 다른 프로그램에서 사용할 수 있도록 준비한 함수·타입 등의 모음입니다. Small도 Print, Window, String 같은 도구를 제공하는 라이브러리입니다. 우리가 함수 내부를 매번 직접 만들지 않아도 되는 이유입니다.

**C++ 표준 라이브러리**는 표준 C++ 환경이 제공하는 공통 도구 모음입니다. `std::min(8, 3)`은 두 값 중 작은 3을 돌려주고, `std::abs(-12)`는 절댓값 12를 돌려줍니다. 절댓값은 수의 부호를 제외한 크기입니다.

`std::`는 그 이름이 표준 라이브러리의 이름 공간에 속한다는 표시입니다. 별도 언어로 바뀐 것이 아니라, 같은 C++ 함수 호출에서 사용할 도구의 이름이 늘어난 것입니다.

## Small 밖에도 이미 많은 도구가 있습니다
우리는 지금까지 `Print`, `String`, `Array`처럼 Small이 준비한 이름을 사용했습니다. 하지만 C++ 자체의 생태계에는 모든 표준 C++ 환경에서 사용할 수 있는 **Standard Library**가 있습니다.

Small도 C++ 위에 만들어졌기 때문에 그 도구들을 함께 사용할 수 있습니다. 이제부터 Small이 숨겨주던 부분을 하나씩 직접 만나 봅니다.

## 먼저 실행해 보세요

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

## `std::`는 표준 라이브러리의 이름표
`std::min`의 `std::`는 이 이름이 C++ Standard Library의 `std` namespace 안에 있다는 뜻입니다. namespace는 같은 이름들이 서로 충돌하지 않도록 묶어 주는 방법입니다.

Small에서는 beginner mode가 `Small::`을 숨겨주었지만, 표준 라이브러리는 여기서부터 `std::`를 직접 써 봅니다.

표준 라이브러리는 매우 크므로 전부 외우는 것이 목표가 아닙니다. 필요한 기능이 이미 있는지 찾아보고 사용할 수 있다는 사실을 아는 것이 중요합니다.

## 조금 더 C++답게

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

## Small을 버리는 lesson이 아닙니다
지금은 Small과 Standard Library를 같은 프로그램에서 함께 사용합니다. 익숙한 환경을 유지하면서 C++의 실제 이름과 도구를 조금씩 늘려 가는 단계입니다.

다음에는 Small의 `String`과 `Array`에 대응하는 표준 C++ type을 직접 사용해 봅니다.

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


# 기존 35강 — std::string and std::vector


## 컨테이너는 여러 값을 담는 도구입니다

**컨테이너(container)**는 여러 원소를 모아 저장하고 접근하는 도구입니다. 이미 배운 Small Array도 이런 역할을 합니다. 표준 라이브러리의 std::vector는 길이를 늘리거나 줄일 수 있는 컨테이너입니다.

std::string은 문자열 타입이고, std::vector<int>는 int 원소들을 담는 타입입니다. `push_back(15)`는 끝에 15라는 새 원소를 하나 추가합니다. 기존 위치의 값을 바꾸는 대입과 달리 원소 개수도 늘어납니다.

이름만 바꾸면 모든 동작이 같아지는 것은 아닙니다. Small Array의 범위 밖 접근은 오류로 알려 주지만 표준 vector의 []에는 같은 검사를 기대하면 안 됩니다. 반드시 유효한 인덱스를 사용하세요. std::string도 UTF-8 문자열에서는 size가 화면의 글자 수가 아니라 바이트 수입니다.

## 익숙한 개념에 새로운 이름 붙이기
Small의 `String`과 `Array`는 처음 배우기 편하도록 만든 type입니다. 표준 C++에서는 문자열에 `std::string`, 크기가 변하는 연속된 값 모음에 `std::vector`를 많이 사용합니다.

개념은 이미 알고 있습니다. 이름과 몇 가지 member function이 달라질 뿐입니다.

Small의 `String`은 `std::string`으로부터 만들 수 있도록 연결되어 있어서 두 세계를 단계적으로 섞어 쓸 수도 있습니다. 하지만 이 lesson의 목적은 표준 type 자체의 이름과 사용법에 익숙해지는 것입니다.

## 먼저 실행해 보세요

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

## Length()는 size()로
Small에서는 `text.Length()`와 `numbers.Length()`로 길이를 확인했습니다. 표준 `std::string`과 `std::vector`에서는 `size()`를 사용합니다.

여기에는 한 가지 차이도 있습니다. Small의 `Array`는 처음 만들 때 길이나 값들을 정하고, 그 뒤에는 길이를 바꾸는 기능을 일부러 제공하지 않습니다. 반면 `std::vector`는 크기가 변할 수 있는 container라서 `push_back()`으로 끝에 새 값을 추가할 수 있습니다.

문법과 기능의 범위는 조금 달라도 “object에게 member function을 호출한다”는 개념은 이미 class lesson에서 배웠습니다.

Lesson 33 이후이므로 큰 표준 object를 읽기만 하는 함수에는 `const std::vector<int>&` 같은 일반적인 C++ style도 자연스럽게 사용할 수 있습니다.

## 조금 더 C++답게

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

## 새로운 문법보다 이미 아는 개념을 보세요
`std::vector<int>`도 여러 int를 순서대로 저장하고 index로 접근합니다. `std::string`도 여러 문자를 저장합니다. Small에서 배운 loop, search, sorting 아이디어는 그대로 적용됩니다.

예제의 `for (int value : numbers)`는 container의 모든 값을 차례로 보는 C++의 **range-based for**입니다. 기존 index for를 계속 사용해도 됩니다.

## 크기와 타입을 명시적으로 바꾸기

`static_cast<int>(text.size())`는 size가 돌려주는 값을 int로 바꾸겠다는 뜻입니다. 표준 컨테이너의 size는 음수가 없는 크기 타입이므로 int와 다릅니다. 이 장의 작은 데이터는 int로 표현 가능하지만, 아주 큰 크기까지 무조건 변환해도 된다는 뜻은 아닙니다.

숫자를 변환할 때에는 값이 보존되는지 생각하세요. 예를 들어 양수 `3.9`를 int로 바꾸면 3이 되어 소수 부분을 잃습니다. 4장에서 배운 정수 나눗셈도 계산 뒤에 타입만 바꾼다고 소수 부분이 복원되지는 않습니다.

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


# 기존 36강 — #include and Namespaces


## 헤더와 이름 공간은 도구를 찾기 위한 장치입니다

**헤더(header)**는 함수나 타입을 사용하기 위해 컴파일러가 알아야 할 선언 등을 담은 파일입니다. **컴파일러**는 C++ 소스 코드를 검사하고 실행할 프로그램을 만드는 도구입니다. `#include <iostream>`은 표준 입출력에 필요한 헤더 내용을 포함하도록 지시합니다. 실행 중 입력을 받는 명령과는 다릅니다.

**이름 공간(namespace)**은 이름이 충돌하지 않도록 구분하는 묶음입니다. std::cout의 std는 이름 공간이고 cout은 그 안의 이름입니다. include로 사용에 필요한 내용을 알려 주는 것과, std::로 어떤 이름을 말하는지 지정하는 것은 역할이 다릅니다.

**스트림(stream)**은 데이터를 순서대로 주고받는 통로로 생각하면 됩니다. cout은 출력 통로이고 cin은 입력 통로입니다. Small의 Print와 Input을 통해 익힌 출력·입력 개념을 표준 도구의 다른 표기로 다시 만납니다.

## 지금까지 보이지 않던 첫 줄
Small IDE는 `SmallMain()` 프로그램을 compile할 때 `small.h`를 자동으로 포함해 주었습니다. 그래서 처음부터 `#include`를 쓰지 않고 프로그램의 핵심에 집중할 수 있었습니다.

일반 C++에서는 사용하는 library의 header를 source에 직접 적습니다. 이제 `#include <iostream>`과 `#include <string>`을 직접 쓰고, 표준 console 입출력도 만나 봅시다.

## 먼저 실행해 보세요

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

## header, namespace, 그리고 stream
`#include <iostream>`은 표준 console 입출력인 `std::cout`과 `std::cin`을 사용할 수 있게 합니다. `#include <string>`은 `std::string`을 위한 header입니다.

`std::cout`은 **standard output stream**입니다. `<<` 뒤의 값을 왼쪽에서 오른쪽으로 출력 stream에 보냅니다. `"\n"`은 줄바꿈 문자입니다.

`std::cin`은 **standard input stream**입니다. `std::getline(std::cin, name)`은 입력에서 한 줄을 읽어 `name`에 저장합니다.

여기서 `std::`는 Standard Library의 `std` namespace 안의 이름이라는 뜻입니다. stream의 내부 구조나 `<<` 연산자의 구현을 지금 알 필요는 없습니다. Small의 `Print`와 `Input`이 하던 일을 표준 C++에서는 어떤 표면으로 만나는지만 익히면 됩니다.

## 조금 더 C++답게

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

## 이제 마지막으로 entry point를 바꿉니다
이 lesson에서는 `#include`, `std::cout`, `std::cin`, `std::getline`, `std::string`, namespace를 직접 사용했습니다. 아직 프로그램의 시작만 `SmallMain()`이었습니다.

다음 lesson에서는 `SmallMain()`의 비밀을 열고 진짜 C++ entry point인 `main()`을 직접 작성합니다. 그 순간부터 Small도 특별한 내장 기능이 아니라 **명시적으로 include해서 사용하는 C++ library**가 됩니다.

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


# 기존 37강 — The Secret of SmallMain()


## 시작 함수와 실행 준비를 구분합니다

**진입점(entry point)**은 여기서 프로그램 본문을 시작하는 함수 main을 뜻합니다. 지금까지는 Small이 main을 제공하고, 그 안에서 실행 준비를 마친 뒤 우리가 작성한 SmallMain을 호출했습니다. SmallMain은 C++의 새 문법이 아니라 이런 약속에 따라 호출되는 일반 함수입니다.

**런타임(runtime)**은 실행 중 창이나 소리 같은 기능을 지원하는 기반입니다. InitializeSmall은 그 기반을 준비하고 ShutdownSmall은 정리합니다. 직접 main을 쓰면 프로그램의 일뿐 아니라 그 앞뒤의 준비와 정리도 직접 적습니다.

이 장에서는 왜 두 호출이 필요한지와 어떤 순서인지까지만 이해하면 됩니다. 내부 구현이나 객체 정리의 고급 기법까지 배우는 장은 아닙니다.

## `SmallMain()`의 비밀
처음부터 사용한 `SmallMain()`은 C++ 언어의 특별한 문법이 아닙니다. Small runtime이 여러분 대신 진짜 entry point를 준비하고, 필요한 초기화를 한 뒤 `SmallMain()`을 호출해 주었습니다.

개념적으로 그동안 뒤에서는 이런 일이 일어났습니다.

`main() → Small::InitializeSmall(argc, argv) → SmallMain() → Small::ShutdownSmall()`

이제 IDE는 여러분이 직접 top-level `main()`을 작성하면 숨겨진 entry point도, 자동 `small.h` include도, beginner namespace shortcut도 붙이지 않습니다. 따라서 Small을 계속 사용하려면 일반 library처럼 source에서 직접 `#include <small.h>`를 적습니다.

## 먼저 실행해 보세요

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

## InitializeSmall은 Small 기능을 준비합니다
`#include <small.h>`는 compiler에게 Small의 type과 function 선언을 보여줍니다. 그리고 직접 `main()`을 쓸 때 Window, Sound 같은 runtime 기능을 사용하려면 `Small::InitializeSmall()`을 처음에 한 번 호출합니다.

프로그램이 끝나기 전에는 `Small::ShutdownSmall()`을 호출합니다. 이 함수는 오디오와 Small runtime의 기반 자원을 정리합니다. 사용자가 만든 Window 같은 지역 객체는 그 전에 범위를 끝내 정리해야 합니다. `SmallMain()`을 사용할 때는 함수가 끝나 지역 객체가 정리된 뒤 숨겨진 entry point가 Shutdown을 호출했지만, 직접 `main()`을 쓰면 이 순서도 source에 명시합니다.

또 beginner mode가 끝났으므로 `Small::Print`, `Small::Window`, `Small::Black`처럼 `Small::` namespace도 직접 적습니다.

`return 0;`은 프로그램이 정상적으로 끝났다는 값을 운영체제에 돌려주는 전통적인 형태입니다. C++에서는 main 끝의 `return 0;`을 생략할 수도 있지만 여기서는 의미를 보여주기 위해 적습니다.

command-line argument를 사용하는 일반적인 main 형태도 그대로 지원합니다.

## 다음 단계

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

## 창 객체를 먼저 정리합니다

두 번째 예제는 창을 사용하는 부분을 별도의 중괄호로 감쌌습니다. 이 범위가 끝나면 지역 Window 객체가 정리되고, 그 뒤 ShutdownSmall을 호출합니다. 창 닫기와 객체의 수명이 끝나는 것은 같지 않습니다. Small 런타임을 사용하는 지역 객체의 범위를 먼저 끝낸 뒤 런타임을 종료하세요.

명령줄 인자 형태의 `char* argv[]`는 포인터와 배열 표기가 포함된 고급 형태입니다. 지금 외울 필요는 없으며, 명령줄 인자를 다루지 않으면 첫 예제의 `int main()`을 쓰면 충분합니다. 두 번째 연습은 선택 심화입니다.

## 이제 source가 스스로 필요한 것을 말합니다
`SmallMain()` 시절에는 IDE가 `small.h`와 beginner namespace shortcut을 자동으로 준비했습니다. 이제 `main()` 프로그램은 ordinary C++ source처럼 자신이 사용하는 Small library를 직접 include하고 namespace를 명시합니다.

Small IDE에 별도의 “Standard C++ mode” 버튼은 없습니다. top-level `main()`을 작성하는 것 자체가 이 경계를 만듭니다.

Small API를 하나도 사용하지 않는다면 `#include <small.h>`도 `Small::InitializeSmall()`도 필요 없습니다. 마지막 lesson에서 바로 그런 프로그램을 작성합니다.

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


# 기존 38강 — You Already Know C++


## 달라진 표기와 그대로인 개념을 구분하세요

변수는 값을 저장하고, 조건문은 실행할 길을 고르며, 반복문은 일을 되풀이하고, 함수는 이름 붙인 일을 수행합니다. 이런 개념과 문법은 Small 없이도 그대로 C++입니다.

달라진 것은 입출력에 사용하는 도구의 이름과 프로그램 준비를 적는 방식입니다. Print 대신 cout을 사용해도 출력이라는 목적은 같고, Array 대신 vector를 사용해도 원소를 반복해 합산하는 알고리즘은 같습니다. 단, 각 도구의 세부 규칙까지 완전히 같다는 뜻은 아닙니다.

첫 예제를 실행한 뒤, “입력을 받는 부분”, “값을 기억하는 부분”, “출력하는 부분”, “프로그램이 시작하고 끝나는 부분”을 직접 짚어 보세요. 새로운 코드를 볼 때에도 먼저 그 역할을 찾는 습관이 도움이 됩니다.

## 이제 Small 없이도 시작할 수 있습니다
마지막 프로그램에는 새로운 핵심 개념이 없습니다. Lesson 36에서 이미 사용한 `#include <iostream>`, `std::string`, `std::cout`, `std::cin`, `std::getline`을 그대로 사용합니다.

달라지는 것은 딱 하나입니다. Lesson 37에서 배운 진짜 `main()`을 entry point로 사용하고, Small을 전혀 include하지 않습니다.

## 먼저 실행해 보세요

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

## 이미 본 조각들이 하나의 일반 C++ 프로그램이 됩니다
Lesson 36에서는 같은 표준 입출력 코드를 `SmallMain()` 안에서 사용했습니다. 이제 `SmallMain()`이 `main()`으로 바뀌었고 Small이 사라졌을 뿐입니다.

Small의 `Print` 대신 `std::cout`, `Input` 대신 `std::getline`과 `std::cin`, `String` 대신 `std::string`을 사용합니다. 이 이름과 사용법은 앞 lesson에서 이미 만났습니다.

따라서 마지막 프로그램은 갑자기 새로운 C++를 배우는 예제가 아니라, **지금까지 배운 조각만으로 ordinary C++ source가 완성된다는 확인**입니다.

## 다음 단계

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

## 여기서 끝이 아니라 다음 단계의 시작
이제 여러 source file과 header를 사용하는 프로젝트, 더 큰 Standard Library, debugging, 다른 library 사용법을 배울 준비가 되었습니다.

Small IDE는 single-file 프로그램을 빠르게 실험하는 도구로 계속 사용할 수 있습니다. 더 큰 프로그램을 만들고 싶어질 때는 우리가 계획한 **Small Project** 같은 중간 단계나 일반 개발 IDE로 넘어가면 됩니다.

중요한 것은 Small에서 별도의 언어를 배운 것이 아니라는 점입니다. 처음부터 C++의 변수, 함수, loop, object와 memory model을 사용했고, 마지막에 그 주변의 편의를 하나씩 걷어냈습니다.

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
