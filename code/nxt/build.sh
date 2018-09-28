#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
docker run -it -v $DIR:/home/nxtosek/nxtOSEK/build/nxt teknight/nxtosek ${1:-all} | sed '/^.*toppers_osek.*warning.*$\|^.*toppers_osek.*function.*$/d' ; test ${PIPESTATUS[0]} -eq 0
