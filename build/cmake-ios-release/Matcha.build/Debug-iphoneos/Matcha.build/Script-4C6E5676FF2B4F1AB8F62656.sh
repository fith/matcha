#!/bin/sh
make -C /Users/kevin/Scratch/c/matcha/build/cmake-ios-release -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/CMakeScripts/Matcha_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
