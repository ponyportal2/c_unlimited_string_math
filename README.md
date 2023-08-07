# Unlimited String Math in C

This library I wrote adds an ability to do arithmetic on potentially unlimited strings of digits (supporting the dot) in C.

The quality of the code leaves much to be desired, as I was just starting to work in C when I wrote this :)

To make the library support more chars in the string please make the #defined macroed values bigger in unlim_math.h

* add_positive_10String - addition
* sub_positive_10String - subtraction
* mult_positive_10String - multiplication

The library is built into an .a file. For it to work in your project, you need to place unlim_math.a and unlim_math.h in your project folder.

To build the library, just write "make" in the terminal in src folder.

The library is tested and works on Linux, Mac and WSL.

The library passed auto-tests at Programming School 21 from Sberbank (School 42 analogue).

-----------------------------------------

Эта написанная мной библиотека добавляет в C подсчеты стрингов цифр потенциально неограниченного количества (с поддержкой точки).

Качество кода оставляет желать лучшего, так как я только начинал работать в С, когда это писал :)

Чтобы библиотека поддерживала больше символов в строке, увеличьте макроопределенные значения в файле unlim_math.h

* add_positive_10String - сложение
* sub_positive_10String - вычитание
* mult_positive_10String - умножение

Библиотека билдится в .a файл. Для работы нужно поместить в папку вашего проекта unlim_math.а и unlim_math.h

Для билда библиотеки достаточно написать make в терминале в папке src проекта.

Библиотека протестирована и работает на Linux, Mac и WSL.

Библиотека прошла авто-тесты в Школе программирования 21 от Сбера (аналог Школы 42).
