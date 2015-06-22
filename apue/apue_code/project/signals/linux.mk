include ../Make.defines.linux

PROGS = sigusr reenter sig_chld tsleep2 read1 read2 critical sigsetjmp_mask suspend1 \
			suspend2  presystem

.PHONY:all
all: $(PROGS) sleep1.o sleep2.o tsleep2.o abort.o system.o
	$(MAKE) $(CFLAGS) -o $@ $(PROGS) $(LDFLAGS) $(LDLIBS)

sleep1.o : sleep1.c 

sleep2.o : sleep2.c

tsleep2: tsleep2.o sleep2.o
	gcc -o tsleep2 tsleep2.o sleep2.o $(LDFLAGS) $(LDLIBS)

.PHONY:clean
clean:
	-rm -f $(TEMPFILES) $(PROGS)
