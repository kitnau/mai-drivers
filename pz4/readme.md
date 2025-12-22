# Создать символьный драйвер, который будет автоматически создавать спец файл устройства
```
static int __init aut_init(void) {
	int res = 0;

	res = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);
    if (res < 0) {
        pr_err(DEVICE_NAME ": failed to allocate device numbers with error %d\n", res);
        return res;
    }

    cdev_init(&dev, &fops);
    dev.owner = THIS_MODULE;

	res = cdev_add(&dev, dev_no, 1);
    if (res < 0) {
        pr_err(DEVICE_NAME ": failed to add character device with error %d\n", res);
        unregister_chrdev_region(dev_no, 1);
        return res;
    }

	dev_class = class_create(CLASS_NAME);
    if (IS_ERR(dev_class)) {
        pr_err(DEVICE_NAME ": failed to create device class\n");
        res = PTR_ERR(dev_class);
        cdev_del(&dev);
        unregister_chrdev_region(dev_no, 1);
        return res;
    }

	device = device_create(dev_class, NULL, dev_no, NULL, DEVICE_NAME);
    if (IS_ERR(device)) {
        pr_err(DEVICE_NAME ": Failed to create device node\n");
        res = PTR_ERR(device);
        class_destroy(dev_class);
        cdev_del(&dev);
        unregister_chrdev_region(dev_no, 1);
        return res;
    }

	pr_info(DEVICE_NAME ": registered %s\n", DEVICE_NAME);
	return SUCCESS;
}
```

# Реализовать чтение и запись в глобальный буфер
```
static ssize_t device_read(struct file* flip, char __user* user_buf, size_t count, loff_t* offset) 
static ssize_t device_write(struct file* flip, const char __user* user_buf, size_t count, loff_t* offset)
```

# Реализовать ioctl для сброса содержимого буфера и получения информации чист ли буфер
```
#include <linux/ioctl.h>

#define DRIVER_IOCTLID 0x11

#define DRIVER_BUF_IS_EMPTY _IOR(DRIVER_IOCTLID, 1, int)
#define DRIVER_CLEAR_BUF _IO(DRIVER_IOCTLID, 0)
```

# Проверка 

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
└─$ sudo ./usrapp            
Written "Test write" to dev
fdread: "Test "
Buffer is empty: false
Buffer is empty after DRIVER_CLEAR_BUF: true
```               
