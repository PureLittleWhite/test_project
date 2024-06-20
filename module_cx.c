#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("chenxi");

static long ioctl_demo(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret;
	char* buff;
	
	/* 申请内存空间 */
	buff = kmalloc(200, GFP_KERNEL);
	if (!buff)
	{	
		return -ENOMEM;
		goto out;
	}
		
	/* 将用户态数据存储到申请的内存空间中 */
	if (copy_from_user(buff, (void*)arg, 200))
	{
		return -EFAULT;
		goto out;
	}

	buff = "Hello APPLIC";

	/* 将数据导出到内存空间中 */
	if (copy_to_user((void*)arg, buff, 13))    // 返回数据至用户空间
	{
		ret = -EFAULT;
		goto out;
	}

	/* 释放所申请的内存空间 */
	kfree(buff);
	
out:
	return ret;
}
 
struct file_operations ioctl_ops = {
    .unlocked_ioctl = ioctl_demo,
};
 
static struct miscdevice ioctl_dev = {
    MISC_DYNAMIC_MINOR,
    "ioctl_demo",
    &ioctl_ops,
}; 
 
static int ioctl_mod_init(void)
{
    int ret;
 
    ret = misc_register(&ioctl_dev);
    if (ret) {        
        pr_err("ioctl_demo: misc device register failed\n");
		return -1;
    } 
 
    printk(KERN_ALERT "ioctl module init!\n");
 
    return 0;
}
 
static void ioctl_mod_exit(void)
{
    misc_deregister(&ioctl_dev); 
    printk(KERN_ALERT "ioctl module exit!\n");
}
 
module_init(ioctl_mod_init);
module_exit(ioctl_mod_exit);