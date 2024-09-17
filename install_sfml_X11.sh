#!/usr/bin/env bash

# Install SFML
. /etc/os-release
case "${ID}" in
ubuntu)
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
    sudo dnf install libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libXrender-devel
    ;;
nixos)
    if [ "$(env | grep X11 -c)" -lt 3 ]; then
        nix develop
    fi
    ;;
*)
    echo "Unsupported OS"
    exit 1
    ;;
esac
