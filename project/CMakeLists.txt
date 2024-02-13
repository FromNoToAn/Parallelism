# CMakeList.txt: проект CMake для CMake_Parallelism_Dz_1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMake_Parallelism_Dz_1")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMake_Parallelism_Dz_1 "CMake_Parallelism_Dz_1.cpp")

set(FL_VAL 0)
option(FL "FL" OFF)

if(FL)
    set(FL_VAL 1)
endif()

target_compile_definitions(CMake_Parallelism_Dz_1 PRIVATE FL_VAL=${FL_VAL})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMake_Parallelism_Dz_1 PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.

message("FL: ${FL_VAL}")
