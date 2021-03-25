SEARCH_DEPTH = 12
build:
	mkdir -p out
	g++ -g *.cpp -o out/main
run: build
	./out/main ${SEARCH_DEPTH}
clean:
	rm out/*
debug:
	gdb --args out/main ${SEARCH_DEPTH}
build-wasm:
	em++ *.cpp -s WASM=1 -o out/index.html
run-wasm: build-wasm
	cd out && python3 -m http.server
