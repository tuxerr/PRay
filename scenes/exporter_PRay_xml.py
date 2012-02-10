#-*- coding: utf8 -*-

bl_info = {
    'name': 'Export to PRay xml (.xml)',
    'author': 'Vincent A.',
    'version': (0, 0, 0),
    'blender': (2, 5, 0),
    'api': 35774,
    'location': 'File > Export > Export to PRay xml (.xml)',
    'description': 'Export Blender objects and camera to the PRay xml format',
    'warning': '',
    'wiki_url': '',
    'tracker_url': '',
    "support": 'COMMUNITY',
    "category": "Import-Export"}

# HOW TO INSTALL THE SCRIPT:
#
# -> copy it to /usr/share/blender/2.62/scripts/addons
#   (replace 2.62 by your Blender version)
# -> Open Blender, go to File/User Preferences
# -> In the import-Export category, enable the script "Export to PRay xml"
# -> Press Save as default to keep the script installed for all the next Blender uses
# -> You should now find the script in File/Export


# TODO: fix the exported camera data

import bpy 
from mathutils import Color

def writeTriangle(f, verts, verts_id, col):
    l = ['a', 'b', 'c']
    print(col)
    f.write("\t<object>\n")
    f.write('\t\t<shape>\n\t\t\t<triangle>\n')
    for i,v in enumerate(verts_id):
        print('%s %f %f %f' % (l[i], verts[v].co.x, verts[v].co.y, verts[v].co.z))
        f.write('\t\t\t\t<%s x="%f" y="%f" z="%f"/>\n' % (l[i], verts[v].co.x, verts[v].co.y, verts[v].co.z))
    f.write('\t\t\t</triangle>\n\t\t</shape>\n')
    f.write('\t\t<material>\n\t\t\t<phong>\n')
    f.write('\t\t\t\t<color r="%d" g="%d" b="%d"/>\n' % (int(255*col.r), int(255*col.g), int(255*col.b)))
    f.write('\t\t\t\t<specular v="0.6"/>\n\t\t\t\t<diffuse v="0.5"/>\n\t\t\t\t<ambiant v="0"/>\n\t\t\t\t<shininess v="100"/>\n')
    f.write('\t\t\t</phong>\n\t\t</material>\n')
    f.write("\t</object>\n")

def main(filename):
    print(filename)
    sce = bpy.context.scene
    obs = sce.objects
    f = open(filename, 'w')
    f.write('<?xml version="1.0" encoding="utf-8"?>\n<scene>\n\t<directionalLight>\n\t\t<color r="255" g="255" b="255"/>\n\t\t<direction x="-1" y="-1" z="-1"/>\n\t</directionalLight>\n\t<ambientLight>\n\t\t<color r="255" g="255" b="255"/>\n\t</ambientLight>\n')
    for ob in obs:
        print('ob',ob.name)
        if ob.type == 'CAMERA':
            f.write('\t<camera>\n')
            f.write('\t\t<position x="%f" y="%f" z="%f"/>\n' %(ob.location.x, ob.location.y, ob.location.z))
            f.write('\t\t<target x="0" y="0" z="0"/>\n')
            f.write('\t\t<normal x="0" y="0" z="1"/>')
            f.write('\n\t\t<viewplane w="16/2" h="9/2" d="%f"/>\n\t</camera>\n' %(ob.data.lens/16))
        if ob.type == 'MESH':        
            
            mesh = ob.data
            verts = mesh.vertices
            faces = mesh.faces
            for face in faces:
                print('face')
                vs = face.vertices
                if len(ob.material_slots) < 1:
                    col = Color()
                    col.r=1
                    col.g=1
                    col.b=1
                else:
                    if ob.material_slots[0].material.use_vertex_color_paint:
                        col = mesh.vertex_colors[0].data[face.index].color1
                    else:
                        col = ob.material_slots[0].material.diffuse_color
                if len(vs)==3:
                    writeTriangle(f, verts, vs, col)
                elif len(vs)==4:
                    vs1 = vs[:3]
                    vs2 = [vs[0],vs[2], vs[3]]
                    writeTriangle(f, verts, vs1, col)
                    writeTriangle(f, verts, vs2, col)
                else:
                    print("Pas de face")
    
    f.write("</scene>")
    f.close()          
    print('endend')        
            
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty


class Export(bpy.types.Operator, ExportHelper):
    '''Export to PRay xml format'''
    bl_idname = "export.xml"
    bl_label = "Export"
    filename_ext = ".xml"
    filter_glob = StringProperty(default="*.xml", options={'HIDDEN'})



    @classmethod
    def poll(cls, context):
        return context.active_object is not None

    def execute(self, context):
        return main(self.filepath)


def menu_func(self, context):
    self.layout.operator(Export.bl_idname, text=info)


def register():
    bpy.utils.register_class(Export)
    bpy.types.INFO_MT_file_export.append(menu_func)


def unregister():
    bpy.utils.unregister_class(Export)
    bpy.types.INFO_MT_file_export.remove(menu_func)


if __name__ == "__main__":
    register()
