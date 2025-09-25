#FROM ghcr.io/catthehacker/ubuntu
FROM ghcr.io/rockylinux/rockylinux
#FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y apache2 curl && \
    rm -rf /var/lib/apt/lists/*

EXPOSE 80
CMD ["apache2ctl", "-D", "FOREGROUND"]
