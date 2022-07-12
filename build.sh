#!/usr/bin/env bash

make clean
make clean target=win32
make clean target=win64

make
make target=win32
make target=win64

make -C demo clean
make -C demo clean target=win32
make -C demo clean target=win64

make -C demo
make -C demo target=win32
make -C demo target=win64
