#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/sched/clock.h>
#include <asm/page.h>

#define TIMER_RESTART 5000

// Define a timer, used for periodically monitoring resource usage
static struct timer_list resource_timer;

// retrieves the current CPU time in nanoseconds using sched_clock()
// logs the result using printk()
static void get_cpu_usage(void)
{
    // Obtain CPU usage information using the kernel's sched_clock function
    unsigned long long t = sched_clock();
    printk(KERN_INFO "CPU time (ns): %llu\n", t);
}

// Obtains memory usage information using the si_meminfo() function
// The total system memory and free memroy are logged using printk()
static void get_memory_usage(void)
{
    // Declare struct used to store information on memory usage
    struct sysinfo si;
    // Fill the sysinfo struct with memory usage info
    si_meminfo(&si);
    // Log the total ram and free ram using printk()
    /**NOTE:
    * Conversion of totalram and freeram into kB based on PAGE_SHIFT
    * macro borrowed from /fs/proc/meminfo.c implementation of show_val_kb()
    */
    printk(
        KERN_INFO "Total RAM: %lu, Free RAM: %lu\n", 
        si.totalram << (PAGE_SHIFT - 10), 
        si.freeram  << (PAGE_SHIFT - 10)
    );
}

// Timer callback function that is called whenever the timer expires
// logs current resource usage by calling the above functions
// restarts the timer to continue monitoring usage every 5 seconds
static void resource_monitor_callback(struct timer_list *timer)
{
    // Print status message
    printk(KERN_INFO "Resource Monitor: Gathering system resource usage...\n");
    // Get cpu and memory usage using helper functions
    get_cpu_usage();
    get_memory_usage();

    // Restart the timer to periodically gather resource usage
    mod_timer(&resource_timer, jiffies + msecs_to_jiffies(TIMER_RESTART));
}

// Module initialization function
// Called when the model is loaded/initialized
static int __init resource_monitor_init(void)
{
    // Print initialization message
    printk(KERN_INFO "Resource Monitor: Initializing...\n");

    // Initialize and start the timer for periodic resource monitoring
    timer_setup(&resource_timer, resource_monitor_callback, 0);
    mod_timer(&resource_timer, jiffies + msecs_to_jiffies(TIMER_RESTART));

    return 0;
}

// Module exit function
// Is called when the module is unloaded/cleaned up
static void __exit resource_monitor_exit(void)
{
    // Cleanup: Remove the timer and release its resources
    del_timer_sync(&resource_timer);
    // Log an exit message
    printk(KERN_INFO "Resource Monitor: Exiting...\n");
}

// Register module initialization and exit functions
module_init(resource_monitor_init);
module_exit(resource_monitor_exit);

// Define module metadata including license, author, description, and version
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eva Wooton");
MODULE_DESCRIPTION("A real-time system resource monitoring kernel module.");
MODULE_VERSION("1.0");
