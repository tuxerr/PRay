#include "sceneLoader.h"
#include "logger.h"

#include "sphere.h"
#include "triangle.h"
#include "directionalLight.h"
#include "ambientLight.h"
#include "vec3.h"
#include "phongMaterial.h"
#include "uglyMaterial.h"

using namespace std;

int SceneLoader::load(string scene_file, Scene** scene, int xRes, int yRes) {
    TiXmlDocument doc(scene_file);
    if ( !doc.LoadFile() ) {
        Logger::log(LOG_ERROR) << "Scene loading failed : " << scene_file << endl;
        Logger::log(LOG_ERROR) << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
	return -1;
    } else {

        Logger::log(LOG_INFO) << "Start loading " << scene_file << endl;

        list<Object*> objects;
        list<DirectionalLight> lDirLights;
        AmbientLight ambientLight;
        Camera* camera=0;

        TiXmlHandle hdl(&doc);
        TiXmlElement* node = hdl.FirstChildElement().FirstChildElement().Element();

        while ( node ) {
            string nodeName(node->Value());
            if ( nodeName.compare("camera")==0 ) {
                Vec3<float> position = readVec3Float(node->FirstChildElement("position"));
                Vec3<float> target = readVec3Float(node->FirstChildElement("target"));
                Vec3<float> normal = readVec3Float(node->FirstChildElement("normal"));
                camera = new Camera(position,
                                    target,
                                    normal,
                                    16/2, 9/2,
                                    35,
                                    xRes, yRes);
            } else if ( nodeName.compare("directionalLight")==0 ) {
                Color color = readColor(node->FirstChildElement("color"));
                Vec3<float> direction = readVec3Float(node->FirstChildElement("direction"));
                lDirLights.push_back(DirectionalLight(color, direction.normalize()));
            } else if ( nodeName.compare("ambientLight")==0 ) {
	        Color color = readColor(node->FirstChildElement("color"));
		ambientLight = AmbientLight(color);
	    } else if ( nodeName.compare("object")==0 ) {
                Material* material = readMaterial(node->FirstChildElement("material"));
                Object* object = readShape(node->FirstChildElement("shape"), material);
                objects.push_back(object);
            } else {
                Logger::log(LOG_ERROR)<<"Unknown primary node"<<endl;
            }

            node = node->NextSiblingElement();
        }

        Logger::log(LOG_INFO) << "Scene loaded with success" << endl;

        *scene = new Scene(objects,lDirLights,ambientLight,camera);

	return 0;
    }
}

Object* SceneLoader::readShape(TiXmlElement* node, Material* material) {
    Object* object = 0;
    TiXmlElement* child = node->FirstChildElement();
    string childName(child->Value());

    if (childName.compare("sphere")==0 ) {
        Vec3<float> center = readVec3Float(child->FirstChildElement("center"));
        float radius = 0;
        child->FirstChildElement("radius")->QueryFloatAttribute("v", &radius);

        Logger::log(LOG_DEBUG)<<"Sphere : ("<<center.x<<","<<center.y<<","<<center.z<<") "
                              <<radius<<endl;

        object = new Sphere(center, radius, material);
    } else if (childName.compare("triangle")==0 ){
        Vec3<float> a = readVec3Float(child->FirstChildElement("a"));
        Vec3<float> b = readVec3Float(child->FirstChildElement("b"));
        Vec3<float> c = readVec3Float(child->FirstChildElement("c"));

	Logger::log(LOG_DEBUG)<<"Triangle : ("<<a.x<<","<<a.y<<","<<a.z<<") ("
			      <<b.x<<","<<b.y<<","<<b.z<<") ("
			      <<c.x<<","<<c.y<<","<<c.z<<")"<<endl;

        object = new Triangle(a, b, c, material);
    } else {
        Logger::log(LOG_ERROR)<<"Unknown shape"<<endl;
    }

    return object;
}

Material* SceneLoader::readMaterial(TiXmlElement* node) {
    Material* material = 0;
    TiXmlElement* child = node->FirstChildElement();
    string childName(child->Value());

    if (childName.compare("phong")==0 ) {
        Color color = readColor(child->FirstChildElement("color"));
        float specular=0, diffuse=0, ambiant=0, shininess=0;
        child->FirstChildElement("specular")->QueryFloatAttribute("v", &specular);
        child->FirstChildElement("diffuse")->QueryFloatAttribute("v", &diffuse);
        child->FirstChildElement("ambiant")->QueryFloatAttribute("v", &ambiant);
        child->FirstChildElement("shininess")->QueryFloatAttribute("v", &shininess);

        Logger::log(LOG_DEBUG)<<"Material : Phong : ("<<color.getR()<<","<<color.getG()<<","<<color.getB()
                              <<") "<<specular<<" "<<diffuse<<" "<<ambiant<<" "<<shininess<<endl;

        material = new PhongMaterial(color, specular, diffuse, ambiant, shininess);
    } else if (childName.compare("ugly")==0 ) {
        Color color = readColor(child->FirstChildElement("color"));

        Logger::log(LOG_DEBUG)<<"Material : Ugly : ("<<color.getR()<<","<<color.getG()<<","<<color.getB()
                              <<")"<<endl;

        material = new UglyMaterial(color);
    } else {
        Logger::log(LOG_ERROR)<<"Unknown material"<<endl;
    }

    return material;
}

Color SceneLoader::readColor(TiXmlElement* node) {
    float r=0, g=0, b=0;
   
    node->QueryFloatAttribute("r", &r);
    node->QueryFloatAttribute("g", &g);
    node->QueryFloatAttribute("b", &b);

    return Color(r/256, g/256, b/256);
}

Vec3<float> SceneLoader::readVec3Float(TiXmlElement* node) {
    float x=0, y=0, z=0;
    
    node->QueryFloatAttribute("x", &x);
    node->QueryFloatAttribute("y", &y);
    node->QueryFloatAttribute("z", &z);

    return Vec3<float>(x, y, z);
}
