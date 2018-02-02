FROM ubuntu:16.04
MAINTAINER Ding Peilong "77676182@qq.com"
ENV REFRESHED_AT 2018-02-02

RUN apt-get -qq update && apt-get -qq install redis-server redis-tools

EXPOSE 6379

ENTRYPOINT ["/usr/bin/redis-server"]
CMD []
