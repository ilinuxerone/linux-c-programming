include ../Make.defines.linux

PROGS = error

all: $(PROGS)
	$(MAKE) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)


.PHONY:clean
clean:
	-rm -f $(PROGS) $(TEMPFILES) file.hole