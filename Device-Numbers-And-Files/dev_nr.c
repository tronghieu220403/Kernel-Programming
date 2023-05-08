#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hieu GNU/Linux");
MODULE_DESCRIPTION("Register a device nr. and implement some callback function");
MODULE_VERSION("1.0");


/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
} ;

#define MYMAJOR 64

/**
 * @brief This function is called, when the module is loaded into the kernel
 * In Linux, the register_chrdev() function is used to register a character device driver with the kernel. A character device driver is a type of device driver that provides access to devices that transfer data as a stream of characters, such as serial ports and terminals.
 * When a character device driver is registered with the kernel using register_chrdev(), the system creates a device file in the /dev directory that corresponds to the device, and associates the driver's file operations structure with the device file. The file operations structure defines the operations that can be performed on the device file, such as reading and writing data.

 */
static int __init ModuleInit(void) {
	int retval;
	printk("Hello, Kernel!\n");
	/* register device nr. */
	retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);
	// this function is used to regiester a character device driver with the kernel
	if(retval == 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		printk("Could not register device number!\n");
		return -1;
	}
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	unregister_chrdev(MYMAJOR, "my_dev_nr");
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

