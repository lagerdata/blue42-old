
### Createing binary build tree
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-gcc-toolchain.cmake

### Sharing folder between host and docker
docker run -it --name [continer name] -v /path/to/host/folder:/path/to/docker/folder --rm [image name]