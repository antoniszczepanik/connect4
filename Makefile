build:
	mkdir -p out
	em++ *.cpp -o out/index.html
clean:
	rm out/*

server:
	cd out && python3 -m http.server

