# Real-time System Resource Monitoring Kernel Module


### Overview
This project implements a Linux kernel module that monitors and logs system resource usage, including CPU and memory usage, in real-time. The module collects resource usage information directly from the Linux kernel without relying on procfs or sysfs interfaces.

### Prerequisites
- Familiarity with Linux kernel programming and kernel modules.
- A Linux system with kernel development tools (e.g., GCC, make) and kernel headers installed.

### Module Architecture
The kernel module is designed with the following components:

1. A timer for periodically monitoring system resource usage.
2. Functions to gather CPU and memory usage information directly from the kernel's internal functions and data structures.
3. A timer callback function that logs resource usage and restarts the timer for continuous monitoring.

### Building and Installing the Kernel Module
1. Download the source code for the kernel module and navigate to the project directory:
```
$ git clone https://github.com/etmp/realtime_resource_monitor.git
$ cd realtime_resource_monitor
```

2. Compile the kernel module:
`$ make`

After a successful compilation, you should see a resource_monitor.ko file generated in the directory.

3. Load the kernel module:
`$ sudo insmod resource_monitor.ko`
The kernel module will start monitoring system resource usage every 5 seconds.

4. Verify that the kernel module is loaded and working:
`$ dmesg | tail`
You should see log messages about the kernel module's initialization and resource usage information.

5. Unload the kernel module when you're done:
`$ sudo rmmod resource_monitor`


### Limitations
The current implementation provides a simplified representation of CPU usage using the scheduler's clock, which is not a perfect indicator of CPU utilization. A more accurate approach would involve calculating the percentage of time spent in user mode, system mode, and idle mode. 

### Future Enhancements
Improve CPU usage calculation for a more accurate representation of system utilization.
Add support for monitoring disk usage.
Implement a user-space application or library for interacting with the kernel module, providing a more user-friendly interface for obtaining resource usage information.
Add support for monitoring other system resources, such as network usage and file system usage.
