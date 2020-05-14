cmake_minimum_required(VERSION 3.5)

project(SpectrumAnalyzer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB SPECTRUMANALYZER_SRC
    "src/*.hpp"
    "src/*.cpp"
)

file(GLOB SPECTRUMANALYZER_TEST
    ${SPECTRUMANALYZER_SRC}
    "test/*.hpp"
    "test/*.cpp"
    "test/*.ui"
)

add_library(SpectrumAnalyzer STATIC
    ${SPECTRUMANALYZER_SRC}
)


#add_executable(SpectrumAnalyzerExe
#    ${SPECTRUMANALYZER_SRC}
#    ${SPECTRUMANALYZER_TEST}
#)


include_directories("../DSP/src")

target_link_libraries(SpectrumAnalyzer PRIVATE Qt5::Widgets)
#target_link_libraries(SpectrumAnalyzerExe PRIVATE Qt5::Widgets)

#qt5_wrap_ui(SPECTRUMANALYZER_TEST MainMindow.ui)

target_compile_definitions(SpectrumAnalyzer PRIVATE SPECTRUMANALYZER_LIBRARY)
