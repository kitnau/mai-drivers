```
┌──(kali㉿kali)-[~/develop/kernel/pz6]
└─$ lspci -k | grep -A3 "00:03.0"
00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)
        Subsystem: Intel Corporation PRO/1000 MT Desktop Adapter
        Kernel driver in use: test_pci_driver
        Kernel modules: e1000
                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz6]
└─$ dmesg | tail -10 | grep test_pci_driver
                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz6]
└─$ dmesg | grep test_pci_driver           
[ 5910.309708] test_pci_driver: net device initialized
[ 5910.333220] test_pci_driver: open
[ 5981.196308] test_pci_driver: unregistered
[ 5981.196646] test_pci_driver: release
[ 5981.333447] test_pci_driver: net device initialized
[ 5981.355126] test_pci_driver: open
```
