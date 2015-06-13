## Make script for replacer
## yeholmes@163.com
## 2014 04 22

CROSS_COMPILE := 
# CROSS_COMPILE      := $(TOOLCHAIN_ROOT_PATH)/bin/arm-linux-androideabi-
# CROSS_COMPILE      := arm-linux-gnueabi-
# CROSS_COMPILE      := arm-linux-gnueabihf-
# CROSS_COMPILE      := arm-buildroot-linux-uclibcgnueabi-
# CROSS_COMPILE      := arm-none-eabi-
# CROSS_COMPILE      := arm-bcm2708hardfp-linux-gnueabi-
# export PATH=$PATH:/home/ye/android-ndk-r9d/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/bin

CC                 := $(CROSS_COMPILE)gcc
LD                 := $(CROSS_COMPILE)ld
CFLAGS             := -Wall -g -O2 -march=armv7-a \
	-mabi=aapcs-linux # --sysroot=$(SYSROOT) -DABI_armeabi=1

LDFLAGS            := 
INSTALL_PATH       := /system/bin
TARGET             := auto-input remote lremote scheduler # replacer alarm

all : $(TARGET)

lremote : remote.c
	gcc -Wall -O2 -ggdb -o $@ $^

remote : remote.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

auto-input : auto-input.o external.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

%.o : %.c external.h linux-input.h intermsg.h
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

install : replacer
	adb push $^ $(INSTALL_PATH)

scheduler : sched-main.o scheduler.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

.PHONY : clean
clean :
	rm -rf $(TARGET) *.o

