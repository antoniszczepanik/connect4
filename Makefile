SEARCH_DEPTH = 12
build:
	mkdir -p out
	g++ *.cpp -o out/main
run: build
	./out/main ${SEARCH_DEPTH}
clean:
	rm out/*
server:
	cd out && python3 -m http.server

