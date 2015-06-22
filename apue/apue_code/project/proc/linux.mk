include ../Make.defines.linux

PROGS = fork vfork wait waitpid

all: $(PROGS)
	$(MAKE) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)


.PHONY:clean
clean:
	-rm -f $(PROGS) $(TEMPFILES) file.hole