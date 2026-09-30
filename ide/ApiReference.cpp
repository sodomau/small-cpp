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

    add("Console","Print","Print(values...)","Print values, then move to the next line.",
        {P("values","printable values","One or more values to print.")},"nothing",R"(Print("Score: ", score);)");
    add("Console","Write","Write(values...)","Print values without moving to the next line.",
        {P("values","printable values","One or more values to print.")},"nothing",R"(Write("Loading...");)");
    add("Console","Format","Format(values...)","Combine printable values into text.",
        {P("values","printable values","Values to combine.")},"text",R"(String message = Format("Score: ", score);)");
    add("Input","Input","Input(prompt)","Read one line of text.",{P("prompt","text","Text shown before input. Optional.")},
        "the text entered by the user",R"(String name = Input("Name: ");)");
    add("Input","InputInt","InputInt(prompt)","Read an integer.",{P("prompt","text","Text shown before input. Optional.")},
        "the integer entered by the user",R"(int age = InputInt("Age: ");)");
    add("Input","InputReal","InputReal(prompt)","Read a real number.",{P("prompt","text","Text shown before input. Optional.")},
        "the number entered by the user",R"(double speed = InputReal("Speed: ");)");
    add("Random","RandomInt","RandomInt(min, max)","Choose a random integer.",
        {P("min","integer","Smallest possible value."),P("max","integer","Largest possible value.")},
        "a random integer from min through max","int dice = RandomInt(1, 6);","Both endpoints are included.");
    add("Random","RandomReal","RandomReal(min, max)","Choose a random real number.",
        {P("min","real number","Smallest possible value."),P("max","real number","Upper limit.")},
        "a random real number from min up to max","double x = RandomReal(0.0, 1.0);","min is included; max is excluded.");
    add("Time","Sleep","Sleep(seconds)","Pause the current program.",{P("seconds","real number","How long to wait.")},
        "nothing","Sleep(0.5);");
    add("Time","StopWatch","StopWatch watch","Create a stopwatch that starts immediately.",{},"a stopwatch object",
        "StopWatch watch;","Use watch.Elapsed() and watch.Reset().");
    add("Time","StopWatch.Elapsed","StopWatch.Elapsed()","Check how much time has passed.",{},"elapsed time in seconds","double dt = watch.Elapsed();");
    add("Time","StopWatch.Reset","StopWatch.Reset()","Restart elapsed-time measurement from zero.",{},"nothing","watch.Reset();");
    add("Time","Timer","Timer timer","Create a repeating timer.",{},"a timer object","Timer timer;","Use Start, Stop, and IsRunning.");
    add("Time","Timer.Start","Timer.Start(interval, function)","Start calling a function repeatedly.",
        {P("interval","real number","Seconds between calls."),P("function","function","No parameters and no return value.")},"nothing","timer.Start(1.0, Tick);");
    add("Time","Timer.Stop","Timer.Stop()","Stop a running timer.",{},"nothing","timer.Stop();");
    add("Time","Timer.IsRunning","Timer.IsRunning()","Check whether a timer is running.",{},"true or false","if (timer.IsRunning()) Print(\"Running\");");
    add("String","String","String text","Store and work with text.",{},"a text value",R"(String name = "Alice";)",
        "Use + to join strings and [index] to access a character.");
    add("String","String.Length","String.Length()","Get the number of characters.",{},"the text length","int n = text.Length();");
    add("String","String.Substring","String.Substring(start, length)","Take part of a string.",
        {P("start","integer","Index of first character."),P("length","integer","Number of characters. Optional.")},"new text",
        "String first = text.Substring(0, 3);");
    add("Array","Array","Array<T> values","Store a fixed-length sequence of values.",{},"an array","Array<int> scores = {10, 20, 30};",
        "Use values[index] to access an element.");
    add("Array","Array.Length","Array.Length()","Get the number of elements.",{},"the array length","int n = scores.Length();");
    add("File","File.Open","File.Open(filename, mode)","Open a file.",
        {P("filename","text","File to open."),P("mode","FileMode","Read, Write, Append, ReadBinary, or WriteBinary. Optional.")},
        "nothing",R"(file.Open("notes.txt");)","Read is the default mode.");
    add("File","File.Close","File.Close()","Close the file.",{},"nothing","file.Close();");
    add("File","File.IsOpen","File.IsOpen()","Check whether the file is open.",{},"true or false","if (file.IsOpen()) Print(\"Open\");");
    add("File","File.End","File.End()","Check whether reading reached the end.",{},"true or false","while (!file.End()) Print(file.Input());");
    add("File","File.Input","File.Input()","Read one line of text from a text file.",{},"text","String line = file.Input();");
    add("File","File.InputInt","File.InputInt()","Read an integer from a text file.",{},"an integer","int value = file.InputInt();");
    add("File","File.InputReal","File.InputReal()","Read a real number from a text file.",{},"a real number","double value = file.InputReal();");
    add("File","File.Write","File.Write(values...)","Write printable values without a newline.",
        {P("values","printable values","Values to write.")},"nothing",R"(file.Write("Score: ", score);)");
    add("File","File.Print","File.Print(values...)","Write printable values, then a newline.",
        {P("values","printable values","Values to write.")},"nothing",R"(file.Print("Score: ", score);)");
    add("File","File.ReadInt","File.ReadInt()","Read a native binary integer.",{},"an integer","int score = file.ReadInt();");
    add("File","File.ReadReal","File.ReadReal()","Read a native binary real number.",{},"a real number","double time = file.ReadReal();");
    add("File","File.WriteInt","File.WriteInt(value)","Write a native binary integer.",
        {P("value","integer","Value to store.")},"nothing","file.WriteInt(score);");
    add("File","File.WriteReal","File.WriteReal(value)","Write a native binary real number.",
        {P("value","real number","Value to store.")},"nothing","file.WriteReal(time);");
    add("Color","RGB","RGB(red, green, blue)","Make a color.",
        {P("red","integer","0 to 255."),P("green","integer","0 to 255."),P("blue","integer","0 to 255.")},
        "a Color","Color orange = RGB(255, 128, 0);","Named colors: Black, White, Red, Green, Blue, Yellow, Cyan, Magenta, Gray.");
    add("Window","Window","Window window","Create a graphics window object.",{},"a window object","Window window;","Call Open before drawing.");
    add("Window","Window.Open","Window.Open(width, height)","Open the graphics window.",
        {P("width","integer","Width in pixels."),P("height","integer","Height in pixels.")},"nothing","window.Open(800, 600);");
    add("Window","Window.SetTitle","Window.SetTitle(title)","Change the window title.",{P("title","text or printable values","New title.")},
        "nothing",R"(window.SetTitle("My Game");)");
    add("Window","Window.Title","Window.Title()","Get the window title.",{},"text","Print(window.Title());");
    add("Window","Window.Close","Window.Close()","Close the window.",{},"nothing","window.Close();");
    add("Window","Window.IsOpen","Window.IsOpen()","Check whether the window is open.",{},"true or false","while (window.IsOpen()) { }");
    add("Window","Window.Width","Window.Width()","Get the drawing width.",{},"width in pixels","int w = window.Width();");
    add("Window","Window.Height","Window.Height()","Get the drawing height.",{},"height in pixels","int h = window.Height();");
    add("Drawing","Window.Clear","Window.Clear(color)","Fill the whole window with a color.",{P("color","Color","Background color.")},"nothing","window.Clear(Black);");
    add("Drawing","Window.SetPixel","Window.SetPixel(x, y, color)","Set one pixel.",
        {P("x, y","integer","Pixel position."),P("color","Color","Pixel color.")},"nothing","window.SetPixel(10, 20, Red);");
    add("Drawing","Window.DrawLine","Window.DrawLine(x1, y1, x2, y2, color)","Draw a line.",
        {P("x1, y1","number","Start."),P("x2, y2","number","End."),P("color","Color","Line color.")},"nothing","window.DrawLine(10, 10, 200, 100, White);");
    add("Drawing","Window.DrawRectangle","Window.DrawRectangle(x, y, width, height, color)","Draw a rectangle outline.",
        {P("x, y","number","Top-left."),P("width, height","number","Size."),P("color","Color","Outline color.")},"nothing","window.DrawRectangle(20, 20, 100, 60, White);");
    add("Drawing","Window.FillRectangle","Window.FillRectangle(x, y, width, height, color)","Draw a filled rectangle.",
        {P("x, y","number","Top-left."),P("width, height","number","Size."),P("color","Color","Fill color.")},"nothing","window.FillRectangle(20, 20, 100, 60, Blue);");
    add("Drawing","Window.DrawCircle","Window.DrawCircle(x, y, radius, color)","Draw a circle outline.",
        {P("x, y","number","Center."),P("radius","number","Radius."),P("color","Color","Outline color.")},"nothing","window.DrawCircle(400, 300, 30, White);");
    add("Drawing","Window.FillCircle","Window.FillCircle(x, y, radius, color)","Draw a filled circle.",
        {P("x, y","number","Center."),P("radius","number","Radius."),P("color","Color","Fill color.")},"nothing","window.FillCircle(400, 300, 30, Yellow);");
    add("Drawing","Window.DrawText","Window.DrawText(x, y, text, color, size)","Draw text.",
        {P("x, y","number","Position."),P("text","text","Text to draw."),P("color","Color","Optional."),P("size","integer","Optional.")},
        "nothing",R"(window.DrawText(20, 30, "Hello", White, 24);)");
    add("Drawing","Window.Show","Window.Show()","Show the frame you have drawn.",{},"nothing","window.Show();");
    add("Keyboard","Window.KeyDown","Window.KeyDown(key)","Check whether a key is held down.",{P("key","Key or character","Key to check.")},
        "true or false","if (window.KeyDown(Key::Left)) x -= 5;");
    add("Keyboard","Window.KeyPressed","Window.KeyPressed(key)","Check whether a key was just pressed.",{P("key","Key or character","Key to check.")},
        "true or false","if (window.KeyPressed(Key::Space)) Jump();");
    add("Keyboard","Window.KeyReleased","Window.KeyReleased(key)","Check whether a key was just released.",{P("key","Key or character","Key to check.")},
        "true or false","if (window.KeyReleased(Key::Space)) Print(\"Released\");");
    add("Mouse","Window.MouseX","Window.MouseX()","Get the mouse x position.",{},"x position in pixels","int x = window.MouseX();");
    add("Mouse","Window.MouseY","Window.MouseY()","Get the mouse y position.",{},"y position in pixels","int y = window.MouseY();");
    add("Mouse","Window.MouseDown","Window.MouseDown(button)","Check whether a mouse button is held down.",{P("button","MouseButton","Left, Right, or Middle.")},
        "true or false","if (window.MouseDown(MouseButton::Left)) { }");
    add("Mouse","Window.MousePressed","Window.MousePressed(button)","Check whether a mouse button was just pressed.",{P("button","MouseButton","Left, Right, or Middle.")},
        "true or false","if (window.MousePressed(MouseButton::Left)) Print(\"Click\");");
    add("Mouse","Window.MouseReleased","Window.MouseReleased(button)","Check whether a mouse button was just released.",{P("button","MouseButton","Left, Right, or Middle.")},
        "true or false","if (window.MouseReleased(MouseButton::Left)) Print(\"Released\");");
    add("Sound","PlaySound","PlaySound(sound)","Play a built-in sound without waiting.",{P("sound","Sound","Click, Pop, Jump, Hit, Coin, Shoot, Explosion, Win, or Lose.")},
        "nothing","PlaySound(Sound::Coin);");
    add("Sound","PlaySoundAndWait","PlaySoundAndWait(sound)","Play a built-in sound and wait.",{P("sound","Sound","Built-in sound.")},
        "nothing","PlaySoundAndWait(Sound::Win);");
    add("Sound","Beep","Beep(frequency, seconds)","Play a tone without waiting.",{P("frequency","number","Hz."),P("seconds","real number","Duration.")},
        "nothing","Beep(440, 0.2);");
    add("Sound","BeepAndWait","BeepAndWait(frequency, seconds)","Play a tone and wait.",{P("frequency","number","Hz."),P("seconds","real number","Duration.")},
        "nothing","BeepAndWait(440, 0.2);");
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
    add("Image.Width","Image.Width()","Get the image width.",{},"width in pixels","int w = image.Width();");
    add("Image.Height","Image.Height()","Get the image height.",{},"height in pixels","int h = image.Height();");
    add("Image.Pixel","Image.Pixel(x, y)","Read a pixel color.",{P("x, y","integer","Pixel position.")},"a Color","Color c = image.Pixel(10, 20);");
    add("Image.Alpha","Image.Alpha(x, y)","Read a pixel's transparency.",{P("x, y","integer","Pixel position.")},"an integer from 0 to 255","int a = image.Alpha(10, 20);");
    add("Image.SetPixel","Image.SetPixel(x, y, color, alpha)","Change a pixel.",
        {P("x, y","integer","Pixel position."),P("color","Color","New color."),P("alpha","integer","0 to 255. Optional.")},
        "nothing","image.SetPixel(10, 20, Red);");
    add("LoadImage","LoadImage(filename)","Load an image from a file.",{P("filename","text","Image file to load.")},
        "an Image",R"(Image image = LoadImage("photo.png");)");
    add("SaveImage","SaveImage(image, filename)","Save an image to a file.",
        {P("image","Image","Image to save."),P("filename","text","Destination file.")},"nothing",R"(SaveImage(image, "result.png");)");
    add("DrawImage","DrawImage(window, image, x, y, width, height)","Draw an image in a window.",
        {P("window","Window","Destination."),P("image","Image","Image to draw."),P("x, y","number","Top-left position."),P("width, height","number","Optional drawing size.")},
        "nothing","DrawImage(window, image, 100, 100);","Omit width and height to use the image's original size.");
    return a;
}
