cmake_minimum_required(VERSION 3.21)
project(SmallCppIDE VERSION 0.76.9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

if(WIN32 AND NOT MINGW)
    message(FATAL_ERROR "Small C++ v0.7 needs a Qt MinGW 64-bit kit on Windows, not an MSVC kit.")
endif()

find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets Multimedia)
set(SMALL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(SMALL_BIN "${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>")
set(SMALL_SDK "${SMALL_BIN}/runtime")

# The reusable runtime deliberately contains NO main(). Learners who write
# main() link only this archive. SmallMain() programs additionally link the
# tiny precompiled small_entry archive below.
add_library(small_runtime STATIC
    "${SMALL_ROOT}/runtime/small_runtime.cpp"
    "${SMALL_ROOT}/runtime/small_sound.cpp"
    "${SMALL_ROOT}/runtime/small_platform.cpp"
    "${SMALL_ROOT}/runtime/small_platform_win.cpp"
    "${SMALL_ROOT}/runtime/small.h"
    "${SMALL_ROOT}/runtime/small_internal.h"
)
set_target_properties(small_runtime PROPERTIES AUTOMOC OFF DEBUG_POSTFIX "")
target_include_directories(small_runtime PUBLIC "${SMALL_ROOT}/runtime")
target_link_libraries(small_runtime PRIVATE Qt6::Widgets Qt6::Multimedia)

add_library(small_entry STATIC "${SMALL_ROOT}/runtime/small_main.cpp")
set_target_properties(small_entry PROPERTIES AUTOMOC OFF DEBUG_POSTFIX "")
target_include_directories(small_entry PRIVATE "${SMALL_ROOT}/runtime")
target_link_libraries(small_entry PRIVATE small_runtime)

# IDE-only exit pause support. This is deliberately separate from small_runtime:
# linking this object enables the console pause; omitting it gives normal
# release-style process termination.
add_library(small_ide_pause OBJECT "${SMALL_ROOT}/runtime/small_ide_pause.cpp")
set_target_properties(small_ide_pause PROPERTIES AUTOMOC OFF)

# First real extension: Image. It depends on Core; Core does not depend on it.
add_library(small_image STATIC
    "${SMALL_ROOT}/extensions/image/src/image.cpp"
    "${SMALL_ROOT}/extensions/image/include/small/image.h"
)
set_target_properties(small_image PROPERTIES AUTOMOC OFF DEBUG_POSTFIX "")
target_include_directories(small_image PUBLIC
    "${SMALL_ROOT}/runtime"
    "${SMALL_ROOT}/extensions/image/include"
)
target_link_libraries(small_image PRIVATE small_runtime Qt6::Gui)

add_custom_target(small_sdk ALL
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${SMALL_SDK}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${SMALL_ROOT}/runtime/small.h" "${SMALL_SDK}/small.h"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:small_runtime>" "${SMALL_SDK}/$<TARGET_FILE_NAME:small_runtime>"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:small_entry>" "${SMALL_SDK}/$<TARGET_FILE_NAME:small_entry>"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_OBJECTS:small_ide_pause>" "${SMALL_SDK}/small_ide_pause.o"
    COMMAND "${CMAKE_COMMAND}" -E make_directory
            "${SMALL_BIN}/extensions/image/include/small"
            "${SMALL_BIN}/extensions/image/lib"
            "${SMALL_BIN}/extensions/image/tutorial"
            "${SMALL_BIN}/extensions/image/examples"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/generated/image-extension-$<CONFIG>.json"
            "${SMALL_BIN}/extensions/image/extension.json"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${SMALL_ROOT}/extensions/image/include/small/image.h"
            "${SMALL_BIN}/extensions/image/include/small/image.h"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:small_image>"
            "${SMALL_BIN}/extensions/image/lib/$<TARGET_FILE_NAME:small_image>"
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${SMALL_ROOT}/extensions/image/examples"
            "${SMALL_BIN}/extensions/image/examples"
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${SMALL_ROOT}/extensions/image/tutorial"
            "${SMALL_BIN}/extensions/image/tutorial"
    DEPENDS small_runtime small_entry small_ide_pause small_image
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${SMALL_ROOT}/tutorial" "${SMALL_BIN}/tutorial"
    COMMENT "Preparing the precompiled Small C++ runtime and tutorial content"
    VERBATIM
)

# Record the actual kit selected in Qt Creator. No C:/Qt guessing, no qmake
# subprocess, and no mixing one MinGW compiler with another Qt installation.
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/$<CONFIG>/SmallBuildConfig.h"
CONTENT "#pragma once
namespace SmallBuildConfig {
inline constexpr const char* Compiler = R\"small(${CMAKE_CXX_COMPILER})small\";
inline constexpr const char* CompilerId = R\"small(${CMAKE_CXX_COMPILER_ID})small\";
inline constexpr const char* CompilerVersion = R\"small(${CMAKE_CXX_COMPILER_VERSION})small\";
inline constexpr const char* QtBin = R\"small($<TARGET_FILE_DIR:Qt6::Core>)small\";
inline constexpr const char* RuntimeFile = R\"small($<TARGET_FILE_NAME:small_runtime>)small\";
inline constexpr const char* EntryFile = R\"small($<TARGET_FILE_NAME:small_entry>)small\";
inline constexpr const char* IdePauseFile = R\"small(small_ide_pause.o)small\";
inline constexpr const char* QtLibraries[] = {
    R\"small($<TARGET_LINKER_FILE:Qt6::Widgets>)small\",
    R\"small($<TARGET_LINKER_FILE:Qt6::Gui>)small\",
    R\"small($<TARGET_LINKER_FILE:Qt6::Multimedia>)small\",
    R\"small($<TARGET_LINKER_FILE:Qt6::Core>)small\"
};
}
")

set(SMALL_IDE_SOURCES
    SmallSettings.h
    MainWindow.h MainWindow.cpp
    EditorDocument.h EditorDocument.cpp
    ExampleCatalog.h ExampleCatalog.cpp
    ExamplesBrowser.h ExamplesBrowser.cpp
    ApiReference.h ApiReference.cpp
    ApiBrowser.h ApiBrowser.cpp
    SmallExamples.qrc
    TutorialCatalog.h TutorialCatalog.cpp
    TutorialBrowser.h TutorialBrowser.cpp
    
    BuildController.h BuildController.cpp
    DebugController.h DebugController.cpp
    EntryPoint.h EntryPoint.cpp
    ExtensionRegistry.h ExtensionRegistry.cpp
    Diagnostics.h Diagnostics.cpp
    RuntimeDiagnostics.h RuntimeDiagnostics.cpp
    CodeEditor.h CodeEditor.cpp
    Highlighter.h Highlighter.cpp
)

add_library(small_ide_components STATIC ${SMALL_IDE_SOURCES})
set_target_properties(small_ide_components PROPERTIES AUTORCC ON)
target_link_libraries(small_ide_components PUBLIC Qt6::Widgets)
target_include_directories(small_ide_components PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/$<CONFIG>"
)

file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/image-extension-$<CONFIG>.json" CONTENT
"{\n  \"id\": \"image\",\n  \"name\": \"Image\",\n  \"header\": \"small/image.h\",\n  \"library\": \"$<TARGET_FILE_NAME:small_image>\",\n  \"include\": \"include\",\n  \"lib\": \"lib\",\n  \"tutorial\": \"tutorial\",\n  \"examples\": \"examples\"\n}\n")

