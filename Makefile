#ubuntu的内核源码树
KERN_VER = $(shell uname -r)
KERN_DIR = /lib/modules/$(KERN_VER)/build	

obj-m	+= module_cx.o

all:
	make -C $(KERN_DIR) M=`pwd` modules 
	gcc APP.c -o APP.out
	insmod module_cx.ko

.PHONY: clean	
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf APP.out file.txt
	rmmod module_cx.ko
