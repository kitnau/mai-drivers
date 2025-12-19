


```
┌──(kali㉿kali)-[~/develop/kernel/pz4]
└─$ make      
make -C /lib/modules/6.16.8+kali-amd64/build M=/home/kali/develop/kernel/pz4 modules
make[1]: Entering directory '/usr/src/linux-headers-6.16.8+kali-amd64'
make[2]: Entering directory '/home/kali/develop/kernel/pz4'
  CC [M]  aut_driver.o
  MODPOST Module.symvers
WARNING: modpost: missing MODULE_DESCRIPTION() in aut_driver.o
  CC [M]  aut_driver.mod.o
  CC [M]  .module-common.o
  LD [M]  aut_driver.ko
  BTF [M] aut_driver.ko
make[2]: Leaving directory '/home/kali/develop/kernel/pz4'
make[1]: Leaving directory '/usr/src/linux-headers-6.16.8+kali-amd64'
gcc usrapp.c -o usrapp
                                                                                                           
┌──(kali㉿kali)-[~/develop/kernel/pz4]
└─$ sudo insmod aut_driver.ko
                                                                                                           
┌──(kali㉿kali)-[~/develop/kernel/pz4]
└─$ ./usrapp
open write err -1
                                                                                                           
┌──(kali㉿kali)-[~/develop/kernel/pz4]
└─$ ./usrapp.c
zsh: permission denied: ./usrapp.c
                                                                                                           
┌──(kali㉿kali)-[~/develop/kernel/pz4]
└─$ sudo ./usrapp            
Written "Test write" to dev
fdread: "Test "
Buffer is empty: false
Buffer is empty after DRIVER_CLEAR_BUF: true
```                                                                                                           
┌──(kali㉿kali)-[~/develop/kernel/pz4]
└─$ 
