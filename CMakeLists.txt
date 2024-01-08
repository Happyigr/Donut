# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.12)

# Устанавливаем название проекта
project(MyDonut)

# Добавляем исполняемый файл
add_executable(MyDonut src/main.cpp src/Terminal.cpp src/Misc.cpp)

# Добавляем директорию с заголовочными файлами
target_include_directories(MyDonut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем библиотеку ncurses
find_package(Curses REQUIRED)
target_link_libraries(MyDonut PRIVATE ${CURSES_LIBRARIES})
target_include_directories(MyDonut PRIVATE ${CURSES_INCLUDE_DIRS})
