#!/bin/sh
# AUTO-GENERATED FILE, DO NOT EDIT!
if [ -f $1.org ]; then
  sed -e 's!^C:/Users/Adriano/AppData/Local/Temp!/tmp!ig;s! C:/Users/Adriano/AppData/Local/Temp! /tmp!ig;s!^C:/MinGW/msys/1\.0/!/!ig;s! C:/MinGW/msys/1\.0/! /!ig;s!^C:/MinGW/msys/1\.0!/usr!ig;s! C:/MinGW/msys/1\.0! /usr!ig;s!^c:/MinGW!/mingw!ig;s! c:/MinGW! /mingw!ig;s!^d:!/d!ig;s! d:! /d!ig;s!^c:!/c!ig;s! c:! /c!ig;' $1.org > $1 && rm -f $1.org
fi
