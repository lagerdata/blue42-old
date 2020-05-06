### Get image ID
    docker images

### Initial setup (running in vm, use image id from step 1 above)
    docker run -it --name blue42 -v /vagrant/projects/blue42/:/app --rm IMAGE_ID /bin/bash -c "mkdir -p _build; cd _build ; cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-gcc-toolchain.cmake"

### Compile (running in vm)
    docker run -it --name blue42 -v /vagrant/projects/blue42/:/app --rm IMAGE_ID /bin/bash -c "cd _build ; cmake --build ."
