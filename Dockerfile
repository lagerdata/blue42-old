# For help with editing and block commenting add plugin to sublime

#macos
#Press cmd(⌘)-shift-p and type "add repo".
#Then paste in the GitHub address for this package:

#https://github.com/jaytaylor/Dockerfile.sublime-syntax

#Press cmd(⌘)-shift-p and type "install".
#Enter "Dockerfile.sublime-syntax" and press enter.
#Restart Sublime
#windows
#Replace cmd(⌘) with Ctrl

#usage:
# e.g.
# docker build -t lager .
# docker docker run --name lager_bash --rm -it lager bash

#NOTE: THIS IS WILL GENERATE A VERY LARGE IMAGE (~17GB). TO REDUCE SIZE COMMENT TOOLS THAT MIGHT NOT BE NECESSARY

FROM ubuntu:20.04

MAINTAINER Akbar Dhanaliwala <akbar@lagerdata.com>

WORKDIR /app

ARG DEBIAN_FRONTEND=noninteractive

# Download tools(including gcc), prerequisites
RUN apt-get update && \
apt-get install -y wget curl git unzip bzip2 build-essential gcc-multilib pkg-config python python-setuptools python3 \
python3-pip python3-setuptools python-cryptography python-pyparsing python-pyelftools nano bash \
ruby gcc-arm-none-eabi clang cmake ninja-build libncurses-dev flex bison gperf ccache libffi-dev libssl-dev dfu-util \
libasound2-dev libgconf-2-4 libnotify-dev libnss3-tools libnss3 libpython2.7 \
		&& apt-get clean all

# Install python-pip
# NOTE: Python2 was deprecated on Jan.1, 2020. Ubuntu 20.04 does not ship with python2
RUN curl https://bootstrap.pypa.io/get-pip.py --output /tmp/get-pip.py
RUN python2 /tmp/get-pip.py && rm /tmp/get-pip.py


# Microchip Tools Dependencies - i386
###COMMENT/UNCOMMENT BELOW
RUN dpkg --add-architecture i386 \
    && apt-get update -yq \
    && apt-get upgrade -yq \
    && apt-get install -yq --no-install-recommends cpio \
    libc6:i386 libx11-6:i386 libxext6:i386 libstdc++6:i386 libexpat1:i386 \
    libxext6 libxrender1 libxtst6 libgtk2.0-0 libxslt1.1 libncurses5-dev \
	unzip \
	xz-utils
###COMMENT/UNCOMMENT ABOVE

# Download and Install XC8 Compiler, Current Version
###COMMENT/UNCOMMENT BELOW
RUN curl -fSL -A "Mozilla/4.0" -o /tmp/xc8.run "http://www.microchip.com/mplabxc8linux" \
    && chmod a+x /tmp/xc8.run \
    && /tmp/xc8.run --mode unattended --unattendedmodeui none \
        --netservername localhost --LicenseType FreeMode --prefix /opt/microchip/xc8 \
    && rm /tmp/xc8.run

ENV PATH $PATH:/opt/microchip/xc8/bin
###COMMENT/UNCOMMENT ABOVE

# Download and Install XC16 Compiler, Current Version
###COMMENT/UNCOMMENT BELOW
RUN curl -fSL -A "Mozilla/4.0" -o /tmp/xc16.run "http://www.microchip.com/mplabxc16linux" \
    && chmod a+x /tmp/xc16.run \
    && /tmp/xc16.run --mode unattended --unattendedmodeui none \
        --netservername localhost --LicenseType FreeMode --prefix /opt/microchip/xc16 \
    && rm /tmp/xc16.run

ENV PATH $PATH:/opt/microchip/xc16/bin
###COMMENT/UNCOMMENT ABOVE

# Download and Install XC32 Compiler, Current Version
###COMMENT/UNCOMMENT BELOW
RUN curl -fSL -A "Mozilla/4.0" -o /tmp/xc32.run "http://www.microchip.com/mplabxc32linux" \
    && chmod a+x /tmp/xc32.run \
    && /tmp/xc32.run --mode unattended --unattendedmodeui none \
        --netservername localhost --LicenseType FreeMode --prefix /opt/microchip/xc32 \
    && rm /tmp/xc32.run

