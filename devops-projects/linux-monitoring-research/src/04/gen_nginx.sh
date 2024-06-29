#!/bin/bash

count=1
day=$(date +%d)

function create_files {
    touch methods.txt
    echo "GET" | sudo tee -a methods.txt
    echo "POST" | sudo tee -a methods.txt
    echo "PUT" | sudo tee -a methods.txt
    echo "PATCH" | sudo tee -a methods.txt
    echo "DELETE" | sudo tee -a methods.txt

    touch url.txt
    echo "/works" | sudo tee -a url.txt
    echo "/services" | sudo tee -a url.txt
    echo "/portfolio" | sudo tee -a url.txt
    echo "/blog" | sudo tee -a url.txt
    echo "/tutorials" | sudo tee -a url.txt
    echo "/index.html" | sudo tee -a url.txt
    echo "/about-us" | sudo tee -a url.txt
    echo "/products/item123" | sudo tee -a url.txt
    echo "/blog/post-42" | sudo tee -a url.txt
    echo "/user/login" | sudo tee -a url.txt
    echo "/user/profile" | sudo tee -a url.txt
    echo "/api/data" | sudo tee -a url.txt
    echo "/contact-us" | sudo tee -a url.txt
    echo "/services/service-A" | sudo tee -a url.txt
    echo "/portfolio/project-5" | sudo tee -a url.txt

    touch protocol.txt
    echo "HTTP/1.1" | sudo tee -a protocol.txt
    echo "HTTP/1.0" | sudo tee -a protocol.txt
    echo "HTTP/2" | sudo tee -a protocol.txt
    echo "SPDY/3.1" | sudo tee -a protocol.txt
    echo "HTTPS/1.1" | sudo tee -a protocol.txt
    echo "HTTP/1.1" | sudo tee -a protocol.txt
    echo "HTTP/2.0" | sudo tee -a protocol.txt
    echo "HTTP/1.0" | sudo tee -a protocol.txt
    echo "HTTP/2.0" | sudo tee -a protocol.txt

    touch codes.txt
    echo "200" | sudo tee -a codes.txt
    echo "201" | sudo tee -a codes.txt
    echo "400" | sudo tee -a codes.txt
    echo "401" | sudo tee -a codes.txt
    echo "403" | sudo tee -a codes.txt
    echo "404" | sudo tee -a codes.txt
    echo "500" | sudo tee -a codes.txt
    echo "501" | sudo tee -a codes.txt
    echo "502" | sudo tee -a codes.txt
    echo "503" | sudo tee -a codes.txt

    touch agents.txt
    echo "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36" | sudo tee -a agents.txt
    echo "Chrome/15.0.860.0 (Windows; U; Windows NT 6.0; en-US) AppleWebKit/533.20.25 (KHTML, like Gecko) Version/15.0.860.0" | sudo tee -a agents.txt
    echo "Opera/9.60 (Windows NT 6.0; U; ru) Presto/2.1.1" | sudo tee -a agents.txt
    echo "radian6_default_(www.radian6.com/crawler)" | sudo tee -a agents.txt
    echo "Sosospider+(+http://help.soso.com/webspider.htm)" | sudo tee -a agents.txt
    echo "FyberSpider (+http://www.fybersearch.com/fyberspider.php)" | sudo tee -a agents.txt
    echo "Googlebot/2.1 (+http://www.googlebot.com/bot.html)" | sudo tee -a agents.txt
}

function logs {
    for ((; count <= 5; count++ )); do
        countStr=$(shuf -i 100-1000 -n1)
        for (( i = 0; i < countStr; i++ )); do
            # 1) IP (любые корректные, т.е. не должно быть ip вида 999.111.777.777)
            echo -n "$(shuf -i 1-255 -n1).$(shuf -i 1-255 -n1).$(shuf -i 1-255 -n1).$(shuf -i 1-255 -n1)" | sudo tee -a $count.log
            echo -n " - claduinm " | sudo tee -a $count.log # мя пользователя (обычно "-" в случае отсутствия аутентификации).
            # 4) Даты (в рамках заданного дня лога, должны идти по увеличению)
            echo -n "[$day$(date +/%b/%Y:$(shuf -n1 -i 1-23):$(shuf -n1 -i 1-59):$(shuf -n1 -i 1-59)) +0500] " | sudo tee -a $count.log
            # 3) Методы (GET, POST, PUT, PATCH, DELETE)
            echo -n "\"$(shuf -n1 methods.txt) " | sudo tee -a $count.log
            # 5) URL запроса агента
            echo -n "$(shuf -n1 url.txt) " | sudo tee -a $count.log
            echo -n "$(shuf -n1 protocol.txt)\" " | sudo tee -a $count.log
            # 2) Коды ответа (200, 201, 400, 401, 403, 404, 500, 501, 502, 503)
            echo -n "$(shuf -n1 codes.txt) " | sudo tee -a $count.log
            echo -n $RANDOM | sudo tee -a $count.log # колличество байтов, отвправленных клиенту в ответ на запрос
            echo -n " " | sudo tee -a $count.log
            # 6) Агенты (Mozilla, Google Chrome, Opera, Safari, Internet Explorer, Microsoft Edge, Crawler and bot, Library and net tool)
            echo "\"$(shuf -n1 agents.txt)\"" | sudo tee -a $count.log
        done
    done
}

function delete_files {
    sudo rm -rf methods.txt
    sudo rm -rf url.txt
    sudo rm -rf protocol.txt
    sudo rm -rf codes.txt
    sudo rm -rf agents.txt
}

create_files
logs
delete_files

# 200 (OK): Успешный запрос
# 201 (Created): Ресурс успешно создан
# 400 (Bad Request): Некорректный запрос
# 401 (Unauthorized): Требуется аутентификация
# 403 (Forbidden): Доступ запрещен
# 404 (Not Found): Запрашиваемый ресурс не найден
# 500 (Internal Server Error): Внутренняя ошибка сервера
# 501 (Not Implemented): Запрос не выполнен (функциональность не реализована)
# 502 (Bad Gateway): Ошибка шлюза (неверный ответ от прокси или шлюза)
# 503 (Service Unavailable): Сервис временно недоступен