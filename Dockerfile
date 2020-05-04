FROM ubuntu:19.10

MAINTAINER Akbar Dhanaliwala <akbar@lagerdata.com>

WORKDIR /app


ENV SDK_ROOT=/opt/nordic

# Download tools and prerequisites
RUN apt-get update && \
apt-get install -y wget curl git unzip bzip2 build-essential gcc-multilib pkg-config python gcc-arm-none-eabi cmake ninja-build \
		&& apt-get clean all


RUN mkdir -p $SDK_ROOT \
		&& wget https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v16.x.x/nRF5_SDK_16.0.0_98a08e2.zip -O nordic_sdk.zip \
		&& unzip -q nordic_sdk.zip -d $SDK_ROOT/nRF5_SDK_16.0.0 \
		&& rm nordic_sdk.zip


RUN curl -SL https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2?revision=bc2c96c0-14b5-4bb4-9f18-bceb4050fee7?product=GNU%20Arm%20Embedded%20Toolchain,64-bit,,Linux,7-2018-q2-update > /tmp/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2 \
		&& tar xvjf /tmp/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2 -C /usr/local/ \
		&& rm /tmp/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2


# Add micro-ecc to SDK
RUN wget https://github.com/kmackay/micro-ecc/archive/v1.0.zip -O micro-ecc_v1.0.zip \
		&& unzip -q micro-ecc_v1.0.zip -d $SDK_ROOT/nRF5_SDK_16.0.0/external/micro-ecc \
		&& mv $SDK_ROOT/nRF5_SDK_16.0.0/external/micro-ecc/micro-ecc-1.0 $SDK_ROOT/nRF5_SDK_16.0.0/external/micro-ecc/micro-ecc \
		&& make -C $SDK_ROOT/nRF5_SDK_16.0.0/external/micro-ecc/nrf52hf_armgcc/armgcc \
		&& rm micro-ecc_v1.0.zip

# Install nRF Tools (makes it easy to build a DFU package)
RUN apt-get install -y python-pip \
		&& pip install nrfutil

