EXAMPLE_SRC_FOLDER := example/src
EXAMPLE_LIB_FOLDER := example/lib
EXAMPLE_OUTPUT_FOLDER := example/build
EXAMPLE_HTML_TEMPLATE := example/src/web/index_template.html
EXAMPLE_SRCS := $(shell find $(EXAMPLE_SRC_FOLDER) -name "*.c")
EXAMPLE_LIBS := $(shell find $(EXAMPLE_LIB_FOLDER) -name "*.c")

CFLAGS = \
	-O3 \
	-Wall \
	-Werror \
	-Wall \
	-Wno-deprecated \
	-Wno-parentheses \
	-Wno-format

WASM_OPTIONS = \
	-O3 \
	--bind \
	--memory-init-file 1 \
	--llvm-lto 3 \
	--llvm-opts 3 \
	--js-opts 1 \
	--closure 1 \
	-s ENVIRONMENT=web \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s AGGRESSIVE_VARIABLE_ELIMINATION=1 \
	-s ABORTING_MALLOC=1 \
	-s EXIT_RUNTIME=0 \
	-s NO_FILESYSTEM=1 \
	-s DISABLE_EXCEPTION_CATCHING=2 \
	-s BINARYEN_TRAP_MODE=\'allow\'
	#-s 'EXTRA_EXPORTED_RUNTIME_METHODS=["UTF8ToString"]'
	
dist: dist/*
	cp -f src/canvas.c dist/
	cp -f src/canvas.h dist/
	cp -f src/window.c dist/
	cp -f src/window.h dist/

example-populate-libs:
	cp -f src/canvas.c $(EXAMPLE_LIB_FOLDER)/
	cp -f src/canvas.h $(EXAMPLE_LIB_FOLDER)/
	cp -f src/window.c $(EXAMPLE_LIB_FOLDER)/
	cp -f src/window.h $(EXAMPLE_LIB_FOLDER)/

example: example-populate-libs
	emcc $(EXAMPLE_SRCS) $(EXAMPLE_LIBS) -I $(EXAMPLE_LIB_FOLDER)/ $(WASM_OPTIONS) --shell-file $(EXAMPLE_HTML_TEMPLATE) -o $(EXAMPLE_OUTPUT_FOLDER)/index.html

demo: example
	emrun --no_browser --no_emrun_detect example/build/index.html 2>/dev/null