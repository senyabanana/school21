## Dashboard

* Создадим панель для отображения `CPU`<br/>
    ![cpu](./pictures/CPU.png)
* Создaдим панель для отображения `доступной оперативной памяти`<br/>
    ![ram](./pictures/RAM.png)
* Создадим панель для отображения объема `всей памяти`, `занятой памяти` и `свободной памяти`<br/>
    ![disk](./pictures/Disk_usage.png)
* Создадим панель для отображения `количества операций ввода/вывода на жестком диске`<br/>
    ![iops](./pictures/Iops.png)
* Конечный результат
    ![full](./pictures/full.png)
* Запустим bash-скрипт из Part 2 и проверим результаты работы
    ![res](./pictures/result.png)
* Запустим команду `stress -c 2 -i 1 -m 1 --vm-bytes 32M -t 60`
    ![stress](./pictures/stress.png)