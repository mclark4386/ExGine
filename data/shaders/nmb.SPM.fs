/**
 SteepParallax.glsl.vrt
 Morgan McGuire 2005 morgan@cs.brown.edu
 */

/** Color texture (with alpha) */
uniform sampler2D tex;
//uniform vec3 wsEyePos;
vec3 wsEyePos = vec3(0.0,0.0,5.0);

/** rgb = normal, a = bump height */
uniform sampler2D nmb;

/** Multiplier for bump map.  Typically on the range [0, 0.05]
  This increases with texture scale and bump height. */
//uniform float bumpScale;
float bumpScale = 0.03;

varying vec3 lightDirection;
varying vec3 _tsE;
varying vec3 halfAngle;
varying mat3 textureSpaceMatrix;

void main(void) {

    // We are at height bumpScale.  March forward until we hit a hair or the 
    // base surface.  Instead of dropping down discrete y-voxels we should be
    // marching in texels and dropping our y-value accordingly (TODO: fix)
    float height = 1.0;

    // Number of height divisions
    float numSteps = 5.0;

    /** Texture coordinate marched forward to intersection point */
    vec2 offsetCoord = gl_TexCoord[0].st;
    vec4 NB = texture2D(nmb, offsetCoord);

    vec3 tsE = normalize(_tsE);

    // Increase steps at oblique angles
    // Note: tsE.z = N dot V
    numSteps = mix(numSteps*2.0, numSteps, tsE.z);

    // We have to negate tsE because we're walking away from the eye.
    //vec2 delta = vec2(-_tsE.x, _tsE.y) * bumpScale / (_tsE.z * numSteps);
    float step;
    vec2 delta;


    // Constant in z
    step = 1.0 / numSteps;
    delta = vec2(-_tsE.x, _tsE.y) * bumpScale / (_tsE.z * numSteps);

        // Can also step along constant in xy; the results are essentially
        // the same in each case.
        // delta = 1.0 / (25.6 * numSteps) * vec2(-tsE.x, tsE.y);
        // step = tsE.z * bumpScale * (25.6 * numSteps) / (length(tsE.xy) * 400);

    while (NB.a < height) {
        height -= step;
        offsetCoord += delta;
        NB = texture2D(nmb, offsetCoord);
    }

    height = NB.a;

    // Choose the color at the location we hit
    const vec3 color = texture2D(tex, offsetCoord).rgb;

    lightDirection = normalize(lightDirection);

    // Use the normals out of the bump map
    vec3 tsN = NB.xyz * 2.0 - 1.0;

    // Smooth normals locally along gradient to avoid making slices visible.
    // The magnitude of the step should be a function of the resolution and
    // of the bump scale and number of steps.
//    tsN = normalize(texture2D(nmb, offsetCoord + vec2(tsN.x, -tsN.y) * mipScale).xyz * 2 - 1 + tsN);

    //const vec3 tsH = normalize(lightDirection + normalize(_tsE));

    const float NdotL = max(0.0, dot(tsN, lightDirection));
    const float NdotH = max(0.0, dot(tsN, halfAngle));
    float spec = NdotH * NdotH;

    vec3 lightColor = vec3(1.5, 1.5, 1) * 0.9;
    vec3 ambient = vec3(0.4,0.4,0.6) * 1.4;

    float selfShadow = 0.0;

    // Don't bother checking for self-shadowing if we're on the
    // back side of an object.
    if (NdotL > 0.0) {

        // Trace a shadow ray along the light vector.
        const int numShadowSteps = mix(60.0,5.0,lightDirection.z);
        step = 1.0 / numShadowSteps;
        delta = vec2(lightDirection.x, -lightDirection.y) * bumpScale / (numShadowSteps * lightDirection.z);

            // We start one iteration out to avoid shadow acne 
            // (could start bumped a little without going
            // a whole iteration).
            height = NB.a + step * 0.1;

            while ((NB.a < height) && (height < 1.0)) {
                height += step;
                offsetCoord += delta;
                NB = texture2D(nmb, offsetCoord);
            }

            // We are in shadow if we left the loop because
            // we hit a point
            selfShadow = (NB.a < height);

            // Shadows will make the whole scene darker, so up the light contribution
            lightColor = lightColor * 1.2;
        }
        

        gl_FragColor.rgb = color * ambient + color * NdotL * selfShadow * lightColor;

}
