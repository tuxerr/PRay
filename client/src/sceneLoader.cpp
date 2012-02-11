#include "sceneLoader.h"
#include "logger.h"

#include "sphere.h"
#include "triangle.h"
#include "directionalLight.h"
#include "ambientLight.h"
#include "vec3.h"
#include "phongMaterial.h"
#include "uglyMaterial.h"

//#define SCENELOADER_DEBUG

using namespace std;

int SceneLoader::load(string scene_file, Scene** scene, int xRes, int yRes) {
    TiXmlDocument doc(scene_file);
    if ( !doc.LoadFile() ) {
        Logger::log(LOG_ERROR) << "Scene loading failed : " << scene_file << endl;
        Logger::log(LOG_ERROR) << "Error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
	return -1;
    } else {
        Logger::log(LOG_INFO) << "Start loading " << scene_file << endl;

        list<Object*> objects;
        list<DirectionalLight> lDirLights;
        AmbientLight ambientLight;
        Camera* camera=0;
        TiXmlElement* tmp_node = 0;

        TiXmlHandle hdl(&doc);
        TiXmlElement* node = hdl.FirstChildElement().FirstChildElement().Element();
        if (node == NULL) {
            Logger::log(LOG_ERROR)<<"Error on top of the file"<<endl;
            return -1;
        }

        while ( node ) {
            string nodeName(node->Value());
            if ( nodeName.compare("camera")==0 ) {
                Vec3<float> position, target, normal;
                float w = 8, h = 4.5, d = 35;

                tmp_node = node->FirstChildElement("position");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <position> near line "<<node->Row()<<endl;
                } else {
                    position = readVec3Float(tmp_node);
                }

                tmp_node = node->FirstChildElement("target");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <target> near line "<<node->Row()<<endl;
                } else {
                    target = readVec3Float(tmp_node);
                }

                tmp_node = node->FirstChildElement("normal");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <normal> near line "<<node->Row()<<endl;
                } else {
                    normal = readVec3Float(tmp_node);
                }

                tmp_node = node->FirstChildElement("viewplane");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <viewplane> near line "<<node->Row()<<endl;
                } else {
                    tmp_node->QueryFloatAttribute("w", &w);
                    tmp_node->QueryFloatAttribute("h", &h);
                    tmp_node->QueryFloatAttribute("d", &d);
                }

                if ( w / h - (float)xRes / (float)yRes  > 1e-4 ) {
                    Logger::log(LOG_WARNING)<<"The camera and the screen have not the same ratio"<<endl;
                    Logger::log(LOG_INFO)<<"Camera ratio : "<<(float)yRes / (float)xRes<<endl;
                    Logger::log(LOG_INFO)<<"Screen ratio : "<<w / h<<endl;
                }

                camera = new Camera(position,
                                    target-position,
                                    normal,
                                    w, h, d,
                                    xRes, yRes);
            } else if ( nodeName.compare("directionalLight")==0 ) {
                Color color;
                Vec3<float> direction;

                tmp_node = node->FirstChildElement("color");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <color> near line "<<node->Row()<<endl;
                } else {
                    color = readColor(tmp_node);
                }

                tmp_node = node->FirstChildElement("direction");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <direction> near line "<<node->Row()<<endl;
                } else {
                    direction = readVec3Float(tmp_node);
                }

                lDirLights.push_back(DirectionalLight(color, direction.normalize()));
            } else if ( nodeName.compare("ambientLight")==0 ) {
                Color color;

                tmp_node = node->FirstChildElement("color");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <color> near line "<<node->Row()<<endl;
                } else {
                    color = readColor(tmp_node);
                }

		ambientLight = AmbientLight(color);
	    } else if ( nodeName.compare("object")==0 ) {
                Material* material = 0;

                tmp_node = node->FirstChildElement("material");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <material> near line "<<node->Row()<<endl;
                } else {
                    material = readMaterial(tmp_node);
                }

                tmp_node = node->FirstChildElement("shape");
                if (tmp_node == NULL) {
                    Logger::log(LOG_ERROR)<<"Missing <shape> near line "<<node->Row()<<endl;
                } else {
                    readShape(tmp_node->FirstChildElement(), &objects, material);
                }
            } else {
                Logger::log(LOG_ERROR)<<"Unknown primary node line "<<node->Row()<<endl;
            }

            node = node->NextSiblingElement();
        }

        Logger::log(LOG_INFO) << "Scene loaded ("<<(int) objects.size()<<" objects)" << endl;

        *scene = new Scene(objects,lDirLights,ambientLight,camera);

	return 0;
    }
}

