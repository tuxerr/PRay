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
from mathutils import Color, Matrix, Vector

class Material:
    def __init__(self):
        self.color       = Color()
        self.color.r     = 1
        self.color.g     = 1
        self.color.b     = 1
        self.specular    = 0.6
        self.diffuse     = 0.5
        self.ambiant     = 0
        self.shininess   = 100
        self.reflexivity = 0
        self.transparency= 0 
    def __eq__(self, mat): 
        return self.color.r == mat.color.r          \
            and self.color.g == mat.color.g         \
            and self.color.b == mat.color.b         \
            and self.specular == mat.specular       \
            and self.diffuse == mat.diffuse         \
            and self.ambiant == mat.ambiant         \
            and self.reflexivity == mat.reflexivity \
            and self.shininess == mat.shininess
    
    def __hash__(self):
        return hash(self.specular) + hash(self.diffuse) + hash(self.ambiant) + hash(self.shininess) + hash(self.reflexivity) + hash(self.color.r) + hash(self.color.g) + hash(self.color.b)
        
    def __str__(self):
        return "Material:    r: "+str(self.color.r) +", g: "+ str(self.color.g) +", b: "+ str(self.color.b)

def writeTriangle(f, verts, vecs, verts_id, material):
    l = ['a', 'b', 'c']
    
    
    f.write('\t\t\t\t<triangle>\n')
    for i,v in enumerate(verts_id):
        f.write('\t\t\t\t\t<%s x="%f" y="%f" z="%f"/>\n' % (l[i], vecs[v].x, vecs[v].y, vecs[v].z))
        f.write('\t\t\t\t\t<normal_%s x="%f" y="%f" z="%f"/>\n' % (l[i], verts[v].normal.x, verts[v].normal.y, verts[v].normal.z))
    f.write('\t\t\t\t</triangle>\n')

def main(filename):
    sce = bpy.context.scene
    obs = sce.objects
    dfaces = {}
    f = open(filename, 'w')
    f.write('<?xml version="1.0" encoding="utf-8"?>\n<scene>\n\t<directionalLight>\n\t\t<color r="255" g="255" b="255"/>\n\t\t<direction x="-1" y="-1" z="-1"/>\n\t</directionalLight>\n\t<ambientLight>\n\t\t<color r="255" g="255" b="255"/>\n\t</ambientLight>\n')
    for ob in obs:
        if ob.type == 'CAMERA':
            camz = Vector().to_4d()
            camy = Vector().to_4d()
            camy.y = 1
            camy.w = 0
            camz.z = -10
            #camz.w = 0
            target = ob.matrix_world * camz
            normal = ob.matrix_world*camy
            f.write('\t<camera>\n')
            f.write('\t\t<position x="%f" y="%f" z="%f"/>\n' %(ob.location.x, ob.location.y, ob.location.z))
            f.write('\t\t<target x="%f" y="%f" z="%f"/>\n' %(target.x, target.y, target.z))
            f.write('\t\t<normal x="%f" y="%f" z="%f"/>' % (normal.x, normal.y, normal.z))
            f.write('\n\t\t<viewplane w="16/2" h="9/2" d="%f"/>\n\t</camera>\n' %(ob.data.lens/4))
        if ob.type == 'MESH':        
            
            mesh = ob.data
            verts = mesh.vertices
            ob_mat = ob.matrix_world
            scale = Matrix()
            scale[0][0] = ob.scale.x
            scale[1][1] = ob.scale.y
            scale[2][2] = ob.scale.z
            verts = [ob_mat * scale * vert.co.to_4d() for vert in verts]
            faces = mesh.faces
            for face in faces:
                material = Material()
                
                if len(ob.material_slots) > 0:
                    #print("index", face.material_index)
                    mat = ob.material_slots[face.material_index].material
                    if mat.use_vertex_color_paint:
                        material.color = mesh.vertex_colors[0].data[face.index].color1
                        print("mat", material.color)
                    else:
                        material.color = mat.diffuse_color
                        if mat.use_transparency:
                            material.transparency= mat.raytrace_transparency.fresnel_factor
                        if mat.use_raytrace:
                            material.reflexivity = mat.raytrace_mirror.reflect_factor
                            material.ambiant     = mat.ambient
                            material.diffuse     = mat.diffuse_intensity
                            material.specular    = mat.specular_intensity
                            material.shininess   = mat.specular_hardness
                print ("Blend mat", material.color)
                if not material in dfaces:
                    print("new mat", material.color)
                    dfaces[material] = []
                dfaces[material].append(face)
                
            for material in dfaces:
                f.write("\t<object>\n")
                f.write('\t\t<shape>\n')
                f.write('\t\t\t<list>\n')
                print ('material ', material.color)
                for face in dfaces[material]:
                    vs = face.vertices                    
                    if len(vs)==3:
                        writeTriangle(f, mesh.vertices, verts, vs, material)
                    elif len(vs)==4:
                        vs1 = vs[:3]
                        vs2 = [vs[0],vs[2], vs[3]]
                        writeTriangle(f, mesh.vertices, verts, vs1, material)
                        writeTriangle(f, mesh.vertices, verts, vs2, material)
                    else:
                        print("Pas de face")
                        
                f.write('\t\t\t</list>\n')
                f.write('\t\t</shape>\n')
                f.write('\t\t<material>\n\t\t\t<phong>\n')
                f.write('\t\t\t\t<color r="%d" g="%d" b="%d"/>\n' % (int(255*material.color.r), int(255*material.color.g), int(255*material.color.b)))
                f.write('\t\t\t\t<specular v="%f"/>\n' % (material.specular))
                f.write('\t\t\t\t<diffuse v="%f"/>\n' % (material.diffuse))
                f.write('\t\t\t\t<ambiant v="%f"/>\n' % (material.ambiant))
                f.write('\t\t\t\t<shininess v="%f"/>\n' % (material.shininess))
                f.write('\t\t\t\t<reflexivity v="%f"/>\n' % (material.reflexivity))
                f.write('\t\t\t\t<transparency v="%f"/>\n' % (material.transparency))
                f.write('\t\t\t</phong>\n\t\t</material>\n')
                f.write("\t</object>\n")
    
    f.write("</scene>")
    f.close()          
    print ("\nExport to PRay xml completed.")
    return {'FINISHED'}        
            
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
        return True

    def execute(self, context):
        return main(self.filepath)


def menu_func(self, context):
    self.layout.operator(Export.bl_idname, text='Export to PRay xml (.xml)')


def register():
    bpy.utils.register_class(Export)
    bpy.types.INFO_MT_file_export.append(menu_func)


def unregister():
    bpy.utils.unregister_class(Export)
    bpy.types.INFO_MT_file_export.remove(menu_func)


if __name__ == "__main__":
    register()