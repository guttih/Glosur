#!/bin/bash

#Text Color commands
#
#Brief: Commands to change the color of a text
highlight=$(echo -en '\033[01;37m')
purpleColor=$(echo -en '\033[01;35m')
cyanColor=$(echo -en '\033[01;36m')
errorColor=$(echo -en '\033[01;31m')
warningColor=$(echo -en '\033[00;33m')
successColor=$(echo -en '\033[01;32m')
norm=$(echo -en '\033[0m')

FILE=$(basename -- "$1")
EXTENSION=$(echo "${FILE##*.}" | awk '{print toupper($0)}')
FILENAME="${FILE%.*}"
# echo "FILE:$FILE"
# echo "FILENAME:$FILENAME"
# echo "EXTENSION:$EXTENSION"

if [[ $EXTENSION == "CPP" ]]; then
    echo "cpp file"
fi
OUTFILE=$FILENAME.o
PARAMS="$FILE -o $OUTFILE -lstdc++ -I."
echo "gcc $PARAMS"
if gcc $PARAMS;then
    echo "${successColor}Success${norm} running ${highlight}./$OUTFILE${norm}"
    ./"$OUTFILE"
    
else
    echo "${errorColor}Error ${norm} building ${highlight}./$1${norm}"
fi

if [ -f ./"$OUTFILE" ]; then
    rm ./"$OUTFILE"
fi
# gcc template-function.cpp -o template-function.o -lstdc++