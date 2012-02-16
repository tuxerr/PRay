#include "sceneLoader.hpp"
#include "logger.hpp"
#include "settings.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "directionalLight.hpp"
#include "ambientLight.hpp"
#include "vec3.hpp"
#include "phongMaterial.hpp"
#include "uglyMaterial.hpp"

//#define SCENELOADER_DEBUG

using namespace std;

int SceneLoader::load(string scene_file, Scene** scene, int xRes, int yRes) {
    TiXmlDocument doc(scene_file);
    if ( !doc.LoadFile() ) {
        Logger::log(LOG_ERROR) << "Scene loading failed : " << scene_file << endl;
        Logger::log(LOG_ERROR) << "Error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
	return -1;
    } else {
        Logger::log(LOG_INFO) << "Start loading scene : " << scene_file << endl;

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
                VEC3F position, target, normal;
                float w = 8, d = 35;

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
                    tmp_node->QueryFloatAttribute("d", &d);
                }

		camera = new Camera(position,
                                    target-position,
                                    normal,
                                    w, d,
                                    xRes, yRes,
                                    Settings::getAsFloat("camera_translation_factor"),
                                    Settings::getAsFloat("camera_rotation_angle"));
            } else if ( nodeName.compare("directionalLight")==0 ) {
                Color color;
                VEC3F direction;

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
        VEC3F center = readVec3Float(node->FirstChildElement("center"));
        float radius = 0;
        node->FirstChildElement("radius")->QueryFloatAttribute("v", &radius);

#ifdef SCENELOADER_DEBUG
        Logger::log(LOG_DEBUG)<<"Sphere : ("<<center.x<<","<<center.y<<","<<center.z<<") "
                              <<radius<<endl;
#endif
        objects->push_back(new Sphere(center, radius, material));
    } else if ( nodeName.compare("triangle")==0 ) {
        VEC3F a = readVec3Float(node->FirstChildElement("a"));
        VEC3F b = readVec3Float(node->FirstChildElement("b"));
        VEC3F c = readVec3Float(node->FirstChildElement("c"));
	TiXmlElement* child_normal_a = node->FirstChildElement("normal_a");
	TiXmlElement* child_normal_b = node->FirstChildElement("normal_b");
	TiXmlElement* child_normal_c = node->FirstChildElement("normal_c");

	VEC3F na;
        VEC3F nb;
        VEC3F nc;

	VEC3F normal = ((b - a) * (b - c)).normalize();
	
	if(child_normal_a != NULL) {
	  na = readVec3Float(child_normal_a);
	} else {
	  na = normal;
	}
	
	if(child_normal_b != NULL) {
	  nb = readVec3Float(child_normal_b);
	} else {
	  nb = normal;
	}

	if(child_normal_c != NULL) {
	  nc = readVec3Float(child_normal_c);
	} else {
	  nc = normal;
	}

#ifdef SCENELOADER_DEBUG
	Logger::log(LOG_DEBUG)<<"Triangle : ("<<a.x<<","<<a.y<<","<<a.z<<") ("
			      <<b.x<<","<<b.y<<","<<b.z<<") ("
			      <<c.x<<","<<c.y<<","<<c.z<<")"<<endl;
#endif
        Triangle* tr = new Triangle(a, b, c, na, nb, nc, material);
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
        material = new PhongMaterial(color, specular, diffuse, ambiant, shininess, reflexivity,
				     Settings::getAsInt("max_reflections"));
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

VEC3F SceneLoader::readVec3Float(TiXmlElement* node) {
    float x=0, y=0, z=0;

    node->QueryFloatAttribute("x", &x);
    node->QueryFloatAttribute("y", &y);
    node->QueryFloatAttribute("z", &z);

    return VEC3F(x, y, z);
}
