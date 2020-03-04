
#include "vec3.h"

class DistancePointTriangleExact {
public:
  struct Result {
    float sqrDistance;
    //float parameter[3];  // barycentric coordinates for triangle.v[3]
    vec3 closest;
  };
  struct Triangle {
    vec3 v[3];
    Triangle(vec3 v1, vec3 v2, vec3 v3) // : v{ v1, v2, v3 } 
    {
      v[0] = v1; v[1] = v2; v[2] = v3;
    };
  };
  
  Result operator()(vec3 const& point, Triangle const& triangle);
};