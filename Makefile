# this target prepares source/header files for distribution and then demos the example project
.PHONY: all
all: dist demo

.PHONY: dist
dist:
	cp -f src/canvas.c dist/
	cp -f src/canvas.h dist/
	cp -f src/window.c dist/
	cp -f src/window.h dist/

# below are targets which delegate to the example project's Makefile

.PHONY: clean
clean:
	$(MAKE) -C example clean

.PHONY: demo
demo:
	$(MAKE) -C example demo