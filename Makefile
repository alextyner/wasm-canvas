# this target prepares source/header files for distribution and then demos the example project
.PHONY: all
all: dist demo

.PHONY: dist
dist:
	cp -f src/canvas.c dist/
	cp -f src/canvas.h dist/
	cp -f src/window.c dist/
	cp -f src/window.h dist/

.PHONY: docs
docs: docs/index.html

docs/index.html: src/canvas.h src/window.h
	cd src && doxygen Doxyfile

# below are targets which delegate to the example project's Makefile

.PHONY: clean
clean:
	$(MAKE) -C example clean

.PHONY: populate-example-libs
populate-example-libs:
	cp -f src/canvas.c example/lib/
	cp -f src/canvas.h example/lib/
	cp -f src/window.c example/lib/
	cp -f src/window.h example/lib/

.PHONY: demo
demo: populate-example-libs
	$(MAKE) -C example demo