./main < test.txt > output.txt
diff output.txt answers.txt
error=$?
if [ $error -eq 0 ]
then
  echo "Passed all tests."
elif [ $error -eq 1 ]
then
  echo "Test Failed."
else
  echo "Unknown error."
fi
