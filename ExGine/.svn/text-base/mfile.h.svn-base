//test format
#ifndef __MFILE_H__
#define __MFILE_H__

#include "exogl.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>//test    */

#include <string>
#include <fstream>

#define MFILE_VERSION "EXO_MODEL_V1.3"

using namespace std;

class mFile
{
public:
	mFile(){verts=0;norms=0;text=0;tangents=0;indices=0;weights=0;matrixIndices=0;numBones=0;uniforms=0;vertCount=0;normCount=0;textCount=0; Index = false;Static = true;};
	mFile(const char* filename){tangents=0;verts=0;norms=0;text=0;indices=0;weights=0;matrixIndices=0;numBones=0;uniforms=0;vertCount=0;normCount=0;textCount=0;Index = false;Static = true; open(filename);}
	~mFile();
	int open(const char* filename);
	void print(ostream& out);//test function   */
	void operator<<(ostream& out){print(out);};
	GLfloat* getVerts(){return verts;};
	GLfloat* getNorms(){return norms;};
	GLfloat* getText(){return text;};
	GLfloat* getTangents(){return tangents;};
	GLfloat* getWeights(){return weights;};
	GLfloat* getMatrixIndices(){return matrixIndices;};
	GLfloat* getNumBones(){return numBones;};
	GLuint* getIndices(){return indices;};
	string* getUniforms(){return uniforms;};
	bool isIndexed(){return Index;};
	bool isStatic(){return Static;};
	const char* getTextureName(){return textureName.c_str();};
	const char* getNormalmapName(){return normalmapName.c_str();};
	const char* getFilename(){return filename.c_str();};
	const char* getVertexShader(){return vertexShader.c_str();};
	const char* getFragmentShader(){return fragmentShader.c_str();};
	int getVertCount(){return vertCount;};
	
	
protected:

	int vertCount;
	int normCount;
	int textCount;
	
	GLfloat* verts;
	GLfloat* norms;
	GLfloat* text;
	GLfloat* tangents;
	
	GLuint* indices;
	
	GLfloat* weights;
	GLfloat* matrixIndices;
	GLfloat* numBones;
	
	fstream file;
	
	string filename;
		
	string textureName;	
	string normalmapName;
	
	string vertexShader;
	string fragmentShader;
	
	int uniCount;
	string* uniforms;
	
	bool Index;
	bool Static;
	
	enum{
		NO_VERTS = 0x00000001,
		NO_NORMS = 0x00000010,
		NO_TEXT = 0x00000100,
		FAIL_OPEN = 0x00001000,
		IS_OPEN = 0x000100000
	};
		
};

int mFile::open(const char* _filename)
{
	filename = _filename;
	file.open(filename.c_str(), ios::in);//open file for input
	if(!file.is_open())//if that doesn't work
		return FAIL_OPEN;//return our shame
	int ret = NO_VERTS + NO_NORMS + NO_TEXT;//init the return value
	string temp;
	int properties,currentUniform;

	if (file.eof()) return ret;
	string test;
	file>>test;
	if (test.compare(MFILE_VERSION) != 0) return ret;
	
	test.clear();
	file>>test;
	if (test.compare("V") == 0) 
		Index = false;
	else if (test.compare("I") == 0) 
		Index = true;
		
	test.clear();
	file>>test;
	if (test.compare("S") == 0) 
		Static = true;
	else if (test.compare("A") == 0) 
		Static = false;	
	
	file>>vertCount;
	normCount = vertCount*3;
	textCount = vertCount*2;

	verts = new GLfloat[vertCount*3];
	text = new GLfloat[textCount];
	norms = new GLfloat[normCount];
	tangents = new GLfloat[normCount];
	
	if(Index)
		indices = new GLuint[vertCount];
	
	if(!Static)
	{
		numBones = new GLfloat[vertCount];
		weights = new GLfloat[vertCount*4];
		matrixIndices = new GLfloat[vertCount*4];
	}
	
	try{

		for(int i=0;i<(vertCount*3)&&file>>verts[i];i++)
			{if(ret&NO_VERTS)//check that the return value is correct
							ret -= NO_VERTS;}
							
		for(int i=0;i<(textCount)&&file>>text[i];i++)
			{if(ret&NO_TEXT)//check that the return value is correct
							ret -= NO_TEXT;}
							
		for(int i=0;i<(normCount)&&file>>norms[i];i++)
			{if(ret&NO_NORMS)//check that the return value is correct
							ret -= NO_NORMS;}
		for(int i=0;i<(normCount)&&file>>tangents[i];i++)
			{if(ret&NO_NORMS)//check that the return value is correct
							ret -= NO_NORMS;}
		if(Index)
		{
		}
		if(!Static)
		{
			for(int i=0;i<(vertCount)&&file>>numBones[i];i++);
			//check that the return value is correct
			for(int i=0;i<(vertCount*4)&&file>>weights[i];i++);
			//check that the return value is correct
			for(int i=0;i<(vertCount*4)&&file>>matrixIndices[i];i++);
			//check that the return value is correct
		}
		if(file>>textureName)
			if(file>>normalmapName);
		
		if(file>>properties)
		{
			//std::clog<<"Should be "<<properties<<" properties."<<std::endl;
			
			for(int i=0;i<properties;i++)
			{
				if(file>>temp)
				{
					if(temp.compare("VS") == 0)
					{
						file>>vertexShader;
						//std::clog<<"Should have loaded VS: "<<vertexShader<<std::endl;
					}
					else if(temp.compare("FS") == 0)
					{
						file>>fragmentShader;	
						//std::clog<<"Should have loaded FS: "<<fragmentShader<<std::endl;
					}
					else if(temp.compare("UI") == 0)
					{
						if(uniforms == 0)
						{
							file>>uniCount;
							uniforms = new string[uniCount];
							currentUniform = 0;
						}
						else
							file>>temp;
					}
					else if(temp.compare("UD") == 0)
					{
						if(uniforms != 0&&currentUniform<uniCount)
						{
							file>>uniforms[currentUniform];
							currentUniform++;
						}
					}
				}
			}
		}
		
	}catch(...)
	{
		std::clog<<"mesh file loading error! (invalid file or memory error)"<<endl;
		exit(0);
	}

	return ret;//GET OUT OF MY SIGHT!!! ... j/k <.<
}

