FROM alpine:3.18

RUN	apk update \
	&& apk add \
	curl tar mariadb-client \
	php81 php81-fpm php81-openssl php81-mysqli php81-phar \
	php81-mbstring php81-gd

RUN	curl https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
	-o wp-cli.phar \
	&& chmod +x wp-cli.phar \
	&& mv wp-cli.phar /usr/local/bin/wp

RUN	adduser -S -G www-data www-data
RUN	sed -i 's/display_errors = Off/display_errors = On/g' /etc/php81/php.ini 

COPY	conf/www.conf /etc/php81/php-fpm.d/www.conf
COPY	tools/ /scripts

WORKDIR	/var/www/wordpress

EXPOSE	9000

CMD sh /scripts/wp-start.sh
