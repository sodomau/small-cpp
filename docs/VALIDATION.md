# Validation record — v0.8

## 실제 수행

환경: Debian 13 x86-64. GCC 14.2.0, Clang (설치된 Swift toolchain), CMake 3.31.6.

- `tests/test_values.cpp`: 공개 API 56개 검사, GCC로 컴파일 및 실행 성공.
- 동일한 56개 검사: Clang으로 컴파일 및 실행 성공.
- 동일 테스트를 Clang AddressSanitizer / UndefinedBehaviorSanitizer로 실행: 성공.
- `examples/reference/console.cpp`, `ball.cpp`, `colors.cpp`: Qt include 경로 없이 공개 헤더만 강제 포함하여
  GCC `-std=c++20 -Wall -Wextra -Werror -c` 컴파일 성공.
  이 검사는 객체 파일 컴파일 검사이며 Qt와의 최종 링크/실행 검사가 아닙니다.
- `tests/check_layout.py`: 구조 검사 16개 통과.
- CMake configure/generate 문법 및 Kit 경로 헤더 생성은 임시 mock Qt imported targets로 검사했습니다.
  이는 실제 Qt 라이브러리 검증이 아닙니다. mock 파일은 배포 ZIP에 포함하지 않았습니다.

## 수행하지 못함

이 작업 환경에는 Qt 6 개발 패키지가 없으며, 패키지 설치에 필요한 네트워크에 접근할 수 없었습니다.
따라서 다음을 실제 검증했다고 주장하지 않습니다.

- 전체 Qt IDE 및 런타임 빌드/링크
- Windows MinGW에서의 GUI 실행
- 실제 창 닫기 / 저장 대화상자 클릭 동작
- 실제 오디오 출력
- 이전 버전 대비 Windows Run 소요 시간

## 포함한 Qt 테스트 (이 환경에서는 미실행)

`tests/test_qt.cpp`에 다음 회귀 테스트를 작성했습니다. Qt 환경에서
`SMALL_BUILD_TESTS=ON`으로 빌드한 뒤 실행할 수 있습니다.

- 이전 줄 선언의 세미콜론 누락 위치
- Ctrl+S/O 단축키와 수정 표시
- 창 닫기 Cancel / Discard
- 닫기에서 Save를 고른 뒤 Save As 취소
- 기본 파일명과 저장 후 닫기
- Window 생성과 실제 Open 분리
- front/back buffer 분리
- KeyPressed 프레임 경계, 포커스 상실 시 키 해제
- 실제 컴파일/링크/프로그램 출력 및 이벤트 루프 heartbeat
- 컴파일 도중 Stop

테스트 소스도 전체 Qt 빌드와 함께 확인이 필요합니다.

## 수동 확인 순서

1. 새 폴더의 `ide/CMakeLists.txt`를 기존 Qt MinGW Kit로 빌드합니다.
2. SmallCppIDE에서 기본 프로그램을 Run하여 창/키보드/Space 소리를 확인합니다.
3. 몇 줄을 바꾸고 다시 Run합니다. 상태 표시줄 Compile / Link 시간을 비교합니다.
4. `*`가 있는 상태에서 IDE X 버튼 → Cancel: 문서가 남아야 합니다.
5. X → Save → 파일 저장 창 Cancel: IDE가 남아야 합니다.
6. X → Save → 저장 완료: 파일에 내용이 있고 IDE가 닫혀야 합니다.
7. X → Discard: 저장하지 않고 닫혀야 합니다.
