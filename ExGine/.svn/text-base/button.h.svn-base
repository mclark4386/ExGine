#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "widgets.h"

class Button:public Widget
{
public:
	Button();
	Button(int _x, int _y, int _w, int _h);
	~Button(){delete [] plane; delete [] planeUV; delete [] color;};
	int reposition(int _x, int _y);
	int reshape(int _w, int _h);
	void draw(GLuint textureUnit = 0);
protected:
	int w;
	int h;
	int x;
	int y;	
	
	GLuint* BufferName;

	GLfloat* plane;
	GLfloat* planeUV;
	GLubyte* color;
	GLfloat* norm;
	
	Texture* textures[2];
	
	string hitFilename;
	
	enum
	{
		POSITION_OBJECT=0, //marker for the position VBO
		UV_OBJECT=1,//marker for the UV VBO
		NORMAL_OBJECT=2,//marker for the normal VBO
		COLOR_OBJECT=3//marker for the color VBO
	}markers;
};

Button::Button()
{
	x=0;y=0;w=50;h=50; filename = "testbutton.tga"; hitFilename = "testbutton_hit.tga";
	BufferName = new GLuint[4];
	plane = new GLfloat[8];
	
	plane[0] = (GLfloat)x; plane[1] = (GLfloat)y;
	plane[2] = (GLfloat)x; plane[3] = (GLfloat)y+h;
	plane[4] = (GLfloat)x+w; plane[5] = (GLfloat)y+h;
	plane[6] = (GLfloat)x+w; plane[7] = (GLfloat)y;
	
	planeUV = new GLfloat[8];
	
	planeUV[0] = 0.0; planeUV[1] = 0.0;
	planeUV[2] = 0.0; planeUV[3] = 1.0;
	planeUV[4] = 1.0; planeUV[5] = 1.0;
	planeUV[6] = 1.0; planeUV[7] = 0.0;
	
	color = new GLubyte[12];
	
	color[0]=1.0, color[1]=0.0,color[2]=1.0;
	color[3]=1.0, color[4]=0.0,color[5]=1.0;
	color[6]=1.0, color[7]=0.0,color[8]=1.0;
	color[9]=1.0, color[10]=0.0,color[11]=1.0;
	
	norm = new GLfloat[3];
	
	norm[0]=0.0; norm[1]=0.0; norm[2]=1.0;
	
	glGenBuffers(4,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), planeUV, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(GLfloat), norm, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLubyte), color, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), plane, GL_STATIC_DRAW);
	
	Texture* temp;
	
	textures[0] = new Texture();
	
	int tempText = textures[0]->load(filename.c_str());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::cout<<"diffuse is the wrong format"<<std::endl;
				break;
			case TFILE_NOFILE:
				std::cout<<"diffuse not found"<<std::endl;
				break;
			case TFILE_NOREAD:
				std::cout<<"diffuse not readable"<<std::endl;
				break;
			case TFILE_OOM:
				std::cout<<"don't have the memory to load the diffuse"<<std::endl;
				break;
			default:
				std::cout<<"unknown error loading diffuse"<<std::endl;
				break;
		}
		temp = textures[0];
		textures[0] = 0;
		delete temp;
	}
	
	textures[1] = new Texture();
	
	tempText = textures[1]->load(hitFilename.c_str());
	
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::cout<<"normal map is the wrong format"<<std::endl;
				break;
			case TFILE_NOFILE:
				std::cout<<"normal map not found"<<std::endl;
				break;
			case TFILE_NOREAD:
				std::cout<<"normal map not readable"<<std::endl;
				break;
			case TFILE_OOM:
				std::cout<<"don't have the memory to load the normal map"<<std::endl;
				break;
			default:
				std::cout<<"unknown error loading normal map"<<std::endl;
				break;
		}
		temp = textures[1];
		textures[1] = 0;
		delete temp;
	}//*/
}

Button::Button(int _x, int _y, int _w, int _h, string _filename, string _hitFilename)
{
	x=_x;y=_y;w=_w;h=_h;
	filename = _filename;
	hitFilename = _hitFilename;
	BufferName = new GLuint[4];
	plane = new GLfloat[8];
	
	plane[0] = (GLfloat)x; plane[1] = (GLfloat)y;
	plane[2] = (GLfloat)x; plane[3] = (GLfloat)y+h;
	plane[4] = (GLfloat)x+w; plane[5] = (GLfloat)y+h;
	plane[6] = (GLfloat)x+w; plane[7] = (GLfloat)y;
	
	planeUV = new GLfloat[8];
	
	planeUV[0] = 0.0; planeUV[1] = 0.0;
	planeUV[2] = 0.0; planeUV[3] = 1.0;
	planeUV[4] = 1.0; planeUV[5] = 1.0;
	planeUV[6] = 1.0; planeUV[7] = 0.0;
	
	color = new GLubyte[12];
	
	color[0]=1.0, color[1]=0.0,color[2]=1.0;
	color[3]=1.0, color[4]=0.0,color[5]=1.0;
	color[6]=1.0, color[7]=0.0,color[8]=1.0;
	color[9]=1.0, color[10]=0.0,color[11]=1.0;
	
	norm = new GLfloat[3];
	
	norm[0]=0.0; norm[1]=0.0; norm[2]=1.0;
	
	glGenBuffers(4,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), planeUV, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(GLfloat), norm, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLubyte), color, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(GLfloat), plane, GL_STATIC_DRAW);
	
	Texture* temp;
	
	textures[0] = new Texture();
	
	int tempText = textures[0]->load(filename.c_str());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::cout<<"diffuse is the wrong format"<<std::endl;
				break;
			case TFILE_NOFILE:
				std::cout<<"diffuse not found"<<std::endl;
				break;
			case TFILE_NOREAD:
				std::cout<<"diffuse not readable"<<std::endl;
				break;
			case TFILE_OOM:
				std::cout<<"don't have the memory to load the diffuse"<<std::endl;
				break;
			default:
				std::cout<<"unknown error loading diffuse"<<std::endl;
				break;
		}
		temp = textures[0];
		textures[0] = 0;
		delete temp;
	}
	
	textures[1] = new Texture();
	
	tempText = textures[1]->load(hitFilename.c_str());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::cout<<"normal map is the wrong format"<<std::endl;
				break;
			case TFILE_NOFILE:
				std::cout<<"normal map not found"<<std::endl;
				break;
			case TFILE_NOREAD:
				std::cout<<"normal map not readable"<<std::endl;
				break;
			case TFILE_OOM:
				std::cout<<"don't have the memory to load the normal map"<<std::endl;
				break;
			default:
				std::cout<<"unknown error loading normal map"<<std::endl;
				break;
		}
		temp = textures[1];
		textures[1] = 0;
		delete temp;
	}//*/
}

int Button::reshape(int _w, int _h)
{
	w=_w;
	h=_h;
	return 0;
}

int Button::reposition(int _x, int _y)
{
	x=_x;
	y=_y;
	return 0;
}

void Button::draw(GLuint textureUnit)
{
	try
	{
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind to the UV buffer...
	glTexCoordPointer(2, GL_FLOAT, 0, 0);//and read it 
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind to the Normal buffer...
	glNormalPointer(GL_FLOAT, 0, 0);//and read it
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind to the pos. buffer...
	glVertexPointer(2,GL_FLOAT, 0,0);//and read it
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind to the color buffer...
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, 0);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	if(textures[0])
		textures[0]->applyToModel();
	
	glDrawArrays(GL_QUADS, 0, 4);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	}
	catch(...)
	{std::cout<<"error!"<<std::endl;}
}
#endif
