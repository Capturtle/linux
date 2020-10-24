/*
 * SO2 lab3 - task 3
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

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
	/* TODO 2: call task_info_alloc for current pid */
	ti1 = task_info_alloc(current->pid);
	
	/* TODO 2: call task_info_alloc for parent PID */
	ti2 = task_info_alloc(current->real_parent->pid);

	struct list_head *i;
    void *elem;

	read_lock(&lock);
    list_for_each(i, lh) {
        struct pid_list *pl = list_entry(i, struct pid_list, list);
        if (pl->pid == pid) {
            read_unlock(&lock);
            return 1;
        }
    }
    read_unlock(&lock);

	/* TODO 2: call task_info alloc for next process PID */
	/*커널 링크드 리스트 공부하고 여기 풀기 */
	//t3 = list_entry(t1->sibling, ,

	/* TODO 2: call text_info_alloc for next process of the nex process */

	return 0;
}

static void memory_exit(void)
{

	/* TODO 3: print ti* field values */

	/* TODO 4: free ti* structures */
}

module_init(memory_init);
module_exit(memory_exit);
