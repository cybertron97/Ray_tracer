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
    double max_d = std::max((double)0, dot(n,I)); //possibly checking for the bug as well
    // std :: cout << "diffuse " << max_d <<std ::endl;
//colorD += color_diffuse * L * max_d;


    vec3 R = (I - n * (2 * dot(I,n))).normalized();
    vec3 C = (intersection_point - ray.endpoint).normalized();
    double max_s = std :: pow(std::max((double)0, dot(R,C)),specular_power);
// std :: cout << "diffuse " << max_s <<std ::endl;
    //colorS += color_specular * L * max_s;
       //sahdow
        Hit hit;
        Ray s_ray (intersection_point, I);
        hit = world.Closest_Intersection(s_ray);
    if ((world.enable_shadows) && (hit.dist != 0 || ((I.magnitude())< hit.dist)))
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






//     vec3 colorS;
//     vec3 colorD;
//
//   for(unsigned int i = 0; i < world.lights.size(); i++)
//       {
//
//          vec3 light_intersect = (-intersection_point + (world.lights[i]->position));
//         // std :: cout << "light_intersect " << l_decay <<std ::endl;
//          vec3 L = world.lights[i]->Emitted_Light((light_intersect)); //L doesnt change for specular
//          vec3 n = normal.normalized(); //getting a seg fault
// 		     vec3 l = light_intersect.normalized();
//         //calc diffuse
//         double ln;
//     		if(dot(l,n) < 0)
//         {
//     		    ln = 0;
//     		}
//     		else{ ln = dot(l,n); }
//
//     	//	colorD +=color_diffuse * L * ln;
//
//        //have to ask TA
//         // if(dot((light_intersect), normal)<0)
//         // {colorD = {0,0,0};  }
//         // else {
//         //   colorD += ld*color_diffuse*dot((light_intersect), normal);
//         //   //std:: cout << "colord" << colorD << std ::endl;
//         // }
//         //color  = colorA + colorD;
//
//        //specular
//       vec3 R = (l - n * (2 * dot(l,n))).normalized();
//       vec3 C = (intersection_point - ray.endpoint).normalized();
//       double  RC;
// 		if(dot(R,C) < 0)
//     {
// 			RC = 0; //if less than the max then set to zero else make it equivalent to dot product
// 		}
// 		else
//     {
//       RC = dot(R,C);
//      }
//           double specular_intensity = pow(RC, specular_power);
//         //  colorS += color_specular * L * specular_intensity;
//         //std:: cout << "colord" << colorD << std ::endl;
//         //std:: cout << "colors" << colorS << std ::endl;
//
//   //  color  = colorA + colorD + colorS;
//     //TODO; //determine the color
//     //enabbling shadows
//     Hit hit;
//     Ray s_ray (intersection_point, l);
//     hit = world.Closest_Intersection(s_ray);
//     //std:: cout << "hit.dist" << hit.dist << std ::endl;
//
//
//
//      if ((world.enable_shadows) && (hit.dist != 0 || ((l.magnitude())< hit.dist)))
//      {
//        //color ambient
//        //std:: cout << "hit.dist" << hit.dist << std ::endl;
//        //std:: cout << "in the if loop" << std ::endl;
//      }
//    else {        colorS += color_specular * L * specular_intensity;
//         colorD += color_diffuse * L * ln; }
//
//
//
//     color  = colorA + colorD + colorS;
//
//
// }


    return color;
}
