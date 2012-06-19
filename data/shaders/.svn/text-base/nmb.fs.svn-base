uniform sampler2D tex;
uniform sampler2D nmb;

varying vec3 halfAngle;
varying vec3 lightDirection;
varying mat3 textureSpaceMatrix;
varying vec3 _tsE;

void main()
{
	float ambient = 0.2;
	float parallexBias = 0.01;

	float height = 0.1;
	float numSteps = 6.0;
	
	vec3 tsE = normalize(_tsE);

	numSteps = max((numSteps*2.0), tsE.z);

	float step = 1.0/numSteps;

	vec2 uv = gl_TexCoord[0].st;
	
	float depth = ((texture2D(nmb,uv).w)) * parallexBias;
	
	vec2 offset = vec3(depth * (textureSpaceMatrix*halfAngle)).st;
	
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

	vec4 diffuseColor = texture2D(tex, uv);
	vec4 glossColor = vec4(0.2);
	vec3 normal = texture2D(nmb,uv).xyz;
	normal = vec3(2.0) * (normal - vec3(0.5));

	float NdotL = max(0.0,dot(normal,lightDirection));
	float NdotH = max(0.0,dot(normal,halfAngle));

	float selfShadow = 0.0;

	float diffuse = smoothstep(0.0, 1.0, dot(normal, lightDirection));
	//float specular = smoothstep(0.0, 1.0, dot(normal, halfAngle));
	float specular = NdotH * NdotH;
	float pF = pow(specular, 6.0);

	if(NdotH>0.0)
	{
		int numSSteps = int(max(60.0,lightDirection.z));

		step = 1.0/float(numSSteps);
	
		uv = (vec2(lightDirection.x, -lightDirection.y) * parallexBias) / (float(numSSteps) * lightDirection.z);

		height = postDepth + step * 0.1;

		while( (postDepth<height) && (height < 1.0) )
		{
			height += step;
			uv += offset;
			postDepth = (texture2D(nmb, uv).w);
		}
		
		selfShadow = float(postDepth < height);

		diffuse = diffuse * 1.2;
 	}
	
	//gl_FragColor = vec4(1.0,1.0,0.0,1.0);
	//gl_FragColor = vec4(vec4((ambient + diffuse) * diffuseColor + NdotL * selfShadow * diffuseColor * diffuse * pF).rgb,texture2D(tex,uv).a);
	gl_FragColor = (ambient + diffuse) * selfShadow * diffuseColor + glossColor * pF;
	//gl_FragColor = (ambient + diffuse) * diffuseColor + diffuse * pF;
}	
