# Лабораторная работа №4

## Задание 1

### Необходимые знания

1. Функция `kill`. Посылает сишнал процессу в зависимости от Pid (=0,>1,=-1,<-1) меняется посылка процесса. Если sig=0 то сигнал не посылается, но проверка на существование этого сигнала все равно происходит.
2. Неблокирующий wait c `WNOHANG` - означает немедленное возвращение управления, если ни один дочерний процесс не завершил выполнение.
3. Функция `alarm`- установка таймера для подачи сигнала, сигнал `SIGALRM`- ожидание sleep() может быть реализованна с помощью SIGALARM, функция `signal` - один из способов изменения поведения процесса, при получении сигнала (изменяет реакцию процесса на какой-либо сигнал).

Дополнить программу parallel\_min\_max.c из ***лабораторной работы №3***, так чтобы после заданного таймаута родительский процесс посылал дочерним сигнал SIGKILL. Таймаут должен быть задан, как именной необязательный параметр командной строки (`--timeout 10`). Если таймаут не задан, то выполнение программы не должно меняться.

### Ресурсы
1. [Системный вызов kill](http://man7.org/linux/man-pages/man2/kill.2.html)
2. [Системный вызов waitpid. Здесь информация о WNOHANG](https://linux.die.net/man/2/waitpid)
3. [Системный вызов signal](http://man7.org/linux/man-pages/man2/signal.2.html)
4. [Системный вызов alarm](http://man7.org/linux/man-pages/man2/alarm.2.html)

## Задание 2

### Необходимые знания

1. Что такое зомби процессы, как появляются, как исчезают.

Создать программу, с помощью которой можно продемонстрировать зомби процессы. Необходимо объяснить, как появляются зомби процессы, чем они опасны, и как можно от них избавиться.


####Как появляются зомби процессы?
Процесс при завершении (как нормальном, так и в результате не обрабатываемого сигнала) освобождает все свои ресурсы и становится «зомби» — пустой записью в таблице процессов, хранящей статус завершения предназначенный для чтения родительским процессом.


####Чем опасны зомби процессы?
Зомби не занимают памяти (как процессы-сироты), но блокируют записи в таблице процессов, размер которой ограничен для каждого пользователя и системы в целом.

При достижении лимита пользователь, от имени которого выполняется программа, и все его программы не будут способны создавать новые дочерние процессы. Кроме всего прочего, пользователь, от имени которого выполняется родительский процесс, не сможет зайти на консоль (локальную или удалённую) или выполнить какие-либо команды на уже открытой консоли (потому что для этого командный интерпретатор sh должен создать новый процесс), и для восстановления работоспособности (завершения виновной программы) будет необходимо вмешательство системного администратора.

####Как можно избавиться от зомби процессов?
Зомби процесс существует до тех пор, пока родительский процесс не прочитает его статус с помощью системного вызова wait(), в результате чего запись в таблице процессов будет освобождена.

При завершении процесса система уведомляет родительский процесс о завершении дочернего с помощью сигнала SIGCHLD, таким образом может быть удобно(но не обязательно) осуществлять вызов wait() в обработчике данного сигнала.

Проверка на наличие процесса.
`top | grep zombie`

Убйиство процесса
```
lenovo@15ikb:~$ ps -xal | grep defunct
1  1000 18889 18888  20   0      0     0 -      Z    pts/0      0:00 [zombie] <defunct>
0  1000 18949 18933  20   0  15648  1060 pipe_w S+   pts/2      0:00 grep --color=auto defunct
lenovo@15ikb:~$ kil -KILL 18888

Command 'kil' not found, did you mean:

  command 'kile' from deb kile
  command 'cil' from deb cil
  command 'kill' from deb procps
  command 'kid' from deb python-kid
  command 'uil' from deb uil
  command 'kig' from deb kig
  command 'kic' from deb kic
  command 'pil' from deb picolisp

Try: sudo apt install <deb name>

lenovo@15ikb:~$ kill -KILL 18888
lenovo@15ikb:~$

```

https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%BE%D1%86%D0%B5%D1%81%D1%81-%D0%B7%D0%BE%D0%BC%D0%B1%D0%B8

### Ресурсы

1. [Немного теории по зомби процессам](https://www-cdf.fnal.gov/offline/UNIX_Concepts/concepts.zombies.txt)

## Задание 3

### Необходимые знания

1. Работа виртуальной памяти.

Скомпилировать process_memory.c. Объяснить, за что отвечают переменные `etext`-первый адрес за концом сегмента текста(кода программы), `edata`-первый адрес за концом сегмента инициализированных данных, `end`-первый адрес за концом сегмента не инициализированных данных.


```
lenovo@15ikb:~/University/os_lab_2019/lab4/src$ ./process_memory

Address etext: DAFEDB9D
Address edata: DB1EF018
Address end  : DB1EF050
ID main 	 is at virtual address: DAFED8BA
ID showit 	 is at virtual address: DAFEDA37
ID cptr 	 is at virtual address: DB1EF010
ID buffer1 	 is at virtual address: DB1EF030
ID i 	 is at virtual address: 1AB3D6C4
A demonstration
ID buffer2 	 is at virtual address: 1AB3D6A0
Alocated memory at DCD76670
This message is output by the function showit()

```
### Ресурсы

1. [etext, edata, end](https://linux.die.net/man/3/edata)
2. [Неплохая статья (перевод), про то, как устроена память](https://habrahabr.ru/company/nixsolutions/blog/277759/)

## Задание 4

Создать makefile, который собирает программы из задания 1 и 3.

## Задание 5

### Необходимые знания

1. POSIX threads: как создавать, как дожидаться завершения.
2. Как линковаться на бибилотеку `pthread`

Доработать parallel_sum.c так, чтобы:

* Сумма массива высчитывалась параллельно.
* Массив генерировался с помощью функции `GenerateArray` из ***лабораторной работы №3***.
* Программа должна принимать входные аргументы: количество потоков, seed для генерирования массива, размер массива (`./psum --threads_num "num" --seed "num" --array_size "num"`).
* Вместе с ответом программа должна выводить время подсчета суммы (генерация массива не должна попадать в замер времени).
* Вынести функцию, которая считает сумму в отдельную библиотеку.
```
lenovo@15ikb:~/University/os_lab_2019/lab4/src$ ./parallel_sum --seed 12 --array_size 20 --threads_num 8
Array: 60 14 94 8 23 55 29 73 97 64 78 69 57 74 68 4 7 67 87 60
Total: 1088
Elapsed time: 1.074000ms

lenovo@15ikb:~/University/os_lab_2019/lab4/src$ ./parallel_sum --seed 12 --array_size 20 --threads_num 9
Array: 60 14 94 8 23 55 29 73 97 64 78 69 57 74 68 4 7 67 87 60
Ошибка сегментирования (стек памяти сброшен на диск)

```
### Ресурсы

1. [Туториал по POSIX threads от университета Карнеги-Меллона (в этой лабе вам нужно только начало)](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html#SCHEDULING)
2. [Как можно мерить время (кстати в 3й лабораторной работе тоже есть пример)](https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html)

## Задание 6

Создать makefile для parallel_sum.c.

## Перед тем, как сдавать

Залейте ваш код в ваш репозиторий на GitHub. Убедитесь, что вы не добавляете в репозиторий бинарные файлы (программы, утилиты, библиотеки и т.д.).
