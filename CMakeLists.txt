# CMakeList.txt : CMake project for BowlingGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
project ("BowlingGame")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



# Add source to this project's executable.
add_executable (BowlingGame "src/BowlingCore/BowlingGame.cpp" "include/BowlingCore/BowlingGame.h")

target_include_directories(BowlingGame PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
)

# Setting the required C++ standard explicitly
set_target_properties(BowlingGame PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
