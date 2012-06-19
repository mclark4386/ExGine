uniform sampler2D tex;
uniform sampler2D nmb;

void main()
{
	gl_FragData[0] = texture2D(tex, gl_TexCoord[0].st);
}
