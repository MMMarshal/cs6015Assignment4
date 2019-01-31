
all: main

main: main.cpp
	clang++ -std=c++11 -c main.cpp
	clang++ -o main main.o
	chmod +x ./test.sh

cover:
	clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o classifier
	rm -f classifier.profdata classifier.profraw rm -f ./*.profraw
	-LLVM_PROFILE_FILE=input1.profraw ./classifier < test.txt
	-LLVM_PROFILE_FILE=1.profraw ./classifier < testFiles/testError1-1.txt
	-LLVM_PROFILE_FILE=2.profraw ./classifier < testFiles/testError1-2.txt
	-LLVM_PROFILE_FILE=3.profraw ./classifier < testFiles/testError1-3.txt
	-LLVM_PROFILE_FILE=4.profraw ./classifier < testFiles/testError1-4.txt
	-LLVM_PROFILE_FILE=5.profraw ./classifier < testFiles/testError2-1.txt
	-LLVM_PROFILE_FILE=6.profraw ./classifier < testFiles/testError2-2.txt
	-LLVM_PROFILE_FILE=7.profraw ./classifier < testFiles/testError2-3.txt
	-LLVM_PROFILE_FILE=8.profraw ./classifier < testFiles/testError3-1.txt
	-LLVM_PROFILE_FILE=9.profraw ./classifier < testFiles/testError3-2.txt
	-LLVM_PROFILE_FILE=10.profraw ./classifier < testFiles/testError3-3.txt
	-LLVM_PROFILE_FILE=11.profraw ./classifier < testFiles/testError3-4.txt
	-LLVM_PROFILE_FILE=12.profraw ./classifier < testFiles/testError4-1.txt
	-LLVM_PROFILE_FILE=13.profraw ./classifier < testFiles/testError4-2.txt
	-LLVM_PROFILE_FILE=14.profraw ./classifier < testFiles/testError4-3.txt
	xcrun llvm-profdata merge -sparse input1.profraw 1.profraw 2.profraw 3.profraw 4.profraw 5.profraw 6.profraw 7.profraw 8.profraw 9.profraw 10.profraw 11.profraw 12.profraw 13.profraw 14.profraw -o classifier.profdata
	xcrun llvm-cov show ./classifier -instr-profile=classifier.profdata

test: main
	./test.sh

clean:
	rm -f ./main.o
	rm -f ./output.txt
	rm -f ./classifier
	rm -f ./main
	rm -f ./classifier.profdata
	rm -f ./*.profraw
