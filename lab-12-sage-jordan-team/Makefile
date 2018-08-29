CC=gcc
IDIR =./include
CFLAGS=-I$(IDIR) -std=c99

srcdir = ./src
libdir = ./lib
builddir = ./build

.PHONY: all
all: DroneWars

DroneWars: $(libdir)/libsimulator.a DroneWars.o | $(builddir)
	$(CC) $(builddir)/DroneWars.o -L$(libdir) -lm -lsimulator -o DroneWars

DroneWars.o: $(srcdir)/DroneWars.c | $(builddir)
	$(CC) $(CFLAGS) -c $(srcdir)/DroneWars.c -o $(builddir)/DroneWars.o


.PHONY: run
run: all
	./DroneWars

.PHONY: clean
clean:
	rm DroneWars
	rm -r $(builddir)

$(builddir):
	mkdir -p $(builddir)