//Testing print
void mFile::print(ostream& out = cout)
{
	out<<"Vert count: "<<vertCount<<"\n"
		<<"Normal count: "<<normCount<<"\n"
		<<"Texture coords count: "<<textCount<<endl;
	
	if(Index)
		out<<"Indexed"<<endl;
	else
		out<<"Not Indexed"<<endl;
		
	if(Static)
		out<<"Static"<<endl;
	else
		out<<"Animated"<<endl;
		
	out<<"Verts: "<<endl;
	for(int i=0; i<vertCount*3&&verts != 0;i+=3)
		{for(int j=i;j<i+3;j++)
			out<<verts[j]<<" ";
		out<<endl;
		}
	out<<endl;
	
	out<<"Normals: "<<endl;
	for(int i=0; i<normCount&&norms != 0;i+=3)
		{for(int j=i;j<i+3;j++)
			out<<norms[j]<<" ";
		out<<endl;
		}
	out<<endl;
	
	out<<"texture coords: "<<endl;
	for(int i=0; i<textCount&&text != 0;i+=2)
		{for(int j=i;j<i+2;j++)
			out<<text[j]<<" ";
		out<<endl;
		}
	out<<endl;
	
	out<<"Tangents: "<<endl;
	for(int i=0; i<normCount&&tangents != 0;i+=3)
		{for(int j=i;j<i+3;j++)
			out<<tangents[j]<<" ";
		out<<endl;
		}
	out<<endl;
	
	if(indices != 0)
	{
		out<<"indices: "<<endl;
		for(int i=0; i<normCount&&indices != 0;i+=3)
			{for(int j=i;j<i+3;j++)
				out<<indices[j]<<" ";
			out<<endl;
			}
		out<<endl;
	}
		
	if(weights != 0)
	{
		out<<"weights: "<<endl;
		for(int i=0; i<normCount&&weights != 0;i+=3)
			{for(int j=i;j<i+3;j++)
				out<<weights[j]<<" ";
			out<<endl;
			}
		out<<endl;
	}
	
	if(matrixIndices != 0)
	{
		out<<"matrixIndices: "<<endl;
		for(int i=0; i<normCount&&matrixIndices != 0;i+=3)
			{for(int j=i;j<i+3;j++)
				out<<matrixIndices[j]<<" ";
			out<<endl;
			}
		out<<endl;
	}
	
	if(numBones != 0)
	{
		out<<"numBones: "<<endl;
		for(int i=0; i<vertCount&&numBones != 0;i++)
		{
			out<<numBones[i]<<" ";
			out<<endl;
		}
		out<<endl;
	}
	
//test */
} 

mFile::~mFile()
{
	//if(objnames != 0)
	//	delete [] objnames;
	if(verts != 0)
		delete [] verts;
	if(norms != 0)
		delete [] norms;
	if(text != 0)
		delete [] text;
	if(tangents != 0)
		delete [] tangents;
	if(weights != 0)
		delete [] weights;
	if(matrixIndices != 0)
		delete [] matrixIndices;
	if(numBones != 0)
		delete [] numBones;
	if(indices != 0)
		delete [] indices;
	if(uniforms != 0)
		delete [] uniforms;
		
	if(file.is_open())file.close();
}


#endif
