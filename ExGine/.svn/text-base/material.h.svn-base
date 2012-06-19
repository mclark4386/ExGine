#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "exogl.h"

#include <string>

class Material
{
public:
    Material();
    Material(GLfloat diffuse[4], GLfloat spec[4], GLfloat shin, GLfloat ambient[4], GLfloat emission[4]);
    ~Material(){};
    int addToModel();
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a){diffuse[0]=r;diffuse[1]=g;diffuse[2]=b;diffuse[3]=a;}
    void setSpec(GLfloat r, GLfloat g, GLfloat b, GLfloat a){spec[0]=r;spec[1]=g;spec[2]=b;spec[3]=a;};
    void setShininess(GLfloat shin){shininess[0]=shin;};
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ambient[0]=r;ambient[1]=g;ambient[2]=b;ambient[3]=a;};
    void setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a){emission[0]=r;emission[1]=g;emission[2]=b;emission[3]=a;};
    void setVertexShader(const char* name){vertexShader = name;};
    void setFragmentShader(const char* name){fragmentShader = name;};
 	void getDiffuse(GLfloat _diffuse[]){_diffuse[0]=diffuse[0];_diffuse[1]=diffuse[1];_diffuse[2]=diffuse[2];_diffuse[3]=diffuse[3];};
 	void getSpec(GLfloat _spec[]){_spec[0]=spec[0];_spec[1]=spec[1];_spec[2]=spec[2];_spec[3]=spec[3];};
 	void getShininess(GLfloat& _shininess){_shininess = shininess[0];};
 	void getAmbient(GLfloat _ambient[]){_ambient[0]=ambient[0];_ambient[1]=ambient[1];_ambient[2]=ambient[2];_ambient[3]=ambient[3];};
 	void getEmission(GLfloat _emission[]){_emission[0]=emission[0];_emission[1]=emission[1];_emission[2]=emission[2];_emission[3]=emission[3];};
protected:
    GLfloat diffuse[4];
    GLfloat spec[4];
    GLfloat shininess[1];
    GLfloat ambient[4];
    GLfloat emission[4];
    
    string vertexShader;
    string fragmentShader;
    
    string* uniforms;
};

int Material::addToModel()
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    return 0;
}

Material::Material()
{
    diffuse[0]=0.0;diffuse[1]=0.0;diffuse[2]=0.0;diffuse[3]=1.0;
    for(int i=0;i<4;i++)
    {
	spec[i] = ambient[i] = emission[i] = diffuse[i];
    }
    shininess[0] = 5.0;
}

Material::Material(GLfloat _diffuse[4], GLfloat _spec[4], GLfloat _shin, GLfloat _ambient[4], GLfloat _emission[4])
{
    for(int i=0;i<4;i++)
    {
	diffuse[i] = _diffuse[i];
	spec[i] = _spec[i];
	ambient[i] = _ambient[i];
	emission[i] = _emission[i];
    }
shininess[0] = _shin;
}
#endif
