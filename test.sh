./main < test.txt > output.txt
diff output.txt answers.txt
error=$?
if [ $error -eq 0 ]
then
  echo "Passed first test"
elif [ $error -eq 1 ]
then
  echo "First test failed"
else
  echo "First test unknown error."
fi
for file in ./testFiles/*; do
  ./main < $file
  error=$?
  if [ $error -eq 0 ]
  then
    echo "$file Test Failed"
  else
    echo "$file Test Passsed"
  fi
done
echo test complete
