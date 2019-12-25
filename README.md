# hello_kernel
A small module to print hello world from the kernel in lunix

    git clone https://github.com/mamayadi/hello_kernel.git
    cd hello_kernel
    1  make
    2  sudo insmod module1.ko
    3  dmesg
    4  lsmod
    5  sudo mknod /dev/testpilote c 52 0
    6  sudo chmod 777 /dev/testpilote
    7  sudo echo Hello World > /dev/testpilote
    8  dmesg
    9  sudo rmmod module1
    10  dmesg
