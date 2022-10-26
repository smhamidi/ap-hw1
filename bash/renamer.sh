#!/bin/bash
if [ -d "$1" ]; then #this block is going to handel getting the directory and also showing the message
    echo "directory submitted successfully!"
    desired_dir=$1
else
    echo "your directory is NOT valid, try again"
    exit 1
fi

current_time=$(date --rfc-3339=date) #this is the date with the desired format.I found it using command man date

FLAG=0
while [ True ]; do # This block check whether we have a flag of --copy, -c or not
    if [ "$2" = "--copy" -o "$2" = "-c" ]; then
        FLAG=1
        shift 1
    else
        break
    fi
done


if [ $FLAG = 0 ]; then # WithOUT copying
    for FILE in $desired_dir/file*.*
    do
        if [ ! -d "$FILE" ]; then # This will help us to only do operation on files and not directories.
        file_name=$(basename $FILE)
        new_file_name=$current_time"_"$file_name
        file_extention="."${file_name##*.}
        mv $FILE $desired_dir/$new_file_name
        echo "name: $file_name  type: $file_extention   -> changing name to: $new_file_name"
        
        fi
    done

else # With copying
    for FILE in $desired_dir/file*.*
    do
        if [ ! -d "$FILE" ]; then # This will help us to only do operation on files and not directories.
        file_name=$(basename $FILE)
        file_extention="."${file_name##*.}
        new_file_name=$current_time"_"$file_name
        cp $FILE $desired_dir/$new_file_name
        echo "name: $file_name  type: $file_extention   -> making copy: $new_file_name"
        
        fi
    done
fi