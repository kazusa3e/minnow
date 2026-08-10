CC := clang
CXX := clang++
BUILD_DIR := build


.PHONY: configure
configure:
	cmake -S . -B $(BUILD_DIR) -G Ninja \
		-DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)

.PHONY: build
build: configure
	cmake --build $(BUILD_DIR)

.PHONY: test
test: build
	cmake --build $(BUILD_DIR) --target test

.PHONY: lint
lint:
	cmake --build $(BUILD_DIR) --target tidy

.PHONY: format
format:
	cmake --build $(BUILD_DIR) --target format

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)