file(GENERATE OUTPUT "${SMALL_BIN}/packaging-info.txt"
CONTENT "compiler=${CMAKE_CXX_COMPILER}\nqt_bin=$<TARGET_FILE_DIR:Qt6::Core>\nqt_widgets=$<TARGET_LINKER_FILE:Qt6::Widgets>\nqt_gui=$<TARGET_LINKER_FILE:Qt6::Gui>\nqt_multimedia=$<TARGET_LINKER_FILE:Qt6::Multimedia>\nqt_core=$<TARGET_LINKER_FILE:Qt6::Core>\n")

qt_add_executable(SmallCppIDE
    main.cpp
    SmallApp.qrc
)
# Packaging-only dependency probe for learner Qt runtime.
qt_add_executable(SmallDeployProbe SmallDeployProbe.cpp)
target_link_libraries(SmallDeployProbe PRIVATE
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
set_target_properties(SmallDeployProbe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}")
if(WIN32)
    target_sources(SmallCppIDE PRIVATE smallcpp.rc)
endif()
target_link_libraries(SmallCppIDE PRIVATE small_ide_components)
target_compile_definitions(SmallCppIDE PRIVATE SMALL_IDE_VERSION="${PROJECT_VERSION}")
set_target_properties(SmallCppIDE PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}"
    WIN32_EXECUTABLE TRUE
)
add_dependencies(SmallCppIDE small_sdk)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(small_runtime PRIVATE -Wall -Wextra)
    target_compile_options(small_entry PRIVATE -Wall -Wextra)
    target_compile_options(small_ide_components PRIVATE -Wall -Wextra)
