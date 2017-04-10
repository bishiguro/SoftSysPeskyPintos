#!/bin/bash

# This script has the first part of Pintos setup.
# Modified from commands in https://github.com/JohnStarich/docker-pintos/blob/master/Dockerfile ,
# https://pintosiiith.wordpress.com/2012/09/13/install-pintos-with-qemu/

# Install dependencies/useful tools
apt-get install -y --no-install-recommends \
    coreutils \
    gcc clang make \
    gdb ddd \
    manpages-dev \
    ncurses-dev \
    qemu \
    wget \
    xorg openbox

# change into home directory (install is here for this example)
echo "Installing in home directory."
cd ~/

# Download compressed Pintos files
curl -o pintos.tar.gz -L http://www.stanford.edu/class/cs140/projects/pintos/pintos.tar.gz
echo "Download complete."

# Extract files
tar -xzf pintos.tar.gz
echo "Extraction complete."

# This line might cause some errors if permissions aren't set up correctly.
#It copies everything in src into pintos.

echo "Move files, check permissions if this fails."
mv ./pintos/src /pintos


# Remove compressed file
rm -rf ./pintos.tar.gz ./pintos

echo "Add utils to environment variables. Change /.bashrc to add it to path every session."
ENV PATH=$HOME/pintos/utils:$PATH

# Configure Pintos for QEMU
sed -i 's/bochs/qemu/' $HOME/pintos/*/Make.vars

# Compile Pintos kernel
echo "Compile pintos kernel."
cd $HOME/pintos/threads && make

# Reconfigure Pintos to use QEMU

sed -i 's/\/usr\/class\/cs140\/pintos\/pintos\/src/\/pintos/' $HOME/pintos/utils/pintos-gdb
sed -i 's/LDFLAGS/LDLIBS/' $HOME/pintos/utils/Makefile
sed -i 's/\$sim = "bochs"/$sim = "qemu"/' $HOME/pintos/utils/pintos
sed -i 's/kernel.bin/\/pintos\/threads\/build\/kernel.bin/' $HOME/pintos/utils/pintos
sed -i "s/my (@cmd) = ('qemu');/my (@cmd) = ('qemu-system-x86_64');/" $HOME/pintos/utils/pintos
sed -i 's/loader.bin/\/pintos\/threads\/build\/loader.bin/' $HOME/pintos/utils/Pintos.pm

# Replace incorrect paths (Possibly revise with s flag)
# Fix the path to the utilities (kernel)
sed -i '/kernel.bin/c\my $name = find_file ('$HOME\/pintos\/threads\/build\/kernel.bin');' $HOME/pintos/utils/pintos

# Fix the path to the loader
sed -i '/loader.bin/c\$name = find_file ('$HOME\/pintos\/threads\/build\/loader.bin') if !defined $name;' $HOME/pintos/utils/Pintos.pm

# Fix ACPI bug
# Fix described here under "Troubleshooting": http://arpith.xyz/2016/01/getting-started-with-pintos/
sed -i '/serial_flush ();/a outw( 0x604, 0x0 | 0x2000 );' /pintos/devices/shutdown.c
