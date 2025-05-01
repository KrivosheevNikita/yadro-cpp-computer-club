## Computer Club
Прототип системы, которая следит за работой компьютерного клуба, обрабатывает события и подсчитывает выручку за день и время занятости каждого стола, реализованная в рамках отбора на стажировку в YADRO.

[Исходное тестовое задание](https://github.com/KrivosheevNikita/yadro-cpp-computer-club/blob/main/Исходное%20задание.txt)

## Сборка
```bash
git clone https://github.com/KrivosheevNikita/yadro-cpp-computer-club.git
cd yadro-cpp-computer-club
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
## Запуск
```bash
./task ../test_file.txt
```
## Запуск юнит-тестов
```bash
./tests
```
## Используемые технологии
- C++20
- CMake
- GoogleTest 
