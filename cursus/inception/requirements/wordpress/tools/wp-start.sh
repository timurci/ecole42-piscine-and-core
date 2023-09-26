while ! mariadb -hmariadb -u$MYSQL_USER -p$MYSQL_USER_PASSWORD $MYSQL_DATABASE_NAME; do
    sleep 3
done

if [ ! -f "/var/www/wordpress/wp-config.php" ]; then
	wp core download --allow-root
	wp config create \
		--dbname=$MYSQL_DATABASE_NAME --dbuser=$MYSQL_USER \
		--dbpass=$MYSQL_USER_PASSWORD --dbhost=mariadb --allow-root
	wp core install \
		--url=$DOMAIN_NAME --title=$WPRESS_TITLE \
		--admin_user=$WPRESS_ADMIN_USER \
		--admin_password=$WPRESS_ADMIN_USER_PASSWORD \
		--admin_email=$WPRESS_ADMIN_USER_EMAIL --allow-root # --skip-email
fi

echo Starting php-fpm...
php-fpm81 -F
