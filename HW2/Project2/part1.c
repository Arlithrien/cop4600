#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>


int init(void)
{
  printk(KERN_INFO "Loading module...\n");

  struct task_struct *task;

  for_each_process(task)
  {
    /* on each iteration task points to the next task */
    printk(KERN_INFO "pid: %d | pname: %s | state: %ld\n", task->pid, task->comm, task->state);
  }

  printk(KERN_INFO "Module loaded.\n");
  return 0;
}

void exit(void)
{
  printk(KERN_INFO "Module removed.\n");
}

module_init(init);
module_exit(exit);
