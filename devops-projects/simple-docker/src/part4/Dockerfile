FROM nginx
USER root
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./server.c /home/server.c
COPY ./start_server.sh /home/start_server.sh
RUN apt-get update
RUN apt-get install -y gcc spawn-fcgi libfcgi-dev
WORKDIR /home/
ENTRYPOINT ["sh", "./start_server.sh"]
