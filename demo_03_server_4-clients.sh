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

escape=$(echo -e '\e')

cd ../server
expect <(cat <<EOF
    spawn -noecho ./pray_server --port $PORT
    sleep 2
    send -- "scene ../scenes/bille.xml\r"
    sleep 2
    send -- "render\r"
    expect "Network rendering finished"
    sleep 3
    send -- $escape
EOF
)
