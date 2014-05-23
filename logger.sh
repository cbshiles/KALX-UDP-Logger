#!/bin/bash
# chrontab: 
# 9,29,49 * * * * $HOME/logger/logger.sh
# 1 0 * * * $HOME/logger/logger.sh stop; $HOME/logger.sh


cd /home/kal/logger

if [ -e ./logger.pid ]
then
	read PID < ./logger.pid
	if [ $(ps -p $PID | wc -l) -ne 1 ]
	then
		if [ $1 == "stop" ]
		then
			kill $PID
		fi
		exit 0
	fi
fi

DATE=$(date +"%Y%m%d")
./logger >> logs/logger.${DATE}.out &
echo $! > logger.pid
