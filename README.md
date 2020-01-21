# Egg-Thread
Egg::Thread - Egg-based (Linux daemon handy SDK) simple thread pool

This is the simple thread pool library based on the Egg (Linux daemon handy 
SDK) project. The thread library requires the Egg::System to be installed.

# How to build?

Configure and install thread library for Egg (Linux daemon SDK):

  - create build:
  
    mkdir build

  - enter build:
  
    pushd build

  - configure using cmake: "cmake OPTIONS ..", where the options are:

    * -DBUILD_TESTS=ON|OFF (Default: OFF)
    * -DBUILD_SHARED_LIBS=ON|OFF
    * -DBUILD_STATIC_LIBS=OFF|ON
    * -DCMAKE_INSTALL_PREFIX:PATH=<phoenix prefix>
    * -G"Eclipse CDT4 - Unix Makefiles" (to embed in Eclipse as the project)

  - Typical configuration:

    cmake \
        -DCMAKE_INSTALL_PREFIX:PATH=/opt/egg  \
	      -DBUILD_SHARED_LIBS=ON \
	      -DBUILD_STATIC_LIBS=OFF \
	      -DBUILD_TESTS=ON \
        ..

  - Build and install:
  
    make && make install

  - Clean up: 
  
    rm -rf ./*

  - Leave build
  
    popd
