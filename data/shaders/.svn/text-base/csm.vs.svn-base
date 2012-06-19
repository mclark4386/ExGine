//  input from the user
varying float csm_gain;
varying float csm_offset;
varying float texsize;

//  interpolate these and pass 
//  them into the fragment shader
varying vec3 vertex_pos;
varying vec3 light_pos;
varying float vertex_dist;
varying float light_dist;

//  distance to the point
varying float dist_val;

//attribute vec3 tan;

void main(void)
{
	csm_gain = 1.0;
	csm_offset = 0.0;
	texsize = 1.0;

   // location of the vertex in eye space
   vec3 eyeSpaceVert = (gl_ModelViewMatrix * gl_Vertex).xyz;
  
   // convert to eyeSpace for programs other than Irrlicht
   //vec3 eyeSpaceLight = (gl_ModelViewMatrix * vec4(gl_LightSource[0].position.xyz,1.0)).xyz;
   // gl_LightSource[n].position is already in eyeSpace from Irrlicht!
   vec3 eyeSpaceLight = gl_LightSource[0].position.xyz;
   
   //  the matrix needed to convert to eye space
   //  (this is local, and should already be normalized, I think)
	vec3 eyeSpaceTangent = normalize(gl_NormalMatrix * (-gl_MultiTexCoord2.xyz));	//tangent;
	vec3 eyeSpaceNormal   = normalize(gl_NormalMatrix * gl_Normal); //normal
	vec3 eyeSpaceBinormal  = cross(eyeSpaceNormal, eyeSpaceTangent);	//binormal;
  
   // now convert the light and position, and pass in the texture coordinate
   vertex_pos = vec3 (
        dot (eyeSpaceTangent, eyeSpaceVert),
        dot (eyeSpaceBinormal, eyeSpaceVert),
        dot (eyeSpaceNormal, eyeSpaceVert));
   light_pos = vec3 (
        dot (eyeSpaceTangent, eyeSpaceLight),
        dot (eyeSpaceBinormal, eyeSpaceLight),
        dot (eyeSpaceNormal, eyeSpaceLight))
        - vertex_pos;
   vertex_dist = length (eyeSpaceVert);
   light_dist = length (light_pos);
   //light_pos /= light_dist;
   gl_TexCoord[0].st   = gl_MultiTexCoord0.xy;
   
   //  for the LOD
   dist_val = (0.00333 * vertex_dist * csm_gain + csm_offset) 
      / texsize;
   
   // done
   gl_Position = ftransform();
}
