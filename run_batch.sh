#!/bin/bash
BUILD_DIR=build

echo "[$(date)] Starting batch job..." >> batch.log

cd ./$BUILD_DIR

cmake .. && make && ./transactor >> ../batch.log 2>&1

cd ..
echo "[$(date)] Batch Job complete." >> batch.log