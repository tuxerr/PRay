#!/bin/bash

cmake .

make pray_client

(
    cd client
    ./pray_client --standalone --file ../scenes/suzanne_968.xml
)
