## Свой node_exporter

* Напишем bash-скрипт `info.sh`, который собирает информацию по базовым метрикам системы (ЦПУ, оперативная память, жесткий диск (объем)). <br/>
* Скрипт формирует html-страницу `my_metrics.html` по формату Prometheus, которую будет отдавать nginx. <br/>
* Страница обновляется внутри bash-скрипта `main.sh` в цикле каждые 3 сек. <br/>
* Внесем изменения в конфигурационный файл `nginx.conf` <br/>
    ![nginx](./pictures/nginx_conf.png) <br/>
* Внесем изменения в файл `prometheus.yml` <br/>
    ![prometheus](./pictures/node.png) <br/>
* Запустим скрипт и проверим, что по адресу `http://localhost:9090/` добавились новые метрики <br/>
    ![targets](./pictures/prometheus.png) <br/>
* Сформированная `html страничка` <br/>
    ![cpu](./pictures/my_cpu.png) <br/>
    ![mem_total](./pictures/my_mem_total.png) <br/>
    ![mem_used](./pictures/my_mem_used.png) <br/>
    ![disk_total](./pictures/my_disk_total.png) <br/>
    ![disk_usage](./pictures/my_disk_used.png) <br/>

## Запустим bash-скрипт из Part 2 и проверим результаты работы

![cpu](./pictures/test1_1.png) <br/>
![mem_total](./pictures/test1_2.png) <br/>
![mem_used](./pictures/test1_3.png) <br/>
![disk_total](./pictures/test1_4.png) <br/>
![disk_usage](./pictures/test1_5.png) <br/>

## Запустим команду `stress -c 2 -i 1 -m 1 --vm-bytes 32M -t 60`

![cpu](./pictures/test2_1.png) <br/>
![mem_total](./pictures/test2_2.png) <br/>
![mem_used](./pictures/test2_3.png) <br/>
![disk_total](./pictures/test2_4.png) <br/>
![disk_usage](./pictures/test2_5.png) <br/>