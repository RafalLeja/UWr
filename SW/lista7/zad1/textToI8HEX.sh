#!/bin/bash

cat text.txt | xxd -p -c 0 >text.hex
srec_cat text.hex -HEX_Dump -output text.i8hex -Intel -address-length=2 -output_block_size=8
