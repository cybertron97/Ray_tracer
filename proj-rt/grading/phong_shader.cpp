#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color, colorA;
    colorA += world.ambient_color * world.ambient_intensity * color_ambient;


      

color  = colorA;
    TODO; //determine the color

    return color;
}