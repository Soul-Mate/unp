ROOT=..
PLATFORM=linux
include $(ROOT)/Make.defines.$(PLATFORM)

LIBMISC	= libs.a
OBJS = unp_err.o unp_wsock.o unp_readline.o

all:	$(LIBMISC)

$(LIBMISC):	$(OBJS)
	$(AR) rv $(LIBMISC) $?
	$(RANLIB) $(LIBMISC)


clean:
	rm -f *.o a.out core temp.* $(LIBMISC)