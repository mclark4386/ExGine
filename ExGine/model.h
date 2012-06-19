#ifndef __MODEL_H__
#define __MODEL_H__

//#include "base_elements.h"
#include "object.h"
#include "mfile.h"
#include "texture.h"
#include "glslProgram.h"
#include "animation.h"

class Model
{
public:
	Model(){};
	Model(string _name){};
	Model(mFile* file){};
	~Model();
	void open(string _name);
	virtual void draw(glslProgram* shaderProgram = NULL, bool textured = true, Animation* ani = NULL) = 0; //function to callback
	const char* getName(){return name.c_str();};
	void toggleMipmaps();
	void recolorCode();
	bool checkColor(GLubyte color[]);
	bool isAnimated(){return false;};
protected:
	GLsizeiptr PositionSize;//size of pos. data  
	GLsizeiptr ColorSize;//size of color data
	GLsizeiptr NormalSize;//size of color data
	GLsizeiptr UVSize;//size of color data
	
	int BufferSize;
	
	int VertCount;

	string name;
	
	Texture* textures[2];
	
	GLubyte Color[3];	
	static GLubyte nextColor[3];
	
	GLuint* BufferName;//made it dynamic for win I start playing with files
	
	enum
	{
		POSITION_OBJECT=0, //marker for the position VBO
		UV_OBJECT=1,//marker for the UV VBO
		NORMAL_OBJECT=2,//marker for the normal VBO
		COLOR_OBJECT=3,//marker for the color VBO
		TANGENT_OBJECT=4//marker for the tangents VBO
	}markers;
};

class StaticModel:public Model
{
public:
	StaticModel();
	StaticModel(string _name);
	StaticModel(mFile* file);
	~StaticModel();
	void draw(glslProgram* shaderProgram, bool textured, Animation* ani); //function to callback
};

GLubyte Model::nextColor[3] = {1, 0, 0};

StaticModel::StaticModel()
{	
	BufferSize=5;
	VertCount=0;
	name = "test-plane.em";
	mFile* myM=new mFile(name.c_str());
	//myM->print();//test
	VertCount = myM->getVertCount();
	
	
	BufferName = new GLuint[BufferSize];//setup the buffer names or handles	
	PositionSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
	//PositionData = new GLfloat[VertCount*3];
	
	UVSize = VertCount //number of verts
				  *2 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	NormalSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	ColorSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLubyte);//times the size per float
	GLubyte* ColorData = new GLubyte[VertCount*3];
	
	Color[0] = nextColor[0];
	Color[1] = nextColor[1];
	Color[2] = nextColor[2];
	
	nextColor[0]++;
	if(nextColor[0] == 255)
	{
		nextColor[0] = 0;
		nextColor[1]++;
		if(nextColor[1] == 255)
		{
			nextColor[1] = 0;
			nextColor[2]++;
		}
	}
				  
	//load model color
	#pragma omp parallel for			  
	for(int i=0;i<VertCount;i++)
	{
		ColorData[i*3] = Color[0]; ColorData[(i*3)+1] = Color[1]; ColorData[(i*3)+2] = Color[2];
	}	
	
	glGenBuffers(5,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, UVSize, myM->getText(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getNorms(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind this buffer to the position buffername or handle 	
	//glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STREAM_DRAW);//load the position data into the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, PositionSize, myM->getVerts(), GL_STATIC_DRAW);//load the position data into the buffer//for static models

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models
		
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);//bind this buffer to the tangent buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the tangent data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getTangents(), GL_STATIC_DRAW);//load the tangent data to the buffer//for static models
		
	Texture* temp;
	
	textures[0] = new Texture();
	
	int tempText = textures[0]->load(myM->getTextureName());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"diffuse is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"diffuse not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"diffuse not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the diffuse\n";
				break;
			default:
				std::clog<<"unknown error loading diffuse\n";
				break;
		}
		temp = textures[0];
		textures[0] = 0;
		delete temp;
	}
	
	textures[1] = new Texture();
	
	tempText = textures[1]->load(myM->getNormalmapName());
	
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"normal map is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"normal map not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"normal map not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the normal map\n";
				break;
			default:
				std::clog<<"unknown error loading normal map\n";
				break;
		}
		temp = textures[1];
		textures[1] = 0;
		delete temp;
	}//*/
	
	delete myM;
}

