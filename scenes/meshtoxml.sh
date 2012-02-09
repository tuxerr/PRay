#!/bin/bash
cat $1 | sed -e 's/ \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\)/<object><shape><triangle><a x="\1" y="\2" z="\3"\/><b x="\4" y="\5" z="\6"\/><c x="\7" y="\8" z="\9"\/><\/triangle><\/shape><material><ugly><color r="255" g="0" b="0"\/><\/ugly><\/material><\/object>/g'

