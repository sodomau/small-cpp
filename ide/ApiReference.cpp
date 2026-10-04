#include "ApiReference.h"

namespace {
ApiEntry E(QString c, QString n, QString u, QString s,
           QVector<ApiParameter> p, QString r, QString x,
           QString note = {}, QString proto = {})
{ return {c,n,u,s,p,r,x,note,proto}; }
ApiParameter P(QString n, QString t, QString m) { return {n,t,m}; }
}

QVector<ApiEntry> ApiReference::core()
{
    QVector<ApiEntry> a;
    auto add=[&](QString c,QString n,QString u,QString s,QVector<ApiParameter> p,
                 QString r,QString x,QString note={},QString proto={})
        { a.append(E(c,n,u,s,p,r,x,note,proto)); };

    add("Console","print","print(values...)","Print values, then move to the next line.",
        {P("values","printable values","One or more values to print.")},"nothing",R"(print("Score: ", score);)");
    add("Console","write","write(values...)","Print values without moving to the next line.",
        {P("values","printable values","One or more values to print.")},"nothing",R"(write("Loading...");)");
    add("Console","format","format(values...)","Combine printable values into text.",
        {P("values","printable values","Values to combine.")},"text",R"(String message = format("Score: ", score);)","Use Small::format when passing std::string to distinguish it from std::format.");
    add("Input","input","input(prompt)","Read one line of text.",{P("prompt","text","Text shown before input. Optional.")},
        "the text entered by the user",R"(String name = input("Name: ");)");
    add("Input","input_int","input_int(prompt)","Read an integer.",{P("prompt","text","Text shown before input. Optional.")},
        "the integer entered by the user",R"(int age = input_int("Age: ");)");
    add("Input","input_real","input_real(prompt)","Read a real number.",{P("prompt","text","Text shown before input. Optional.")},
        "the number entered by the user",R"(double speed = input_real("Speed: ");)");
    add("Random","random_int","random_int(min, max)","Choose a random integer.",
        {P("min","integer","Smallest possible value."),P("max","integer","Largest possible value.")},
        "a random integer from min through max","int dice = random_int(1, 6);","Both endpoints are included.");
    add("Random","random_real","random_real(min, max)","Choose a random real number.",
        {P("min","real number","Smallest possible value."),P("max","real number","Upper limit.")},
        "a random real number from min up to max","double x = random_real(0.0, 1.0);","min is included; max is excluded.");
    add("Time","sleep","sleep(seconds)","Pause the current program.",{P("seconds","real number","How long to wait.")},
        "nothing","sleep(0.5);");
    add("Time","StopWatch","StopWatch watch","Create a stopwatch that starts immediately.",{},"a stopwatch object",
        "StopWatch watch;","Use watch.elapsed() and watch.reset().");
    add("Time","StopWatch.elapsed","StopWatch.elapsed()","Check how much time has passed.",{},"elapsed time in seconds","double dt = watch.elapsed();");
    add("Time","StopWatch.reset","StopWatch.reset()","Restart elapsed-time measurement from zero.",{},"nothing","watch.reset();");
    add("Time","Timer","Timer timer","Create a repeating timer.",{},"a timer object","Timer timer;","Use start, stop, and is_running.");
    add("Time","Timer.start","Timer.start(interval, function)","Start calling a function repeatedly.",
        {P("interval","real number","Seconds between calls."),P("function","function","No parameters and no return value.")},"nothing","timer.start(1.0, tick);");
    add("Time","Timer.stop","Timer.stop()","Stop a running timer.",{},"nothing","timer.stop();");
    add("Time","Timer.is_running","Timer.is_running()","Check whether a timer is running.",{},"true or false","if (timer.is_running()) print(\"Running\");");
    add("String","String","String text","Store and work with text.",{},"a text value",R"(String name = "Alice";)",
        "Use + to join strings and [index] to access a character.");
    add("String","String.length","String.length()","Get the number of characters.",{},"the text length","int n = text.length();");
    add("String","String.substring","String.substring(start, length)","Take part of a string.",
        {P("start","integer","Index of first character."),P("length","integer","Number of characters. Optional.")},"new text",
        "String first = text.substring(0, 3);");
    add("Array","Array","Array<T> values","Store a fixed-length sequence of values.",{},"an array","Array<int> scores = {10, 20, 30};",
        "Use values[index] to access an element.");
    add("Array","Array.length","Array.length()","Get the number of elements.",{},"the array length","int n = scores.length();");
    add("File","File.open","File.open(filename, mode)","Open a file.",
        {P("filename","text","File to open."),P("mode","FileMode","Read, write, Append, ReadBinary, or WriteBinary. Optional.")},
        "nothing",R"(file.open("notes.txt");)","Read is the default mode.");
    add("File","File.close","File.close()","Close the file.",{},"nothing","file.close();");
    add("File","File.is_open","File.is_open()","Check whether the file is open.",{},"true or false","if (file.is_open()) print(\"open\");");
    add("File","File.end","File.end()","Check whether reading reached the end.",{},"true or false","while (!file.end()) print(file.input());");
    add("File","File.input","File.input()","Read one line of text from a text file.",{},"text","String line = file.input();");
    add("File","File.input_int","File.input_int()","Read an integer from a text file.",{},"an integer","int value = file.input_int();");
    add("File","File.input_real","File.input_real()","Read a real number from a text file.",{},"a real number","double value = file.input_real();");
    add("File","File.write","File.write(values...)","Write printable values without a newline.",
        {P("values","printable values","Values to write.")},"nothing",R"(file.write("Score: ", score);)");
    add("File","File.print","File.print(values...)","Write printable values, then a newline.",
        {P("values","printable values","Values to write.")},"nothing",R"(file.print("Score: ", score);)");
    add("File","File.read_int","File.read_int()","Read a native binary integer.",{},"an integer","int score = file.read_int();");
    add("File","File.read_real","File.read_real()","Read a native binary real number.",{},"a real number","double time = file.read_real();");
    add("File","File.write_int","File.write_int(value)","Write a native binary integer.",
        {P("value","integer","value to store.")},"nothing","file.write_int(score);");
    add("File","File.write_real","File.write_real(value)","Write a native binary real number.",
        {P("value","real number","value to store.")},"nothing","file.write_real(time);");
    add("Color","rgb","rgb(red, green, blue)","Make a color.",
        {P("red","integer","0 to 255."),P("green","integer","0 to 255."),P("blue","integer","0 to 255.")},
        "a Color","Color orange = rgb(255, 128, 0);","Named colors: Black, White, Red, Green, Blue, Yellow, Cyan, Magenta, Gray.");
    add("Window","Window","Window window","Create a graphics window object.",{},"a window object","Window window;","Call open before drawing.");
    add("Window","Window.open","Window.open(width, height)","Open the graphics window.",
        {P("width","integer","width in pixels."),P("height","integer","height in pixels.")},"nothing","window.open(800, 600);");
    add("Window","Window.set_title","Window.set_title(title)","Change the window title.",{P("title","text or printable values","New title.")},
        "nothing",R"(window.set_title("My Game");)");
    add("Window","Window.title","Window.title()","Get the window title.",{},"text","print(window.title());");
    add("Window","Window.close","Window.close()","Close the window.",{},"nothing","window.close();");
    add("Window","Window.is_open","Window.is_open()","Check whether the window is open.",{},"true or false","while (window.is_open()) { }");
    add("Window","Window.width","Window.width()","Get the drawing width.",{},"width in pixels","int w = window.width();");
    add("Window","Window.height","Window.height()","Get the drawing height.",{},"height in pixels","int h = window.height();");
    add("Drawing","Window.clear","Window.clear(color)","Fill the whole window with a color.",{P("color","Color","Background color.")},"nothing","window.clear(Black);");
    add("Drawing","Window.set_pixel","Window.set_pixel(x, y, color)","Set one pixel.",
        {P("x, y","integer","pixel position."),P("color","Color","pixel color.")},"nothing","window.set_pixel(10, 20, Red);");
    add("Drawing","Window.draw_line","Window.draw_line(x1, y1, x2, y2, color)","Draw a line.",
        {P("x1, y1","number","start."),P("x2, y2","number","end."),P("color","Color","Line color.")},"nothing","window.draw_line(10, 10, 200, 100, White);");
    add("Drawing","Window.draw_rectangle","Window.draw_rectangle(x, y, width, height, color)","Draw a rectangle outline.",
        {P("x, y","number","Top-left."),P("width, height","number","Size."),P("color","Color","Outline color.")},"nothing","window.draw_rectangle(20, 20, 100, 60, White);");
    add("Drawing","Window.fill_rectangle","Window.fill_rectangle(x, y, width, height, color)","Draw a filled rectangle.",
        {P("x, y","number","Top-left."),P("width, height","number","Size."),P("color","Color","Fill color.")},"nothing","window.fill_rectangle(20, 20, 100, 60, Blue);");
    add("Drawing","Window.draw_circle","Window.draw_circle(x, y, radius, color)","Draw a circle outline.",
        {P("x, y","number","Center."),P("radius","number","Radius."),P("color","Color","Outline color.")},"nothing","window.draw_circle(400, 300, 30, White);");
    add("Drawing","Window.fill_circle","Window.fill_circle(x, y, radius, color)","Draw a filled circle.",
        {P("x, y","number","Center."),P("radius","number","Radius."),P("color","Color","Fill color.")},"nothing","window.fill_circle(400, 300, 30, Yellow);");
    add("Drawing","Window.draw_text","Window.draw_text(x, y, text, color, size)","Draw text.",
        {P("x, y","number","Position."),P("text","text","Text to draw."),P("color","Color","Optional."),P("size","integer","Optional.")},
        "nothing",R"(window.draw_text(20, 30, "Hello", White, 24);)");
    add("Drawing","Window.show","Window.show()","Show the frame you have drawn.",{},"nothing","window.show();");
    add("Keyboard","Window.key_down","Window.key_down(key)","Check whether a key is held down.",{P("key","Key or character","Key to check.")},
        "true or false","if (window.key_down(Key::Left)) x -= 5;");
    add("Keyboard","Window.key_pressed","Window.key_pressed(key)","Check whether a key was just pressed.",{P("key","Key or character","Key to check.")},
        "true or false","if (window.key_pressed(Key::Space)) Jump();");
    add("Keyboard","Window.key_released","Window.key_released(key)","Check whether a key was just released.",{P("key","Key or character","Key to check.")},
        "true or false","if (window.key_released(Key::Space)) print(\"Released\");");
    add("Mouse","Window.mouse_x","Window.mouse_x()","Get the mouse x position.",{},"x position in pixels","int x = window.mouse_x();");
    add("Mouse","Window.mouse_y","Window.mouse_y()","Get the mouse y position.",{},"y position in pixels","int y = window.mouse_y();");
    add("Mouse","Window.mouse_down","Window.mouse_down(button)","Check whether a mouse button is held down.",{P("button","MouseButton","Left, Right, or Middle.")},
        "true or false","if (window.mouse_down(MouseButton::Left)) { }");
    add("Mouse","Window.mouse_pressed","Window.mouse_pressed(button)","Check whether a mouse button was just pressed.",{P("button","MouseButton","Left, Right, or Middle.")},
        "true or false","if (window.mouse_pressed(MouseButton::Left)) print(\"Click\");");
    add("Mouse","Window.mouse_released","Window.mouse_released(button)","Check whether a mouse button was just released.",{P("button","MouseButton","Left, Right, or Middle.")},
        "true or false","if (window.mouse_released(MouseButton::Left)) print(\"Released\");");
    add("Sound","play_sound","play_sound(sound)","Play a built-in sound without waiting.",{P("sound","Sound","Click, Pop, Jump, Hit, Coin, Shoot, Explosion, Win, or Lose.")},
        "nothing","play_sound(Sound::Coin);");
    add("Sound","play_sound_and_wait","play_sound_and_wait(sound)","Play a built-in sound and wait.",{P("sound","Sound","Built-in sound.")},
        "nothing","play_sound_and_wait(Sound::Win);");
    add("Sound","beep","beep(frequency, seconds)","Play a tone without waiting.",{P("frequency","number","Hz."),P("seconds","real number","Duration.")},
        "nothing","beep(440, 0.2);");
    add("Sound","beep_and_wait","beep_and_wait(frequency, seconds)","Play a tone and wait.",{P("frequency","number","Hz."),P("seconds","real number","Duration.")},
        "nothing","beep_and_wait(440, 0.2);");
    return a;
}

