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

Пока что просто запускается и подключается к серверу на порт 5123:
```bash
$ ./build/client
Socket created
Socket connected
Sending from Client 1
Sending from Client 1
...
```
Отсылает сообщение "Client 1" раз в 2 секунды.