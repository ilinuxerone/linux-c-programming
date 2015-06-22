include ../Make.defines.linux

OBJS = getpwnam.o

.PHONY: all
all: $(PROGS)
	$(MAKE) $(CFLAGS) -o $@  $^ $(LDLIBS) $(LDFLAGS)
#all: $(OBJS) 

.PHONY:clean
clean: 
	-rm $(TEMPFILES) $@

