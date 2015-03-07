#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>

/*define*/
#define DEV_MAJOR   123
#define DEV_NAME    "cdata"
#define DEV_IOCTLID 0xD0
#define IOCTL_WRITE _IOW(DEV_IOCTLID, 1, int)


/*fop implementation*/
static int cdata_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "open CDATA file = %p \n", filp);
    /*if(MINOR(inode->i_rdev) != 0){*/
        /*printk("error minor number\n");*/
        /*return -ENODEV;*/
    /*}*/
	return 0;
}
static ssize_t cdata_read(struct file *flip, char * fp, loff_t * loff ){
    printk(KERN_INFO "read CDATA  data\n");
    return 0;
}

static int cdata_close(struct inode *inode, struct file * flip){
    printk(KERN_INFO "close CDATA\n");
    return 0;
}

static int cdata_ioctl(struct file * flip, unsigned int cmd, unsigned long arg){
    switch (cmd) {
        case IOCTL_WRITE:
            printk(KERN_INFO "IOCTL_WRITE arg = %d\n", arg);
            break;
        default:
            printk(KERN_INFO "default arg = %d \n", arg);
            return -1;
    }
    return 0;
}

struct file_operations cdata_fops = {	
    owner:      THIS_MODULE,
    open:		cdata_open,
    read:       cdata_read,
    release:    cdata_close,
    unlocked_ioctl:      cdata_ioctl,
};

/*module init*/
int cdata_init_module(void)
{
    printk(KERN_INFO "CDATA V1.0 \n");

    if(register_chrdev(DEV_MAJOR, DEV_NAME, &cdata_fops) < 0){
        printk(KERN_ALERT "can not register this devie\r\n");
        return -1;
    }
    return 0;
}

void cdata_cleanup_module(void)
{
    printk(KERN_INFO "CDATA V1.0 clean \n");
    unregister_chrdev(DEV_MAJOR,DEV_NAME);

}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
