const float LINEAR_ATTENUATION_FACTOR    = 0.0;
const float QUADRATIC_ATTENUATION_FACTOR = 5.0;


uniform sampler2D diffuse;
uniform vec2 light_position;

varying vec2 tex_coord_var;
varying vec2 pix_position;
uniform int spotlight_on;

float attenuate(float dist, float lin_att, float quad_att)
{
     return 1.0 / (1.0 + (lin_att * dist) + (quad_att * dist  * dist));
}

void main()
{
    if (spotlight_on == 1) {
        float brightness = attenuate(distance(light_position, pix_position),
                                     LINEAR_ATTENUATION_FACTOR, QUADRATIC_ATTENUATION_FACTOR);
        vec4 color = texture2D(diffuse, tex_coord_var);
        
        gl_FragColor = vec4(color.rgb * brightness, color.a);
    }
    else {
        
        gl_FragColor = texture2D(diffuse, tex_coord_var);
    }
}

