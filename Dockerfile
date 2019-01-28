FROM gcc:7.4.0
COPY . /usr/src/app
RUN wget https://github.com/coder3101/testcaser/archive/v0.5.2-beta.zip
RUN unzip v0.5.2-beta.zip
RUN cp -r testcaser-0.5.2-beta/testcaser/ /usr/local/include
RUN cp testcaser-0.5.2-beta/bin/virtualjudge /usr/bin/
WORKDIR /usr/src/app

