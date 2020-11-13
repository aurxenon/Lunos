#!/bin/bash

source Toolchain/SourceToolchain.sh &> /dev/null

if [ "$1" == "-debug" ]; then
    qemu-system-i386 -s -S -kernel $LUNOS_DIR/Kernel/bin/LunosKernel -rtc base=localtime -hda hda.txt
elif [ "$1" == "-tests" ]; then
    for test in bin/*; do
        #exec 2> /dev/null
        ./$test
    done
elif [ "$1" == "" ]; then
    qemu-system-i386 -kernel $LUNOS_DIR/Kernel/bin/LunosKernel -rtc base=localtime -hda hda.txt
fi