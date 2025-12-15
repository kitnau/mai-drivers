# Скомпилировать символьный драйвер
Драйвер находится в файле hello.c

```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ make
make -C /lib/modules/6.16.8+kali-amd64/build M=/home/kali/develop/kernel/pz3 modules
make[1]: Entering directory '/usr/src/linux-headers-6.16.8+kali-amd64'
make[2]: Entering directory '/home/kali/develop/kernel/pz3'
  CC [M]  hello.o
  MODPOST Module.symvers
WARNING: modpost: missing MODULE_DESCRIPTION() in hello.o
  CC [M]  hello.mod.o
  LD [M]  hello.ko
  BTF [M] hello.ko
make[2]: Leaving directory '/home/kali/develop/kernel/pz3'
make[1]: Leaving directory '/usr/src/linux-headers-6.16.8+kali-amd64'
```

# Загрузка модуля
```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ sudo insmod hello.ko
```
```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ lsmod | grep hello 
hello                  12288  0
```

В логах ядра показано, что модуль загрузился
```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ dmesg | tail -1 
[ 3106.220437] Hello world 1.
```
```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ cat /proc/devices | grep foo
244 foo
```

# Создать файл устройства
```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ sudo mknod /dev/foo_device c 244 0                                              
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ sudo chmod 660 /dev/foo_device
```

# Напичать приложение для открытия спец файла устройства
```
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	const char *dev = "/dev/foo_device";
	
	int fd = open(dev, O_RDWR);
	
	if (fd < 0) {
		printf ("failed to open '%s' \n", dev);
		return fd;
	}
	printf ("opened  '%s' device with fd: '%d'", dev, fd);
	
	close(fd);
	
}
```
```
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ gcc -o main main.c                            
                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz3]
└─$ sudo ./main                   
[sudo] password for kali: 
opened  '/dev/foo_device' device with fd: '3'
```
