
all: main

main: main.cpp
	clang++ -c main.cpp
	clang++ -o main main.o

cover:
	clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp -o classifier
	rm -f classifier.profdata classifier.profraw
	LLVM_PROFILE_FILE=classifier.profraw ./classifier < test.txt
	xcrun llvm-profdata merge -sparse classifier.profraw -o classifier.profdata
	xcrun llvm-cov show ./classifier -instr-profile=classifier.profdata

test: main
	bash ./test.sh

clean:
	rm -f ./main.o
	rm -f ./output.txt
	rm -f ./classifier
	rm -f ./main
	rm -f ./classifier.profdata
	rm -f ./classifier.profraw
