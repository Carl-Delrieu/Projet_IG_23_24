#version 140
#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in float a_weight0;
layout (location = 3) in float a_weight1;


uniform mat4 transform;
uniform mat4 fixed_bone;
uniform mat4 mobile_bone;

out vec3 g_vertex;
out vec3 g_normal;

void main()
{
    vec4 point_tmp = transform * vec4(a_vertex,1.0);
    point_tmp = (fixed_bone * mobile_bone * a_weight0 + fixed_bone * a_weight1) * point_tmp;
    point_tmp = point_tmp/point_tmp.w;

    gl_Position = point_tmp;
    g_vertex = point_tmp.xyz;
    g_normal = a_normal;
}