#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit res;
    res.dist =0; 
vec3 diff = ray.endpoint - center;
double d = dot(ray.direction, diff);
double a = dot (ray.direction, ray.direction);
double square_root = sqrt(pow(d,2) -  (diff.magnitude_squared() - pow(radius,2))); //follow the formula
double t_1= d + square_root;
double t_2 = d - square_root;
if (square_root < 0)
{
  res.dist = -1;

}
else if (t_1 > 0.0001 || t_2 > 0.0001 )
{
  if (t_1>t_2)
  {
    res.dist = t_1;
  }
  else res.dist =t_2;

}

return res ;
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
