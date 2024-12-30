FROM --platform=linux/amd64 ubuntu:22.04 AS builder

ARG DEBIAN_FRONTEND=noninteractive

# 替换为清华的镜像源
#RUN sed -i 's/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list && \
#    sed -i 's/security.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list

# 更新包列表并安装必要的工具
RUN apt-get update && apt-get install -y \
    cmake\
    g++\
    wget


RUN wget https://go.dev/dl/go1.23.2.linux-amd64.tar.gz && tar -zxf go1.23.2.linux-amd64.tar.gz -C /usr/local
ENV PATH=$PATH:/usr/local/go/bin:/usr/local/go/pkg/bin
#
#WORKDIR /src
#COPY . .
#
#RUN ls && cd ./POSIX/golang && cmake . -DCMAKE_INSTALL_PREFIX=. && make -j8 install



