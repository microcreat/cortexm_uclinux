#!/bin/sh
echo "Content-type: text/html"
echo ""
echo ""
ps>ps.txt
date>date.txt

# picture
nm=`cat file.name`
if [[ $nm == "d" ]] ; then \
  nm="a"; \
elif [[ $nm == "a" ]] ; then \
  nm="b"; \
elif [[ $nm == "b" ]] ; then \
  nm="c"; \
elif [[ $nm == "c" ]] ; then \
  nm="d"; \
fi
echo $nm>file.name
fl="pi."$nm

to_show="ping13_150.jpg"
rm -f $to_show
ln -s $fl $to_show 

cat test-2.htm
