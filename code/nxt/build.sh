#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
docker run -it -v $DIR:/home/nxtosek/nxtOSEK/build/nxt teknight/nxtosek:version1 ${1:-all}
