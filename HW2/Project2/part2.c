
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

void dfs(struct task_struct *task)
{
  struct task_struct *task;
  struct list_head *list;

  list_for_each(list, &init_task->children) {
    task = list_entry(list, struct task_struct, sibling);
    /* task points to the next child in the list */
    printk(KERN_INFO "pid: %d | pname: %s | state: %ld\n", task->pid, task->comm, task->state);

    dfs(task);
  }  
}

int init(void)
{
  printk(KERN_INFO "Loading module...\n");

  dfs(&init_task);

  printk(KERN_INFO "Module loaded.\n");
  return 0;
}

void exit(void)
{
  printk(KERN_INFO "Module removed.\n");
}

module_init(init);
module_exit(exit);