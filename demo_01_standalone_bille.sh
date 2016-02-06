#!/usr/bin/env bash

cmake .

make pray_client

cd client
./pray_client --standalone --file ../scenes/bille.xml
