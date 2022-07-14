FROM ubuntu:latest

RUN apt update -y && \ 
    apt install cmake g++ wget libgtk-3-dev xauth dbus -y && \
    wget https://www.sqlite.org/2022/sqlite-autoconf-3370200.tar.gz && \
    tar -xvf sqlite-autoconf-3370200.tar.gz && cd sqlite-autoconf-3370200 && \
    ./configure --prefix=/usr/local && make install && cd .. && \
    rm -rf sqlite-autoconf-3370200.tar.gz

RUN useradd -ms /bin/bash default && mkdir -p cadastro && chown -R default:default /cadastro

WORKDIR /cadastro

USER default

CMD ["tail", "-f", "/dev/null"]