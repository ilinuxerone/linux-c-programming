include ../Make.defines.linux

AR = ar
LIBMISC = libapue.a
OBJS = error2.o prexit.o system.o tellwait.o prmask.o signal.o signal_intr.o sleep.o \
 		setfl.o clrfl.o openmax.o pathalloc.o daemonize.o

RANLIB = ranlib

.PHONY:all
all: $(OBJS)
	$(AR) rv $(LIBMISC) $?
	$(RANLIB) $(LIBMISC)
	
.PHONY:clean
clean:
	rm -f *.o a.out core temp.*  $(LIBMISC)
	
