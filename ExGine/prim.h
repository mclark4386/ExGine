#ifndef __PRIM_H__
#define __PRIM_H__

#include "object.h"

class Plane:public Object
{
public:
	Plane(Scalar _xScale, Scalar _yScale);
	~Plane();
	void draw(GLuint textureUnit);
	void rescale(float _xScale=1, float _yScale=1);
protected:
	GLfloat verts[6*3];
	GLfloat norms[6*3];
	GLfloat uvs[6*2];
	GLuint* BufferName;
	float xScale, yScale;
	
	enum
	{
		POSITION_OBJECT=0, //marker for the position VBO
		UV_OBJECT=1,//marker for the UV VBO
		NORMAL_OBJECT=2,//marker for the normal VBO
		COLOR_OBJECT=3,//marker for the color VBO
		TANGENT_OBJECT=4//marker for the tangents VBO
	}markers;
};

Plane::Plane(Scalar _xScale=1, Scalar _yScale=1)
{
	xScale = _xScale;
	yScale = _yScale;
	//init the verts
	verts[0]=0.5;verts[1]=0.5;verts[2]=0.0;
	verts[3]=-0.5;verts[4]=0.5;verts[5]=0.0;
	verts[6]=-0.5;verts[7]=-0.5;verts[8]=0.0;
	verts[9]=0.5;verts[10]=0.5;verts[11]=0.0;
	verts[12]=-0.5;verts[13]=-0.5;verts[14]=0.0;
	verts[15]=0.5;verts[16]=-0.5;verts[17]=0.0;

	//init the norms
	norms[0]=0.0;norms[1]=0.0;norms[2]=1.0;
	norms[3]=0.0;norms[4]=0.0;norms[5]=1.0;
	norms[6]=0.0;norms[7]=0.0;norms[8]=1.0;
	norms[9]=0.0;norms[10]=0.0;norms[11]=1.0;
	norms[12]=0.0;norms[13]=0.0;norms[14]=1.0;
	norms[15]=0.0;norms[16]=0.0;norms[17]=1.0;

	//init uvs
	uvs[0]=1.0;uvs[1]=1.0;
	uvs[2]=0.0;uvs[3]=1.0;
	uvs[4]=-0.0;uvs[5]=0.0;
	uvs[6]=1.0;uvs[7]=1.0;
	uvs[8]=-0.0;uvs[9]=0.0;
	uvs[10]=1.0;uvs[11]=-0.0;
	
	int VertCount = 6;
	
	
	BufferName = new GLuint[3];//setup the buffer names or handles	
	int PositionSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
	//PositionData = new GLfloat[VertCount*3];
	
	//PositionData = myM->getVerts();
		
	int UVSize = VertCount //number of verts
				  *2 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
				  
	int NormalSize = VertCount //number of verts
				  *3 //times the number of coords per vert
				  *sizeof(GLfloat);//times the size per float
	
	glGenBuffers(3,BufferName);//generate "3" buffers using the buffername/handle array "BufferName"
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, UVSize, &uvs, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	//above here is just init. the variables, now we setup the buffers
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind this buffer to the color buffername or handle
	//glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STREAM_DRAW);//load the color data to the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, NormalSize, &norms, GL_STATIC_DRAW);//load the color data to the buffer//for static models
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind this buffer to the position buffername or handle 	
	//glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STREAM_DRAW);//load the position data into the buffer//for animated models
	glBufferData(GL_ARRAY_BUFFER, PositionSize, &verts, GL_STATIC_DRAW);//load the position data into the buffer//for static models	
}		

Plane::~Plane()
{
	glDeleteBuffers(3, BufferName);
	delete [] BufferName;
}

void Plane::draw(GLuint textureUnit = 0)
{
	glScalef(xScale,yScale,1.0f);
	try
	{
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glEnable(GL_TEXTURE_2D);
	glClientActiveTexture(GL_TEXTURE0+textureUnit);
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[UV_OBJECT]);//bind to the UV buffer...
	glTexCoordPointer(2, GL_FLOAT, 0, 0);//and read it 
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[NORMAL_OBJECT]);//bind to the Normal buffer...
	glNormalPointer(GL_FLOAT, 0, 0);//and read it
	
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);//bind to the pos. buffer...
	glVertexPointer(3,GL_FLOAT, 0,0);//and read it
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	//glScalef(xScale, yScale, 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	catch(...)
	{std::cout<<"error in prim plane draw!"<<std::endl;}
}

class Sphere:public Object
{
	public:
Sphere(float _xScale, float _yScale, float _zScale);
	~Sphere();
	void draw(GLuint textureUnit);
	void rescale(float _xScale=1, float _yScale=1, float _zScale=1);
protected:
	GLfloat verts[240*3];
	GLfloat norms[240*3];
	GLfloat uvs[240*2];
	GLuint* BufferName;
	float xScale, yScale, zScale;
};

