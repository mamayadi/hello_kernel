obj-m += module1.o
default:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
