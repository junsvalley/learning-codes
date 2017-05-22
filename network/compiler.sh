#!/bin/bash

gcc -g -O0 -Wall high_concurrency_client.c -o hclient
gcc -g -O0 -Wall high_concurrency_server.c -o hserver -lpthread

