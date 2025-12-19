obj-m += aut_driver.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc usrapp.c -o usrapp

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm usrapp
