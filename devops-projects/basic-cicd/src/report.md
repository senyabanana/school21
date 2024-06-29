# Basic CI/CD

## Part 1. Настройка gitlab-runner

* Установка `gitlab-runner`<br>
    1. `sudo curl -L --output /usr/local/bin/gitlab-runner "https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64"`<br>
    2. `sudo chmod +x /usr/local/bin/gitlab-runner`<br>
    3. `sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash`<br>
    4. `sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner`<br>
    5. `sudo gitlab-runner start`<br>
* Регистрация в `gitlab-runner`<br>
    1. `sudo gitlab-runner register`<br>
    2. URL: https://repos.21-school.ru<br>
    3. token: `<your_token_from_the_platform>`<br>
    4. `sudo gitlab-runner run`<br>
    5. `service gitlab-runner status`<br>
    ![status](pictures/part1.png)<br>*Проверяем статус*<br>
    ![dump](pictures/part1.2.png)<br>*Делаем дамп образа*<br>

## Part 2. Сборка

![done](pictures/part2.png)<br><br>

## Part 3. Тест кодстайла

![done](pictures/part3.png)<br><br>

## Part 4. Интеграционные тесты

![done](pictures/part4.png)<br><br>
![done](pictures/part4.1.png)<br><br>

## Part 5. Этап деплоя

![done](pictures/part5.png)<br><br>

## Part 6. Дополнительно. Уведомления

![done](pictures/part6.png)<br><br>
![done](pictures/part6.1.png)<br><br>