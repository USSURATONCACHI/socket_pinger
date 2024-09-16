#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <port>"
    exit 1
fi

PORT=$1

# Function to stop all background jobs
cleanup() {
    echo "Stopping all clients..."
    kill $(jobs -p) 2>/dev/null
    wait $(jobs -p) 2>/dev/null
}

trap cleanup SIGINT SIGTERM

./build/client Name1 $PORT 1 &
./build/client Name2 $PORT 2 &
./build/client Name3 $PORT 3 &

wait
