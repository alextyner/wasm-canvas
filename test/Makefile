CC = emcc
CFLAGS = \
	-O3 \
	-Wall \
	-Werror \
	-Wno-deprecated \
	-Wno-parentheses \
	-Wno-format
HEADERS_FOLDER = lib
HTML_TEMPLATE = src/web/index_template.html

WASMFLAGS = \
	-O3 \
	--memory-init-file 1 \
	--closure 1 \
	--shell-file $(HTML_TEMPLATE) \
	-s ENVIRONMENT=web \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s AGGRESSIVE_VARIABLE_ELIMINATION=1 \
	-s ABORTING_MALLOC=1 \
	-s "EXPORTED_FUNCTIONS=['_main', '_malloc']" \
	-s EXIT_RUNTIME=0 \
	-s NO_FILESYSTEM=1 \
	-s DISABLE_EXCEPTION_CATCHING=2 
	# --bind \
	#-s 'EXTRA_EXPORTED_RUNTIME_METHODS=["UTF8ToString"]'

build/index.html: src/driver.o lib/window.o lib/canvas.o
	$(CC) $(WASMFLAGS) lib/window.o lib/canvas.o src/driver.o -o build/index.html
	
src/driver.o: src/driver.c
	$(CC) $(CFLAGS) -I $(HEADERS_FOLDER)/ -c -o src/driver.o src/driver.c

lib/window.o: lib/window.c

lib/canvas.o: lib/canvas.c

.PHONY: demo
demo: build/index.html
	emrun --no_browser --no_emrun_detect build/index.html 2>/dev/null
	
.PHONY: clean
clean:
	rm -f src/driver.o
	rm -f lib/window.o
	rm -f lib/canvas.o
