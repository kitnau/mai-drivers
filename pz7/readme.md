# Задание
1) Добавить драйвер из 6 пз (net + pci) в ядро, чтобы он был виден в make menuconfig
2) Создать патч

# Добавление драйвера в ядро

Перейти в папку ethernet драйверов:

```
cd ~/develop/kernel/pz7/linux/drivers/net/ethernet
```
Создать папку для хранения нового драйвера, поместить в неё файл драйвера, Makefile и создать Kconfig, чтобы драйвер был виден в GUI у make menuconfig.
Добавить в Kconfig и Makefile каталога ethernet ссылки на соответствующие файлы самого драйвера, чтобы он появился в отображении каталога настроек ethernet.


# Видимость файла в make menuconfig

Из папки, куда склонировано ядро:
```
┌──(kali㉿kali)-[~/develop/kernel/pz7/linux]
└─$ make menuconfig
```

Далее пройтись по меню до следующего пункта:
```
Device drivers ->

-> Network device supprot ->

-> Ethernet driver supprot ->

-> Test PCI network driver 
```

```
──────────────────────────────────────── Ethernet driver support ──────────────────────────────────────────┐   
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty submenus ----).  Highlighted       │   
  │  letters are hotkeys.  Pressing <Y> includes, <N> excludes, <M> modularizes features.  Press <Esc><Esc> to │   
  │  exit, <?> for Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < > module capable   │   
  │                                                                                                            │   
  │ ┌─────────────────↑(-)───────────────────────────────────────────────────────────────────────────────────┐ │   
  │ │                 <M>     STMicroelectronics Multi-Gigabit Ethernet driver                               │ │   
  │ │                 [ ]       Support for STMMAC Selftests                                                 │ │   
  │ │                 <M>       STMMAC Platform bus support                                                  │ │   
  │ │                 <M>         Generic driver for DWMAC                                                   │ │   
  │ │                 <M>       Intel GMAC support                                                           │ │   
  │ │                 < >       STMMAC PCI bus support                                                       │ │   
  │ │                 [*]   Sun devices                                                                      │ │   
  │ │                 <M>     Sun Happy Meal 10/100baseT support                                             │ │   
  │ │                 <M>     Sun GEM support                                                                │ │   
  │ │                 <M>     Sun Cassini support                                                            │ │   
  │ │                 <M>     Sun Neptune 10Gbit Ethernet support                                            │ │   
  │ │                 [*]   Synopsys devices                                                                 │ │   
  │ │                 < >     Synopsys DWC Enterprise Ethernet (XLGMAC) driver support                       │ │   
  │ │                 [*]   Tehuti devices                                                                   │ │   
  │ │                 <M>     Tehuti Networks 10G Ethernet                                                   │ │   
  │ │                 < >     Tehuti Networks TN40xx 10G Ethernet adapters                                   │ │   
  │ │                 [*]   Texas Instruments (TI) devices                                                   │ │   
  │ │                 [ ]     TI CPSW Phy mode Selection (DEPRECATED)                                        │ │   
  │ │                 <M>     TI ThunderLAN support                                                          │ │   
  │ │                 [*]   Vertexcom devices                                                                │ │   
  │ │                 < >     Vertexcom MSE102x SPI                                                          │ │   
  │ │                 [*]   VIA devices                                                                      │ │   
  │ │                 <M>     VIA Rhine support                                                              │ │   
  │ │                 [ ]       Use MMIO instead of PIO                                                      │ │   
  │ │                 <M>     VIA Velocity support                                                           │ │   
  │ │                 [*]   Wangxun devices                                                                  │ │   
  │ │                 < >     Wangxun(R) GbE PCI Express adapters support                                    │ │   
  │ │                 < >     Wangxun(R) 10/25/40GbE PCI Express adapters support                            │ │   
  │ │                 < >     Wangxun(R) 10/25/40G Virtual Function Ethernet support                         │ │   
  │ │                 < >     Wangxun(R) GbE Virtual Function Ethernet support                               │ │   
  │ │                 [*]   WIZnet devices                                                                   │ │   
  │ │                 < >     WIZnet W5100 Ethernet support                                                  │ │   
  │ │                 < >     WIZnet W5300 Ethernet support                                                  │ │   
  │ │                 [*]   Xilinx devices                                                                   │ │   
  │ │                 < >     Xilinx 10/100 Ethernet Lite support                                            │ │   
  │ │                 < >     Xilinx LL TEMAC (LocalLink Tri-mode Ethernet MAC) driver                       │ │   
  │ │                 [*]   Xircom devices                                                                   │ │   
  │ │                 <M>     Xircom 16-bit PCMCIA support                                                   │ │   
  │ │                 <*>   Test PCI network driver                                                          │ │   
  │ └────────────────────────────────────────────────────────────────────────────────────────────────────────┘ │   
  ├────────────────────────────────────────────────────────────────────────────────────────────────────────────┤   
  │                          <Select>    < Exit >    < Help >    < Save >    < Load >                          │   
  └────────────────────────────────────────────────────────────────────────────────────────────────────────────┘   
          
```

# Создание патча
Создание гита будучи в папке ~/develop/kernel/pz7/linux/drivers/net/ethernet. Для этого его надо инициализировать и добавить ссылки на измененные папки.
```
git init
git add drivers/net/ethernet/testpci
git add drivers/net/ethernet/Kconfig
git add drivers/net/ethernet/Makefile
git commit -m "pz7"
git format-patch -1 HEAD
```
