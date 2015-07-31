#!/bin/sh
ps -C watch_process > ./stop_tmp

if [ "$?" -ne 0 ]
then
	echo "watch process not be started!"
#	rm -f ./stop_tmp
	exit -1
fi
#rm -f ./stop_tmp
killall watch_process
if [ "$?" -eq 0 ]
then
	echo "watch process stop sucess!"
else
	echo "watch process stop fail!"
fi
exit 0
	
