if [ ! -f "wordpress_key" ]; then

sed -i -e "s/{DB_USER}/${MYSQL_USER}/g" /var/www/wordpress/wp-config.php;
sed -i -e "s/{DB_PASSWORD}/${MYSQL_USER_PASSWORD}/g" /var/www/wordpress/wp-config.php;
sed -i -e "s/{WP_HOME}/${DOMAIN_NAME}/g" /var/www/wordpress/wp-config.php;
sed -i -e "s/{WP_SITEURL}/${DOMAIN_NAME}/g" /var/www/wordpress/wp-config.php;

curl -s https://api.wordpress.org/secret-key/1.1/salt > wordpress_key
sed -i -e '/^{INSERT_KEY}/{r /dev/stdin' -e 'd;}' /var/www/wordpress/wp-config.php < wordpress_key

fi

php-fpm81 -F
