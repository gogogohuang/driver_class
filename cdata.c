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
#include <linux/slab.h>
#include <linux/ioctl.h>
#include "cdata_def.h"

/*define*/
#define DEV_MAJOR   123
#define DEV_NAME    "cdata"
#define DEV_IOCTLID 0xD0
#define IOCTL_WRITE _IOW(DEV_IOCTLID, 1, int)
#define IOCTL_SetName _IOWR(DEV_IOCTLID, 2, int)

static char *buf;

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

static ssize_t cdata_write(struct file *flip, char * fp, loff_t * loff ){
    printk(KERN_INFO "write CDATA  data\n");
    return 0;
}


static int cdata_close(struct inode *inode, struct file * flip){
    printk(KERN_INFO "close CDATA\n");
    return 0;
}

static int cdata_ioctl(struct file * flip, unsigned int cmd, unsigned long arg){
    switch (cmd) {
        case IOCTL_WRITE:
            printk(KERN_INFO "IOCTL_WRITE arg = s d\n", (char *)arg);
            return 0;

        case IOCTL_SetName:
            if(strlen((char *)arg) > LEN_OF_NAME){
                printk(KERN_ALERT "the length is over %d \n",LEN_OF_NAME);
                return -EFAULT;
            }
            /*check memory is valid or invalid*/ 
            if(copy_from_user(buf, (char *)arg, LEN_OF_NAME)){
                printk(KERN_ALERT "can not copy data from user\n");
                return -EFAULT; 
            }
            printk(KERN_INFO "IOCTL_SetName Name = %s\n", buf);
            return 0;

        default:
            printk(KERN_INFO "No IOCTL Command \n");
            return -ENOTTY;
    }
    return 0;
}

struct file_operations cdata_fops = {	
    owner:      THIS_MODULE,
    open:		cdata_open,
    read:       cdata_read,
    write:      cdata_write,
    release:    cdata_close,
    unlocked_ioctl:      cdata_ioctl,
};

/*module init*/
int cdata_init_module(void)
{
    printk(KERN_INFO "CDATA V1.0 \n");
    buf = (char *)kmalloc(LEN_OF_NAME, GFP_KERNEL);
    if(register_chrdev(DEV_MAJOR, DEV_NAME, &cdata_fops) < 0){
        printk(KERN_ALERT "can not register this devie\r\n");
        return -1;
    }
    printk(KERN_INFO "register CDATA \n");
    return 0;
}

void cdata_cleanup_module(void)
{
    printk(KERN_INFO "unregister CDATA \n");
    kfree(buf);
    unregister_chrdev(DEV_MAJOR,DEV_NAME);

}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
