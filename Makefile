clear:
	rm -rf build


build:
	mkdir build
	cd build && \
	cmake .. && \
	cmake --build .

test:
	build/tests/test_search