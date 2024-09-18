# lab1
## Эта программа предназначена для отрисовки графа, заданного матрицей смежности, и пути в нем, если он существует
## Установка
1. Клонируйтие репозиторий (git clone https://github.com/tvorog24/oop24.git)
2. Перейдите в папку репозитория (cd oop24)
3. Перейдите в папку graph_drawing (cd graph_drawing)
## Использование
Чтобы собрать программу, введите _make_. Чтобы запустить программу, перейдите в папку build и введите _./lab1_. 
Для получения лучшего результата следуйте инструкциям программы. 
## Тестирование
Последовательно введите в консоль команды:
1. g++ --coverage tests.cpp funcs.cpp input.cpp -o tests
2. ./tests
### Получения визуализации
Убедитесь, что у вас установлен gcovr. Далее введите _gcovr -e catch.hpp -e tests.cpp --html-details -o coverage.html_. Откройте в браузере .../oop24/graph_drawing/coverage.html
## Документация 
Для того чтобы получить документацию по функциям, разработанным в рамках проекта, убедитесь, что у вас установлен doxygen. Затем используйте команду _doxygen_. Откройте через браузер .../oop24/graph_drawing/html/index.html
## Лицензия
Этот проект лицензирован под MIT License — смотрите файл LICENSE для подробностей.




