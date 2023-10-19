LINK?=tcakmako.42.fr
NAME=inception

ERROR=\033[31;1mError:\033[0m
SUCCESS=\033[32;1m+\033[0m

all: $(NAME)

$(NAME): add-host compose

compose:
	@docker-compose up --build \
		|| echo -e "$(ERROR) Cannot compose dockerfile."

prune:
	@docker image rm -f inception_nginx inception_mariadb inception_wordpress \
		&& echo -e "$(SUCCESS) docker has successfuly removed images."
	@docker volume rm -f inception_wordpress_db inception_wordpress_web \
		&& echo -e "$(SUCCESS) docker has successfuly removed volumes."
	@docker system prune -f \
		&& echo -e "$(SUCCESS) docker system prune is complete."

start: $(NAME)

stop: clean

clean:
	@docker-compose down && echo -e "$(SUCCESS) Stopped docker compose."

fclean: clean prune remove-host

add-host:
	@grep /etc/hosts -e $(LINK) > /dev/null || echo "127.0.0.1	$(LINK)" >> /etc/hosts \
		&& echo -e "$(SUCCESS) Added $(LINK) to /etc/hosts." \
		|| echo -e "$(ERROR) Cannot add $(LINK) to /etc/hosts."

remove-host:
	@sed -i "/127.0.0.1	$(LINK)/d" /etc/hosts \
		&& echo -e "$(SUCCESS) Removed $(LINK) from /etc/hosts." \
		|| echo -e "$(ERROR) Cannot remove $(LINK) from /etc/hosts."

.PHONY: all prune start stop clean fclean add-host
