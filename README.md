# socket_pinger

Состоит из двух программ: `./build/server` и `./build/client`.

## server

Принимает порт в качестве единственного аргумента. Запуск сервера:
```bash
$ ./build/server 5123
Socket created (port = 5123)
Socket listening...
```

## client

Принимает аргументы: имя клиента, порт сервера, период отправки в секундах:
```bash
$ ./build/client Client17 5000 0.33
Socket created
Socket connected
Sending (Client17)
Sending (Client17)
Sending (Client17)
Sending (Client17)
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
Message: Client17
Message: Client17
Message: Client17
Message: Client17
Message: Client17
Connection ended.
...
```