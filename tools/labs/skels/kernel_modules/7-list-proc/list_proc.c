#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("List current processes");
MODULE_AUTHOR("Kernel Hacker");
MODULE_LICENSE("GPL");

static int my_proc_init(void)
{
	struct task_struct *p;
    p = current; 

	/* TODO: print current process pid and its name */

	//char				comm[TASK_COMM_LEN];

	pr_info("pid is %d\n", p->pid);
	pr_info("name is %s\n", p->comm);
	/* TODO: print the pid and name of all processes */

	
	return 0;
}

static void my_proc_exit(void)
{
	/* TODO: print current process pid and name */
}

module_init(my_proc_init);
module_exit(my_proc_exit);
