cmake_minimum_required(VERSION 3.14)
project(MoneyLab)

# Це змусить CMake самому викачати бібліотеку
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main 
)
FetchContent_MakeAvailable(ftxui)

set(CMAKE_CXX_STANDARD 17)
# Генеруємо файл для автодоповнення в Neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(money_app main.cpp)

# Прив'язуємо бібліотеку до нашого екзешника
target_link_libraries(money_app PRIVATE ftxui::screen ftxui::dom ftxui::component)
