#ifndef __ANIMATEDMODEL_H__
#define __ANIMATEDMODEL_H__

#include "model.h"
#include "animation.h"

/*************************************
 * 
 * transforms....
 * 
 * ***********************************/

class AModel:public Model
{
public:
	AModel(){};
	AModel(mFile* myM);
	~AModel(){};
	void draw(glslProgram* shaderProgram, bool textured, Animation* ani);
	bool isAnimated(){return true;};
protected:
	bool update();
	
	GLsizeiptr WeightsSize;//size of color data
	GLsizeiptr NumBonesSize;//size of color data
	GLsizeiptr MatrixIndicesSize;//size of color data
		
	enum
	{
		NUMBONES_OBJECT=5, //marker for the numBones attribute
		WEIGHTS_OBJECT=6,//marker for the 
		MATRIXINDICES_OBJECT=7,//marker for the 
	}amarkers;
};

AModel::AModel(mFile* myM)
{
	std::clog<<"Animated"<<std::endl;
	
	BufferSize = 8;
	VertCount = 0;
	
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
	
	NumBonesSize = VertCount //number of verts
				  *sizeof(GLfloat);//times the size per float 
				  
	WeightsSize = VertCount //number of verts
				  *4 //times the number of possible bones per vert
				  *sizeof(GLubyte);//times the size per float
				  
	MatrixIndicesSize = VertCount //number of verts
				  *4 //times the number of possible bones per vert
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
	
	glGenBuffers(8,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
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

	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NUMBONES_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NumBonesSize, myM->getNumBones(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[WEIGHTS_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, WeightsSize, myM->getWeights(), GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[MATRIXINDICES_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, MatrixIndicesSize, myM->getMatrixIndices(), GL_STATIC_DRAW);//load the color data to the buffer//for static models

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

void AModel::draw(glslProgram* shaderProgram = NULL, bool textured = true, Animation* ani = NULL)
{
		std::cout<<"Animated"<<std::endl;
	static glslProgram* defaultAShader = new glslProgram("data/shaders/test.AM.vs","data/shaders/test.fs");string log;
	defaultAShader->GetFullLog(log);
	std::clog<<"Animated Shader Log:\n"<<log<<std::endl;
	//if(shaderProgram == NULL)
	//{
		shaderProgram = defaultAShader;
	//}/
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
	
	//if(ani != NULL)
	//{
		shaderProgram->sendUniform("boneAnimation", ani->getCurrentFrames(), false, ani->getBoneCount());
		shaderProgram->sendUniform("delta", ani->getCurrentDelta());
	//}
		
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
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NUMBONES_OBJECT]);
	glVertexAttribPointer(shaderProgram->getAttributeLocation("numBones"), 1, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[WEIGHTS_OBJECT]);
	glVertexAttribPointer(shaderProgram->getAttributeLocation("weights"), 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[MATRIXINDICES_OBJECT]);
	glVertexAttribPointer(shaderProgram->getAttributeLocation("matrixIndices"), 4, GL_FLOAT, GL_FALSE, 0, 0);
		
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableVertexAttribArray(shaderProgram->getAttributeLocation("numBones"));
	glEnableVertexAttribArray(shaderProgram->getAttributeLocation("weights"));
	glEnableVertexAttribArray(shaderProgram->getAttributeLocation("matrixIndices"));
	
	glDrawArrays(GL_TRIANGLES, 0, VertCount);
	
	glDisableVertexAttribArray(shaderProgram->getAttributeLocation("matrixIndices"));
	glDisableVertexAttribArray(shaderProgram->getAttributeLocation("weights"));
	glDisableVertexAttribArray(shaderProgram->getAttributeLocation("numBones"));
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

bool AModel::update()
{
	return true;
}

#endif
