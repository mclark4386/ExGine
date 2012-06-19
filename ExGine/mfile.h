//test format
#ifndef __MFILE_H__
#define __MFILE_H__

#include "exogl.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>//test    */

#include <string>
#include <fstream>

#define MFILE_VERSION "EXO_MODEL_V1.2"

using namespace std;

class mFile
{
public:
	mFile(){verts=0;norms=0;text=0;tangents=0;vertCount=0;normCount=0;textCount=0; Index = false;Static = true;};
	mFile(const char* filename){tangents=0;verts=0;norms=0;text=0;vertCount=0;normCount=0;textCount=0;open(filename);}
	~mFile();
	int open(const char* filename);
	void print();//test function   */
	GLfloat* getVerts(){return verts;};
	GLfloat* getNorms(){return norms;};
	GLfloat* getText(){return text;};
	GLfloat* getTangents(){return tangents;};
	bool isIndexed(){return Index;};
	bool isStatic(){return Static;};
	const char* getTextureName(){return textureName.c_str();};
	const char* getNormalmapName(){return normalmapName.c_str();};
	const char* getFilename(){return filename.c_str();};
	int getVertCount(){return vertCount;};
	
	
protected:

	int vertCount;
	int normCount;
	int textCount;
	
	GLfloat* verts;
	GLfloat* norms;
	GLfloat* text;
	GLfloat* tangents;
	
	fstream file;
	
	string filename;
	
	string textureName;
	
	string normalmapName;
	
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

	if (file.eof()) return ret;
	string test;
	file>>test;
	if (test.compare(MFILE_VERSION) != 0) return ret;
	
	test.clear();
	file>>test;
	if (test.compare("V") !=0) 
		Index = false;
	else if (test.compare("I") !=0) 
		Index = true;
		
	test.clear();
	file>>test;
	if (test.compare("S") !=0) 
		Static = true;
	else if (test.compare("A") !=0) 
		Static = false;	
	
	file>>vertCount;
	normCount = vertCount*3;
	textCount = vertCount*2;

	verts = new GLfloat[vertCount*3];
	text = new GLfloat[textCount];
	norms = new GLfloat[normCount];
	tangents = new GLfloat[normCount];

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
		if(file>>textureName)
			if(file>>normalmapName);
	}catch(...)
	{
		cout<<"error!"<<endl;
		exit(0);
	}

	return ret;//GET OUT OF MY SIGHT!!! ... j/k <.<
}

//Testing print
void mFile::print()
{
	cout<<"Vert count: "<<vertCount<<endl
		<<"Normal count: "<<normCount<<endl
		<<"Texture coords count: "<<textCount<<endl;
		
	cout<<"Verts: "<<endl;
	for(int i=0; i<vertCount*3&&verts != 0;i+=3)
		{for(int j=i;j<i+3;j++)
			cout<<verts[j]<<" ";
		cout<<endl;
		}
	cout<<endl;
	
	cout<<"Normals: "<<endl;
	for(int i=0; i<normCount&&norms != 0;i+=3)
		{for(int j=i;j<i+3;j++)
			cout<<norms[j]<<" ";
		cout<<endl;
		}
	cout<<endl;
	
	cout<<"texture coords: "<<endl;
	for(int i=0; i<textCount&&text != 0;i+=2)
		{for(int j=i;j<i+2;j++)
			cout<<text[j]<<" ";
		 cout<<endl;
		}
	cout<<endl;
	
	cout<<"Tangents: "<<endl;
	for(int i=0; i<normCount&&tangents != 0;i+=3)
		{for(int j=i;j<i+3;j++)
			cout<<tangents[j]<<" ";
		cout<<endl;
		}
	cout<<endl;
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
	if(file.is_open())file.close();
}


#endif
