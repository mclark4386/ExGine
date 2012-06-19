uniform sampler2D tex;
uniform sampler2D nmb;

varying vec3 normal;
varying vec3 lightVec;
varying vec3 viewVec;

void main()
{
	vec3 nnormal = normalize(normal);
	vec3 nlightVec = normalize(lightVec);
	vec3 nviewVec = normalize(viewVec);
	
	vec3 reflectVec = reflect(-nlightVec, nnormal);
	
	float specValue = clamp(dot(reflectVec,nviewVec), 0.0, 1.0);
	specValue = pow(specValue, 6.0);
	vec4 spec = gl_LightSource[0].specular * specValue;
	vec4 diffuse = texture2D(tex,gl_TexCoord[0].st) * max(dot(nlightVec,nnormal),0.0);
	//gl_FragColor = texture2D(tex,gl_TexCoord[0].st);
	gl_FragColor = diffuse;// + vec4(spec.rgb,1.0);
}
