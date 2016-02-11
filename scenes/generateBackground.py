#!/usr/bin/env python2
# -*-coding:Utf-8 -*

# Usage : python generateBackground.py > testRefraction.xml

def genTriangle(a, b, c, col):
    result = ''
    result += '\t<object>\n'
    result += '\t\t<shape>\n'
    result += '\t\t\t<triangle>\n'
    result += '\t\t\t\t<a x="' + str(a[0]) + '" y="' + str(a[1]) + '" z=" ' + str(a[2]) + '"/>\n'
    result += '\t\t\t\t<b x="' + str(b[0]) + '" y="' + str(b[1]) + '" z=" ' + str(b[2]) + '"/>\n'
    result += '\t\t\t\t<c x="' + str(c[0]) + '" y="' + str(c[1]) + '" z=" ' + str(c[2]) + '"/>\n'
    result += '\t\t\t</triangle>\n'
    result += '\t\t</shape>\n'
    result += '\t\t<material>\n'
    result += '\t\t\t<phong>\n'
    result += '\t\t\t\t<color r="' + str(col[0]) + '" g="' + str(col[1]) + '" b="' + str(col[2]) + '"/>\n'
    result += '\t\t\t\t<specular v="0"/>\n'
    result += '\t\t\t\t<diffuse v="1"/>\n'
    result += '\t\t\t\t<ambiant v="0.2"/>\n'
    result += '\t\t\t\t<shininess v="0"/>\n'
    result += '\t\t\t\t<reflexivity v="0"/>\n'
    result += '\t\t\t</phong>\n'
    result += '\t\t</material>\n'
    result += '\t</object>\n'
    return result

def generateBackground(size, number):
    result = ''
    base = 200
    offset = 30
    for i in range(number):
        for j in range(number):
            result += genTriangle([i*size, j*size, 0], [(i+1)*size, (j+1)*size, 0], [i*size, (j+1)*size, 0], [offset+base*((i+j)%2), offset+base*((i+j)%2), offset+base*((i+j)%2)])
            result += genTriangle([i*size, j*size, 0], [(i+1)*size, j*size, 0], [(i+1)*size, (j+1)*size, 0], [offset+base*((i+j)%2), offset+base*((i+j)%2), offset+base*((i+j)%2)])

            result += genTriangle([0, i*size, j*size], [0, (i+1)*size, (j+1)*size], [0, i*size, (j+1)*size], [offset+base*((i+j)%2), offset+base*((i+j)%2), offset+base*((i+j)%2)])
            result += genTriangle([0, i*size, j*size], [0, (i+1)*size, j*size], [0, (i+1)*size, (j+1)*size], [offset+base*((i+j)%2), offset+base*((i+j)%2), offset+base*((i+j)%2)])

            result += genTriangle([i*size, 0, j*size], [i*size, 0, (j+1)*size], [(i+1)*size, 0, (j+1)*size], [offset+base*((i+j)%2), offset+base*((i+j)%2), offset+base*((i+j)%2)])
            result += genTriangle([i*size, 0, j*size], [(i+1)*size, 0, (j+1)*size], [(i+1)*size, 0, j*size], [offset+base*((i+j)%2), offset+base*((i+j)%2), offset+base*((i+j)%2)])
    return result




def generateRefractionScene():
    result = '<?xml version="1.0" encoding="utf-8"?>\n'
    result+= '<scene>\n'
    result+= '\t<camera>\n'
    result+= '\t\t<position x="7" y="5" z="2.5"/>\n'
    result+= '\t\t<target x="1" y="1" z="0.75"/>\n'
    result+= '\t\t<normal x="0" y="0" z="1"/>\n'
    result+= '\t\t<viewplane w="16/2" h="9/2" d="35"/>\n'
    result+= '\t</camera>\n'

    result+= '\t<pointLight>\n'
    result+= '\t\t<color r="255" g="255" b="255"/>\n'
    result+= '\t\t<point x="5" y="3" z="5"/>\n'
    result+= '\t</pointLight>\n'

    result+= '\t<ambientLight>\n'
    result+= '\t\t<color r="255" g="255" b="255"/>\n'
    result+= '\t</ambientLight>\n'

    result+= '\t<object>\n'
    result+= '\t\t<shape>\n'
    result+= '\t\t\t<sphere>\n'
    result+= '\t\t\t\t<center x="2" y="2" z="0.9"/>\n'
    result+= '\t\t\t\t<radius v="0.3"/>\n'
    result+= '\t\t\t</sphere>\n'
    result+= '\t\t</shape>\n'
    result+= '\t\t<material>\n'
    result+= '\t\t\t<phong>\n'
    result+= '\t\t\t\t<color r="220" g="30" b="30"/>\n'
    result+= '\t\t\t\t<specular v="0.4"/>\n'
    result+= '\t\t\t\t<diffuse v="0.6"/>\n'
    result+= '\t\t\t\t<ambiant v="0.05"/>\n'
    result+= '\t\t\t\t<shininess v="100"/>\n'
    result+= '\t\t\t\t<reflexivity v="0.3"/>\n'
    result+= '\t\t\t</phong>\n'
    result+= '\t\t</material>\n'
    result+= '\t</object>\n'

    result+= '\t<object>\n'
    result+= '\t\t<shape>\n'
    result+= '\t\t\t<sphere>\n'
    result+= '\t\t\t\t<center x="1.5" y="1" z="1"/>\n'
    result+= '\t\t\t\t<radius v="0.4"/>\n'
    result+= '\t\t\t</sphere>\n'
    result+= '\t\t</shape>\n'
    result+= '\t\t<material>\n'
    result+= '\t\t\t<phong>\n'
    result+= '\t\t\t\t<color r="50" g="50" b="240"/>\n'
    result+= '\t\t\t\t<specular v="0.6"/>\n'
    result+= '\t\t\t\t<diffuse v="0.5"/>\n'
    result+= '\t\t\t\t<ambiant v="0.05"/>\n'
    result+= '\t\t\t\t<shininess v="100"/>\n'
    result+= '\t\t\t\t<reflexivity v="0.3"/>\n'
    result+= '\t\t\t</phong>\n'
    result+= '\t\t</material>\n'
    result+= '\t</object>\n'

    result+= '\t<object>\n'
    result+= '\t\t<shape>\n'
    result+= '\t\t\t<sphere>\n'
    result+= '\t\t\t\t<center x="1.5" y="1" z="1.5"/>\n'
    result+= '\t\t\t\t<radius v="0.2"/>\n'
    result+= '\t\t\t</sphere>\n'
    result+= '\t\t</shape>\n'
    result+= '\t\t<material>\n'
    result+= '\t\t\t<phong>\n'
    result+= '\t\t\t\t<color r="50" g="50" b="240"/>\n'
    result+= '\t\t\t\t<specular v="0.6"/>\n'
    result+= '\t\t\t\t<diffuse v="0.5"/>\n'
    result+= '\t\t\t\t<ambiant v="0.05"/>\n'
    result+= '\t\t\t\t<shininess v="100"/>\n'
    result+= '\t\t\t\t<reflexivity v="0.3"/>\n'
    result+= '\t\t\t</phong>\n'
    result+= '\t\t</material>\n'
    result+= '\t</object>\n'

    result += generateBackground(0.5, 10)
    result += '</scene>\n'
    print(result)


generateRefractionScene()
