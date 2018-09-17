#!/bin/bash

(! find report/**/*.tex | xargs grep -E '[.!?](\s\b)') || ((echo "ERROR! Found one or more matches of illegal regex pattern" >&2); exit 1)
