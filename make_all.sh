#!/bin/bash

START_DIR=$PWD
CHOIRSATB_DIR=$START_DIR/ChoirSATB
SEEDPROTOTEST_DIR=$START_DIR/SeedProtoTest
THEMACHINE_DIR=$START_DIR/TheMachine

cd $CHOIRSATB_DIR; make clean; make all
cd $SEEDPROTOTEST_DIR; make clean; make all
cd $THEMACHINE_DIR;  make clean; make all

echo "Done, Maybe."
cd $START_DIR
