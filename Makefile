build:
	mkdir -p out
	g++ *.cpp -o out/main
run: build
	./out/main
clean:
	rm out/*

server:
	cd out && python3 -m http.server

