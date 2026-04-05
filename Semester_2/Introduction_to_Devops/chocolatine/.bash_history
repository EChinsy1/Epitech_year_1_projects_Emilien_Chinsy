touch tempnana.txt && banana-check-repo | grep "Banana" > tempnana.txt || true; cat tempnana.txt
while IFS=':' read -r file line bruh;           do             echo "::error file=$file,line=$line,title=coding style error error::$error";           done < tempnana.txt
exit
