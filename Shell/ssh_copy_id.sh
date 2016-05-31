#!/bin/bash

ssh root@172.16.1.233 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub
