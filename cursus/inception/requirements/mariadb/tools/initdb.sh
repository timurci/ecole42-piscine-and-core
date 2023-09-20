if [ ! -f "initdb.sq"]; then

cat << EOF > initdb.sq 
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD'; 
CREATE DATABASE $MYSQL_DATABASE_NAME CHARACTER SET utf8 COLLATE utf8_general_ci; 
CREATE USER '$MYSQL_USER'@'%' IDENTIFIED by '$MYSQL_USER_PASSWORD'; 
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE_NAME.* TO '$MYSQL_USER'@'%'; 
FLUSH PRIVILEGES; 
EOF

mysqld --user=root --bootstrap --skip-grant-tables=OFF < initdb.sq

sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf
sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf

fi

echo "************************************************************"
echo "=======================  INITDB.SQ  ========================"
cat initdb.sq
echo "====================  INITDB.SQ - EOF  ====================="
echo "************************************************************"

mkdir -p /run/mysqld
mysqld --user=root --console