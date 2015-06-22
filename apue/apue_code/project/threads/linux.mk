include ../Make.defines.linux

EXTRA=
EXTRALIBS=-lpthread
#EXTRALIBS=-pthread
#此时要省略$(MAKE)   $(CFLAGS) -o $@  $^  $(LDLIBS) $(LDFLAGS)这命令

PROGS = threadid exitstatus  badexit cleanup

.PHONY:all
all: $(PROGS) 
	$(MAKE)   $(CFLAGS) -o $@  $(PROGS)  $(LDLIBS) $(LDFLAGS) 

.PHONY:clean
clean:
	-rm  $(TEMPFILES) $@
