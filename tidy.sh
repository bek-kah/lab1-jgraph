#!/bin/bash

mkdir -p output

mv *.jgr *.jpg output/ 2>/dev/null

echo "All .jgr and .jpg files moved to ./output"