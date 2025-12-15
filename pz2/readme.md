#Сборка модуля
Сборка при помощи команды make.

```
┌└─$ make
make -C /lib/modules/6.16.8+kali-amd64/build/ M=/home/kali/develop/kernel/pz2 modules
make[1]: Entering directory '/usr/src/linux-headers-6.16.8+kali-amd64'
make[2]: Entering directory '/home/kali/develop/kernel/pz2'
  CC [M]  simple.o
  MODPOST Module.symvers
  CC [M]  simple.mod.o
  LD [M]  simple.ko
  BTF [M] simple.ko
make[2]: Leaving directory '/home/kali/develop/kernel/pz2'
make[1]: Leaving directory '/usr/src/linux-headers-6.16.8+kali-amd64'
                                                        
```

#Загрузка модуля

```
┌──(kali㉿kali)-[~/develop/kernel/pz2]
└─$ sudo insmod simple.ko
```

#Проверить модуль ядра

```
┌──(kali㉿kali)-[~/develop/kernel/pz2]
└─$ lsmod | grep simple
simple                 12288  0
```
```
┌──(kali㉿kali)-[~/develop/kernel/pz2]
└─$ dmesg | tail -10
[  922.270670] 06:37:56.245876 X11 events  RRScreenChangeNotify event received
[  922.271098] 06:37:56.246313 X11 events  Monitor 0 (w,h)=(1920,1075) (x,y)=(0,0)
[  922.271258] 06:37:56.246406 X11 events  Sending monitor positions (8 of them)  to the host: VINF_SUCCESS
[  922.272765] 06:37:56.247945 X11 events  received X11 event (89)
[  922.273020] 06:37:56.248241 X11 events  RRScreenChangeNotify event received
[  922.277805] 06:37:56.252990 X11 events  Monitor 0 (w,h)=(1920,1075) (x,y)=(0,0)
[  922.277921] 06:37:56.253121 X11 events  Sending monitor positions (8 of them)  to the host: VINF_SUCCESS
[ 1058.197584] simple: loading out-of-tree module taints kernel.
[ 1058.197589] simple: module verification failed: signature and/or required key missing - tainting kernel
[ 1058.205352] Hello from the mai 307 team
```


#Удаление модуля

```                                                                                                                 
┌──(kali㉿kali)-[~/develop/kernel/pz2]
└─$ sudo rmmod simple    
                                                                                                                    
┌──(kali㉿kali)-[~/develop/kernel/pz2]
└─$ lsmod | grep simple
```
