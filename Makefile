build:
	mkdir -p out
	g++ -O1 *.cpp -o out/main
run: build
	./out/main
clean:
	rm out/*

server:
	cd out && python3 -m http.server

