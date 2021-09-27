#!/bin/bash
LNA_PATH='./test/EtherGame.lna'
JSON_PATH='./test/etherGame.json'
CONTEXT_PATH='./test/context.lna'
PARAM='currentBalance/play'
OUTFILE_PATH='./test/out'

./main --lna "$LNA_PATH" --json "$JSON_PATH" --context "$CONTEXT_PATH" --param "$PARAM" --out_file "$OUTFILE_PATH"