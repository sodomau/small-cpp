---
title: Share with Friends
part: sharing
part-title: Small Steps VII — Share Your Program
goal: Test and share the whole program folder as a ZIP.
related-example: reference/console
---

## Make a small greeting card

@code example.cpp

Save this as MyCard.cpp. Try it, then publish it to a new folder. Or use a program you finished in an earlier lesson.

## Check before sending

Open the published folder and double-click MyCard.exe. Check the result. If your program uses extra files, check those too. Keep all the files and folders Publish created together, including the DLLs, source, relink, and licenses folders. You do not need to open or edit them to share the program.

**Send the whole folder, not just the exe.** The other files help the program run and include its source and license information. Only include pictures, sounds, and other materials you have permission to share.

![Open Folder takes you to your finished program.](ready.png)

## Make a ZIP

1. Close the running program.
2. In File Explorer, go to the parent of the published folder.
3. Right-click the whole folder and choose **Compress to ZIP file**. On older Windows versions, use **Send to → Compressed (zipped) folder**.
4. Send the ZIP to your friend using your usual file-sharing method. Some services block executable files, even inside ZIPs; use a method your school or family allows.

Your friend should save the ZIP, choose **Extract All…**, open the extracted folder, and double-click the exe. Do not run it from inside the ZIP. This package is for Windows x64, not a phone or a Mac. Your friend does not need Small C++ installed.

## Exercise — Test what your friend receives

Personalize the card below and publish it. Make a ZIP, extract it to a different folder, and run the exe from that extracted copy. If possible, also try it on another Windows x64 computer. Check the name, message, and any extra files before sending it.

@exercise exercise_starter.cpp

### Hint

Change the strings in Print. Keep Input so the card stays visible. The code below is one possible card; the important check is running the complete extracted package.

@solution exercise_solution.cpp
