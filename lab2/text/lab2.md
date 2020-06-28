# Лабораторная работа №2

## Задание 1

### Необходимые знания

1. Как менять занчения переменных внутри функций в Си.

### Задание

В папке swap лежит 3 файла: swap.c, swap.h и main.c. Ваша задача закончить метод Swap в swap.c, так, чтобы он менял местами два символа. Скомпилировать программу. Если вы все сделали верно, то программа, которую вы собрали выведет "b a".
```
lenovo@15ikb:~/Документы/OS labs/lab2/src/swap$ gcc -o Prog main.c swap.c
lenovo@15ikb:~/Документы/OS labs/lab2/src/swap$ ./Prog
b a
```
### Ресурсы

1. [Как компилировать простые программы с gcc (заменить сс на gcc).](https://www.classes.cs.uchicago.edu/archive/2014/winter/51081-1/LabFAQ/lab3/compile.html)

## Задание 2

### Необходимые знания

1. Выделение и освобождение памяти в куче Си.
2. В чем разница между стеком и кучей (прямо в задании не потребуется, но я спрошу).
3. Использование аргументов командной строки.


### Задание

В папке revert\_string содержатся файлы main.c, revert\_string.h, revert\_string.c. Вам необходимо реализовать метод RevertString в revert_string.c, который должен переворачивать данную пользователем строку.
Изучить код main.c, скомпилировать программу, рассказать, как она работает и, что делает.

### Ресурсы

1. [Кратко про выделение/освобождение памяти и указатели.](https://computer.howstuffworks.com/c29.htm)
2. [Разница между стеком и кучей.](https://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap)
3. [Кратко про аргументы командной строки от создателей gcc.](https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html)
4. [Пример с аргументами командной строки.](https://www.cprogramming.com/tutorial/c/lesson14.html)

## Задание 3

### Необходимые знания

1. Основы работы компилятора: препроцессор (Препроцессор лучше всего рассматривать как отдельную программу, которая выполняется перед компиляцией. При запуске программы препроцессор просматривает код сверху вниз, файл за файлом, в поиске директив. Директивы — это специальные команды, которые начинаются с символа # и НЕ заканчиваются точкой с запятой.), компилятор (Программа, которая переводит текст программы на C++ в машинный исполняемый код.) , линковщик ( программа, которая производит компоновку — принимает на вход один или несколько объектных модулей и собирает по ним исполнимый модуль). Их роли и порядок работы.
2. Что такое статическая и динамическая линковка. В чем разница? При динамической компоновке код библиотеки помещается во внешний модуль (dll), связывание с которым происходит на этапе выполнения. Отсюда и название - динамическая. При статической компоновке код библиотеки собирается вместе с клиентским кодом, как одно целое.
3. Опции компилятора:
* -I Используется для добавления ваших собственных каталогов для поиска заголовочных файлов в процессе сборки.
* -L Передается компоновщику. Используется для добавления ваших собственных каталогов для поиска библиотек в процессе сборки.
* -l Передается компоновщику. Используется для добавления ваших собственных библиотек для поиска в процессе сборки.
* -shared это создание таких библиотек, которые  загружаются  приложениями  при запуске. Если такая библиотека
   установлена  правильно, то все приложения, запускаемые после установки библиотеки, начинают использовать эту новую разделяемую библиотеку.
* -o Эта опция означает, что необходима только компиляция. Из исходных файлов программы создаются объектные файлы в виде name.o. Компоновка не производится.
* -с Эта опция означает, что необходима только компиляция. Из исходных файлов программы создаются объектные файлы в виде name.o. Компоновка не производится.
* -fPIC Передаёт  компилятору  для генерации позиционно-независимого кода, который может быть использован при  создании общих объектных файлов (динамически связываемых библиотек).
4. Утилита ar.
To create an archive from files class1.o, class2.o, class3.o, the following command would be used:

`ar rcs libclass.a class1.o class2.o class3.o`

Unix linkers, usually invoked through the C compiler cc, can read ar files and extract object files from them, so if libclass.a is an archive containing class1.o, class2.o and class3.o, then

`cc main.c libclass.a`

or (if libclass.a is placed in standard library path, like /usr/local/lib)

`cc main.c -lclass`

or (during linking)

`ld ... main.o -lclass ...`

is the same as:

`cc main.c class1.o class2.o class3.o`


5. Переменная окружения `LD_LIBRARY_PATH`
You can temporarily substitute a different library for this particular execution. In Linux, the environment variable LD_LIBRARY_PATH is a colon-separated set of directories where libraries should be searched for first, before the standard set of directories; this is useful when debugging a new library or using a nonstandard library for special purposes.
http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html


### Задание

В **задании 2**, вы написали маленькую библиотеку с одной функцией, переворота строки. Тем не менее этот код уже можно переиспользовать, а чтобы это было удобнее делать, его необходимо вынести в библиотеку. Ваше задание скомпилировать статическую и динамическую библиотеки с RevertString и залинковать их в приложения с main.c.
```
lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ gcc -c src/main.c  -o bin/main.o

lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ gcc -c src/revert_string.c -o bin/static/revert_string.o

lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ gcc -c -fPIC src/revert_string.c -o bin/shared/revert_string.o

```
Создаем архив для статистической библиотеки
`lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ ar rcs bin/static/revert_string.a bin/static/revert_string.o `

Компануем статистическую библиотеку
`lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ gcc bin/main.o -Lbin/static -lrevert -o bin/statically-linked
`
Теперь созданная нами программа не библиотеконезависима)
`lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ bin/statically-linked qwertyui
Reverted: iuytrewq
`

Теперь создадим динамическую библиотеку
`lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ gcc -shared bin/shared/revert_string.o  -o bin/shared/libshared.so
`
Теперь линкуемся к нашей динамической библиотеке
`lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ gcc bin/main.o -Lbin/shared -lshared -o bin/use-shared-library
`
Показываем где лежит наша библиотека
`lenovo@15ikb:~/Документы/OS labs/lab2/RevertString$ LD_LIBRARY_PATH=$(pwd)/bin/shared bin/use-shared-library qwer
Reverted: rewq
`
***Получится две программы, первая будет использовать статическую билиотеку, а вторая динамическую.***

### Ресурсы

1. [Как создавать статические и динамические библиотеки и линковаться на них.](https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index)

## Задание 4

### Необходимые знания

3. Переменная окружения `LD_LIBRARY_PATH`

### Задание

Если вы зайдете в update.sh, то увидите, слежующую строчку `sudo apt -y install libcunit1 libcunit1-doc libcunit1-dev`. Это установка в вашу систему библиотеки для юнит тестирования на языке Си - CUnit. В папочке test вы найдете tests.c - готовую программу, которая запускает несколько юнит тестов для функции RevertString. Ваша задача, скомпилировать эту программу с динамической библиотекой из **Задания 3**. Важно, что программа с тестами и программа из **Задания 2** должны использовать одну библиотеку (один файл).

P.S. Разумеется, тесты должны проходить :)

```

CUnit - A unit testing framework for C - Version 2.1-3
http://cunit.sourceforge.net/
x

Suite: Suite
  Test: test of RevertString function ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      1      1    n/a      0        0
               tests      1      1      1      0        0
             asserts      4      4      4      0      n/a

Elapsed time =    0.000 seconds
```
#Не знаю что делает apt -y!

### Ресурсы

1. [Как cлинковаться с CUnit.](https://mysnippets443.wordpress.com/2015/03/07/ubuntu-install-cunit/)

## Перед тем, как сдавать

Залейте ваш код в ваш репозиторий на GitHub. Убедитесь, что вы не добавляете в репозиторий бинарные файлы (программы, утилиты, библиотеки и т.д.).

<!--
## Задание 5* (Необязательно, за допополнительные баллы)

###Необходимые знания

1. Как пользоваться интернетом.

###Задание

В папке bin лежит динамическая библиотека libsimple.so. С помощью утилить `objdump` определить, какие функции она содержит.

###Ресурсы

1. [Аргументы коммандной строки для objdump](https://sourceware.org/binutils/docs/binutils/objdump.html)
-->
