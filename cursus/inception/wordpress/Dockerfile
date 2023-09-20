FROM alpine:3.18

RUN	apk update \
	&& apk add \
	curl tar php81 php81-fpm php81-openssl php81-mysqli

RUN	curl https://github.com/wp-cli/wp-cli/releases/download/v2.8.1/wp-cli-2.8.1.phar \
	-o wp-cli.phar \
	&& chmod +x wp-cli.phar \
	&& mv wp-cli.phar /usr/local/bin/wp

RUN	curl https://wordpress.org/wordpress-6.3.1.tar.gz \
	-o wordpress.tar.gz \
	&& mkdir -p /var/www \
	&& tar -xzf wordpress.tar.gz -C /var/www/ \
	&& rm -rf wordpress.tar.gz

#RUN	adduser -SD -s /sbin/nologin -h /var/www/ -G www-data www-data
RUN	adduser -S -G www-data www-data

COPY	conf/wp-config.php /var/www/wordpress
COPY	conf/www.conf /etc/php81/php-fpm.d/www.conf
COPY	tools/wp-start.sh .

EXPOSE	9000

CMD sh wp-start.sh
