include ../Make.defines.linux

PROGS = seek echo mycp mycat fileflag mydup2 filetype access  umask  chmod \
		myls  unlink mywc myls3 zap  devrdev longpath

.PHONY: all
all: $(PROGS) 
	$(MAKE)  $(CFLAGS) -o $@   $^  $(LDLIBS) $(LDFLAGS)

.PHONY:clean
clean:
	-rm -f $(TEMPFILES) $(PROGS)
	
