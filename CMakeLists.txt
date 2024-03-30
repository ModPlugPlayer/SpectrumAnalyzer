#Build script of Spectrum Analyzer
#Copyright (C) 2020 Volkan Orhan

#This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

#This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

#You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA


cmake_minimum_required(VERSION 3.5)

project(SpectrumAnalyzer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

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


add_executable(SpectrumAnalyzerExe
    ${SPECTRUMANALYZER_SRC}
    ${SPECTRUMANALYZER_TEST}
)


include_directories("../DSP/src")

target_link_libraries(SpectrumAnalyzer PRIVATE Qt6::Widgets)
target_link_libraries(SpectrumAnalyzerExe PRIVATE Qt6::Widgets)

qt_wrap_ui(SPECTRUMANALYZER_TEST MainMindow.ui)

target_compile_definitions(SpectrumAnalyzer PRIVATE SPECTRUMANALYZER_LIBRARY)
