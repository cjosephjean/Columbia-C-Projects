#!/bin/bash

# Detect if CTRL-C was pressed
on_ctrl_c()
{
    echo "Ignoring CTRL-C";
}
# Call on_ctrl_c() when the interrupt signal is received.
# The interupt signal is sent when you press CTRL-C.
trap on_ctrl_c INT

mkfifo mypipe-$$
cat mypipe-$$ | nc -l $1 | /home/jae/cs3157-pub/bin/mdb-lookup-cs3157 > mypipe-$$

#Kill the Pipe at the end of the shell script
rm -rf mypipe*
