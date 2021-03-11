build:
	mkdir -p bin
	g++ *.cpp -o bin/main
run: build
	./bin/main
