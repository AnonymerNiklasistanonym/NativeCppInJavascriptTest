NAPI_MODULE_NAME="greet.node"

.PHONY: build_napi_module clean

all: build_napi_module

build_napi_module:
	# Create build directory with build information
	node-gyp configure
	# Build the node module
	node-gyp build
	# Copy typings
	cp "src/typings/index.d.ts" "build/Release/${NAPI_MODULE_NAME}.d.ts"

clean:
	rm -rf build
