#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/interrupt.h>

#define DRIVER_NAME "test_pci_driver"

static const struct pci_device_id pci_eth_device_tbl[] = {
	{ PCI_DEVICE(0x8086, 0x100e) },
	{ 0, }
};

MODULE_DEVICE_TABLE(pci, pci_eth_device_tbl);

struct net_device *netdev;
struct pci_dev *pci_device;
void __iomem *bar0_base;

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

	int err;

	err = pcim_enable_device(dev);
	if (err) {
	    pr_err(DRIVER_NAME ": Failed to enable PCI device: %d\n", err);
	    return err;
	}

	pci_set_master(dev);

	bar0_base = pci_iomap(dev, 0, 0);
	if (!bar0_base) {
	    pr_err(DRIVER_NAME ": Failed to map BAR0\n");
	    return -ENOMEM;
	}
	pci_device = dev;

	const int len = pci_resource_len(dev, 0);

	int j;
	
	for (int i = 0; i < len; i++) {
	    if (ioread8(bar0_base + i) == 0x70) {
		pr_info(DRIVER_NAME ": MAC found at offset %d\n", i);
		for (j = 0; j < 6; j++) {
		    pr_info(DRIVER_NAME ": MAC %02x:%02x:%02x:%02x:%02x:%02x\n",
		           ioread8(bar0_base + i),
		           ioread8(bar0_base + i + 1),
		           ioread8(bar0_base + i + 2),
		           ioread8(bar0_base + i + 3),
		           ioread8(bar0_base + i + 4),
		           ioread8(bar0_base + i + 5));
		}
		break;
	    }
}

	return 0;
}

static void pci_driver_remove(struct pci_dev *dev)
{
    pr_info(DRIVER_NAME ": unregistered\n");
    if (bar0_base) {
        pci_iounmap(dev, bar0_base);
        bar0_base = NULL;
    }
    if (netdev) {
        unregister_netdev(netdev);
        free_netdev(netdev);
        netdev = NULL;
    }
    pci_device = NULL;
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

