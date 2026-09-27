# Application-specific makefile.  This file only needs to
# set the APPROOT, SRCS, HDRS, and EXEC variables properly 
# (i.e. the location of the apps directory in relation to this Makefile), and
# then include the Makerules file from the main apps directory.
# All the real work in done in Makerules.  Things are setup
# this way because the build procedure for all apps is basically the same.


SRCS=n3_injection.c
EXEC=n3_injection.dlx.obj

include ../Makerules

include $(APPROOT)/Makerules

WORKOBJS += work/circular_buffer.o

$(OUTDLX): work/circular_buffer.o

work/circular_buffer.o: ../common/circular_buffer.c ../include/circular_buffer.h ../../../include/lab2-api.h
	$(CC) $(CFLAGS) $(INCDIR) -c -o $@ $<

