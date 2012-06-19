uniform sampler2D tex;
uniform sampler2D nmb;

varying vec3 halfAngle;
varying vec3 lightDirection;
varying mat3 textureSpaceMatrix;
varying vec3 _tsE;

void main()
{
	float ambient = 0.2;
	float parallexBias = 0.07;

	float height = 1.0;
	float numSteps = 6.0;
	
	_tsE = normalize(_tsE);

	numSteps = max(numSteps*2.0, numStep, _tsE.z);

	float step = 1.0/numSteps;

	vec2 uv = gl_TexCoord[0].st;
	
	float depth = ((texture2D(nmb,uv).w)) * parallexBias;
	
	vec2 offset = depth * mul(textureSpaceMatrix, halfAngle);
	
	float postDepth = (texture2D(nmb, uv+offset).w);
	
	while(postDepth<height)
	{
		height-=step;
		offset+=offset;
		postDepth = (texture2D(nmb, uv+offset).w);
	}

	height = postDepth;
	
	//if(postDepth<0.96f)
	//{
	//	offset *= (postDepth + ((texture2D(nmb,uv).w))) * 0.5;
	//}
	
	uv += offset;

	vec3 normal = texture2D(nmb,uv).xyz;
	normal = vec3(2.0) * (normal - vec3(0.5));

	const float NdotL = max(0.0,dot(normal,lightDirection));
	const float NdotH = max(0.0,dot(normal,halfAngle);

	float selfShadow = 0.0;

	float diffuse = smoothstep(0.0, 1.0, dot(normal, lightDirection));
	//float specular = smoothstep(0.0, 1.0, dot(normal, halfAngle));
	float specular = NdotH * NdotH;
	float pF = pow(specular, 16.0);
	
	vec4 diffuseColor = texture2D(tex, uv);
	vec4 glossColor = vec4(0.2);

	if(NdotH>0.0)
	{
		const int numSSteps = max(60.0,5.0,lightDirection.z);

		step = 1.0/numSSteps;
	
		uv = vec2(lightDirection.x, -lightDirection.y) * parallexBias / (numSSteps * lightDirection.z);

		height = postDepth + step * 0.1;

		while( (postDepth<height) && (height < 1.0) )
		{
			height += step;
			uv += offest;
			postDepth = (texture2D(nmb, uv).w);
		}
		
		selfShadow = (postDepth < height);

		diffuseColor = diffuseColor * 1.2;
 	}
	
	glFragColor = vec4(1.0,1.0,0.0,1.0);
	//gl_FragColor = vec4(vec4(ambient * diffuseColor + NdotL * selfShadow * diffuseColor * diffuse).rgb,texture2D(tex,uv).a);
	//gl_FragColor = (ambient + diffuse) * NdotL * selfShadow * diffuseColor + glossColor * pF;
}	
