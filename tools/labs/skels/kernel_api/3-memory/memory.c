/*
 * SO2 lab3 - task 3
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/list.h>

MODULE_DESCRIPTION("Memory processing");
MODULE_AUTHOR("SO2");
MODULE_LICENSE("GPL");

struct task_info {
	pid_t pid;
	unsigned long timestamp;
};

static struct task_info *ti1, *ti2, *ti3, *ti4;

static struct task_info *task_info_alloc(int pid)
{
	struct task_info *ti;

	/* TODO 1: allocated and initialize a task_info struct */

	ti = (struct task_info *)kmalloc(sizeof(struct task_info), GFP_KERNEL);	
	ti->pid = pid;

	ti->timestamp = jiffies; // need readlock? 

	return ti;
}

static int memory_init(void)
{
	struct task_struct *nextProc;
	struct task_struct *nextnextProc;

	/* TODO 2: call task_info_alloc for current pid */
	ti1 = task_info_alloc(current->pid);
	
	/* TODO 2: call task_info_alloc for parent PID */
	ti2 = task_info_alloc(current->parent->pid);

	/* TODO 2: call task_info alloc for next process PID */
	/*커널 링크드 리스트 공부하고 여기 풀기 */

	nextProc = next_task(current->parent);
	ti3 = task_info_alloc(nextProc->pid);

	/* TODO 2: call text_info_alloc for next process of the next process */
	nextnextProc = next_task(nextProc);
	ti4 = task_info_alloc(nextnextProc->pid);

	printk("ti1 pid = %d timestamp = %lu\n", ti1->pid, ti1->timestamp);
	printk("ti2 pid = %d timestamp = %lu\n", ti2->pid, ti2->timestamp);
	printk("ti3 pid = %d timestamp = %lu\n", ti3->pid, ti3->timestamp);
	printk("ti4 pid = %d timestamp = %lu\n", ti4->pid, ti4->timestamp);
	
	return 0;
}

static void memory_exit(void)
{

	/* TODO 3: print ti* field values */

	/* TODO 4: free ti* structures */
}

module_init(memory_init);
module_exit(memory_exit);
