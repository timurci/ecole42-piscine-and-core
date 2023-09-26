<?php

define( 'DB_NAME',     'wordpress');
define( 'DB_USER',     '{DB_USER}' );
define( 'DB_PASSWORD', '{DB_PASSWORD}' );
define( 'DB_HOST',     'mariadb' );
define( 'DB_CHARSET',  'utf8' );
define( 'DB_COLLATE',  '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */

{INSERT_KEY}

/**#@-*/

$table_prefix = 'wp_';

define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */

define( 'WP_HOME', 'https://{WP_HOME}' );
define( 'WP_SITEURL', 'https://{WP_SITEURL}' );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