Sphere::Sphere(float _xScale=1, float _yScale=1, float _zScale=1)
{
	//init the verts
	verts[0]=0.262869;verts[1]=-0.809012;verts[2]=-0.525738;
	verts[3]=0.425323;verts[4]=-0.309011;verts[5]=-0.850654;
	verts[6]=0.7236;verts[7]=-0.52572;verts[8]=-0.447215;
	verts[9]=0.425323;verts[10]=-0.309011;verts[11]=-0.850654;
	verts[12]=0.262869;verts[13]=-0.809012;verts[14]=-0.525738;
	verts[15]=-0.162456;verts[16]=-0.499995;verts[17]=-0.850654;
	verts[18]=-0.276385;verts[19]=-0.85064;verts[20]=-0.447215;
	verts[21]=-0.162456;verts[22]=-0.499995;verts[23]=-0.850654;
	verts[24]=0.262869;verts[25]=-0.809012;verts[26]=-0.525738;
	verts[27]=-0.162456;verts[28]=-0.499995;verts[29]=-0.850654;
	verts[30]=0;verts[31]=0;verts[32]=-1;
	verts[33]=0.425323;verts[34]=-0.309011;verts[35]=-0.850654;
	verts[36]=0.850648;verts[37]=0;verts[38]=-0.525736;
	verts[39]=0.7236;verts[40]=-0.52572;verts[41]=-0.447215;
	verts[42]=0.425323;verts[43]=-0.309011;verts[44]=-0.850654;
	verts[45]=0.425323;verts[46]=-0.309011;verts[47]=-0.850654;
	verts[48]=0.425323;verts[49]=0.309011;verts[50]=-0.850654;
	verts[51]=0.850648;verts[52]=0;verts[53]=-0.525736;
	verts[54]=0.7236;verts[55]=0.52572;verts[56]=-0.447215;
	verts[57]=0.850648;verts[58]=0;verts[59]=-0.525736;
	verts[60]=0.425323;verts[61]=0.309011;verts[62]=-0.850654;
	verts[63]=0.425323;verts[64]=-0.309011;verts[65]=-0.850654;
	verts[66]=0;verts[67]=0;verts[68]=-1;
	verts[69]=0.425323;verts[70]=0.309011;verts[71]=-0.850654;
	verts[72]=-0.688189;verts[73]=-0.499997;verts[74]=-0.525736;
	verts[75]=-0.162456;verts[76]=-0.499995;verts[77]=-0.850654;
	verts[78]=-0.276385;verts[79]=-0.85064;verts[80]=-0.447215;
	verts[81]=-0.162456;verts[82]=-0.499995;verts[83]=-0.850654;
	verts[84]=-0.688189;verts[85]=-0.499997;verts[86]=-0.525736;
	verts[87]=-0.52573;verts[88]=0;verts[89]=-0.850652;
	verts[90]=-0.894425;verts[91]=0;verts[92]=-0.447215;
	verts[93]=-0.52573;verts[94]=0;verts[95]=-0.850652;
	verts[96]=-0.688189;verts[97]=-0.499997;verts[98]=-0.525736;
	verts[99]=-0.52573;verts[100]=0;verts[101]=-0.850652;
	verts[102]=0;verts[103]=0;verts[104]=-1;
	verts[105]=-0.162456;verts[106]=-0.499995;verts[107]=-0.850654;
	verts[108]=-0.688189;verts[109]=0.499997;verts[110]=-0.525736;
	verts[111]=-0.52573;verts[112]=0;verts[113]=-0.850652;
	verts[114]=-0.894425;verts[115]=0;verts[116]=-0.447215;
	verts[117]=-0.52573;verts[118]=0;verts[119]=-0.850652;
	verts[120]=-0.688189;verts[121]=0.499997;verts[122]=-0.525736;
	verts[123]=-0.162456;verts[124]=0.499995;verts[125]=-0.850654;
	verts[126]=-0.276385;verts[127]=0.85064;verts[128]=-0.447215;
	verts[129]=-0.162456;verts[130]=0.499995;verts[131]=-0.850654;
	verts[132]=-0.688189;verts[133]=0.499997;verts[134]=-0.525736;
	verts[135]=-0.162456;verts[136]=0.499995;verts[137]=-0.850654;
	verts[138]=0;verts[139]=0;verts[140]=-1;
	verts[141]=-0.52573;verts[142]=0;verts[143]=-0.850652;
	verts[144]=0.262869;verts[145]=0.809012;verts[146]=-0.525738;
	verts[147]=-0.162456;verts[148]=0.499995;verts[149]=-0.850654;
	verts[150]=-0.276385;verts[151]=0.85064;verts[152]=-0.447215;
	verts[153]=-0.162456;verts[154]=0.499995;verts[155]=-0.850654;
	verts[156]=0.262869;verts[157]=0.809012;verts[158]=-0.525738;
	verts[159]=0.425323;verts[160]=0.309011;verts[161]=-0.850654;
	verts[162]=0.7236;verts[163]=0.52572;verts[164]=-0.447215;
	verts[165]=0.425323;verts[166]=0.309011;verts[167]=-0.850654;
	verts[168]=0.262869;verts[169]=0.809012;verts[170]=-0.525738;
	verts[171]=0.425323;verts[172]=0.309011;verts[173]=-0.850654;
	verts[174]=0;verts[175]=0;verts[176]=-1;
	verts[177]=-0.162456;verts[178]=0.499995;verts[179]=-0.850654;
	verts[180]=0.951058;verts[181]=-0.309013;verts[182]=0;
	verts[183]=0.7236;verts[184]=-0.52572;verts[185]=-0.447215;
	verts[186]=0.850648;verts[187]=0;verts[188]=-0.525736;
	verts[189]=0.850648;verts[190]=0;verts[191]=-0.525736;
	verts[192]=0.951058;verts[193]=0.309013;verts[194]=0;
	verts[195]=0.951058;verts[196]=-0.309013;verts[197]=0;
	verts[198]=0.894425;verts[199]=0;verts[200]=0.447215;
	verts[201]=0.951058;verts[202]=-0.309013;verts[203]=0;
	verts[204]=0.951058;verts[205]=0.309013;verts[206]=0;
	verts[207]=0.951058;verts[208]=0.309013;verts[209]=0;
	verts[210]=0.850648;verts[211]=0;verts[212]=-0.525736;
	verts[213]=0.7236;verts[214]=0.52572;verts[215]=-0.447215;
	verts[216]=0;verts[217]=-1;verts[218]=0;
	verts[219]=-0.276385;verts[220]=-0.85064;verts[221]=-0.447215;
	verts[222]=0.262869;verts[223]=-0.809012;verts[224]=-0.525738;
	verts[225]=0.262869;verts[226]=-0.809012;verts[227]=-0.525738;
	verts[228]=0.587786;verts[229]=-0.809017;verts[230]=0;
	verts[231]=0;verts[232]=-1;verts[233]=0;
	verts[234]=0.276385;verts[235]=-0.85064;verts[236]=0.447215;
	verts[237]=0;verts[238]=-1;verts[239]=0;
	verts[240]=0.587786;verts[241]=-0.809017;verts[242]=0;
	verts[243]=0.587786;verts[244]=-0.809017;verts[245]=0;
	verts[246]=0.262869;verts[247]=-0.809012;verts[248]=-0.525738;
	verts[249]=0.7236;verts[250]=-0.52572;verts[251]=-0.447215;
	verts[252]=-0.951058;verts[253]=-0.309013;verts[254]=0;
	verts[255]=-0.894425;verts[256]=0;verts[257]=-0.447215;
	verts[258]=-0.688189;verts[259]=-0.499997;verts[260]=-0.525736;
	verts[261]=-0.688189;verts[262]=-0.499997;verts[263]=-0.525736;
	verts[264]=-0.587786;verts[265]=-0.809017;verts[266]=0;
	verts[267]=-0.951058;verts[268]=-0.309013;verts[269]=0;
	verts[270]=-0.7236;verts[271]=-0.52572;verts[272]=0.447215;
	verts[273]=-0.951058;verts[274]=-0.309013;verts[275]=0;
	verts[276]=-0.587786;verts[277]=-0.809017;verts[278]=0;
	verts[279]=-0.587786;verts[280]=-0.809017;verts[281]=0;
	verts[282]=-0.688189;verts[283]=-0.499997;verts[284]=-0.525736;
	verts[285]=-0.276385;verts[286]=-0.85064;verts[287]=-0.447215;
	verts[288]=-0.587786;verts[289]=0.809017;verts[290]=0;
	verts[291]=-0.276385;verts[292]=0.85064;verts[293]=-0.447215;
	verts[294]=-0.688189;verts[295]=0.499997;verts[296]=-0.525736;
	verts[297]=-0.688189;verts[298]=0.499997;verts[299]=-0.525736;
	verts[300]=-0.951058;verts[301]=0.309013;verts[302]=0;
	verts[303]=-0.587786;verts[304]=0.809017;verts[305]=0;
	verts[306]=-0.7236;verts[307]=0.52572;verts[308]=0.447215;
	verts[309]=-0.587786;verts[310]=0.809017;verts[311]=0;
	verts[312]=-0.951058;verts[313]=0.309013;verts[314]=0;
	verts[315]=-0.951058;verts[316]=0.309013;verts[317]=0;
	verts[318]=-0.688189;verts[319]=0.499997;verts[320]=-0.525736;
	verts[321]=-0.894425;verts[322]=0;verts[323]=-0.447215;
	verts[324]=0.587786;verts[325]=0.809017;verts[326]=0;
	verts[327]=0.7236;verts[328]=0.52572;verts[329]=-0.447215;
	verts[330]=0.262869;verts[331]=0.809012;verts[332]=-0.525738;
	verts[333]=0.262869;verts[334]=0.809012;verts[335]=-0.525738;
	verts[336]=0;verts[337]=1;verts[338]=0;
	verts[339]=0.587786;verts[340]=0.809017;verts[341]=0;
	verts[342]=0.276385;verts[343]=0.85064;verts[344]=0.447215;
	verts[345]=0.587786;verts[346]=0.809017;verts[347]=0;
	verts[348]=0;verts[349]=1;verts[350]=0;
	verts[351]=0;verts[352]=1;verts[353]=0;
	verts[354]=0.262869;verts[355]=0.809012;verts[356]=-0.525738;
	verts[357]=-0.276385;verts[358]=0.85064;verts[359]=-0.447215;
	verts[360]=0.688189;verts[361]=-0.499997;verts[362]=0.525736;
	verts[363]=0.951058;verts[364]=-0.309013;verts[365]=0;
	verts[366]=0.894425;verts[367]=0;verts[368]=0.447215;
	verts[369]=0.951058;verts[370]=-0.309013;verts[371]=0;
	verts[372]=0.688189;verts[373]=-0.499997;verts[374]=0.525736;
	verts[375]=0.587786;verts[376]=-0.809017;verts[377]=0;
	verts[378]=0.276385;verts[379]=-0.85064;verts[380]=0.447215;
	verts[381]=0.587786;verts[382]=-0.809017;verts[383]=0;
	verts[384]=0.688189;verts[385]=-0.499997;verts[386]=0.525736;
	verts[387]=0.587786;verts[388]=-0.809017;verts[389]=0;
	verts[390]=0.7236;verts[391]=-0.52572;verts[392]=-0.447215;
	verts[393]=0.951058;verts[394]=-0.309013;verts[395]=0;
	verts[396]=-0.262869;verts[397]=-0.809012;verts[398]=0.525738;
	verts[399]=0;verts[400]=-1;verts[401]=0;
	verts[402]=0.276385;verts[403]=-0.85064;verts[404]=0.447215;
	verts[405]=0;verts[406]=-1;verts[407]=0;
	verts[408]=-0.262869;verts[409]=-0.809012;verts[410]=0.525738;
	verts[411]=-0.587786;verts[412]=-0.809017;verts[413]=0;
	verts[414]=-0.7236;verts[415]=-0.52572;verts[416]=0.447215;
	verts[417]=-0.587786;verts[418]=-0.809017;verts[419]=0;
	verts[420]=-0.262869;verts[421]=-0.809012;verts[422]=0.525738;
	verts[423]=-0.587786;verts[424]=-0.809017;verts[425]=0;
	verts[426]=-0.276385;verts[427]=-0.85064;verts[428]=-0.447215;
	verts[429]=0;verts[430]=-1;verts[431]=0;
	verts[432]=-0.850648;verts[433]=0;verts[434]=0.525736;
	verts[435]=-0.951058;verts[436]=-0.309013;verts[437]=0;
	verts[438]=-0.7236;verts[439]=-0.52572;verts[440]=0.447215;
	verts[441]=-0.951058;verts[442]=-0.309013;verts[443]=0;
	verts[444]=-0.850648;verts[445]=0;verts[446]=0.525736;
	verts[447]=-0.951058;verts[448]=0.309013;verts[449]=0;
	verts[450]=-0.7236;verts[451]=0.52572;verts[452]=0.447215;
	verts[453]=-0.951058;verts[454]=0.309013;verts[455]=0;
	verts[456]=-0.850648;verts[457]=0;verts[458]=0.525736;
	verts[459]=-0.951058;verts[460]=0.309013;verts[461]=0;
	verts[462]=-0.894425;verts[463]=0;verts[464]=-0.447215;
	verts[465]=-0.951058;verts[466]=-0.309013;verts[467]=0;
	verts[468]=-0.262869;verts[469]=0.809012;verts[470]=0.525738;
	verts[471]=-0.587786;verts[472]=0.809017;verts[473]=0;
	verts[474]=-0.7236;verts[475]=0.52572;verts[476]=0.447215;
	verts[477]=-0.587786;verts[478]=0.809017;verts[479]=0;
	verts[480]=-0.262869;verts[481]=0.809012;verts[482]=0.525738;
	verts[483]=0;verts[484]=1;verts[485]=0;
	verts[486]=0.276385;verts[487]=0.85064;verts[488]=0.447215;
	verts[489]=0;verts[490]=1;verts[491]=0;
	verts[492]=-0.262869;verts[493]=0.809012;verts[494]=0.525738;
	verts[495]=0;verts[496]=1;verts[497]=0;
	verts[498]=-0.276385;verts[499]=0.85064;verts[500]=-0.447215;
	verts[501]=-0.587786;verts[502]=0.809017;verts[503]=0;
	verts[504]=0.688189;verts[505]=0.499997;verts[506]=0.525736;
	verts[507]=0.587786;verts[508]=0.809017;verts[509]=0;
	verts[510]=0.276385;verts[511]=0.85064;verts[512]=0.447215;
	verts[513]=0.587786;verts[514]=0.809017;verts[515]=0;
	verts[516]=0.688189;verts[517]=0.499997;verts[518]=0.525736;
	verts[519]=0.951058;verts[520]=0.309013;verts[521]=0;
	verts[522]=0.894425;verts[523]=0;verts[524]=0.447215;
	verts[525]=0.951058;verts[526]=0.309013;verts[527]=0;
	verts[528]=0.688189;verts[529]=0.499997;verts[530]=0.525736;
	verts[531]=0.951058;verts[532]=0.309013;verts[533]=0;
	verts[534]=0.7236;verts[535]=0.52572;verts[536]=-0.447215;
	verts[537]=0.587786;verts[538]=0.809017;verts[539]=0;
	verts[540]=0.162456;verts[541]=-0.499995;verts[542]=0.850654;
	verts[543]=0.276385;verts[544]=-0.85064;verts[545]=0.447215;
	verts[546]=0.688189;verts[547]=-0.499997;verts[548]=0.525736;
	verts[549]=0.688189;verts[550]=-0.499997;verts[551]=0.525736;
	verts[552]=0.52573;verts[553]=0;verts[554]=0.850652;
	verts[555]=0.162456;verts[556]=-0.499995;verts[557]=0.850654;
	verts[558]=0;verts[559]=0;verts[560]=1;
	verts[561]=0.162456;verts[562]=-0.499995;verts[563]=0.850654;
	verts[564]=0.52573;verts[565]=0;verts[566]=0.850652;
	verts[567]=0.52573;verts[568]=0;verts[569]=0.850652;
	verts[570]=0.688189;verts[571]=-0.499997;verts[572]=0.525736;
	verts[573]=0.894425;verts[574]=0;verts[575]=0.447215;
	verts[576]=-0.425323;verts[577]=-0.309011;verts[578]=0.850654;
	verts[579]=-0.7236;verts[580]=-0.52572;verts[581]=0.447215;
	verts[582]=-0.262869;verts[583]=-0.809012;verts[584]=0.525738;
	verts[585]=-0.262869;verts[586]=-0.809012;verts[587]=0.525738;
	verts[588]=0.162456;verts[589]=-0.499995;verts[590]=0.850654;
	verts[591]=-0.425323;verts[592]=-0.309011;verts[593]=0.850654;
	verts[594]=0;verts[595]=0;verts[596]=1;
	verts[597]=-0.425323;verts[598]=-0.309011;verts[599]=0.850654;
	verts[600]=0.162456;verts[601]=-0.499995;verts[602]=0.850654;
	verts[603]=0.162456;verts[604]=-0.499995;verts[605]=0.850654;
	verts[606]=-0.262869;verts[607]=-0.809012;verts[608]=0.525738;
	verts[609]=0.276385;verts[610]=-0.85064;verts[611]=0.447215;
	verts[612]=-0.425323;verts[613]=0.309011;verts[614]=0.850654;
	verts[615]=-0.7236;verts[616]=0.52572;verts[617]=0.447215;
	verts[618]=-0.850648;verts[619]=0;verts[620]=0.525736;
	verts[621]=-0.850648;verts[622]=0;verts[623]=0.525736;
	verts[624]=-0.425323;verts[625]=-0.309011;verts[626]=0.850654;
	verts[627]=-0.425323;verts[628]=0.309011;verts[629]=0.850654;
	verts[630]=0;verts[631]=0;verts[632]=1;
	verts[633]=-0.425323;verts[634]=0.309011;verts[635]=0.850654;
	verts[636]=-0.425323;verts[637]=-0.309011;verts[638]=0.850654;
	verts[639]=-0.425323;verts[640]=-0.309011;verts[641]=0.850654;
	verts[642]=-0.850648;verts[643]=0;verts[644]=0.525736;
	verts[645]=-0.7236;verts[646]=-0.52572;verts[647]=0.447215;
	verts[648]=0.162456;verts[649]=0.499995;verts[650]=0.850654;
	verts[651]=0.276385;verts[652]=0.85064;verts[653]=0.447215;
	verts[654]=-0.262869;verts[655]=0.809012;verts[656]=0.525738;
	verts[657]=-0.262869;verts[658]=0.809012;verts[659]=0.525738;
	verts[660]=-0.425323;verts[661]=0.309011;verts[662]=0.850654;
	verts[663]=0.162456;verts[664]=0.499995;verts[665]=0.850654;
	verts[666]=0;verts[667]=0;verts[668]=1;
	verts[669]=0.162456;verts[670]=0.499995;verts[671]=0.850654;
	verts[672]=-0.425323;verts[673]=0.309011;verts[674]=0.850654;
	verts[675]=-0.425323;verts[676]=0.309011;verts[677]=0.850654;
	verts[678]=-0.262869;verts[679]=0.809012;verts[680]=0.525738;
	verts[681]=-0.7236;verts[682]=0.52572;verts[683]=0.447215;
	verts[684]=0.52573;verts[685]=0;verts[686]=0.850652;
	verts[687]=0.894425;verts[688]=0;verts[689]=0.447215;
	verts[690]=0.688189;verts[691]=0.499997;verts[692]=0.525736;
	verts[693]=0.688189;verts[694]=0.499997;verts[695]=0.525736;
	verts[696]=0.162456;verts[697]=0.499995;verts[698]=0.850654;
	verts[699]=0.52573;verts[700]=0;verts[701]=0.850652;
	verts[702]=0;verts[703]=0;verts[704]=1;
	verts[705]=0.52573;verts[706]=0;verts[707]=0.850652;
	verts[708]=0.162456;verts[709]=0.499995;verts[710]=0.850654;
	verts[711]=0.162456;verts[712]=0.499995;verts[713]=0.850654;
	verts[714]=0.688189;verts[715]=0.499997;verts[716]=0.525736;
	verts[717]=0.276385;verts[718]=0.85064;verts[719]=0.447215;

	//init the norms

	norms[0]=0.262856;norms[1]=-0.808985;norms[2]=-0.525712;
	norms[3]=0.425306;norms[4]=-0.309;norms[5]=-0.850642;
	norms[6]=0.723594;norms[7]=-0.525712;norms[8]=-0.447188;
	norms[9]=0.425306;norms[10]=-0.309;norms[11]=-0.850642;
	norms[12]=0.262856;norms[13]=-0.808985;norms[14]=-0.525712;
	norms[15]=-0.16245;norms[16]=-0.499985;norms[17]=-0.850642;
	norms[18]=-0.276376;norms[19]=-0.850642;norms[20]=-0.447188;
	norms[21]=-0.16245;norms[22]=-0.499985;norms[23]=-0.850642;
	norms[24]=0.262856;norms[25]=-0.808985;norms[26]=-0.525712;
	norms[27]=-0.16245;norms[28]=-0.499985;norms[29]=-0.850642;
	norms[30]=0;norms[31]=0;norms[32]=-1;
	norms[33]=0.425306;norms[34]=-0.309;norms[35]=-0.850642;
	norms[36]=0.850642;norms[37]=0;norms[38]=-0.525712;
	norms[39]=0.723594;norms[40]=-0.525712;norms[41]=-0.447188;
	norms[42]=0.425306;norms[43]=-0.309;norms[44]=-0.850642;
	norms[45]=0.425306;norms[46]=-0.309;norms[47]=-0.850642;
	norms[48]=0.425306;norms[49]=0.309;norms[50]=-0.850642;
	norms[51]=0.850642;norms[52]=0;norms[53]=-0.525712;
	norms[54]=0.723594;norms[55]=0.525712;norms[56]=-0.447188;
	norms[57]=0.850642;norms[58]=0;norms[59]=-0.525712;
	norms[60]=0.425306;norms[61]=0.309;norms[62]=-0.850642;
	norms[63]=0.425306;norms[64]=-0.309;norms[65]=-0.850642;
	norms[66]=0;norms[67]=0;norms[68]=-1;
	norms[69]=0.425306;norms[70]=0.309;norms[71]=-0.850642;
	norms[72]=-0.688162;norms[73]=-0.499985;norms[74]=-0.525712;
	norms[75]=-0.16245;norms[76]=-0.499985;norms[77]=-0.850642;
	norms[78]=-0.276376;norms[79]=-0.850642;norms[80]=-0.447188;
	norms[81]=-0.16245;norms[82]=-0.499985;norms[83]=-0.850642;
	norms[84]=-0.688162;norms[85]=-0.499985;norms[86]=-0.525712;
	norms[87]=-0.525712;norms[88]=0;norms[89]=-0.850642;
	norms[90]=-0.894406;norms[91]=0;norms[92]=-0.447188;
	norms[93]=-0.525712;norms[94]=0;norms[95]=-0.850642;
	norms[96]=-0.688162;norms[97]=-0.499985;norms[98]=-0.525712;
	norms[99]=-0.525712;norms[100]=0;norms[101]=-0.850642;
	norms[102]=0;norms[103]=0;norms[104]=-1;
	norms[105]=-0.16245;norms[106]=-0.499985;norms[107]=-0.850642;
	norms[108]=-0.688162;norms[109]=0.499985;norms[110]=-0.525712;
	norms[111]=-0.525712;norms[112]=0;norms[113]=-0.850642;
	norms[114]=-0.894406;norms[115]=0;norms[116]=-0.447188;
	norms[117]=-0.525712;norms[118]=0;norms[119]=-0.850642;
	norms[120]=-0.688162;norms[121]=0.499985;norms[122]=-0.525712;
	norms[123]=-0.16245;norms[124]=0.499985;norms[125]=-0.850642;
	norms[126]=-0.276376;norms[127]=0.850642;norms[128]=-0.447188;
	norms[129]=-0.16245;norms[130]=0.499985;norms[131]=-0.850642;
	norms[132]=-0.688162;norms[133]=0.499985;norms[134]=-0.525712;
	norms[135]=-0.16245;norms[136]=0.499985;norms[137]=-0.850642;
	norms[138]=0;norms[139]=0;norms[140]=-1;
	norms[141]=-0.525712;norms[142]=0;norms[143]=-0.850642;
	norms[144]=0.262856;norms[145]=0.808985;norms[146]=-0.525712;
	norms[147]=-0.16245;norms[148]=0.499985;norms[149]=-0.850642;
	norms[150]=-0.276376;norms[151]=0.850642;norms[152]=-0.447188;
	norms[153]=-0.16245;norms[154]=0.499985;norms[155]=-0.850642;
	norms[156]=0.262856;norms[157]=0.808985;norms[158]=-0.525712;
	norms[159]=0.425306;norms[160]=0.309;norms[161]=-0.850642;
	norms[162]=0.723594;norms[163]=0.525712;norms[164]=-0.447188;
	norms[165]=0.425306;norms[166]=0.309;norms[167]=-0.850642;
	norms[168]=0.262856;norms[169]=0.808985;norms[170]=-0.525712;
	norms[171]=0.425306;norms[172]=0.309;norms[173]=-0.850642;
	norms[174]=0;norms[175]=0;norms[176]=-1;
	norms[177]=-0.16245;norms[178]=0.499985;norms[179]=-0.850642;
	norms[180]=0.951048;norms[181]=-0.309;norms[182]=0;
	norms[183]=0.723594;norms[184]=-0.525712;norms[185]=-0.447188;
	norms[186]=0.850642;norms[187]=0;norms[188]=-0.525712;
	norms[189]=0.850642;norms[190]=0;norms[191]=-0.525712;
	norms[192]=0.951048;norms[193]=0.309;norms[194]=0;
	norms[195]=0.951048;norms[196]=-0.309;norms[197]=0;
	norms[198]=0.894406;norms[199]=0;norms[200]=0.447188;
	norms[201]=0.951048;norms[202]=-0.309;norms[203]=0;
	norms[204]=0.951048;norms[205]=0.309;norms[206]=0;
	norms[207]=0.951048;norms[208]=0.309;norms[209]=0;
	norms[210]=0.850642;norms[211]=0;norms[212]=-0.525712;
	norms[213]=0.723594;norms[214]=0.525712;norms[215]=-0.447188;
	norms[216]=0;norms[217]=-1;norms[218]=0;
	norms[219]=-0.276376;norms[220]=-0.850642;norms[221]=-0.447188;
	norms[222]=0.262856;norms[223]=-0.808985;norms[224]=-0.525712;
	norms[225]=0.262856;norms[226]=-0.808985;norms[227]=-0.525712;
	norms[228]=0.587756;norms[229]=-0.809015;norms[230]=0;
	norms[231]=0;norms[232]=-1;norms[233]=0;
	norms[234]=0.276376;norms[235]=-0.850642;norms[236]=0.447188;
	norms[237]=0;norms[238]=-1;norms[239]=0;
	norms[240]=0.587756;norms[241]=-0.809015;norms[242]=0;
	norms[243]=0.587756;norms[244]=-0.809015;norms[245]=0;
	norms[246]=0.262856;norms[247]=-0.808985;norms[248]=-0.525712;
	norms[249]=0.723594;norms[250]=-0.525712;norms[251]=-0.447188;
	norms[252]=-0.951048;norms[253]=-0.309;norms[254]=0;
	norms[255]=-0.894406;norms[256]=0;norms[257]=-0.447188;
	norms[258]=-0.688162;norms[259]=-0.499985;norms[260]=-0.525712;
	norms[261]=-0.688162;norms[262]=-0.499985;norms[263]=-0.525712;
	norms[264]=-0.587756;norms[265]=-0.809015;norms[266]=0;
	norms[267]=-0.951048;norms[268]=-0.309;norms[269]=0;
	norms[270]=-0.723594;norms[271]=-0.525712;norms[272]=0.447188;
	norms[273]=-0.951048;norms[274]=-0.309;norms[275]=0;
	norms[276]=-0.587756;norms[277]=-0.809015;norms[278]=0;
	norms[279]=-0.587756;norms[280]=-0.809015;norms[281]=0;
	norms[282]=-0.688162;norms[283]=-0.499985;norms[284]=-0.525712;
	norms[285]=-0.276376;norms[286]=-0.850642;norms[287]=-0.447188;
	norms[288]=-0.587756;norms[289]=0.809015;norms[290]=0;
	norms[291]=-0.276376;norms[292]=0.850642;norms[293]=-0.447188;
	norms[294]=-0.688162;norms[295]=0.499985;norms[296]=-0.525712;
	norms[297]=-0.688162;norms[298]=0.499985;norms[299]=-0.525712;
	norms[300]=-0.951048;norms[301]=0.309;norms[302]=0;
	norms[303]=-0.587756;norms[304]=0.809015;norms[305]=0;
	norms[306]=-0.723594;norms[307]=0.525712;norms[308]=0.447188;
	norms[309]=-0.587756;norms[310]=0.809015;norms[311]=0;
	norms[312]=-0.951048;norms[313]=0.309;norms[314]=0;
	norms[315]=-0.951048;norms[316]=0.309;norms[317]=0;
	norms[318]=-0.688162;norms[319]=0.499985;norms[320]=-0.525712;
	norms[321]=-0.894406;norms[322]=0;norms[323]=-0.447188;
	norms[324]=0.587756;norms[325]=0.809015;norms[326]=0;
	norms[327]=0.723594;norms[328]=0.525712;norms[329]=-0.447188;
	norms[330]=0.262856;norms[331]=0.808985;norms[332]=-0.525712;
	norms[333]=0.262856;norms[334]=0.808985;norms[335]=-0.525712;
	norms[336]=0;norms[337]=1;norms[338]=0;
	norms[339]=0.587756;norms[340]=0.809015;norms[341]=0;
	norms[342]=0.276376;norms[343]=0.850642;norms[344]=0.447188;
	norms[345]=0.587756;norms[346]=0.809015;norms[347]=0;
	norms[348]=0;norms[349]=1;norms[350]=0;
	norms[351]=0;norms[352]=1;norms[353]=0;
	norms[354]=0.262856;norms[355]=0.808985;norms[356]=-0.525712;
	norms[357]=-0.276376;norms[358]=0.850642;norms[359]=-0.447188;
	norms[360]=0.688162;norms[361]=-0.499985;norms[362]=0.525712;
	norms[363]=0.951048;norms[364]=-0.309;norms[365]=0;
	norms[366]=0.894406;norms[367]=0;norms[368]=0.447188;
	norms[369]=0.951048;norms[370]=-0.309;norms[371]=0;
	norms[372]=0.688162;norms[373]=-0.499985;norms[374]=0.525712;
	norms[375]=0.587756;norms[376]=-0.809015;norms[377]=0;
	norms[378]=0.276376;norms[379]=-0.850642;norms[380]=0.447188;
	norms[381]=0.587756;norms[382]=-0.809015;norms[383]=0;
	norms[384]=0.688162;norms[385]=-0.499985;norms[386]=0.525712;
	norms[387]=0.587756;norms[388]=-0.809015;norms[389]=0;
	norms[390]=0.723594;norms[391]=-0.525712;norms[392]=-0.447188;
	norms[393]=0.951048;norms[394]=-0.309;norms[395]=0;
	norms[396]=-0.262856;norms[397]=-0.808985;norms[398]=0.525712;
	norms[399]=0;norms[400]=-1;norms[401]=0;
	norms[402]=0.276376;norms[403]=-0.850642;norms[404]=0.447188;
	norms[405]=0;norms[406]=-1;norms[407]=0;
	norms[408]=-0.262856;norms[409]=-0.808985;norms[410]=0.525712;
	norms[411]=-0.587756;norms[412]=-0.809015;norms[413]=0;
	norms[414]=-0.723594;norms[415]=-0.525712;norms[416]=0.447188;
	norms[417]=-0.587756;norms[418]=-0.809015;norms[419]=0;
	norms[420]=-0.262856;norms[421]=-0.808985;norms[422]=0.525712;
	norms[423]=-0.587756;norms[424]=-0.809015;norms[425]=0;
	norms[426]=-0.276376;norms[427]=-0.850642;norms[428]=-0.447188;
	norms[429]=0;norms[430]=-1;norms[431]=0;
	norms[432]=-0.850642;norms[433]=0;norms[434]=0.525712;
	norms[435]=-0.951048;norms[436]=-0.309;norms[437]=0;
	norms[438]=-0.723594;norms[439]=-0.525712;norms[440]=0.447188;
	norms[441]=-0.951048;norms[442]=-0.309;norms[443]=0;
	norms[444]=-0.850642;norms[445]=0;norms[446]=0.525712;
	norms[447]=-0.951048;norms[448]=0.309;norms[449]=0;
	norms[450]=-0.723594;norms[451]=0.525712;norms[452]=0.447188;
	norms[453]=-0.951048;norms[454]=0.309;norms[455]=0;
	norms[456]=-0.850642;norms[457]=0;norms[458]=0.525712;
	norms[459]=-0.951048;norms[460]=0.309;norms[461]=0;
	norms[462]=-0.894406;norms[463]=0;norms[464]=-0.447188;
	norms[465]=-0.951048;norms[466]=-0.309;norms[467]=0;
	norms[468]=-0.262856;norms[469]=0.808985;norms[470]=0.525712;
	norms[471]=-0.587756;norms[472]=0.809015;norms[473]=0;
	norms[474]=-0.723594;norms[475]=0.525712;norms[476]=0.447188;
	norms[477]=-0.587756;norms[478]=0.809015;norms[479]=0;
	norms[480]=-0.262856;norms[481]=0.808985;norms[482]=0.525712;
	norms[483]=0;norms[484]=1;norms[485]=0;
	norms[486]=0.276376;norms[487]=0.850642;norms[488]=0.447188;
	norms[489]=0;norms[490]=1;norms[491]=0;
	norms[492]=-0.262856;norms[493]=0.808985;norms[494]=0.525712;
	norms[495]=0;norms[496]=1;norms[497]=0;
	norms[498]=-0.276376;norms[499]=0.850642;norms[500]=-0.447188;
	norms[501]=-0.587756;norms[502]=0.809015;norms[503]=0;
	norms[504]=0.688162;norms[505]=0.499985;norms[506]=0.525712;
	norms[507]=0.587756;norms[508]=0.809015;norms[509]=0;
	norms[510]=0.276376;norms[511]=0.850642;norms[512]=0.447188;
	norms[513]=0.587756;norms[514]=0.809015;norms[515]=0;
	norms[516]=0.688162;norms[517]=0.499985;norms[518]=0.525712;
	norms[519]=0.951048;norms[520]=0.309;norms[521]=0;
	norms[522]=0.894406;norms[523]=0;norms[524]=0.447188;
	norms[525]=0.951048;norms[526]=0.309;norms[527]=0;
	norms[528]=0.688162;norms[529]=0.499985;norms[530]=0.525712;
	norms[531]=0.951048;norms[532]=0.309;norms[533]=0;
	norms[534]=0.723594;norms[535]=0.525712;norms[536]=-0.447188;
	norms[537]=0.587756;norms[538]=0.809015;norms[539]=0;
	norms[540]=0.16245;norms[541]=-0.499985;norms[542]=0.850642;
	norms[543]=0.276376;norms[544]=-0.850642;norms[545]=0.447188;
	norms[546]=0.688162;norms[547]=-0.499985;norms[548]=0.525712;
	norms[549]=0.688162;norms[550]=-0.499985;norms[551]=0.525712;
	norms[552]=0.525712;norms[553]=0;norms[554]=0.850642;
	norms[555]=0.16245;norms[556]=-0.499985;norms[557]=0.850642;
	norms[558]=0;norms[559]=0;norms[560]=1;
	norms[561]=0.16245;norms[562]=-0.499985;norms[563]=0.850642;
	norms[564]=0.525712;norms[565]=0;norms[566]=0.850642;
	norms[567]=0.525712;norms[568]=0;norms[569]=0.850642;
	norms[570]=0.688162;norms[571]=-0.499985;norms[572]=0.525712;
	norms[573]=0.894406;norms[574]=0;norms[575]=0.447188;
	norms[576]=-0.425306;norms[577]=-0.309;norms[578]=0.850642;
	norms[579]=-0.723594;norms[580]=-0.525712;norms[581]=0.447188;
	norms[582]=-0.262856;norms[583]=-0.808985;norms[584]=0.525712;
	norms[585]=-0.262856;norms[586]=-0.808985;norms[587]=0.525712;
	norms[588]=0.16245;norms[589]=-0.499985;norms[590]=0.850642;
	norms[591]=-0.425306;norms[592]=-0.309;norms[593]=0.850642;
	norms[594]=0;norms[595]=0;norms[596]=1;
	norms[597]=-0.425306;norms[598]=-0.309;norms[599]=0.850642;
	norms[600]=0.16245;norms[601]=-0.499985;norms[602]=0.850642;
	norms[603]=0.16245;norms[604]=-0.499985;norms[605]=0.850642;
	norms[606]=-0.262856;norms[607]=-0.808985;norms[608]=0.525712;
	norms[609]=0.276376;norms[610]=-0.850642;norms[611]=0.447188;
	norms[612]=-0.425306;norms[613]=0.309;norms[614]=0.850642;
	norms[615]=-0.723594;norms[616]=0.525712;norms[617]=0.447188;
	norms[618]=-0.850642;norms[619]=0;norms[620]=0.525712;
	norms[621]=-0.850642;norms[622]=0;norms[623]=0.525712;
	norms[624]=-0.425306;norms[625]=-0.309;norms[626]=0.850642;
	norms[627]=-0.425306;norms[628]=0.309;norms[629]=0.850642;
	norms[630]=0;norms[631]=0;norms[632]=1;
	norms[633]=-0.425306;norms[634]=0.309;norms[635]=0.850642;
	norms[636]=-0.425306;norms[637]=-0.309;norms[638]=0.850642;
	norms[639]=-0.425306;norms[640]=-0.309;norms[641]=0.850642;
	norms[642]=-0.850642;norms[643]=0;norms[644]=0.525712;
	norms[645]=-0.723594;norms[646]=-0.525712;norms[647]=0.447188;
	norms[648]=0.16245;norms[649]=0.499985;norms[650]=0.850642;
	norms[651]=0.276376;norms[652]=0.850642;norms[653]=0.447188;
	norms[654]=-0.262856;norms[655]=0.808985;norms[656]=0.525712;
	norms[657]=-0.262856;norms[658]=0.808985;norms[659]=0.525712;
	norms[660]=-0.425306;norms[661]=0.309;norms[662]=0.850642;
	norms[663]=0.16245;norms[664]=0.499985;norms[665]=0.850642;
	norms[666]=0;norms[667]=0;norms[668]=1;
	norms[669]=0.16245;norms[670]=0.499985;norms[671]=0.850642;
	norms[672]=-0.425306;norms[673]=0.309;norms[674]=0.850642;
	norms[675]=-0.425306;norms[676]=0.309;norms[677]=0.850642;
	norms[678]=-0.262856;norms[679]=0.808985;norms[680]=0.525712;
	norms[681]=-0.723594;norms[682]=0.525712;norms[683]=0.447188;
	norms[684]=0.525712;norms[685]=0;norms[686]=0.850642;
	norms[687]=0.894406;norms[688]=0;norms[689]=0.447188;
	norms[690]=0.688162;norms[691]=0.499985;norms[692]=0.525712;
	norms[693]=0.688162;norms[694]=0.499985;norms[695]=0.525712;
	norms[696]=0.16245;norms[697]=0.499985;norms[698]=0.850642;
	norms[699]=0.525712;norms[700]=0;norms[701]=0.850642;
	norms[702]=0;norms[703]=0;norms[704]=1;
	norms[705]=0.525712;norms[706]=0;norms[707]=0.850642;
	norms[708]=0.16245;norms[709]=0.499985;norms[710]=0.850642;
	norms[711]=0.16245;norms[712]=0.499985;norms[713]=0.850642;
	norms[714]=0.688162;norms[715]=0.499985;norms[716]=0.525712;
	norms[717]=0.276376;norms[718]=0.850642;norms[719]=0.447188;

	//init the norms

	uvs[0]=0.070041;uvs[1]=0.127489;
	uvs[2]=0.345513;uvs[3]=0.018843;
	uvs[4]=0.25671;uvs[5]=0.299154;
	uvs[6]=0.799413;uvs[7]=0.016041;
	uvs[8]=0.973345;uvs[9]=0.113091;
	uvs[10]=0.761232;uvs[11]=0.17386;
	uvs[12]=0.84907;uvs[13]=0.349457;
	uvs[14]=0.761232;uvs[15]=0.17386;
	uvs[16]=0.973345;uvs[17]=0.113091;
	uvs[18]=0.761232;uvs[19]=0.17386;
	uvs[20]=0.585236;uvs[21]=0.049992;
	uvs[22]=0.799413;uvs[23]=0.016041;
	uvs[24]=0.37185;uvs[25]=0.33093;
	uvs[26]=0.25671;uvs[27]=0.299154;
	uvs[28]=0.345513;uvs[29]=0.018843;
	uvs[30]=0.345513;uvs[31]=0.018843;
	uvs[32]=0.470825;uvs[33]=0.263762;
	uvs[34]=0.37185;uvs[35]=0.33093;
	uvs[36]=0.443752;uvs[37]=0.391496;
	uvs[38]=0.37185;uvs[39]=0.33093;
	uvs[40]=0.470825;uvs[41]=0.263762;
	uvs[42]=0.345513;uvs[43]=0.018843;
	uvs[44]=0.585236;uvs[45]=0.049992;
	uvs[46]=0.470825;uvs[47]=0.263762;
	uvs[48]=0.74016;uvs[49]=0.383515;
	uvs[50]=0.761232;uvs[51]=0.17386;
	uvs[52]=0.84907;uvs[53]=0.349457;
	uvs[54]=0.761232;uvs[55]=0.17386;
	uvs[56]=0.74016;uvs[57]=0.383515;
	uvs[58]=0.655224;uvs[59]=0.301533;
	uvs[60]=0.669244;uvs[61]=0.424481;
	uvs[62]=0.655224;uvs[63]=0.301533;
	uvs[64]=0.74016;uvs[65]=0.383515;
	uvs[66]=0.655224;uvs[67]=0.301533;
	uvs[68]=0.585236;uvs[69]=0.049992;
	uvs[70]=0.761232;uvs[71]=0.17386;
	uvs[72]=0.610471;uvs[73]=0.412778;
	uvs[74]=0.655224;uvs[75]=0.301533;
	uvs[76]=0.669244;uvs[77]=0.424481;
	uvs[78]=0.655224;uvs[79]=0.301533;
	uvs[80]=0.610471;uvs[81]=0.412778;
	uvs[82]=0.563608;uvs[83]=0.317401;
	uvs[84]=0.557188;uvs[85]=0.423418;
	uvs[86]=0.563608;uvs[87]=0.317401;
	uvs[88]=0.610471;uvs[89]=0.412778;
	uvs[90]=0.563608;uvs[91]=0.317401;
	uvs[92]=0.585236;uvs[93]=0.049992;
	uvs[94]=0.655224;uvs[95]=0.301533;
	uvs[96]=0.505202;uvs[97]=0.396308;
	uvs[98]=0.563608;uvs[99]=0.317401;
	uvs[100]=0.557188;uvs[101]=0.423418;
	uvs[102]=0.563608;uvs[103]=0.317401;
	uvs[104]=0.505202;uvs[105]=0.396308;
	uvs[106]=0.470825;uvs[107]=0.263762;
	uvs[108]=0.443752;uvs[109]=0.391496;
	uvs[110]=0.470825;uvs[111]=0.263762;
	uvs[112]=0.505202;uvs[113]=0.396308;
	uvs[114]=0.470825;uvs[115]=0.263762;
	uvs[116]=0.585236;uvs[117]=0.049992;
	uvs[118]=0.563608;uvs[119]=0.317401;
	uvs[120]=0.306593;uvs[121]=0.472843;
	uvs[122]=0.25671;uvs[123]=0.299154;
	uvs[124]=0.37185;uvs[125]=0.33093;
	uvs[126]=0.37185;uvs[127]=0.33093;
	uvs[128]=0.399894;uvs[129]=0.474515;
	uvs[130]=0.306593;uvs[131]=0.472843;
	uvs[132]=0.365434;uvs[133]=0.584014;
	uvs[134]=0.306593;uvs[135]=0.472843;
	uvs[136]=0.399894;uvs[137]=0.474515;
	uvs[138]=0.399894;uvs[139]=0.474515;
	uvs[140]=0.37185;uvs[141]=0.33093;
	uvs[142]=0.443752;uvs[143]=0.391496;
	uvs[144]=0.996065;uvs[145]=0.548444;
	uvs[146]=0.84907;uvs[147]=0.349457;
	uvs[148]=0.973345;uvs[149]=0.113091;
	uvs[150]=0.070041;uvs[151]=0.127489;
	uvs[152]=0.164796;uvs[153]=0.484292;
	uvs[154]=0.007635;uvs[155]=0.494994;
	uvs[156]=0.070257;uvs[157]=0.836224;
	uvs[158]=0.007635;uvs[159]=0.494994;
	uvs[160]=0.164796;uvs[161]=0.484292;
	uvs[162]=0.164796;uvs[163]=0.484292;
	uvs[164]=0.070041;uvs[165]=0.127489;
	uvs[166]=0.25671;uvs[167]=0.299154;
	uvs[168]=0.705352;uvs[169]=0.513436;
	uvs[170]=0.669244;uvs[171]=0.424481;
	uvs[172]=0.74016;uvs[173]=0.383515;
	uvs[174]=0.74016;uvs[175]=0.383515;
	uvs[176]=0.801473;uvs[177]=0.526965;
	uvs[178]=0.705352;uvs[179]=0.513436;
	uvs[180]=0.731746;uvs[181]=0.630335;
	uvs[182]=0.705352;uvs[183]=0.513436;
	uvs[184]=0.801473;uvs[185]=0.526965;
	uvs[186]=0.801473;uvs[187]=0.526965;
	uvs[188]=0.74016;uvs[189]=0.383515;
	uvs[190]=0.84907;uvs[191]=0.349457;
	uvs[192]=0.580483;uvs[193]=0.495366;
	uvs[194]=0.557188;uvs[195]=0.423418;
	uvs[196]=0.610471;uvs[197]=0.412778;
	uvs[198]=0.610471;uvs[199]=0.412778;
	uvs[200]=0.637358;uvs[201]=0.503723;
	uvs[202]=0.580483;uvs[203]=0.495366;
	uvs[204]=0.602506;uvs[205]=0.570233;
	uvs[206]=0.580483;uvs[207]=0.495366;
	uvs[208]=0.637358;uvs[209]=0.503723;
	uvs[210]=0.637358;uvs[211]=0.503723;
	uvs[212]=0.610471;uvs[213]=0.412778;
	uvs[214]=0.669244;uvs[215]=0.424481;
	uvs[216]=0.468867;uvs[217]=0.480697;
	uvs[218]=0.443752;uvs[219]=0.391496;
	uvs[220]=0.505202;uvs[221]=0.396308;
	uvs[222]=0.505202;uvs[223]=0.396308;
	uvs[224]=0.526463;uvs[225]=0.487775;
	uvs[226]=0.468867;uvs[227]=0.480697;
	uvs[228]=0.497174;uvs[229]=0.556099;
	uvs[230]=0.468867;uvs[231]=0.480697;
	uvs[232]=0.526463;uvs[233]=0.487775;
	uvs[234]=0.526463;uvs[235]=0.487775;
	uvs[236]=0.505202;uvs[237]=0.396308;
	uvs[238]=0.557188;uvs[239]=0.423418;
	uvs[240]=0.273953;uvs[241]=0.672183;
	uvs[242]=0.306593;uvs[243]=0.472843;
	uvs[244]=0.365434;uvs[245]=0.584014;
	uvs[246]=0.306593;uvs[247]=0.472843;
	uvs[248]=0.273953;uvs[249]=0.672183;
	uvs[250]=0.164796;uvs[251]=0.484292;
	uvs[252]=0.070257;uvs[253]=0.836224;
	uvs[254]=0.164796;uvs[255]=0.484292;
	uvs[256]=0.273953;uvs[257]=0.672183;
	uvs[258]=0.164796;uvs[259]=0.484292;
	uvs[260]=0.25671;uvs[261]=0.299154;
	uvs[262]=0.306593;uvs[263]=0.472843;
	uvs[264]=0.820322;uvs[265]=0.745361;
	uvs[266]=0.996065;uvs[267]=0.548444;
	uvs[268]=0.970477;uvs[269]=0.930755;
	uvs[270]=0.996065;uvs[271]=0.548444;
	uvs[272]=0.820322;uvs[273]=0.745361;
	uvs[274]=0.801473;uvs[275]=0.526965;
	uvs[276]=0.731746;uvs[277]=0.630335;
	uvs[278]=0.801473;uvs[279]=0.526965;
	uvs[280]=0.820322;uvs[281]=0.745361;
	uvs[282]=0.801473;uvs[283]=0.526965;
	uvs[284]=0.84907;uvs[285]=0.349457;
	uvs[286]=0.996065;uvs[287]=0.548444;
	uvs[288]=0.657594;uvs[289]=0.608518;
	uvs[290]=0.705352;uvs[291]=0.513436;
	uvs[292]=0.731746;uvs[293]=0.630335;
	uvs[294]=0.705352;uvs[295]=0.513436;
	uvs[296]=0.657594;uvs[297]=0.608518;
	uvs[298]=0.637358;uvs[299]=0.503723;
	uvs[300]=0.602506;uvs[301]=0.570233;
	uvs[302]=0.637358;uvs[303]=0.503723;
	uvs[304]=0.657594;uvs[305]=0.608518;
	uvs[306]=0.637358;uvs[307]=0.503723;
	uvs[308]=0.669244;uvs[309]=0.424481;
	uvs[310]=0.705352;uvs[311]=0.513436;
	uvs[312]=0.549353;uvs[313]=0.573688;
	uvs[314]=0.580483;uvs[315]=0.495366;
	uvs[316]=0.602506;uvs[317]=0.570233;
	uvs[318]=0.580483;uvs[319]=0.495366;
	uvs[320]=0.549353;uvs[321]=0.573688;
	uvs[322]=0.526463;uvs[323]=0.487775;
	uvs[324]=0.497174;uvs[325]=0.556099;
	uvs[326]=0.526463;uvs[327]=0.487775;
	uvs[328]=0.549353;uvs[329]=0.573688;
	uvs[330]=0.526463;uvs[331]=0.487775;
	uvs[332]=0.557188;uvs[333]=0.423418;
	uvs[334]=0.580483;uvs[335]=0.495366;
	uvs[336]=0.439226;uvs[337]=0.57985;
	uvs[338]=0.468867;uvs[339]=0.480697;
	uvs[340]=0.497174;uvs[341]=0.556099;
	uvs[342]=0.468867;uvs[343]=0.480697;
	uvs[344]=0.439226;uvs[345]=0.57985;
	uvs[346]=0.399894;uvs[347]=0.474515;
	uvs[348]=0.365434;uvs[349]=0.584014;
	uvs[350]=0.399894;uvs[351]=0.474515;
	uvs[352]=0.439226;uvs[353]=0.57985;
	uvs[354]=0.399894;uvs[355]=0.474515;
	uvs[356]=0.443752;uvs[357]=0.391496;
	uvs[358]=0.468867;uvs[359]=0.480697;
	uvs[360]=0.254347;uvs[361]=0.936976;
	uvs[362]=0.070257;uvs[363]=0.836224;
	uvs[364]=0.273953;uvs[365]=0.672183;
	uvs[366]=0.273953;uvs[367]=0.672183;
	uvs[368]=0.402239;uvs[369]=0.730785;
	uvs[370]=0.254347;uvs[371]=0.936976;
	uvs[372]=0.53122;uvs[373]=0.931906;
	uvs[374]=0.254347;uvs[375]=0.936976;
	uvs[376]=0.402239;uvs[377]=0.730785;
	uvs[378]=0.402239;uvs[379]=0.730785;
	uvs[380]=0.273953;uvs[381]=0.672183;
	uvs[382]=0.365434;uvs[383]=0.584014;
	uvs[384]=0.680229;uvs[385]=0.769369;
	uvs[386]=0.731746;uvs[387]=0.630335;
	uvs[388]=0.820322;uvs[389]=0.745361;
	uvs[390]=0.820322;uvs[391]=0.745361;
	uvs[392]=0.756524;uvs[393]=0.981151;
	uvs[394]=0.680229;uvs[395]=0.769369;
	uvs[396]=0.53122;uvs[397]=0.931906;
	uvs[398]=0.680229;uvs[399]=0.769369;
	uvs[400]=0.756524;uvs[401]=0.981151;
	uvs[402]=0.756524;uvs[403]=0.981151;
	uvs[404]=0.820322;uvs[405]=0.745361;
	uvs[406]=0.970477;uvs[407]=0.930755;
	uvs[408]=0.587882;uvs[409]=0.677246;
	uvs[410]=0.602506;uvs[411]=0.570233;
	uvs[412]=0.657594;uvs[413]=0.608518;
	uvs[414]=0.657594;uvs[415]=0.608518;
	uvs[416]=0.680229;uvs[417]=0.769369;
	uvs[418]=0.587882;uvs[419]=0.677246;
	uvs[420]=0.53122;uvs[421]=0.931906;
	uvs[422]=0.587882;uvs[423]=0.677246;
	uvs[424]=0.680229;uvs[425]=0.769369;
	uvs[426]=0.680229;uvs[427]=0.769369;
	uvs[428]=0.657594;uvs[429]=0.608518;
	uvs[430]=0.731746;uvs[431]=0.630335;
	uvs[432]=0.501152;uvs[433]=0.665489;
	uvs[434]=0.497174;uvs[435]=0.556099;
	uvs[436]=0.549353;uvs[437]=0.573688;
	uvs[438]=0.549353;uvs[439]=0.573688;
	uvs[440]=0.587882;uvs[441]=0.677246;
	uvs[442]=0.501152;uvs[443]=0.665489;
	uvs[444]=0.53122;uvs[445]=0.931906;
	uvs[446]=0.501152;uvs[447]=0.665489;
	uvs[448]=0.587882;uvs[449]=0.677246;
	uvs[450]=0.587882;uvs[451]=0.677246;
	uvs[452]=0.549353;uvs[453]=0.573688;
	uvs[454]=0.602506;uvs[455]=0.570233;
	uvs[456]=0.402239;uvs[457]=0.730785;
	uvs[458]=0.365434;uvs[459]=0.584014;
	uvs[460]=0.439226;uvs[461]=0.57985;
	uvs[462]=0.439226;uvs[463]=0.57985;
	uvs[464]=0.501152;uvs[465]=0.665489;
	uvs[466]=0.402239;uvs[467]=0.730785;
	uvs[468]=0.53122;uvs[469]=0.931906;
	uvs[470]=0.402239;uvs[471]=0.730785;
	uvs[472]=0.501152;uvs[473]=0.665489;
	uvs[474]=0.501152;uvs[475]=0.665489;
	uvs[476]=0.439226;uvs[477]=0.57985;
	uvs[478]=0.497174;uvs[479]=0.556099;

	int VertCount = 240;

	BufferName = new GLuint[3];

	int PositionSize = VertCount*3*sizeof(GLfloat);
	int UVSize = VertCount*2*sizeof(GLfloat);

	int NormalSize = VertCount*3*sizeof(GLfloat);

	glGenBuffers(3,BufferName);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[0]);
	glBufferData(GL_ARRAY_BUFFER, UVSize, uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[1]);
	glBufferData(GL_ARRAY_BUFFER, NormalSize, norms, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[2]);
glBufferData(GL_ARRAY_BUFFER, PositionSize, verts, GL_STATIC_DRAW);
}
Sphere::~Sphere()
{
	glDeleteBuffers(3, BufferName);
	delete [] BufferName;
}


void Sphere::draw(GLuint textureUnit = 0)
{
	try
	{
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glEnable(GL_TEXTURE_2D);
	glClientActiveTexture(GL_TEXTURE0+textureUnit);
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[2]);
	glVertexPointer(3,GL_FLOAT, 0,0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//glScalef(xScale, yScale, 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glActiveTexture(GL_TEXTURE0+textureUnit);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	catch(...)
	{std::cout<<"error in prim sphere draw!"<<std::endl;}
}


#endif
