#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    
Hit hit; 
vec3 u = ray.endpoint -center; 

double g = pow(dot(u, ray.direction),2)-(u.magnitude()-pow(radius,2));  
double t = dot(u, ray.direction)-sqrt(g); 
if (g>=0) 
{
hit.dist=t;
return hit; 


}




return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = point - center; 
    //TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
