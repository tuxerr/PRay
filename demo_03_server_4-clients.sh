#!/usr/bin/env bash

PORT=12345
NB_CLIENTS=4

cmake .

make

cd client
for i in $(seq $NB_CLIENTS)
do
    ./pray_client --server 127.0.0.1 --port $PORT --fork > pray_client.$i.out.log 2> pray_client.$i.err.log
done

cd ../server
./pray_server --port $PORT

#type: scene ../scenes/bille.xml
#type: render
