uniform sampler2D tex;
uniform sampler2D nmb;

varying vec3 halfAngle;
varying vec3 lightDirection;
varying mat3 textureSpaceMatrix;

void main()
{
	float ambient = 0.2;
	float parallexBias = 1.0;
	
	vec2 uv = gl_TexCoord[0].st;
	
	float depth = ((texture2D(nmb,uv).w)) * parallexBias;
	
	vec2 offset = depth * (textureSpaceMatrix*halfAngle).xy;
	
	float postDepth = (texture2D(nmb, uv+offset).w);
	
	if(postDepth<0.96)
	{
		offset *= (postDepth + ((texture2D(nmb,uv).w))) * 0.5;
	}
	
	uv += offset;

	vec3 normal = texture2D(nmb,uv).xyz;
	normal = vec3(2.0) * (normal - vec3(0.5));
	
	float diffuse = smoothstep(0.0, 1.0, dot(normal, lightDirection));
	float specular = smoothstep(0.0, 1.0, dot(normal, halfAngle));
	float pF = pow(specular, 16.0);
	
	vec4 diffuseColor = texture2D(tex, uv);
	vec4 glossColor = vec4(0.2);
	
	gl_FragColor = (ambient + diffuse) * diffuseColor + glossColor * pF;
}	