endif()

# A plain C++ test target: Qt is not needed to parse/use the public header.
option(SMALL_BUILD_TESTS "Build the Small C++ regression tests" OFF)
if(SMALL_BUILD_TESTS)
    enable_testing()
    find_package(Qt6 REQUIRED COMPONENTS Test)
    add_executable(small_values_test "${SMALL_ROOT}/tests/test_values.cpp")
    set_target_properties(small_values_test PROPERTIES AUTOMOC OFF)
    target_include_directories(small_values_test PRIVATE "${SMALL_ROOT}/runtime")
    add_test(NAME small_values COMMAND small_values_test)

    add_executable(small_manual_main_test "${SMALL_ROOT}/tests/test_manual_main.cpp")
    set_target_properties(small_manual_main_test PROPERTIES AUTOMOC OFF)
    target_include_directories(small_manual_main_test PRIVATE "${SMALL_ROOT}/runtime")
    target_link_libraries(small_manual_main_test PRIVATE small_runtime)
    add_test(NAME small_manual_main COMMAND small_manual_main_test)
    set_tests_properties(small_manual_main PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen;SMALL_TEST_NO_CONSOLE_PAUSE=1")

    add_executable(small_manual_main_default_test "${SMALL_ROOT}/tests/test_manual_main_default.cpp")
    set_target_properties(small_manual_main_default_test PROPERTIES AUTOMOC OFF)
    target_include_directories(small_manual_main_default_test PRIVATE "${SMALL_ROOT}/runtime")
    target_link_libraries(small_manual_main_default_test PRIVATE small_runtime)
    add_test(NAME small_manual_main_default COMMAND small_manual_main_default_test)
    set_tests_properties(small_manual_main_default PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen;SMALL_TEST_NO_CONSOLE_PAUSE=1")

    add_executable(small_standard_main_test "${SMALL_ROOT}/tests/test_standard_main.cpp")
    set_target_properties(small_standard_main_test PROPERTIES AUTOMOC OFF)
    target_link_libraries(small_standard_main_test PRIVATE small_runtime)
    add_test(NAME small_standard_main COMMAND small_standard_main_test)

    qt_add_executable(small_qt_test "${SMALL_ROOT}/tests/test_qt.cpp")
    target_link_libraries(small_qt_test PRIVATE small_ide_components small_runtime
        Qt6::Test Qt6::Widgets Qt6::Multimedia)
    set_target_properties(small_qt_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}")
    add_dependencies(small_qt_test small_sdk)
    add_test(NAME small_qt COMMAND small_qt_test -o small_qt-results.txt,txt)
    set_tests_properties(small_qt PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
    set_tests_properties(small_qt PROPERTIES TIMEOUT 120)

    qt_add_executable(small_tabs_test "${SMALL_ROOT}/tests/test_tabs.cpp")
    target_link_libraries(small_tabs_test PRIVATE small_ide_components Qt6::Test Qt6::Widgets)
    set_target_properties(small_tabs_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}")
    add_dependencies(small_tabs_test small_sdk)
    add_test(NAME small_tabs COMMAND small_tabs_test)
    set_tests_properties(small_tabs PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen" TIMEOUT 180)


    qt_add_executable(small_examples_ui_test "${SMALL_ROOT}/tests/test_examples.cpp")
    target_link_libraries(small_examples_ui_test PRIVATE small_ide_components Qt6::Test Qt6::Widgets)
    set_target_properties(small_examples_ui_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}")
    add_dependencies(small_examples_ui_test small_sdk)
    add_test(NAME small_examples_ui COMMAND small_examples_ui_test -o small_examples-results.txt,txt)
    set_tests_properties(small_examples_ui PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen" TIMEOUT 180)

    qt_add_executable(small_tutorial_ui_test "${SMALL_ROOT}/tests/test_tutorial.cpp")
    target_link_libraries(small_tutorial_ui_test PRIVATE small_ide_components Qt6::Test Qt6::Widgets)
    set_target_properties(small_tutorial_ui_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}")
    add_dependencies(small_tutorial_ui_test small_sdk)
    add_test(NAME small_tutorial_ui COMMAND small_tutorial_ui_test -o small_tutorial-results.txt,txt)
    set_tests_properties(small_tutorial_ui PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen" TIMEOUT 180)

    find_package(Python3 QUIET COMPONENTS Interpreter)
    if(Python3_Interpreter_FOUND)
        add_test(NAME small_ide_console_pause
            COMMAND "${Python3_EXECUTABLE}" "${SMALL_ROOT}/tests/test_ide_pause.py"
                    "${CMAKE_CXX_COMPILER}" "$<TARGET_OBJECTS:small_ide_pause>")
        add_test(NAME small_tutorial_content
            COMMAND "${Python3_EXECUTABLE}" "${SMALL_ROOT}/tools/verify_tutorial.py")
        add_test(NAME small_example_catalog
            COMMAND "${Python3_EXECUTABLE}" "${SMALL_ROOT}/tools/verify_example_catalog.py")
        add_test(NAME small_tutorial_validator_regressions
            COMMAND "${Python3_EXECUTABLE}" "${SMALL_ROOT}/tests/test_tutorial_validation.py")
        file(GLOB SMALL_CONTENT_CHECKS CONFIGURE_DEPENDS "${SMALL_ROOT}/tools/verify_*.py")
        foreach(check_script IN LISTS SMALL_CONTENT_CHECKS)
            get_filename_component(check_name "${check_script}" NAME_WE)
            if(NOT check_name STREQUAL "verify_tutorial" AND NOT check_name STREQUAL "verify_example_catalog")
                add_test(NAME "small_${check_name}" COMMAND "${Python3_EXECUTABLE}" "${check_script}")
            endif()
        endforeach()
    endif()


    # Build every complete tutorial program against the real runtime. This is
    # a link target, not a GUI automation claim; text I/O is tested separately.
    file(GLOB_RECURSE SMALL_TUTORIAL_SOURCES CONFIGURE_DEPENDS
        "${SMALL_ROOT}/tutorial/*.cpp")
    add_custom_target(small_tutorial_programs)
    foreach(tutorial_source IN LISTS SMALL_TUTORIAL_SOURCES)
        get_filename_component(code_name "${tutorial_source}" NAME_WE)
        get_filename_component(lesson_dir "${tutorial_source}" DIRECTORY)
        get_filename_component(lesson_name "${lesson_dir}" NAME)
        set(target_name "small_tutorial_${lesson_name}_${code_name}")
        add_executable(${target_name} "${tutorial_source}")
        set_target_properties(${target_name} PROPERTIES
            AUTOMOC OFF EXCLUDE_FROM_ALL TRUE
            RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}/tutorial")
        target_compile_definitions(${target_name} PRIVATE SMALL_BEGINNER_MODE)
        target_compile_options(${target_name} PRIVATE -include "${SMALL_ROOT}/runtime/small.h")
        target_link_libraries(${target_name} PRIVATE small_entry small_runtime)
        add_dependencies(small_tutorial_programs ${target_name})
    endforeach()

    # Phase 3D: every shipped example must stay compilable with the real Small runtime.
    file(GLOB SMALL_REFERENCE_EXAMPLES "${SMALL_ROOT}/examples/reference/*.cpp")
    file(GLOB SMALL_PROGRAM_EXAMPLES "${SMALL_ROOT}/examples/programs/*.cpp")
    add_custom_target(small_examples)
    foreach(example_source IN LISTS SMALL_REFERENCE_EXAMPLES SMALL_PROGRAM_EXAMPLES)
        get_filename_component(example_name "${example_source}" NAME_WE)
        get_filename_component(example_dir "${example_source}" DIRECTORY)
        get_filename_component(example_group "${example_dir}" NAME)
        set(target_name "small_example_${example_group}_${example_name}")
        add_executable(${target_name} "${example_source}")
        set_target_properties(${target_name} PROPERTIES
            AUTOMOC OFF
            EXCLUDE_FROM_ALL TRUE
            RUNTIME_OUTPUT_DIRECTORY "${SMALL_BIN}/examples"
        )
        target_compile_definitions(${target_name} PRIVATE SMALL_BEGINNER_MODE)
        target_include_directories(${target_name} PRIVATE "${SMALL_ROOT}/runtime")
        target_compile_options(${target_name} PRIVATE
            -include "${SMALL_ROOT}/runtime/small.h")
        add_dependencies(small_examples ${target_name})
        target_link_libraries(${target_name} PRIVATE small_entry small_runtime)
    endforeach()
endif()
