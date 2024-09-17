#!/usr/bin/env bash

# Install SFML
. /etc/os-release
case "${ID}" in
ubuntu)
    # X11
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ;;
fedora)
    # X11
    sudo dnf install libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libXrender-devel
    ;;
nixos)
    # X11
    if [ "$(env | grep X11 -c)" -lt 3 ]; then
        nix develop --command bash -c "./compile.sh"
        exit 0
    fi
    ;;
arch)
    # X11
    sudo pacman -S libxrandr libxcursor libudev freetype2 openal flac libvorbis mesa
    ;;
*)
    echo "Unsupported OS"
    exit 1
    ;;
esac

cmake -B build

if [ $? -ne 0 ]; then
    echo "CMake failed"
    exit 1
fi

cmake --build build -j "$(nproc)"