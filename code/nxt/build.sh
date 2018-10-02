#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
docker run -v $DIR:/home/nxtosek/nxtOSEK/build/nxt teknight/nxtosek ${1:-all} 2>&1 | grep -v "toppers_osek.*warning\|toppers_osek.*function" ; test ${PIPESTATUS[0]} -eq 0
