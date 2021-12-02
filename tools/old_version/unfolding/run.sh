#!/bin/bash
LNA_PATH='./test/EtherGame.lna'
CONTEXT_PATH='./test/context.lna'
PARAM='claimReward/play'
OUTFILE_PATH='./output/out'

./unfolding --lna "$LNA_PATH"  --context "$CONTEXT_PATH" --param "$PARAM" --out_file "$OUTFILE_PATH"