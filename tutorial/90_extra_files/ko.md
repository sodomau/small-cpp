---
title: 추가 파일 함께 넣기
part: sharing
part-title: 작은 걸음 VII — 프로그램 공유하기
goal: 데이터 파일을 프로그램과 함께 배포하세요.
related-example: reference/console
---

## 프로그램이 읽는 파일

코드에서 파일 이름으로 불러오는 그림, 소리, 데이터는 별도의 파일입니다. Publish는 필요한 파일을 추측하지 않으므로 직접 골라 주세요.

@code example.cpp

일반 텍스트 파일 **message.txt**를 만들고 Hello from a file!을 한 줄 적으세요. 저장한 MyMessage.cpp 옆에 두고 프로그램을 실행하세요. 텍스트 파일을 만드는 방법이 필요하면 작은 걸음 IV의 텍스트 파일 수업을 참고하세요. 이름이 message.txt.txt가 아닌 message.txt인지 확인하세요.

## 배포본에 파일 넣기

1. **File → Publish…**를 선택하고 새 대상 폴더를 정하세요.
2. **Extra Files — Optional**에서 **Add Files…**를 누르고 message.txt를 고르세요.
3. 목록을 확인하세요. 잘못 고른 파일은 **Remove**로 빼세요. **Add Files…**를 다시 눌러 더 추가할 수도 있습니다.
4. **Publish**, **Open Folder**를 차례로 누르세요. 폴더에 MyMessage.exe와 message.txt가 함께 있어야 합니다.
5. MyMessage.exe를 더블 클릭해서 파일에 적은 문장이 나오는지 확인하세요.

선택한 파일은 exe 옆에 복사됩니다. picture.png, music.wav처럼 간단한 영어 파일 이름을 쓰고 코드의 이름과 정확히 맞추세요. 현재는 같은 폴더에 놓는 파일을 지원하므로 하위 폴더 경로를 사용하지 마세요. 이름이 같은 파일 두 개를 동시에 넣을 수는 없습니다.

![Add Files로 message.txt를 실행 파일 옆에 넣으세요.](extra-files.png)

## Exercise — 다른 메시지 읽기

소스 옆에 friend.txt를 만들고 새 메시지를 한 줄 적으세요. 프로그램이 friend.txt를 읽도록 바꾸고 저장하세요. Publish에서 friend.txt를 선택해 배포하고 배포 폴더의 exe를 실행하세요.

@exercise exercise_starter.cpp

### Hint

file.Open의 이름을 바꾸세요. 코드만 바꿔서는 파일이 복사되지 않습니다. Add Files에서도 friend.txt를 골라야 합니다. 그림과 소리를 불러오는 프로그램도 같은 방법으로 함께 넣습니다.

@solution exercise_solution.cpp
