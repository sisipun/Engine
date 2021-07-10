#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in VS_OUT {
   vec2 TextureCoord;
   vec3 Normal;
   vec3 FragPos;
} gs_in[];

out GS_OUT {
   vec2 TextureCoord;
   vec3 Normal;
   vec3 FragPos;
} gs_out;

void main() {
    gl_Position = gl_in[0].gl_Position;
    gs_out.TextureCoord = gs_in[0].TextureCoord;
    gs_out.Normal = gs_in[0].Normal;
    gs_out.FragPos = gs_in[0].FragPos;
    EmitVertex();
    
    gl_Position = gl_in[1].gl_Position;
    gs_out.TextureCoord = gs_in[1].TextureCoord;
    gs_out.Normal = gs_in[1].Normal;
    gs_out.FragPos = gs_in[1].FragPos;
    EmitVertex();
    
    gl_Position = gl_in[2].gl_Position;
    gs_out.TextureCoord = gs_in[2].TextureCoord;
    gs_out.Normal = gs_in[2].Normal;
    gs_out.FragPos = gs_in[2].FragPos;
    EmitVertex();

    EndPrimitive();
} 