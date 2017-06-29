<?php

// Set timezone
date_default_timezone_set('Asia/Shanghai');

// Prevent session cookies
ini_set('session.use_cookies', 0);

// Enable Composer autoloader
$autoloader = require dirname(__DIR__) . '/vendor/autoload.php';

// Register test classes
$autoloader->addPsr4('Slim\Tests\\', __DIR__);
