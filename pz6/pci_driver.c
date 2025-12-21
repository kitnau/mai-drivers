#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#define DRIVER_NAME "test_pci_driver"

static const struct pci_device_id pci_eth_device_tbl[] = {
	{ PCI_DEVICE(0x8086, 0x100e) },
	{ 0, }
};

MODULE_DEVICE_TABLE(pci, pci_eth_device_tbl);

struct net_device *netdev;

static int demo_nic_open(struct net_device *dev)
{
	pr_info(DRIVER_NAME ": open\n");
	return 0;
}

static int demo_nic_release(struct net_device *dev)
{
	pr_info(DRIVER_NAME ": release\n");
	netif_stop_queue(dev);
	return 0;
}

static int demo_nic_xmit(struct sk_buff *skb, struct net_device *dev)
{
	pr_info(DRIVER_NAME ": xmit\n");

	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;

	pr_info(DRIVER_NAME ": %pTN<struct sk_buff>\n", (void *)skb);
	pr_info(DRIVER_NAME
		": Packet info - Len: %u, Head: %p, Data: %p, Tail: %d, End: %d\n",
		skb->len, (void *)skb->head, (void *)skb->data, skb->tail,
		skb->end);

	pr_info(DRIVER_NAME ": First %d bytes:\n", skb->len);
	pr_info(DRIVER_NAME ": Hex: ");
	for (uint i = 0; i < skb->len; i++) {
		pr_cont("%02x ", skb->data[i]);
	}
	pr_cont("\n");

	pr_info(DRIVER_NAME ": Chr: ");
	for (uint i = 0; i < skb->len; i++) {
		pr_cont("%c ", skb->data[i]);
	}
	pr_cont("\n");

	dev_kfree_skb(skb);
	return 0;
}

static int demo_nic_init(struct net_device *dev)
{
	pr_info(DRIVER_NAME ": net device initialized\n");

	return 0;
};

const struct net_device_ops ops = {
	.ndo_init = demo_nic_init,
	.ndo_open = demo_nic_open,
	.ndo_stop = demo_nic_release,
	.ndo_start_xmit = demo_nic_xmit,
};

static int pci_driver_probe(struct pci_dev *dev, const struct pci_device_id *ent)
{
	int result;

	netdev = alloc_etherdev(0);
        strcpy(netdev->name, "demo0");
	netdev->netdev_ops = &ops;

	if ((result = register_netdev(netdev))) {
		pr_err(DRIVER_NAME ": net dev register failed: %d", result);
		return result;
	}

	const unsigned long port_addr = pci_resource_start(dev, 0);
	const int len = pci_resource_len(dev, 0);

	u8 *mapped_ptr = ioremap(port_addr, len);

	int j = 0;
	const unsigned char *const ptr = mapped_ptr;
	for (int i = 0; i < len; i++) {
		if (ptr[i] == 0x70) {
			printk(KERN_INFO "offset = %d", i);
			for (j = 0; j < 6; j++) {
				printk(KERN_INFO "MAC %x %x %x %x %x %x \n",
				       (unsigned)ptr[i], (unsigned)ptr[i + 1],
				       (unsigned)ptr[i + 2],
				       (unsigned)ptr[i + 3],
				       (unsigned)ptr[i + 4],
				       (unsigned)ptr[i + 5]);
			}
		}
	}

	iounmap(mapped_ptr);

	return 0;
}

static void pci_driver_remove(struct pci_dev *dev)
{
	pr_info(DRIVER_NAME ": unregistered\n");
	if (netdev) {
		unregister_netdev(netdev);
		free_netdev(netdev);
		netdev = NULL;
	}
}

static struct pci_driver pci_driver = {
	.name = DRIVER_NAME,
	.id_table = pci_eth_device_tbl,
	.probe = pci_driver_probe,
	.remove = pci_driver_remove,
};
module_pci_driver(pci_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test PCI network driver");