Model::~Model()
{
	//delete [] PositionData;
	glDeleteBuffers(5, BufferName);
	delete textures[0];
	delete textures[1];
	delete [] BufferName;
}

void StaticModel::draw(glslProgram* shaderProgram = NULL, bool textured = true, Animation* ani =NULL)
{	
	std::cout<<"Static"<<std::endl;
	if(shaderProgram != NULL)
	{
		//std::clog<<"using shader\n";
		shaderProgram->use();
	}
	
	try
	{
	if(textured)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glClientActiveTexture(GL_TEXTURE0);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind to the UV buffer...
		glTexCoordPointer(2, GL_FLOAT, 0, 0);//and read it 	
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		if(textures[0])
		{
			if(!glIsEnabled(GL_TEXTURE0))
					glActiveTexture(GL_TEXTURE0);
			textures[0]->applyToModel();
			if(shaderProgram != NULL)
				shaderProgram->sendUniform("tex",0);
		}
	
		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_2D);
		glClientActiveTexture(GL_TEXTURE1);
		glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind to the UV buffer...
		glTexCoordPointer(2, GL_FLOAT, 0, 0);//and read it 	
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		
		if(textures[1])
		{
			if(!glIsEnabled(GL_TEXTURE1))
				glActiveTexture(GL_TEXTURE1);
			textures[1]->applyToModel();
			if(shaderProgram != NULL)
				shaderProgram->sendUniform("nmb",1);
		}
	}
		
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_3D);
	glClientActiveTexture(GL_TEXTURE2);
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);//bind to the Normal buffer...
	glTexCoordPointer(3, GL_FLOAT, 0, 0);//and read it
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_3D, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind to the Normal buffer...
	glNormalPointer(GL_FLOAT, 0, 0);//and read it
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind to the pos. buffer...
	glVertexPointer(3,GL_FLOAT, 0,0);//and read it
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind to the pos. buffer...
	glColorPointer(3,GL_UNSIGNED_BYTE, 0,0);//and read it
		
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glDrawArrays(GL_TRIANGLES, 0, VertCount);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
	}
	catch(...)
	{std::clog<<"error!\n";}
	
	if(shaderProgram != NULL)
		shaderProgram->disable();
}

StaticModel::StaticModel(mFile* myM)
{
	BufferSize=5;
	VertCount=0;
	name = myM->getFilename();
	//myM->print();//test
	VertCount = myM->getVertCount();
	
	//For testing... comment
	/*std::clog<<myM->getFilename()<<"\n"
			<<myM->getVertexShader()<<"\n"
			<<myM->getFragmentShader()<<std::endl;//*/
	
	BufferName = new GLuint[BufferSize];//setup the buffer names or handles	
	PositionSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
	//PositionData = new GLfloat[VertCount*3];
	
	//PositionData = myM->getVerts();
		
	UVSize = VertCount //number of verts
				  *2 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	NormalSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	ColorSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLubyte);//times the size per float
	GLubyte* ColorData = new GLubyte[VertCount*3];
				  
	Color[0] = nextColor[0];
	Color[1] = nextColor[1];
	Color[2] = nextColor[2];
	
	nextColor[0]++;
	if(nextColor[0] == 255)
	{
		nextColor[0] = 0;
		nextColor[1]++;
		if(nextColor[1] == 255)
		{
			nextColor[1] = 0;
			nextColor[2]++;
		}
	}
				  
	//load model color	
	#pragma omp parallel for		  
	for(int i=0;i<VertCount;i++)
	{
		ColorData[i*3] = Color[0]; ColorData[(i*3)+1] = Color[1]; ColorData[(i*3)+2] = Color[2];
	}
	
	glGenBuffers(5,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, UVSize, myM->getText(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getNorms(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	//glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind this buffer to the position buffername or handle 	
	//glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STREAM_DRAW);//load the position data into the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, PositionSize, myM->getVerts(), GL_STATIC_DRAW);//load the position data into the buffer//for static models

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);//bind this buffer to the tangent buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the tangent data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getTangents(), GL_STATIC_DRAW);//load the tangent data to the buffer//for static models
	
	Texture* temp;
	
	textures[0] = new Texture();
	
	int tempText = textures[0]->load(myM->getTextureName());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"diffuse is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"diffuse not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"diffuse not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the diffuse\n";
				break;
			default:
				std::clog<<"unknown error loading diffuse\n";
				break;
		}
		temp = textures[0];
		textures[0] = 0;
		delete temp;
	}
	
	textures[1] = new Texture();
	
	tempText = textures[1]->load(myM->getNormalmapName());
	
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"normal map is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"normal map not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"normal map not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the normal map\n";
				break;
			default:
				std::clog<<"unknown error loading normal map\n";
				break;
		}
		temp = textures[1];
		textures[1] = 0;
		delete temp;
	}//*/
	
	delete myM;
}


