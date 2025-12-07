#!/usr/bin/env bash

[[ "$1" == "clean" ]] && rm temp_sender

g++ temp_sender.cpp -o temp_sender