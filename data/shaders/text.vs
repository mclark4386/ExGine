uniform int char;

void main()
{
	if(char<32 || char>126)
		gl_TexCoord[0] = gl_MultiTexCoord0;
	else
	{
		
	}
	gl_Position = ftransform();
}
