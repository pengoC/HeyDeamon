#!/bin/sh
ps -C watch_process > ./start_tmp
if [ "$?" -eq 0 ]
then
	echo "watch process aready started!"
	#rm -f ./start_tmp
	exit -1
fi

#rm -f ./start_tmp

./watch_process

if [ "$?" -eq 0 ]
then
	echo "watch process start success!"
else
	echo "watch process start fail!"
fi

exit 0
