#include "small.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <type_traits>

using namespace Small;

namespace
{
int checks = 0;
std::ostringstream captured;
void Check(bool condition, const char* expression, int line)
{
    ++checks;
    if (!condition)
    {
        std::cerr << "FAIL at line " << line << ": " << expression << '\n';
        std::exit(1);
    }
}
#define CHECK(expression) Check(bool(expression), #expression, __LINE__)
template<class E, class F> bool Throws(F function)
{
    try { function(); } catch (const E&) { return true; } catch (...) { return false; }
    return false;
}
}
namespace Small::small_detail
{
std::ostream& Console() { return captured; }
}

int main()
{
    String empty;
    CHECK(empty.Length() == 0);
    String s = "Hello, world!";
    CHECK(s.Length() == 13);
    CHECK(s[0] == 'H');
    CHECK(s.Substring(0, 5) == String("Hello"));
    CHECK(s.Substring(7) == String("world!"));
    CHECK(s.Substring(13) == empty);
    CHECK(s.Substring(13, 0) == empty);
    CHECK(s.Substring(0, 0) == empty);
    CHECK(Throws<std::out_of_range>([&] { s.Substring(-1); }));
    CHECK(Throws<std::out_of_range>([&] { s.Substring(14); }));
    CHECK(Throws<std::out_of_range>([&] { s.Substring(0, -1); }));
    CHECK(Throws<std::out_of_range>([&] { s.Substring(2, std::numeric_limits<int>::max()); }));
    CHECK(Throws<std::out_of_range>([&] { s[-1]; }));
    CHECK(Throws<std::out_of_range>([&] { s[13]; }));
    String copied = s;
    copied[0] = 'h';
    CHECK(s[0] == 'H');
    CHECK(copied[0] == 'h');
    copied = "new";
    CHECK(copied.Length() == 3);
    CHECK(s.Length() == 13);
    CHECK(s + "!" == String("Hello, world!!"));
    CHECK("say " + s == String("say Hello, world!"));
    String self = "ab";
    self += self;
    CHECK(self == String("abab"));
    CHECK(String("Alice") < String("Bob"));
    CHECK(String("Alice") <= String("Alice"));
    CHECK(String("Bob") > String("Alice"));
    CHECK(String("Bob") >= String("Bob"));
    CHECK(String("Alice") != String("Bob"));
    CHECK("Alice" < String("Bob"));
    CHECK("Alice" <= String("Alice"));
    CHECK("Bob" > String("Alice"));
    CHECK("Bob" >= String("Bob"));
    CHECK("Alice" == String("Alice"));
    const char withZero[] = {'a', '\0', 'b'};
    String binary(withZero, 3);
    CHECK(binary.Length() == 3);
    CHECK(binary.Substring(1, 2).Length() == 2);
    std::ostringstream binaryOutput;
    binaryOutput << binary;
    CHECK(binaryOutput.str().size() == 3);
    CHECK(Throws<std::invalid_argument>([] { String bad(nullptr); }));

    // Small accepts ordinary std::string without introducing an implicit
    // conversion in the opposite direction. Embedded zero bytes are kept.
    static_assert(std::is_convertible_v<std::string, String>);
    static_assert(!std::is_convertible_v<String, std::string>);
    std::string native = "Native title";
    String fromNative = native;
    CHECK(fromNative == "Native title");
    native[0] = 'n';
    CHECK(fromNative[0] == 'N');
    fromNative = native;
    CHECK(fromNative[0] == 'n');
    const std::string nativeZero("A\0B", 3);
    String zeroCopy = nativeZero;
    CHECK(zeroCopy.Length() == 3);
    CHECK(zeroCopy[1] == '\0');
    CHECK(zeroCopy[2] == 'B');
    CHECK(Format("Name: ", native) == "Name: native title");
    CHECK(Format(zeroCopy).Length() == 3);
    const auto acceptsSmallString = [](const String& text) { return text.Length(); };
    CHECK(acceptsSmallString(native) == 12);

    Array<int> a(10);
    CHECK(a.Length() == 10);
    CHECK(a[0] == 0);
    Array<int> b = {10, 20, 30};
    a = b;
    CHECK(a.Length() == 3);
    a[0] = 7;
    CHECK(b[0] == 10);
    a = a;
    CHECK(a[0] == 7);
    Array<int> c = a;
    c[1] = 90;
    CHECK(a[1] == 20);
    auto mutate = [](Array<int> values) { values[0] = 999; return values; };
    Array<int> changed = mutate(a);
    CHECK(a[0] == 7);
    CHECK(changed[0] == 999);
    CHECK(Throws<std::out_of_range>([&] { a[3]; }));
    CHECK(Throws<std::out_of_range>([&] { a[-1]; }));
    CHECK(Throws<std::invalid_argument>([] { Array<int> bad(-10); }));
    a = {};
    CHECK(a.Length() == 0);
    Array<bool> flags(3);
    static_assert(std::is_same_v<decltype(flags[0]), bool&>);
    flags[1] = true;
    const Array<bool> flagCopy = flags;
    CHECK(flagCopy[1]);
    CHECK(!flagCopy[0]);
    Array<String> names = {"Charlie", "Alice", "Bob"};
    for (int i = 0; i < names.Length(); ++i)
        for (int j = i + 1; j < names.Length(); ++j)
            if (names[j] < names[i])
            {
                String temp = names[i]; names[i] = names[j]; names[j] = temp;
            }
    CHECK(names[0] == String("Alice"));
    CHECK(names[2] == String("Charlie"));
    Array<Array<int>> nested(1);
    nested[0] = {1, 2};
    Array<Array<int>> nestedCopy = nested;
    nestedCopy[0][1] = 5;
    CHECK(nested[0][1] == 2);
    Write();
    Write("x=", 3);
    Print(" ", s);
    Print();
    CHECK(captured.str() == "x=3 Hello, world!\n\n");
    StopWatch timer;
    CHECK(timer.Elapsed() >= 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    CHECK(timer.Elapsed() > 0);
    timer.Reset();
    CHECK(timer.Elapsed() >= 0);
    std::cout << checks << " public API checks passed\n";
}
