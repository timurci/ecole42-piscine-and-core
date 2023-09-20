FROM alpine:3.18

RUN	apk update && apk add \
	mariadb mariadb-client

RUN	mysql_install_db --datadir=/var/lib/mysql --user=root

COPY	tools/ /scripts

CMD	sh scripts/initdb.sh
