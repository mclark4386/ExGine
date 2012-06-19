varying vec3 halfAngle;
varying vec3 lightDirection;
varying mat3 textureSpaceMatrix;
varying vec3 _tsE;

void main()
{
	vec3 normal = gl_Normal;
	//vec3 tangent = vec3(1.0,0.0,0.0);
	//vec3 tangent = gl_MultiTexCoord2.xyz;
	vec3 tangent = -gl_MultiTexCoord2.xyz;
	vec2 texcoord = gl_MultiTexCoord0.st;
	
	//finding the texture space matrix for normal computations
	vec4 position = gl_ModelViewMatrix *gl_Vertex;
	normal = normalize(gl_NormalMatrix * normal);
	tangent =  normalize(gl_NormalMatrix * tangent);
	vec3 binormal = cross(normal, tangent);//may need to change this to: gl_NormalMatrix * normalize(vec3(1.0,0.0,0.0));
	textureSpaceMatrix = mat3(tangent,binormal,normal);
	
	//compute half angle and light direction for passing on
	vec3 lightPosition = gl_LightSource[0].position.xyz;
	vec3 eyeDirection = textureSpaceMatrix * normalize(-position.xyz);
	lightDirection = textureSpaceMatrix * normalize(lightPosition - position.xyz);
	halfAngle = normalize(eyeDirection + lightDirection);
	
	_tsE = eyeDirection;
	
	//and of course, pass on the tex coords and vextex position
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//gl_TexCoord[0].st = texcoord * vec2(1.0,-2.0);
	gl_TexCoord[0].st = texcoord;
}
