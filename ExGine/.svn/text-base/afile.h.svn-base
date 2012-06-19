//test format
#ifndef __AFILE_H__
#define __AFILE_H__

#include "exogl.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>//test    */

#include <string>
#include <fstream>

#include <map>

#define AFILE_VERSION "EXO_ANIMATION_V1.0"

using namespace std;

class aFile
{
public:
	aFile(){frames=0; frameCount=0; boneCount=0; fps=0.0f;loops=false;error = false;};
	aFile(const char* filename){frames=0; frameCount=0; boneCount=0; fps=0.0f; loops=false;error = false;open(filename);}
	~aFile();
	int open(const char* filename);
	void print(ostream& out);//test function   */
	void operator<<(ostream& out){print(out);};
	GLfloat* getFrames(){return frames;};
	const char* getFilename(){return filename.c_str();};
	int getFrameCount(){return frameCount;};
	int getBoneCount(){return boneCount;};
	float getFramesPerSecond(){return fps;};
	bool isLooping(){return loops;};
	bool isError(){return error;};
protected:

	int frameCount, boneCount;
	float fps;
	bool loops;
	bool error;
	
	GLfloat* frames;
	
	fstream file;
	
	string filename;
	
	enum{
		NO_FRAMES = 0x00000001,
		FAIL_OPEN = 0x00001000,
		IS_OPEN = 0x000100000
	};
		
};

int aFile::open(const char* _filename)
{
	filename = _filename;
	file.open(filename.c_str(), ios::in);//open file for input
	if(!file.is_open())//if that doesn't work
		return FAIL_OPEN;//return our shame
	int ret = NO_FRAMES;//init the return value
	string temp;

	if (file.eof()) return ret;
	string test;
	file>>test;
	if (test.compare(AFILE_VERSION) != 0) return ret;
	
	file>>frameCount;
	file>>boneCount;
	file>>fps;
	
	if (boneCount>100)
	{
		error = true;
		return FAIL_OPEN;
	}

	frames = new GLfloat[frameCount*boneCount*8];
	
	try{

		for(int i=0;i<(frameCount);i++)
			for(int j=0;j<(boneCount*8)&&file>>frames[(i*boneCount*8)+j];j++)
				{if(ret&NO_FRAMES)//check that the return value is correct
							ret -= NO_FRAMES;}
		test.clear();
		if(file>>test&&test.compare("TRUE") == 0)
			loops = true;
		
	}catch(...)
	{
		std::clog<<"animation file loading error! (invalid file or memory error)"<<endl;
		exit(0);
	}

	return ret;//GET OUT OF MY SIGHT!!! ... j/k <.<
}

//Testing print
void aFile::print(ostream& out = cout)
{

	out<<"frame count: "<<frameCount<<"\n"
		<<"bone count: "<<boneCount<<"\n"
		<<"Frames pre second: "<<fps<<endl;
	
	if(loops)
		out<<"Looped"<<endl;
	else
		out<<"Not looped"<<endl;
	
	if(frames != 0)
	{
		out<<"frames: "<<endl;
		for(int i=0; i<frameCount;i++)
		{
			out<<"Frame["<<i<<"]:"<<endl;
			for(int j=0;j<(boneCount*8);j++)
				out<<frames[(i*boneCount*8)+j]<<" ";
			out<<endl;
		}
		out<<endl;
	}
	
//test */
} 

aFile::~aFile()
{
	//if(objnames != 0)
	//	delete [] objnames;
		
	if(file.is_open())file.close();
}


#endif
