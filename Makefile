clear:
	rm -rf build


build:
	make clear
	mkdir build
	cd build && \
	cmake .. && \
	cmake --build .

test:
	build/tests/test_search