obj-m += realtime_resource_monitor.o

realtime_resource_monitor-objs := src/realtime_resource_monitor.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

