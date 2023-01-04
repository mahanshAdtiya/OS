#include <linux/init.h> 
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h> 
#include <linux/syscalls.h> 
#include <linux/sched.h>  

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahansh"); 

int pid = 0;
module_param(pid, int, 0);

static int __init minit(void){
    struct task_struct *structure;
    structure = pid_task(find_vpid(pid), PIDTYPE_PID);
    printk(KERN_INFO "Process name  : %s\n", structure->comm);
    printk(KERN_INFO "Process Group ID : %d\n", structure->group_leader->pid);
    printk(KERN_INFO "User ID: %d\n", structure->cred->uid.val);
    printk(KERN_INFO "Process Identifier : %d\n", structure->pid);
    return 0;
}

static void __exit mexit(void){
    printk(KERN_INFO "Module Exit \n");
}

module_init(minit);
module_exit(mexit);