void SceneLoader::readShape(TiXmlElement* node, list<Object*>* objects, Material* material) {
    string nodeName(node->Value());

    if ( nodeName.compare("sphere")==0 ) {
        Vec3<float> center = readVec3Float(node->FirstChildElement("center"));
        float radius = 0;
        node->FirstChildElement("radius")->QueryFloatAttribute("v", &radius);

#ifdef SCENELOADER_DEBUG
        Logger::log(LOG_DEBUG)<<"Sphere : ("<<center.x<<","<<center.y<<","<<center.z<<") "
                              <<radius<<endl;
#endif
        objects->push_back(new Sphere(center, radius, material));
    } else if ( nodeName.compare("triangle")==0 ) {
        Vec3<float> a = readVec3Float(node->FirstChildElement("a"));
        Vec3<float> b = readVec3Float(node->FirstChildElement("b"));
        Vec3<float> c = readVec3Float(node->FirstChildElement("c"));

#ifdef SCENELOADER_DEBUG
	Logger::log(LOG_DEBUG)<<"Triangle : ("<<a.x<<","<<a.y<<","<<a.z<<") ("
			      <<b.x<<","<<b.y<<","<<b.z<<") ("
			      <<c.x<<","<<c.y<<","<<c.z<<")"<<endl;
#endif
        Triangle* tr = new Triangle(a, b, c, material);
        objects->push_back(tr);
    } else if ( nodeName.compare("list")==0 ) {
        TiXmlElement* child = node->FirstChildElement();
        while ( child ) {
            readShape(child,  objects, material);
            child = child->NextSiblingElement();
        }
    } else {
        Logger::log(LOG_ERROR)<<"Unknown shape : "<<nodeName<<" (line "<<node->Row()<<")"<<endl;
    }
}

Material* SceneLoader::readMaterial(TiXmlElement* node) {
    Material* material = 0;
    TiXmlElement* child = node->FirstChildElement();
    string childName(child->Value());

    if (childName.compare("phong")==0 ) {
        Color color = readColor(child->FirstChildElement("color"));
        float specular=0, diffuse=0, ambiant=0, shininess=0, reflexivity=0;
        TiXmlElement* child2;

        child2 = child->FirstChildElement("specular");
        if (child2) child2->QueryFloatAttribute("v", &specular);
        child2 = child->FirstChildElement("diffuse");
        if (child2) child2->QueryFloatAttribute("v", &diffuse);
        child2 = child->FirstChildElement("ambiant");
        if (child2) child2->QueryFloatAttribute("v", &ambiant);
        child2 = child->FirstChildElement("shininess");
        if (child2) child2->QueryFloatAttribute("v", &shininess);
        child2 = child->FirstChildElement("reflexivity");
        if (child2) child2->QueryFloatAttribute("v", &reflexivity);

#ifdef SCENELOADER_DEBUG
        Logger::log(LOG_DEBUG)<<"Material : Phong : ("<<color.getR()<<","<<color.getG()<<","<<color.getB()
                              <<") "<<specular<<" "<<diffuse<<" "<<ambiant<<" "<<shininess<<" "<<reflexivity<<endl;
#endif
        material = new PhongMaterial(color, specular, diffuse, ambiant, shininess, reflexivity);
    } else if (childName.compare("ugly")==0 ) {
        Color color = readColor(child->FirstChildElement("color"));

#ifdef SCENELOADER_DEBUG
        Logger::log(LOG_DEBUG)<<"Material : Ugly : ("<<color.getR()<<","<<color.getG()<<","<<color.getB()
                              <<")"<<endl;
#endif
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

    return Color(r/255, g/255, b/255);
}

Vec3<float> SceneLoader::readVec3Float(TiXmlElement* node) {
    float x=0, y=0, z=0;

    node->QueryFloatAttribute("x", &x);
    node->QueryFloatAttribute("y", &y);
    node->QueryFloatAttribute("z", &z);

    return Vec3<float>(x, y, z);
}
