#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color, colorA, colorS, colorD;
    //ambient
    colorA += world.ambient_color * world.ambient_intensity * color_ambient;
  for (unsigned int i = 0; i < world.lights.size(); i++)
  {
    vec3 intersect =  world.lights[i]->position-intersection_point;
    // std :: cout << "light_intersect " << intersect <<std ::endl;

    vec3 L = world.lights[i]->Emitted_Light(intersect);
    vec3 n = normal.normalized();
    vec3 I = intersect.normalized();
    double max_d = std::max(0.0, dot(n,I)); //possibly checking for the bug as well
    // std :: cout << "diffuse " << max_d <<std ::endl;
//colorD += color_diffuse * L * max_d

// calculating the specular 
    vec3 R = ((2 * dot(I,n)* n - I)).normalized();
    vec3 C = (ray.endpoint - intersection_point).normalized();
    double max_s = std :: pow(std::max(0.0, dot(R,C)),specular_power);
// std :: cout << "diffuse " << max_s <<std ::endl;
    //colorS += color_specular * L * max_s;
       //sahdow
        Hit hit;
        Ray s_ray (intersection_point, I);
        hit = world.Closest_Intersection(s_ray);
    if ((world.enable_shadows) && (hit.dist > 0 && ((intersect.magnitude())> hit.dist)))
         {
           //color ambient
           //std:: cout << "hit.dist" << hit.dist << std ::endl;
           //std:: cout << "in the if loop" << std ::endl;
         }
       else {
            colorS += color_specular * L * max_s;
            colorD += color_diffuse * L * max_d;
          }


    color = colorA + colorD + colorS;
  }
    return color;
}
