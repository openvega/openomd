#!/bin/bash

pushd src/main/include/omdc_sbe
for srcFile in *.sbeomdhack
do
    destFile=${srcFile%.sbeomdhack}
    cp ${srcFile} ${destFile}
done
popd
