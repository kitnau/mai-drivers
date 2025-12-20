# Загрузка драйвера в систему

```
┌──(kali㉿kali)-[~/develop/kernel/pz5/driver]
└─$ sudo insmod netdemo.ko
┌──(kali㉿kali)-[~/develop/kernel/pz5/driver]
└─$ dmesg | tail -12
[  246.578321] netdemo: module verification failed: signature and/or required key missing - tainting kernel
[  246.587567] demo_nic initialized
[  246.614592] demo_nic open
...
```

# Проверка появления интерфейса
```
┌──(kali㉿kali)-[~/develop/kernel/pz5/driver]
└─$ ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00                                                       
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP mode DEFAULT group default qlen 1000
    link/ether 08:00:27:1f:b7:23 brd ff:ff:ff:ff:ff:ff
4: demo0: <BROADCAST,MULTICAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UNKNOWN mode DEFAULT group default qlen 1000
    link/ether 00:00:00:00:00:00 brd ff:ff:ff:ff:ff:ff
```
# Включение интерфейса
```                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz5/driver]
└─$ sudo ip link set demo0 up
```

# Компиляция программы и запуск
```
┌──(kali㉿kali)-[~/develop/kernel/pz5/app]
└─$ make
gcc -c rawexample.c
gcc -o rawexample rawexample.o
                                                                
┌──(kali㉿kali)-[~/develop/kernel/pz5/app]
└─$ sudo ./rawexample
Success!
```


# Проверка сообщений, выводимых драйвером при обработке пакета
```
┌──(kali㉿kali)-[~/develop/kernel/pz5/driver]
└─$ dmesg | grep testnetdrv
[ 2658.109341] testnetdrv: xmit
[ 2658.109345] testnetdrv: 00000000395334dc<struct sk_buff>
[ 2658.109346] testnetdrv: Packet info - Len: 25, Head: 0000000036b2e39c, Data: 00000000fb88f38d, Tail: 27, End: 384
[ 2658.109348] testnetdrv: First 25 bytes:
[ 2658.109348] testnetdrv: Hex: 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[ 2658.109356] testnetdrv: Hex: \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d
```
```
┌──(kali㉿kali)-[~/develop/kernel/pz5/driver]
└─$ dmesg | tail -1
[ 3527.749241] demo_nic release
```
