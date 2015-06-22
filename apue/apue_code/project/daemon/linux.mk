include ../Make.defines.linux

PROGS = 

.PHONY:all
all: $(PROGS) daemonize.o
	$(MAKE) $(CFLAGS) -o $@ $(PROGS) $(LDLIBS) $(LDFLAGS)

daemonize.o: daemonize.c

.PHONY:clean
clean:
	-rm $(TEMPFILES) $@