QVector<ApiEntry> ApiReference::image()
{
    QVector<ApiEntry> a;
    auto add=[&](QString n,QString u,QString s,QVector<ApiParameter> p,QString r,QString x,QString note={})
        { a.append(E("Extension — Image",n,u,s,p,r,x,note)); };
    add("Image","Image image(width, height, fill)","Create an image in memory.",
        {P("width, height","integer","Size in pixels."),P("fill","Color","Starting color. Optional.")},
        "an Image","Image image(320, 240, Black);","fill is Black when omitted.");
    add("Image.width","Image.width()","Get the image width.",{},"width in pixels","int w = image.width();");
    add("Image.height","Image.height()","Get the image height.",{},"height in pixels","int h = image.height();");
    add("Image.pixel","Image.pixel(x, y)","Read a pixel color.",{P("x, y","integer","pixel position.")},"a Color","Color c = image.pixel(10, 20);");
    add("Image.alpha","Image.alpha(x, y)","Read a pixel's transparency.",{P("x, y","integer","pixel position.")},"an integer from 0 to 255","int a = image.alpha(10, 20);");
    add("Image.set_pixel","Image.set_pixel(x, y, color, alpha)","Change a pixel.",
        {P("x, y","integer","pixel position."),P("color","Color","New color."),P("alpha","integer","0 to 255. Optional.")},
        "nothing","image.set_pixel(10, 20, Red);");
    add("load_image","load_image(filename)","Load an image from a file.",{P("filename","text","Image file to load.")},
        "an Image",R"(Image image = load_image("photo.png");)");
    add("save_image","save_image(image, filename)","Save an image to a file.",
        {P("image","Image","Image to save."),P("filename","text","Destination file.")},"nothing",R"(save_image(image, "result.png");)");
    add("draw_image","draw_image(window, image, x, y, width, height)","Draw an image in a window.",
        {P("window","Window","Destination."),P("image","Image","Image to draw."),P("x, y","number","Top-left position."),P("width, height","number","Optional drawing size.")},
        "nothing","draw_image(window, image, 100, 100);","Omit width and height to use the image's original size.");
    return a;
}
