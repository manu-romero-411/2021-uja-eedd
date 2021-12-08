#!/bin/zsh

git checkout josanDev
git pull
git checkout manuDev
git merge --no-ff josanDev || code .
