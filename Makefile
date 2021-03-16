build:
	mkdir -p out
	em++ *.cpp -o out/index.html
clean:
	rm out/*

