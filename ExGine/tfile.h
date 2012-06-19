#ifndef __TFILE_H__
#define __TFILE_H__

#define 	TFILE_OPEN			0
#define		TFILE_NOFILE		1
#define		TFILE_BAD_FORMAT	2
#define		TFILE_OOM 			3
#define		TFILE_NOREAD 		4

#include <fstream>
#include <cstdlib>

class tfile
{
public:
	tfile(){data = 0;};
	~tfile(){delete [] data;};	
	int load(const char* filename);
	short int getWidth(){return width;};
	short int getHeight(){return height;};
	GLenum getFormat(){return format;};
	unsigned char getType(){return type;};
	unsigned char getBPP(){return bpp;};
	unsigned char* getData(){return data;};
protected:
	GLenum format;
	short int width;
	short int height;
	unsigned char type;
	unsigned char bpp;
	unsigned char* data;
};

int tfile::load(const char* filename)
{
	//we are dealing with a binary file so it's easier to go this route
	FILE* fp;
	//temp files for reading and switching
	unsigned char tempRGB;
	unsigned char tempUC;
	unsigned short tempUS;
	
	fp = fopen(filename, "rb");
	
	if(!fp)
		return TFILE_NOFILE;
		
	//don't need first 2 bytes (id length and color map type)
	fread(&tempUC,sizeof(unsigned char),1,fp);
	fread(&tempUC,sizeof(unsigned char),1,fp);
	//get what type of tga it is
	fread(&type,sizeof(unsigned char),1,fp);
	//only support uncompressed RGB(A)[2] and uncompressed B&W [3]
	if(type != 2 && type != 3)
	{
		fclose(fp);
		return TFILE_BAD_FORMAT;
	}
	
	//don't need color map origin
	fread(&tempUS,sizeof(unsigned short),1,fp);
	//don't need color map length
	fread(&tempUS,sizeof(unsigned short),1,fp);
	//don't need color map entry size
	fread(&tempUC,sizeof(unsigned char),1,fp);
	//don't need origin X
	fread(&tempUS,sizeof(unsigned short),1,fp);
	//don't need origin Y
	fread(&tempUS,sizeof(unsigned short),1,fp);
	//get width, height and bits per pixel of image
	fread(&width,sizeof(short int),1,fp);
	fread(&height,sizeof(short int),1,fp);
	fread(&bpp,sizeof(unsigned char),1,fp);
	//don't need the descriptor
	fread(&tempUC,sizeof(unsigned char),1,fp);
	//set the format from the bpp
	if(bpp/8 == 3)
		format = GL_RGB;
	else
		format = GL_RGBA;
	//save some calcs by only calcing the image length in bytes once
	long length = width * height * (bpp/8);
	//resize the data dynamic array
	data = new unsigned char[length];
	
	//if we don't have the memory for the image array
	if(!data)
	{
		fclose(fp);
		return TFILE_OOM;
	}		
	//get the image data from the file
	fread(data,sizeof(unsigned char),length,fp);
	if(!data)
	{
		fclose(fp);
		return TFILE_NOREAD;
	}
	//tga stores the bytes in BGR format so now we need to switch them
	#pragma omp parallel for
	for(int i=0;i<length;i += (bpp/8))
	{
		tempRGB = data[i];
		data[i] = data[i+2];
		data[i+2] = tempRGB;
	}
	//we are now done with the file
	fclose(fp);
	
	return TFILE_OPEN;
}
#endif
