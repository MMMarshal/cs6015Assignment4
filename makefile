
all: main

main: main.cpp
	clang++ -std=c++11 -c main.cpp
	clang++ -o main main.o
	chmod +x ./test.sh

fuzzer:
	rm -f -r ./coverage
	mkdir ./coverage
	mkdir ./coverage/RandomStrings
	mkdir ./coverage/BadPoints
	mkdir ./coverage/LegalRandomPoints
	mkdir ./coverage/LegalRandomSquares
	mkdir ./coverage/LegalRandomRectangles
	chmod +x fuzzer.py
	python ./fuzzer.py
	chmod +x ./fuzz
	clang++ -fsanitize=address -std=c++11 -c main.cpp
	clang++ -fsanitize=address -o main main.o


cover:
	chmod +x ./cover.sh
	./cover.sh > coverage.txt

test: main
	./test.sh

clean:
	rm -f -r ./coverage
	rm -f ./classifier.profdata
	rm -f ./quadClassifier
	rm -f ./coverage.txt
	rm -f ./output.txt
	rm -f ./classifier
	rm -f ./*.profraw
	rm -f ./main.o
	rm -f ./main
