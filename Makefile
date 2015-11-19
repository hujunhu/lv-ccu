TARGET := lv-ccu
OBJS := main.o serial_alias.o string_ext.o
INCFLAG := 
LIBFLAG := 
CROSS_COMPILE := bfin-linux-uclibc-
CC := $(CROSS_COMPILE)gcc
STRIP := $(CROSS_COMPILE)strip

# WARNFLAGS := -Wall -DBUILD_DATE="\"`date +%F" "%T" "%Z`"\"
WARNFLAGS := -Wall
LDFLAGS := -lm -lrt -pthread
CCFLAGS := -O2 -g $(WARNFLAGS) -fsigned-char -pthread

#.PHONY伪目标：避免与文件名冲突，提升执行效率
.PHONY: clean all

all:$(OBJS)
	$(CC) $(LIBFLAG) -Wl,-Map,$(TARGET).map -o $(TARGET) $^ $(LDFLAGS)
	md5sum $(TARGET) > lv-ccu.md5

$(OBJS):%.o:%.c
	$(CC) $(INCFLAG) $(CCFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).map
