include ../Make.defines.linux

EXTRA=
EXTRALIBS=-lpthread
#EXTRALIBS=-pthread
#��ʱҪʡ��$(MAKE)   $(CFLAGS) -o $@  $^  $(LDLIBS) $(LDFLAGS)������

PROGS = threadid exitstatus  badexit cleanup

.PHONY:all
all: $(PROGS) 
	$(MAKE)   $(CFLAGS) -o $@  $(PROGS)  $(LDLIBS) $(LDFLAGS) 

.PHONY:clean
clean:
	-rm  $(TEMPFILES) $@
