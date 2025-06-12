#version 110
uniform sampler2D nubes;
uniform sampler2D player;
//uniform float frame;
//uniform float blend;

uniform float dt;

void main()
{
    vec4 nube = texture2D(nubes,gl_TexCoord[0].st);
    vec4 per = texture2D(player,gl_TexCoord[0].st);
    //vec4 pixeles = texture2D(textura, gl_TexCoord[0].st);
    //vec4 tex2 = texture2D(textura_prueba,gl_TexCoord[0].st);
    //vec4 tinta = vec4(dt,dt,0.0,1.0);
    //vec4 composicion = mix(pixeles,tex2,step(blend,gl_TexCoord[0].x));
    //vec4 composicion = mix(pixeles,tex2,tex2.a);

    vec3 rojo = vec3(1.0,0.0,0.0);
    vec3 azul = vec3(0.0,0.0,1.0);

    vec3 mezcla = mix(rojo,azul,dt);

    //gl_FragColor = per-vec4(mezcla,0.1)+nube;//(gl_Color *composicion)*vec4(1.0-vec3(tinta),1.0);
    gl_FragColor = per-vec4(0.0,0.0,0.0,1.3)+nube;
    //gl_FragColor = (gl_Color *vec4(mezcla,1.0))*vec4(1.0-mezcla,1.0);
    //gl_FragColor = (gl_Color *composicion)*vec4(1.0-vec3(tinta),1.0);
}
