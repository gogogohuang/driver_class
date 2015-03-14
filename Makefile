obj-m := cdata.o

#depene on ur running linux kernel
KDIR := /usr/src/linux-headers-3.8.0-44-generic
PWD := $(shell pwd)

default:
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
		
clean:
		rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c
