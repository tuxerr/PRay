import bpy 

sce = bpy.context.scene
obs = sce.objects
for ob in obs:
    if ob.type == 'MESH':
        print (ob.name)
        f = open(ob.name+'.mesh', 'w')
        mesh = ob.data
        verts = mesh.vertices
        faces = mesh.faces
        for face in faces:
            print('face')
            vs = face.vertices
            if len(vs)==3:
                for v in vs:
                    print (verts[v].co.x, verts[v].co.y, verts[v].co.z)
                    f.write(" %f %f %f" % (verts[v].co.x, verts[v].co.y, verts[v].co.z))
                f.write('\n')
            elif len(vs)==4:
                vs1 = vs[:3]
                vs2 = [vs[0],vs[2], vs[3]]
                for v in vs1:
                    print (verts[v].co.x, verts[v].co.y, verts[v].co.z)
                    f.write(" %f %f %f" % (verts[v].co.x, verts[v].co.y, verts[v].co.z))
                print('face')
                f.write('\n')
                for v in vs2:
                    print (verts[v].co.x, verts[v].co.y, verts[v].co.z)
                    f.write(" %f %f %f" % (verts[v].co.x, verts[v].co.y, verts[v].co.z))
                f.write('\n')
            else:
                print("Pas de face")
        f.close()          
            