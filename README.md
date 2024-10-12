# socket_pinger

Состоит из двух программ: `./build/server` и `./build/client`.
Клиент с указанным периодом подключается к серверу и отправляет текстовую строку. 

## Сборка

Сборка стандартным образом через симейк:
```
$ cmake -S . -B build
$ cmake --build build
```

## server

Принимает порт в качестве единственного аргумента. Запуск сервера:
```bash
$ ./build/server 5000
Socket created (port = 5000)
Socket listening...
```

Записывает все сообщения всех клиентов в файл `./log.txt`.

## client

Принимает аргументы: имя клиента, порт сервера, период отправки в секундах:
```bash
$ ./build/client Client17 5000 0.5
Socket created
Socket connected
Sending (Client17)
Sending (Client17)
Sending (Client17)
...
Sending (Client17)
^C

```

Тем временем на сервере:
```bash
$ ./build/server 5000
Socket created (port = 5000)
Socket listening...
...
Accepted connection.
Message: [2024-09-16 14:28:25.529] Client17
Message: [2024-09-16 14:28:26.029] Client17
Message: [2024-09-16 14:28:26.529] Client17
Message: [2024-09-16 14:28:27.029] Client17
Message: [2024-09-16 14:28:27.529] Client17
Message: [2024-09-16 14:28:28.029] Client17
Message: [2024-09-16 14:28:28.529] Client17
Message: [2024-09-16 14:28:29.029] Client17
Message: [2024-09-16 14:28:29.529] Client17
Message: [2024-09-16 14:28:30.029] Client17
Message: [2024-09-16 14:28:30.529] Client17
Connection ended.
```
