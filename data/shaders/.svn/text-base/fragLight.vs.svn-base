varying vec3 normal;
varying vec3 lightVec;
varying vec3 viewVec;

void main()
{
	vec4 ecPos = gl_ModelViewMatrix * gl_Vertex;
	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightVec = vec3(normalize(gl_LightSource[0].position - ecPos));
	viewVec = vec3(normalize(-ecPos));
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
}
