#!/bin/bash

(! find -mindepth 2 -name "*.tex" | xargs grep -E '[.!?]\s\b') || ((echo "ERROR! Found one or more matched of illegal regex pattern" >&2); exit 1)
