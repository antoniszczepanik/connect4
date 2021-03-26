build: clean
	mkdir -p out
	em++ --bind *.cpp -s WASM=1 -o out/wasm.js
clean:
	rm -rf out
serve: build
	cp client/* out/
	cd out && python3 -m http.server