StaticModel::StaticModel(string _name)
{
	BufferSize=5;
	VertCount=0;
	name = _name;
	mFile* myM=new mFile(name.c_str());
	//myM->print();//test
	VertCount = myM->getVertCount();
	
	
	BufferName = new GLuint[BufferSize];//setup the buffer names or handles	
	PositionSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
	//PositionData = new GLfloat[VertCount*3];
	
	//PositionData = myM->getVerts();
		
	UVSize = VertCount //number of verts
				  *2 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	NormalSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	ColorSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLubyte);//times the size per float
	GLubyte* ColorData = new GLubyte[VertCount*3];
				  
	Color[0] = nextColor[0];
	Color[1] = nextColor[1];
	Color[2] = nextColor[2];
	
	nextColor[0]++;
	if(nextColor[0] == 255)
	{
		nextColor[0] = 0;
		nextColor[1]++;
		if(nextColor[1] == 255)
		{
			nextColor[1] = 0;
			nextColor[2]++;
		}
	}
				  
	//load model color	
	#pragma omp parallel for		  
	for(int i=0;i<VertCount;i++)
	{
		ColorData[i*3] = Color[0]; ColorData[(i*3)+1] = Color[1]; ColorData[(i*3)+2] = Color[2];
	}
	
	glGenBuffers(5,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, UVSize, myM->getText(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getNorms(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	//glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind this buffer to the position buffername or handle 	
	//glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STREAM_DRAW);//load the position data into the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, PositionSize, myM->getVerts(), GL_STATIC_DRAW);//load the position data into the buffer//for static models

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);//bind this buffer to the tangent buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the tangent data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getTangents(), GL_STATIC_DRAW);//load the tangent data to the buffer//for static models
	
	Texture* temp;
	
	textures[0] = new Texture();
	
	int tempText = textures[0]->load(myM->getTextureName());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"diffuse is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"diffuse not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"diffuse not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the diffuse\n";
				break;
			default:
				std::clog<<"unknown error loading diffuse\n";
				break;
		}
		temp = textures[0];
		textures[0] = 0;
		delete temp;
	}
	
	textures[1] = new Texture();
	
	tempText = textures[1]->load(myM->getNormalmapName());
	
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"normal map is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"normal map not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"normal map not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the normal map\n";
				break;
			default:
				std::clog<<"unknown error loading normal map\n";
				break;
		}
		temp = textures[1];
		textures[1] = 0;
		delete temp;
	}//*/
	
	delete myM;
}

