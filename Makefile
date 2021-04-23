build: clean
	em++ --bind *.cpp -s WASM=1 -o out/wasm.js
	cp client/* out/
clean:
	rm -rf out
	mkdir -p out
serve: build
	cd out && python3 -m http.server
