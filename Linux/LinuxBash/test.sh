#! /bin/sh

echo "Hello Bash"


echo "Enter password:"

read TRY
TIMES=0;
while [ "$TRY" != "88998899" ]; do

       echo "Sorry, try again"
       TIMES=$(($TIMES+1))
       if [ $TIMES -lt 5 ]; then
       read TRY
       else
       echo "Fial five times "
       break
       fi;
done

echo "Ok success"

exit 0;


COUNTER=1;
while [ $COUNTER -lt 10 ]; do

echo "Here we go"

COUNTER=$(($COUNTER+1))

done


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


if [ $?=0 ]

then

echo "Success"

fi


echo "Is it morning ? Please answer yes or no."

read YES_OR_NO

if [ "$YES_OR_NO" = "yes" ]; then

       echo "Good morning!"

elif [ "$YES_OR_NO" = "no" ]; then

       echo "Good afternoon!"

else
       echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."

       exit 1

fi


for FRUIT in apple banana pear

do

      echo "I like $FRUIT"

done

