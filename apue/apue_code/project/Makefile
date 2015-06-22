DIRS = lib proc  signals file errortest datafiles  threads

all:
	$(MAKE) `./systype.sh`
	
.PHONY:clean
clean:
	for i in $(DIRS); \
	do                \
	(cd $$i && $(MAKE) -f `./systype.sh`.mk clean) || exit 1;  \
	done
	
freebsd:
	for i in $(DIRS);      \
	do                    \
	(cd $$i && $(MAKE) -f freebsd.mk) || exit 1;  \
	done

linux:
	for i in $(DIRS);           \
	do                       \
	(cd $$i && $(MAKE) -f linux.mk) || exit 1; \
	done
macos:
	for i in $(DIRS);        \
	do                     \
	(cd &&i && $(MAKE) -f macos.mk) || exit 1;  \
	done
solaris:
	for i in $(DIRS);               \
	do                                \
	(cd $$i && $(MAKE) -f solaris.mk) || exit 1;  \
	done
	
	
	
