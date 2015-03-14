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
#include <linux/wait.h>
#include "cdata_ioctl.h"

/*define*/
#define DEV_MAJOR   123
#define DEV_NAME    "cdata"
#define DEV_IOCTLID 0xD0

struct string_cdata{
    char    *buf;
    int     idx;
    wait_queue_head_t wq;
    struct timer_list cdata_timer;
};

void flush_buffer(void *priv);

/*fop implementation*/
static int cdata_open(struct inode *inode, struct file *filp)
{   
    struct string_cdata *cd_string;
    /*initialize*/
    cd_string = (struct string_cdata*)kmalloc(sizeof(struct string_cdata), GFP_KERNEL);
    cd_string->buf = (char *)kmalloc(LEN_OF_NAME, GFP_KERNEL);
    cd_string->idx = 0;
    init_waitqueue_head(&cd_string->wq);
    init_timer(&cd_string->cdata_timer);
         
    filp->private_data = (void *)cd_string;
    
    printk(KERN_INFO "open CDATA file = %p \n", filp);
    if(MINOR(inode->i_rdev) != 0){
        printk("error minor number\n");
        return -ENODEV;
    }
	return 0;
}
static ssize_t cdata_read(struct file *flip, const char * buf, size_t size, loff_t * off ){
    printk(KERN_INFO "read CDATA  data\n");
    return 0;
}

void flush_buffer(void *priv){
    printk(KERN_ALERT "flush buffer and wake up AP\n");
    struct string_cdata *buf = (struct string_cdata*)priv;
    buf->idx = 0;
    wake_up(&buf->wq);
}

//process context
static ssize_t cdata_write(struct file *flip, const char *buf, size_t size, loff_t * off ){
    struct string_cdata *ioctl_string = (struct string_cdata*)flip->private_data;
    int idx,i;
    int retval;
    idx = ioctl_string -> idx;
    struct timer_list *timer = &ioctl_string->cdata_timer;
    DECLARE_WAITQUEUE(wait, current); //current is global variable, pointer to process.

    printk(KERN_INFO "write CDATA  data\n");
    
    for(i=0; i<size; i++){
        if(idx>=LEN_OF_NAME){
            printk(KERN_ALERT "buffer full \n");
            
            timer->expires = jiffies +  KERNEL_DELAY_TIMER;
            timer->data =(unsigned long) ioctl_string;
            timer->function = flush_buffer;
           
            add_timer(timer);
            //interruptible_sleep_on
            //----------------------------------------------------
            /*For multi-core, or it will happen race condition*/
            add_wait_queue(&ioctl_string->wq, &wait);
            set_current_state(TASK_INTERRUPTIBLE);
            schedule();
            /*wake_up(&wp) will chagne current state. so we did not change it by ourselves*/
            //set_current_state(TASK_RUNNING);
            remove_wait_queue(&ioctl_string->wq, &wait);
            //---------------------------------------------------
            
            idx = ioctl_string->idx; // buffer clean up, so read idx back to local variable.
        }

        copy_from_user(&ioctl_string->buf[idx], &buf[idx], 1);
        idx++;    

        /*if(idx < LEN_OF_NAME){*/
            /*if(copy_from_user(&ioctl_string->buf[idx++], &buf[idx], 1)){*/
                /*printk(KERN_ALERT "can not copy data from user\n");*/
                /*return -EFAULT;*/
            /*}*/
        /*}else{*/
            /*printk(KERN_ALERT "buffer full\n");*/

            /*Here do kernel scheduling*/
           
            /*interruptible_sleep_on(&ioctl_string->wq);*/
           
            /*Here flush buffer*/
            /*flush_buffer(flip->private_data);*/

            
            /*idx = ioctl_string->idx; // buffer clean up, so read idx back to local variable.*/
            /*printk("idx = %d \n",idx);*/
            /*flush_buffer(cdata);*/
            /*idx = 0;*/
            /*memset(ioctl_string->buf, 0, LEN_OF_NAME);*/
        }
    /*}*/
    /*printk(KERN_INFO "idx = %d \n",idx);*/
    /*set \0*/            
    ioctl_string->buf[idx] = '\0';
    ioctl_string->idx = idx;
    flip->private_data = (void *)ioctl_string;
    //printk(KERN_INFO "IOCTL_SetName Name_priv = %s index = %d \n", ioctl_string->buf, ioctl_string->idx);
    return 0;
}


static int cdata_close(struct inode *inode, struct file * flip){
    struct string_cdata *ioctl_string = (struct string_cdata*)flip->private_data;
    printk(KERN_INFO "close CDATA name = %s\n", ioctl_string->buf);
    return 0;
}

static int cdata_ioctl(struct file * flip, unsigned int cmd, unsigned long arg){
    struct string_cdata *ioctl_string; 
    ioctl_string = (struct string_cdata *)flip->private_data; 
    int idx ;
    idx = ioctl_string->idx;
    
    switch (cmd) {
        case IOCTL_Init:
            printk(KERN_INFO "IOCTL_Init\n");
            return 0;
        
        case IOCTL_WRITE:
            printk(KERN_INFO "IOCTL_WRITE \n");
            return 0;

        case IOCTL_SetAll:
            if(idx > LEN_OF_NAME){
                printk(KERN_ALERT "the length is over %d \n",LEN_OF_NAME);
                return -EFAULT;
            }
            /*check memory is valid or invalid*/ 
            if(copy_from_user(&ioctl_string->buf[idx++], (char *)arg, strlen((char *)arg))){
                printk(KERN_ALERT "can not copy data from user\n");
                return -EFAULT;
            }
            /*set \0*/            
            ioctl_string->buf[idx++] = '\0';
            ioctl_string->idx = idx;
            flip->private_data = (void *)ioctl_string;
            //printk(KERN_INFO "IOCTL_SetName Name_priv = %s index = %d \n", ioctl_string->buf, ioctl_string->idx);
            return 0;


        case IOCTL_SetName:
            if(ioctl_string->idx > LEN_OF_NAME){
                printk(KERN_ALERT "the length is over %d \n",LEN_OF_NAME);
                return -EFAULT;
            }
            /*check memory is valid or invalid*/ 
            if(copy_from_user(&ioctl_string->buf[idx++], (char *)arg, 1)){
                printk(KERN_ALERT "can not copy data from user\n");
                return -EFAULT;
            }
            /*set \0*/            
            ioctl_string->buf[idx] = '\0';
            ioctl_string->idx = idx;
            flip->private_data = (void *)ioctl_string;
            //printk(KERN_INFO "IOCTL_SetName Name_priv = %s index = %d \n", ioctl_string->buf, ioctl_string->idx);
            return 0;

        case IOCTL_EmptyName:
            printk(KERN_INFO "IOCTL_EmptyName\n");
            memset(ioctl_string->buf, 0 , LEN_OF_NAME);
            idx = 0;
            ioctl_string->idx = idx;
            return 0;
        
        case IOCTL_SyncName:
            printk(KERN_INFO "IOCTL_SyncName\n");
            copy_to_user((char *)arg , ioctl_string->buf,  ioctl_string->idx+1);
            flip->private_data = ioctl_string;
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
    unregister_chrdev(DEV_MAJOR,DEV_NAME);

}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
