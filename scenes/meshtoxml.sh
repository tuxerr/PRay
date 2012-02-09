#!/bin/bash
echo '<?xml version="1.0" encoding="utf-8"?>
<scene>
  <camera>
    <position x="-15" y="7" z="20"/>
    <target x="0" y="0" z="0"/>
    <normal x="0" y="1" z="0"/>
    <viewplane w="16/2" h="9/2" d="10"/>
  </camera>
  <directionalLight>
    <color r="255" g="255" b="255"/>
    <direction x="2" y="0" z="-2"/>
  </directionalLight>
  <ambientLight>
    <color r="255" g="255" b="255"/>
  </ambientLight>'
cat $1 | sed -e 's/ \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\) \([^ ]*\)/  <object><shape><triangle><a x="\1" y="\2" z="\3"\/><b x="\4" y="\5" z="\6"\/><c x="\7" y="\8" z="\9"\/><\/triangle><\/shape><material><phong><color r="50" g="50" b="255"\/><specular v="0.6"\/><diffuse v="0.5"\/><ambiant v="0.05"\/><shininess v="100"\/><\/phong><\/material><\/object>/g'
echo '</scene>'

