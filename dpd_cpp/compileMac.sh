#!/bin/bash

echo 'Starting compilation...'

echo 'Removing old executables...'
rm -rf ./bin/triblockProcessor
rm -rf ./bin/triblockBuilder
rm -rf ./bin/colorTriblock
rm -rf ./bin/triblockTime
rm -rf ./bin/triCoresTime
echo '...executables removed.'

echo 'Compiling triblockProcessor...'
make triblockProcessor
echo '...triblockProcessor compiled.'

echo 'Compiling triblockBuilder...'
make triblockBuilder
echo '...triblockBuilder compiled.'

echo 'Compiling colorTriblock...'
make colorTriblock
echo '...colorTriblock compiled.'

echo 'Compiling triblockTime...'
make triblockTime
echo '...triblockTime compiled.'

echo 'Compiling triCoresTime...'
make triCoresTime
echo '...triCoresTime compiled.'

echo '...compilation completed.'
mv -iv triblockProcessor ./bin/ 
mv -iv triblockBuilder ./bin/
mv -iv colorTriblock ./bin/
mv -iv triblockTime ./bin/
mv -iv triCoresTime ./bin/
echo 'Exiting...'

