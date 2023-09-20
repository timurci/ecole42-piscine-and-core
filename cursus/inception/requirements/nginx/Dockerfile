FROM alpine:3.18

RUN	apk update; \
	apk add nginx openssl

RUN	openssl req -new -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
	-out    /etc/ssl/certs/nginx.crt \
	-keyout /etc/ssl/private/nginx.key \
	-subj '/C=TR/'

COPY	conf/nginx.conf /etc/nginx/nginx.conf
COPY	conf/default.conf /etc/nginx/http.d/default.conf

EXPOSE	443

CMD ["nginx", "-g", "daemon off;"]
