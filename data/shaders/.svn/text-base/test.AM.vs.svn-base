///#version 120
uniform mat4 boneAnimation[10];
/*******************
 * row1: init quaternion 
 * row2: final quaternion
 * row3: init transformation (x,y,z,s)
 * row4: final transformation (x,y,z,s)
 *******************/
 uniform float delta;//should be a fraction indication the transition percentage trough this section of the animation


attribute vec4 weights;
attribute vec4 matrixIndices;
attribute float numBones;

//varying vec3 halfAngle;
//varying vec3 lightDirection;
//varying mat3 textureSpaceMatrix;
//varying vec3 _tsE;

void slerp( in float t,
			in vec4 qi,
			in vec4 qf,
			out vec4 q)
	{
		float theta = acos(dot(qi,qf));
		q = ((sin((1.0-t)*theta))/sin(theta)*qi)+(((sin(theta*t))/(sin(theta)))*qf);
	}
	
void decodeAndSlerpBone( in mat4 codedMat,
						in float time,
						out mat4 finalMat)
	{
		vec4 qi = codedMat[0];
		vec4 qf = codedMat[1];
		vec4 ti = codedMat[2];
		vec4 tf = codedMat[3];
		
		vec4 qt;//total rotation after interpolation
		vec4 tt;//total translation after interpolation
		
		slerp(delta,qi,qf,qt);//interpolate the rotation
		tt.x=ti.x+((ti.x-tf.x)*delta);//interpolate the transition
		tt.y=ti.y+((ti.y-tf.y)*delta);//
		tt.z=ti.z+((ti.z-tf.z)*delta);//
		tt.w=ti.w+((ti.w-tf.w)*delta);//
		
		mat3 temp = mat3(1.0-2.0*(qt.y*qt.y)-2.0*(qt.z*qt.z),2.0*qt.x*qt.y-2.0*qt.w*qt.z,2.0*qt.x*qt.z+2.0*qt.w*qt.y,
						2.0*qt.x*qt.y+2.0*qt.w*qt.z,1.0-2.0*(qt.x*qt.x)-2.0*(qt.z*qt.z),2.0*qt.y*qt.z-2.0*qt.w*qt.x,
						2.0*qt.x*qt.z-2.0*qt.w*qt.y,2.0*qt.y*qt.z-2.0*qt.w*qt.x,1.0-2.0*(qt.x*qt.x)-2.0*(qt.y*qt.y));
		finalMat = mat4(temp[0],tt.w,
					temp[1],tt.w,
					temp[2],tt.w,
					tt.xyz,0.0);
	}

void main()
{
	vec4 index = matrixIndices;
	vec4 weight = weights;
	mat4 tempMatrix;
	
	vec4 position = vec4 (0.0, 0.0, 0.0, 0.0);
	vec3 normal = gl_Normal;
	//vec3 tangent = -gl_MultiTexCoord2.xyz;
	vec4 texcoord = gl_MultiTexCoord0;
	normal = normalize(gl_NormalMatrix * normal);
	//tangent =  normalize(gl_NormalMatrix * tangent);
	///vec3 binormal = cross(normal, tangent);//may need to change this to: gl_NormalMatrix * normalize(vec3(1.0,0.0,0.0));
	//textureSpaceMatrix = mat3(tangent,binormal,normal);
	
	vec4 tempNorm = vec4(0.0, 0.0, 0.0, 0.0);
	
	for( float i = 0.0; i < numBones; i += 1.0)
	{
		decodeAndSlerpBone(boneAnimation[int(index.x)],delta,tempMatrix);
		position = position + weight.x * (tempMatrix * gl_Vertex);
		tempNorm = tempNorm + weight.x * (tempMatrix * vec4(normal,0.0));
		
		index = index.yzwx;
		weight = weight.yzwx;
	}
	
	gl_TexCoord[0] = texcoord;
	gl_Position = gl_ModelViewProjectionMatrix * position;
	//mat4 inverseModelView = gl_ModelViewProjectionMatrix * mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	//vec3 finalNormal = (normalize( inverseModelView * tempNormal )).xyz;

//compute half angle and light direction for passing on
	//vec3 lightPosition = gl_LightSource[0].position.xyz;
	//vec3 eyeDirection = textureSpaceMatrix * normalize(-position.xyz);
	//lightDirection = textureSpaceMatrix * normalize(lightPosition - position.xyz);
	//halfAngle = normalize(eyeDirection + lightDirection);
	
	//_tsE = eyeDirection;
	
}
