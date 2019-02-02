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
    vec3 colorS;
    vec3 colorD;

  for(int i = 0; i < world.lights.size(); i++)
      {

         vec3 light_intersect = (-intersection_point + (world.lights[i]->position));
        // std :: cout << "light_intersect " << l_decay <<std ::endl;
         vec3 L = world.lights[i]->Emitted_Light((light_intersect)); //L doesnt change for specular
         vec3 n = normal.normalized();
		     vec3 l = light_intersect.normalized();
        //calculating diffuse
        double ln;
    		if(dot(l,n) < 0)
        {
    		    ln = 0;
    		}
    		else{ ln = dot(l,n); }

    		colorD +=color_diffuse * L * ln;

       //have to ask TA
        // if(dot((light_intersect), normal)<0)
        // {colorD = {0,0,0};  }
        // else {
        //   colorD += ld*color_diffuse*dot((light_intersect), normal);
        //   //std:: cout << "colord" << colorD << std ::endl;
        // }
        //color  = colorA + colorD;
       //specular
      vec3 R = (l - n * (2 * dot(l,n))).normalized();
      vec3 C = (intersection_point - ray.endpoint).normalized();
      double  RC;
		if(dot(R,C) < 0)
    {
			RC = 0;
		}
		else
    { RC = dot(R,C);
     }
          double specular_intensity = pow(RC, specular_power);
          colorS += color_specular * L * specular_intensity;}
//std:: cout << "colord" << colorD << std ::endl;
color  = colorA + colorD + colorS;
    //TODO; //determine the color

    return color;
}
