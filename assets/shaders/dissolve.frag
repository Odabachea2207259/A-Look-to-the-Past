uniform sampler2D dissolve_texture;
uniform sampler2D texture;
uniform float dissolve_value;
uniform float burn_size;

void main() {
    vec4 main_texture = texture2D(texture, gl_TexCoord[0].xy);
    vec4 noise_texture = texture2D(dissolve_texture, gl_TexCoord[0].xy);

    vec4 burn_color = vec4(1.0,0.3,0.0,1.0);

    float dv = 1.0 - dissolve_value;
    
    float burn_size_step = burn_size * step(0.001, dv) * step(dv, 0.999);
    float threshold = smoothstep(noise_texture.x - burn_size_step, noise_texture.x, dv);
    float border = smoothstep(noise_texture.x, noise_texture.x + burn_size_step, dv);
    
    vec4 final_color = main_texture;
    final_color.a *= threshold;
    final_color.rgb = mix(burn_color.rgb, main_texture.rgb, border);
    
    gl_FragColor = final_color;
}
