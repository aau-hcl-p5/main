#!/bin/bash

set -e

if [[ $1 == "test" ]];
then
	make test -C test
else
	if [[ $1 == "upload" ]];
	then 
		PARAM=$(curl --upload-file ./output/nxt_OSEK.rxe https://transfer.sh/nxt_OSEK.rxe | base64)
		curl nxt:5000/Home/Download/"$PARAM"; 
	else
		DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
		docker run -v $DIR:/home/nxtosek/nxtOSEK/build/nxt teknight/nxtosek ${1:-all} 2>&1 | grep -v "toppers_osek.*warning\|toppers_osek.*function" ; test ${PIPESTATUS[0]} -eq 0
	fi
fi
