SEARCH_DEPTH = 2
build:
	mkdir -p out
	g++ -g *.cpp -o out/main
run: build
	./out/main ${SEARCH_DEPTH}
clean:
	rm out/*
debug:
	gdb --args out/main ${SEARCH_DEPTH}

