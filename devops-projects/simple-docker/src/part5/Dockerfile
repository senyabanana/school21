FROM nginx
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./server.c /home/server.c
COPY ./start_server.sh /home/start_server.sh
RUN apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    apt-get clean && rm -rf /var/lib/apt/lists/*; \
    rm -rf /var/lib/apt/lists
WORKDIR /home/
USER nginx
ENTRYPOINT ["sh", "./start_server.sh"]
HEALTHCHECK --interval=30s --timeout=5s --start-period=5s --retries=3 CMD curl -f http://localhost/ || exit 1

