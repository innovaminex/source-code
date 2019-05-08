#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/innovaminex.ico

convert ../../src/qt/res/icons/innovaminex-16.png ../../src/qt/res/icons/innovaminex-32.png ../../src/qt/res/icons/innovaminex-48.png ${ICON_DST}
