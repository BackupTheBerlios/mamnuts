# gmake (GNU make) is presently REQUIRED!

TALKER          = mamnuts
IDENTD          = amnutsIdent
BINDIR          = ..
OBJDIR          = objects
INCDIR          = includes
SRCDIR          = $(CURDIR)
PERMS           = 755
#CC              = cc
CC             = gcc
#CC             = gcc-3.4
#CC             = cc -V 3.0.4 -std=c99 -D_XOPEN_SOURCE=600
# This should take cpp args and cause dependancy info to go to stdout
# It would be nice to use gcc -MMD to make this at the same time as compile
# It would be nice to use gcc 3+ (2.96+) -MP to fix dependancy info for gmake
MAKEDEPEND      = $(CC) -MM
#MAKEDEPEND     = makedepend -f -

# GAMES => include games (i.e., hangman, gun duelling, money)
# IDENTD => include support for "ident" daemon for name resolution
# ISOWEEKS => use ISO 8601 week calendars (Mon-Sun; first week has 4+ days).
# DOUBLEFORK => use old double_fork() code (actually quad fork() with system())
# DUMPCORE => cause crash actions to dump core and exit for debugging
#TALKERCPPFLAGS = -I$(INCDIR)
#TALKERCPPFLAGS = -I$(INCDIR) -DGAMES
#TALKERCPPFLAGS = -I$(INCDIR) -DIDENTD
TALKERCPPFLAGS = -I$(INCDIR) -DIDENTD -DGAMES

# DEBUG => include copious debugging output to stdout
IDENTDCPPFLAGS = -I$(INCDIR)
#IDENTDCPPFLAGS = -I$(INCDIR) -DDEBUG

# These are sort of gcc dependant; roll your own if you use another compiler
# CFLAGS         = -g -O2 -Wall -W
CFLAGS         = -g -O2 -Wall -W -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wnested-externs -Winline -Wlong-long
# CFLAGS         = -g -O2 -Wall -W -pedantic -Wfloat-equal -Wtraditional -Wundef -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn -Wpacked -Wpadded -Wredundant-decls -Wnested-externs -Wunreachable-code -Winline -Wlong-long
#CFLAGS         = -g -O2 -Wall -W -pedantic -Wfloat-equal -Wtraditional -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn -Wpacked -Wpadded -Wredundant-decls -Wnested-externs -Wunreachable-code -Winline -Wlong-long
#CFLAGS         = -g -O2 -Wall -W -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wnested-externs -Winline -Wlong-long
# CFLAGS         = -g -O2 -Wall -W -pedantic -Wfloat-equal -Wtraditional -Wundef -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn -Wpacked -Wpadded -Wredundant-decls -Wnested-externs -Wunreachable-code -Winline -Wlong-long
# CFLAGS         = -g -O2 -Wall -W -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wpadded -Wredundant-decls -Wnested-externs -Wunreachable-code -Winline -Wlong-long
#CFLAGS         = -g -O2 -Wall -W -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wredundant-decls  -Wnested-externs -Wunreachable-code
#CFLAGS         = -g -O2 -Wall -W -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wredundant-decls  -Wnested-externs
#CFLAGS         = -g -O2 -Wall -W -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wredundant-decls  -Wnested-externs
#CFLAGS         = -Q -fprofile-arcs -ftest-coverage -ggdb3 -O2 -Wall -W

LDFLAGS         =

# if you add a new file you must add a line here!
TALKEROBJS      = \
        $(OBJDIR)/mamnuts.o \
        $(OBJDIR)/pager.o \
        $(OBJDIR)/reboot.o \
        $(OBJDIR)/netlinks.o \
        $(OBJDIR)/rooms.o \
        $(OBJDIR)/messages.o \
        $(OBJDIR)/games.o \
        $(OBJDIR)/objects.o \
        $(OBJDIR)/speech.o \
        $(OBJDIR)/strings.o \
        $(OBJDIR)/admin.o \
        $(OBJDIR)/spodlist.o \
# Uncomment this if you're going to use TMORE...
#        $(OBJDIR)/tmore.o \
		
IDENTDOBJS      = \
        $(OBJDIR)/ident.o \

### Plataform dependent stuff: doing manually what automake should be doing:
### Choose your platform (uncomment it's stuff and comment other platforms')

# Solaris
#TALKERLIBS     = -lnsl -lsocket
#IDENTDLIBS     = -lnsl -lsocket

# Linux  and other *NIX
TALKERLIBS     = -lcrypt
IDENTDLIBS     =

#
# you should not need to alter anything below this point
#

#VPATH = $(SRCDIR)
#vpath %.c $(SRCDIR)
#vpath %.h $(SRCDIR)/$(INCDIR)
#vpath %.o $(OBJDIR)

all: build

.PHONY: all compile build install clean distclean

distclean: clean
	@echo "Removing binary and backup files"
	rm -f $(TALKER) $(BINDIR)/$(TALKER) $(IDENTD) $(BINDIR)/$(IDENTD)
	rm -f *.[ch]~ *.[ch].bak $(INCDIR)/*.[ch]~ $(INCDIR)/*.[ch].bak

clean:
	@echo "Removing object and dependancy files"
	rm -f $(TALKEROBJS) $(IDENTDOBJS)
	rm -f $(TALKEROBJS:.o=.d) $(IDENTDOBJS:.o=.d)

install: $(BINDIR)/$(TALKER) $(BINDIR)/$(IDENTD)

build: $(TALKER) $(IDENTD)

compile: $(TALKEROBJS) $(IDENTDOBJS)

$(BINDIR)/$(TALKER) $(BINDIR)/$(IDENTD): $(BINDIR)/%: %
	@echo "Installing $< ..."
	chmod $(PERMS) $<
	ln -f $< $@

$(TALKER): $(TALKEROBJS)
	@echo "Linking $@ ..."
	$(CC) $(LDFLAGS) $^ $(TALKERLIBS) -o $@

$(IDENTD): $(IDENTDOBJS)
	@echo "Linking $@ ..."
	$(CC) $(LDLAGS) $^ $(IDENTDLIBS) -o $@

$(TALKEROBJS): $(OBJDIR)/%.o: %.c
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) $(TALKERCPPFLAGS) -c $< -o $@
	@$(MAKEDEPEND) $(TALKERCPPFLAGS) $< | sed -e 's/#.*//' -e '/\\$$/N' -e 's/\\\n//g' -e 's/  */ /g' -e 's/^ //' -e 's/ $$//' -e '/^$$/d' -e 's!^[^:]*$*\.o *: *!$@: !' -e 'p' -e 's!^[^:]*$*\.o *: *$*\.c *!!' -e '/^$$/d' -e 's/$$/:/' > $(@:.o=.d)

$(IDENTDOBJS): $(OBJDIR)/%.o: %.c
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) $(IDENTDCPPFLAGS) -c $< -o $@
	@$(MAKEDEPEND) $(IDENTDCPPFLAGS) $< | sed -e 's/#.*//' -e '/\\$$/N' -e 's/\\\n//g' -e 's/  */ /g' -e 's/^ //' -e 's/ $$//' -e '/^$$/d' -e 's!^[^:]*$*\.o *: *!$@: !' -e 'p' -e 's!^[^:]*$*\.o *: *$*\.c *!!' -e '/^$$/d' -e 's/$$/:/' > $(@:.o=.d)

-include $(TALKEROBJS:.o=.d) $(IDENTDOBJS:.o=.d)

