#compile
clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o quadClassifier

#remove any previous profdata files
rm -f ./*.profdata
rm -f ./coverage/*.profdata

#create the first .profdata
touch ./coverage/blank.profdata
lastTest=coverage/blank

#loop through tests and merge each profraw file with the last generated profdata file
for currentTest in ./coverage/RandomStrings/*;
do
  ./quadClassifier < $currentTest > ${currentTest}_out.txt
  xcrun llvm-profdata merge -sparse ${lastTest}.profdata ./default.profraw -o ${currentTest}.profdata
  lastTest=${currentTest}
done

for currentTest in ./coverage/BadPoints/*;
do
  ./quadClassifier < $currentTest > ${currentTest}_out.txt
  xcrun llvm-profdata merge -sparse ${lastTest}.profdata ./default.profraw -o ${currentTest}.profdata
  lastTest=${currentTest}
done

for currentTest in ./coverage/LegalRandomPoints/*;
do
  ./quadClassifier < $currentTest > ${currentTest}_out.txt
  xcrun llvm-profdata merge -sparse ${lastTest}.profdata ./default.profraw -o ${currentTest}.profdata
  lastTest=${currentTest}
done

for currentTest in ./coverage/LegalRandomSquares/*;
do
  ./quadClassifier < $currentTest > ${currentTest}_out.txt
  xcrun llvm-profdata merge -sparse ${lastTest}.profdata ./default.profraw -o ${currentTest}.profdata
  lastTest=${currentTest}
done

for currentTest in ./coverage/LegalRandomRectangles/*;
do
  ./quadClassifier < $currentTest > ${currentTest}_out.txt
  xcrun llvm-profdata merge -sparse ${lastTest}.profdata ./default.profraw -o ${currentTest}.profdata
  lastTest=${currentTest}
done

#show code coverage
xcrun llvm-cov show ./quadClassifier -instr-profile=${lastTest}.profdata main.cpp
