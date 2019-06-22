# this target prepares source/header files for distribution and then demos the example project
.PHONY: all
all: dist demo

.PHONY: dist
dist:
	cp -f src/canvas.c include/
	cp -f src/canvas.h include/
	cp -f src/window.c include/
	cp -f src/window.h include/

.PHONY: docs
docs: docs/index.html

docs/index.html: dist src/canvas.h src/window.h
	cd src && doxygen Doxyfile

# below are targets which delegate to the test project's Makefile

.PHONY: clean
clean:
	$(MAKE) -C test clean

.PHONY: populate-test-libs
populate-test-libs:
	cp -f src/canvas.c test/lib/
	cp -f src/canvas.h test/lib/
	cp -f src/window.c test/lib/
	cp -f src/window.h test/lib/

.PHONY: demo
demo: populate-test-libs
	$(MAKE) -C test demo