ENV PATH $PATH:/opt/microchip/xc32/bin
###COMMENT/UNCOMMENT ABOVE

# Install Nordic nRFTools (makes it easy to build a DFU package)
###COMMENT/UNCOMMENT BELOW
RUN pip install nrfutil
###COMMENT/UNCOMMENT ABOVE

#Install FTDI D2XX driver
###COMMENT/UNCOMMENT BELOW
RUN curl -fSL -A "Mozialla/4.0" -o /tmp/libftd2xx-x86_64-1.4.8.gz "https://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx-x86_64-1.4.8.gz"
RUN cd /tmp && tar -xvzf /tmp/libftd2xx-x86_64-1.4.8.gz
RUN cp  /tmp/release/build/lib*  /usr/local/lib/ 2>/dev/null || :
RUN cd /usr/local/lib && ln -s libftd2xx.so.1.4.8 libftd2xx.so && chmod 0755 libftd2xx.so.1.4.8 && rm -rf /tmp/release /tmp/libftd2xx-x86_64-1.4.8.gz

ENV PATH=$PATH:/usr/local/lib
###COMMENT/UNCOMMENT ABOVE

# Install Texas Instruments UniFlash (For building images)
###COMMENT/UNCOMMENT BELOW
RUN pip install teamcity-messages pytest mock pytest-cov pytest mock xmltodict requests pylint coloredlogs pyopenssl pyserial pytz
RUN mkdir /opt/ti && chmod 777 /opt/ti
RUN curl -fSL -A "Mozialla/4.0" -o /tmp/uniflash_sl.6.0.0.2710.run "http://software-dl.ti.com/ccs/esd/uniflash/uniflash_sl.6.0.0.2710.run" \
    && chmod a+x /tmp/uniflash_sl.6.0.0.2710.run \
    && /tmp/uniflash_sl.6.0.0.2710.run --mode unattended --unattendedmodeui none --prefix /opt/ti \
    && rm /tmp/uniflash_sl.6.0.0.2710.run
# avoid needing "./" when calling SLImagecrator
RUN cp /usr/local/lib/libftd2xx.so /opt/ti/simplelink/imagecreator/bin/

# Don't make this an env path since currently SLImageCreator only seems to work from within the bin folder
# ENV PATH $PATH:/opt/ti/simplelink/imagecreator/bin
# todo get SLImageCreator to work outside of bin folder
###COMMENT/UNCOMMENT ABOVE

# Install nanopb and protoc
###COMMENT/UNCOMMENT BELOW
ENV PROTOC_ZIP=protoc-3.7.1-linux-x86_64.zip
RUN curl -OL https://github.com/protocolbuffers/protobuf/releases/download/v3.7.1/$PROTOC_ZIP
RUN unzip -o $PROTOC_ZIP -d /usr/local bin/protoc
RUN unzip -o $PROTOC_ZIP -d /usr/local 'include/*'
RUN rm -f $PROTOC_ZIP
RUN curl -fSL -A "Mozialla/4.0" -o /tmp/nanopb-0.4.1-linux-x86.tar.gz "https://jpa.kapsi.fi/nanopb/download/nanopb-0.4.1-linux-x86.tar.gz"
RUN cd /tmp && tar -xvzf /tmp/nanopb-0.4.1-linux-x86.tar.gz
RUN mkdir -p /opt/nanopb
RUN cp -r /tmp/nanopb-0.4.1-linux-x86 /opt/nanopb/ && rm -rf /tmp/nanopb-0.4.1-linux-x86.tar.gz /tmp/nanopb-0.4.1-linux-x86

ENV PATH=$PATH:/opt/nanopb
###COMMENT/UNCOMMENT ABOVE


# Install ESP32 Toolchain
###COMMENT/UNCOMMENT BELOW
RUN mkdir -p /opt/esp
RUN cd /opt/esp && git clone --recursive https://github.com/espressif/esp-idf.git
RUN cd /opt/esp/esp-idf/ && ./install.sh
SHELL ["/bin/bash", "-c", "source /opt/esp/esp-idf/export.sh"]
###COMMENT/UNCOMMENT ABOVE

