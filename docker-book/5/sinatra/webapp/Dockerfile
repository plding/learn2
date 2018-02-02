FROM ubuntu:16.04
MAINTAINER Ding Peilong "77676182@qq.com"
ENV REFRESHED_AT 2018-02-02

RUN apt-get -qq update && apt-get -qq install ruby ruby-dev build-essential redis-tools
RUN gem install --no-rdoc --no-ri sinatra json redis

RUN mkdir -p /opt/webapp

EXPOSE 4567

CMD [ "/opt/webapp/bin/webapp" ]
