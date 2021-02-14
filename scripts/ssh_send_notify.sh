#!/bin/bash

if [ $# -ne 2 ]; then
	echo "!usage: ./ssh_send_notify.sh (user) (message)"
	exit 1
fi

msg=$2
ssh $1 'DISPLAY=:0 notify-send '$2''
