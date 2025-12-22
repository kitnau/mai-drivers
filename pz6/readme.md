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


┌──(kali㉿kali)-[~/develop/kernel/pz5/app]
└─$ make
gcc -c rawexample.c
gcc -o rawexample rawexample.o
                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz5/app]
└─$ sudo ./rawexample
Success!
                                                        
┌──(kali㉿kali)-[~/develop/kernel/pz5/app]
└─$ dmesg | tail -10
[ 6062.016400] 23:47:24.295061 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6062.017107] 23:47:24.295883 dnd       No guest source window
[ 6062.100672] 23:47:24.378972 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6062.102728] 23:47:24.381480 dnd       No guest source window
[ 6106.436037] test_pci_driver: xmit
[ 6106.436048] test_pci_driver: 0000000071fbdcbb<struct sk_buff>
[ 6106.436049] test_pci_driver: Packet info - Len: 25, Head: 000000003fd69b0b, Data: 000000000cd6e41a, Tail: 27, End: 384
[ 6106.436051] test_pci_driver: First 25 bytes:
[ 6106.436052] test_pci_driver: Hex: 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[ 6106.436059] test_pci_driver: Chr: \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d 

```
