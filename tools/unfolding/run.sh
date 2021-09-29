#!/bin/bash
LNA_PATH='./test/EtherGame.lna'
CONTEXT_PATH='./test/context.lna'
PARAM='currentBalance/play'
OUTFILE_PATH='out'

./main --lna "$LNA_PATH"  --context "$CONTEXT_PATH" --param "$PARAM" --out_file "$OUTFILE_PATH"