#! /bin/sh

echo "Hello Bash"

VARNAME="TELL ME A JOKE"

unset VARNAME

echo $VARNAME

if [ -d fuck ]

then

echo "fuck is already exist"

else

mkdir -p fuck

fi


if :; then echo "always true"; fi


if [ $?==0 ]

then

echo "Success"

fi
