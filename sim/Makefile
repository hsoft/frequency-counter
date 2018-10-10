OBJS = main.o circuit.o
OBJS += $(addprefix ../src/, freqcounter.o)
OBJS += $(addprefix ../seg7-multiplex/src/, seg7multiplex.o)
OBJS += $(addprefix ../seg7-multiplex/sim/, circuit.o)
OBJS += $(addprefix ../common/, intmath.o)

TO_CLEAN = $(OBJS) $(PROGNAME)

SUBMODULE_TARGETS = ../common/README.md

ALL = $(SUBMODULE_TARGETS) $(PROGNAME)

include ../common.mk

CFLAGS = -I. -Iicemu/src -DSIMULATION $(COMMON_CFLAGS) -c
LDFLAGS = -Licemu -licemu `pkg-config --libs --static ncurses libftdi1`

# Rules
$(PROGNAME): $(OBJS)
	$(MAKE) -C icemu clean all
	$(CC) $+ -o $@ $(LDFLAGS)
