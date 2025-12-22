```
┌──(kali㉿kali)-[~/develop/kernel/pz8]
└─$ sudo ip link set demo0 up
ping -c 1 8.8.8.8 -I demo0

ping: Warning: source address might be selected on device other than: demo0
PING 8.8.8.8 (8.8.8.8) from 0.0.0.0 demo0: 56(84) bytes of data.

--- 8.8.8.8 ping statistics ---
1 packets transmitted, 0 received, 100% packet loss, time 0ms

                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz8]
└─$ lsmod | grep pci_driver
ip a | grep demo0

pci_driver             12288  0
6: demo0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UNKNOWN group default qlen 1000

```
