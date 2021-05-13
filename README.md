# PRay

PRay is a parallelized Raytracer that is supposed to run in a client-server mode via TCP sockets.

## Demos

- `demo_00_standalone_test.sh`
- `demo_01_standalone_bille.sh`
- `demo_02_standalone_suzanne.sh`
- `demo_03_server_4-clients.sh`

### Standalone mode

    pray_client --standalone --file=file.xml

#### Camera control (AZERTY keyboard)

| Key   | Action                        |
|:-----:| ----------------------------- |
| z     | translate forward             |
| s     | translate backwards           |
| d     | translate right               |
| q     | translate left                |
| r     | translate up                  |
| f     | translate down                |
| a     | roll left                     |
| e     | roll right                    |
| up    | pitch up                      |
| down  | pitch down                    |
| left  | yaw left                      |
| right | yaw right                     |
| m     | switch mode (camera or scene) |

### Client/server mode

    pray_server --port=port
    pray_client --server=IP --port=port [--fork]

#### Commands

| Command        | Action            |
| -------------- | ----------------- |
| `scene <path>` | Define scene file |
| `render`       | Launch render     |
| _ESC_ / _End_  | Quit              |

## Settings

Both `pray_client` and `pray_server` read `settings.xml` in the
current directory.

## Build

    cmake .
    make

### Dependencies (to build and run on a GNU/Linux platform)

- CMake (2.6+)
- make (or some CMake-supported IDE)
- C++ compiler with C++11 & OpenMP support
- pthread
- SDL
- tinyxml
- ncurses

#### Ubuntu 20.04

    sudo apt-get install cmake make g++ libsdl1.2-dev libtinyxml-dev libncurses-dev
