ROOT=..
PLATFORM=linux
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	test_readline
all:	$(PROGS)

%:	%.c $(LIBS)
	$(CC) $(CFLAGS) $(ROOT)/libs/*.o $@.c -g -o $@ $(LDFLAGS) $(LDLIBS)

include $(ROOT)/Make.libs.inc

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o
	(cd $(ROOT)/libs && make clean)

