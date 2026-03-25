CC = gcc
DEBUG = -g
CFLAGS = $(DEBUG) -Wall -Wextra -Wshadow -Wunreachable-code \
        -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
        -Wdeclaration-after-statement -Wno-return-local-addr \
        -Wunsafe-loop-optimizations -Wuninitialized -Werror \
        -Wno-unused-parameter -pthread
LDFLAGS = -lcrypt 
PROG = thread_crypt
all: $(PROG)
$(PROG): $(PROG).o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
$(PROG).o: $(PROG).c
	$(CC) $(CFLAGS) -c $<

clean cls:
	rm -f $(PROG) *.o *.time *.sha512 *.sha256 *.nt *.des *.yescrypt *~ \#*

tar:
	tar cvfa cs333_lab4_${LOGNAME}.tar.gz *.[ch] [mM]akefile
