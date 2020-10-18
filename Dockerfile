FROM php:7.1-apache
RUN docker-php-ext-install mysqli
RUN apt-get install php7.1-mysql