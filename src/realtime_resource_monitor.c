#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/sched/clock.h>

static struct timer_list resource_timer;

static void get_cpu_usage(void) {
    // Obtain CPU usage information using the kernel's sched_clock function
    unsigned long long t = sched_clock();
    printk(KERN_INFO "CPU time (ns): %llu\n", t);
}

static void get_memory_usage(void) {
    struct sysinfo si;
    si_meminfo(&si);
    printk(KERN_INFO "Total RAM: %lu, Free RAM: %lu\n", si.totalram, si.freeram);
}

static void resource_monitor_callback(struct timer_list *timer) {
    printk(KERN_INFO "Resource Monitor: Gathering system resource usage...\n");
    get_cpu_usage();
    get_memory_usage();

    // Restart the timer to periodically gather resource usage
    mod_timer(&resource_timer, jiffies + msecs_to_jiffies(5000));
}

static int __init resource_monitor_init(void) {
    printk(KERN_INFO "Resource Monitor: Initializing...\n");

    // Initialize and start the timer for periodic resource monitoring
    timer_setup(&resource_timer, resource_monitor_callback, 0);
    mod_timer(&resource_timer, jiffies + msecs_to_jiffies(5000));

    return 0;
}

static void __exit resource_monitor_exit(void) {
    // Cleanup: Remove the timer and release its resources
    del_timer_sync(&resource_timer);

    printk(KERN_INFO "Resource Monitor: Exiting...\n");
}

module_init(resource_monitor_init);
module_exit(resource_monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eva Wooton");
MODULE_DESCRIPTION("A real-time system resource monitoring kernel module.");
MODULE_VERSION("1.0");

