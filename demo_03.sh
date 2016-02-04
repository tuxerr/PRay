#!/usr/bin/env bash

PORT=12345

cmake .

make

(
    cd client
    sleep 2
    ./pray_client --server 127.0.0.1 --port $PORT > /dev/null
)&

(
    cd client
    sleep 3
    ./pray_client --server 127.0.0.1 --port $PORT > /dev/null
)&

(
    cd client
    sleep 4
    ./pray_client --server 127.0.0.1 --port $PORT > /dev/null
)&

(
    cd client
    sleep 5
    ./pray_client --server 127.0.0.1 --port $PORT > /dev/null
)&

cd server
./pray_server --port $PORT
# type: CALCULATE ../scenes/bille.xml
killall pray_client
