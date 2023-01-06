# web-server

## WEB-server написанный на языке C.

### Путеводитель по веткам

main - последняя актуальная версия сервера
default - версия сервера, над которой ведется работа

В других ветках находятся реализации конеретной задачи.
Пример названия: 1.0-1_2

1.0 - версия сервера, для которой решается задача
1_2 - номер/номера задачи/задач

### Структура проекта

web-server--+                                   // репозиторий
            |
            |--server--+                        // файлы сервера
            |          |--headers--+       
            |          |           |--*.h       // заголовочные файлы сервера
            |          |
            |          |--*.c                   // исходные файлы сервера
            |
            |
            |--web                              // файлы веб-разработки (.html, .css, .js)