void Model::open(string _name)
{
	BufferSize =4;
	name = "\0";
	name = _name;
	VertCount = 0;
	mFile* myM=new mFile(name.c_str());
	//myM->print();//test
	VertCount = myM->getVertCount();
	
	GLuint* bntemp = BufferName;
	BufferName = new GLuint[BufferSize];//setup the buffer names or handles	
	glDeleteBuffers(3, bntemp);
	delete [] bntemp;
	PositionSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
	//PositionData = new GLfloat[VertCount*3];
	
	//PositionData = myM->getVerts();
		
	UVSize = VertCount //number of verts
				  *2 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	NormalSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	ColorSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLubyte);//times the size per float
	GLubyte* ColorData = new GLubyte[VertCount*3];
				  
	Color[0] = nextColor[0];
	Color[1] = nextColor[1];
	Color[2] = nextColor[2];
	
	nextColor[0]++;
	if(nextColor[0] == 255)
	{
		nextColor[0] = 0;
		nextColor[1]++;
		if(nextColor[1] == 255)
		{
			nextColor[1] = 0;
			nextColor[2]++;
		}
	}
				  
	//load model color	
	#pragma omp parallel for		  
	for(int i=0;i<VertCount;i++)
	{
		ColorData[i*3] = Color[0]; ColorData[(i*3)+1] = Color[1]; ColorData[(i*3)+2] = Color[2];
	}
	
	glGenBuffers(4,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, UVSize, myM->getText(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getNorms(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind this buffer to the position buffername or handle 	
	//glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STREAM_DRAW);//load the position data into the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, PositionSize, myM->getVerts(), GL_STATIC_DRAW);//load the position data into the buffer//for static models

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models

	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[TANGENT_OBJECT]);//bind this buffer to the tangent buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the tangent data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, myM->getTangents(), GL_STATIC_DRAW);//load the tangent data to the buffer//for static models
	
	
	Texture* ttemp;
	
	ttemp = textures[0];
	textures[0] = new Texture();
	delete ttemp;
	
	int tempText = textures[0]->load(myM->getTextureName());
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"diffuse is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"diffuse not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"diffuse not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the diffuse\n";
				break;
			default:
				std::clog<<"unknown error loading diffuse\n";
				break;
		}
		ttemp = textures[0];
		textures[0] = 0;
		delete ttemp;
	}
	
	ttemp = textures[1];
	textures[1] = new Texture();
	delete ttemp;
	
	tempText = textures[1]->load(myM->getNormalmapName());
	
	
	if(tempText != TFILE_OPEN)
	{
		switch(tempText)
		{
			case TFILE_BAD_FORMAT:
				std::clog<<"normal map is the wrong format\n";
				break;
			case TFILE_NOFILE:
				std::clog<<"normal map not found\n";
				break;
			case TFILE_NOREAD:
				std::clog<<"normal map not readable\n";
				break;
			case TFILE_OOM:
				std::clog<<"don't have the memory to load the normal map\n";
				break;
			default:
				std::clog<<"unknown error loading normal map\n";
				break;
		}
		ttemp = textures[1];
		textures[1] = 0;
		delete ttemp;
	}//*/
	
	delete myM;
}

void Model::toggleMipmaps()
{
	if(textures[0])
		textures[0]->toggleMipmaps();
	if(textures[1])
		textures[1]->toggleMipmaps();
}

bool Model::checkColor(GLubyte color[])
{
	//std::clog<<"color checking: ("<<color[0]<<","<<color[1]<<","<<color[2]<<")";
	//std::clog<<" model color: ("<<Color[0]<<","<<Color[1]<<","<<Color[2]<<")\n";
	
		if(color[0] == Color[0]&&color[1] == Color[1]&&color[2] == Color[2])
		{
				return true;
		}
		return false;
}

void Model::recolorCode()
{
	GLubyte* ColorData = new GLubyte[VertCount*3];
	
	Color[0] = nextColor[0];
	Color[1] = nextColor[1];
	Color[2] = nextColor[2];
	
	nextColor[0]++;
	if(nextColor[0] == 255)
	{
		nextColor[0] = 0;
		nextColor[1]++;
		if(nextColor[1] == 255)
		{
			nextColor[1] = 0;
			nextColor[2]++;
		}
	}
				  
	//load model color	
	#pragma omp parallel for		  
	for(int i=0;i<VertCount;i++)
	{
		ColorData[i*3] = Color[0]; ColorData[(i*3)+1] = Color[1]; ColorData[(i*3)+2] = Color[2];
	}	
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);//bind this buffer to the color buffername or handle
	glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);//load the color data to the buffer//for static models

}

#endif
