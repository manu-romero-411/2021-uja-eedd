#!/bin/zsh

git checkout josanDev
git pull
git checkout manuDev-alt
git merge --no-ff josanDev || code .
