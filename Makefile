all:
	meson compile -C build && ./build/fm

setup:
	meson setup build

build:
	meson compile -C build

clean:
	rm -rf .cache && rm -rf build/

run:
	./build/fm

.PHONY: all build
