#include "DistancePointTriangleExact.h"

// method from ¡¶Distance Between Point and Triangle in 3D.pdf¡·
DistancePointTriangleExact::Result
DistancePointTriangleExact::operator() (vec3 const& point, Triangle const& triangle) {

  vec3 diff = point - triangle.v[0]; // P - B
  vec3 edge0 = triangle.v[1] - triangle.v[0]; //E0
  vec3 edge1 = triangle.v[2] - triangle.v[0]; //E1
  float a = dot(edge0, edge0);
  float b = dot(edge0, edge1);
  float c = dot(edge1, edge1);
  float d = -dot(diff, edge0);
  float e = -dot(diff, edge1);
  float const zero = (float)0;
  float const one = (float)1;
  float det = a * c - b * b;
  float _s = b * e - c * d;
  float _t = b * d - a * e;

  if (_s + _t <= det) // s+t<1 region 0/3/4/5
  {
    if (_s < zero) // region 4/5
    {
      if (_t < zero)  // region 4
      {
        if (d < zero)
        {
          _t = zero;
          if (-d >= a)  // V1
          {
            _s = one;
          }
          else  // E01
          {
            _s = -d / a;
          }
        }
        else
        {
          _s = zero;
          if (e >= zero)  // V0
          {
            _t = zero;
          }
          else if (-e >= c)  // V2
          {
            _t = one;
          }
          else  // E20
          {
            _t = -e / c;
          }
        }
      }
      else  // region 3
      {
        _s = zero;
        if (e >= zero)  // V0
        {
          _t = zero;
        }
        else if (-e >= c)  // V2
        {
          _t = one;
        }
        else  // E20
        {
          _t = -e / c;
        }
      }
    } //if (t0 < zero) 
    else if (_t < zero)  // region 5
    {
      _t = zero;
      if (d >= zero)  // V0
      {
        _s = zero;
      }
      else if (-d >= a)  // V1
      {
        _s = one;
      }
      else  // E01
      {
        _s = -d / a;
      }
    }
    else  // region 0, interior
    {
      float invDet = one / det;
      _s *= invDet;
      _t *= invDet;
    }
  }
  else //if (t0 + t1 <= det) region 1/2/6
  {
    float tmp0, tmp1, numer, denom;

    if (_s < zero)  // region 2
    {
      tmp0 = b + d;
      tmp1 = c + e;
      if (tmp1 > tmp0)
      {
        numer = tmp1 - tmp0;
        denom = a - ((float)2)*b + c;
        if (numer >= denom)  // V1
        {
          _s = one;
          _t = zero;
        }
        else  // E12
        {
          _s = numer / denom;
          _t = one - _s;
        }
      }
      else
      {
        _s = zero;
        if (tmp1 <= zero)  // V2
        {
          _t = one;
        }
        else if (e >= zero)  // V0
        {
          _t = zero;
        }
        else  // E20
        {
          _t = -e / c;
        }
      }
    }
    else if (_t < zero)  // if (t0 < zero) region 6
    {
      tmp0 = b + e;
      tmp1 = a + d;
      if (tmp1 > tmp0)
      {
        numer = tmp1 - tmp0;
        denom = a - ((float)2)*b + c;
        if (numer >= denom)  // V2
        {
          _t = one;
          _s = zero;
        }
        else  // E12
        {
          _t = numer / denom;
          _s = one - _t;
        }
      }
      else
      {
        _t = zero;
        if (tmp1 <= zero)  // V1
        {
          _s = one;
        }
        else if (d >= zero)  // V0
        {
          _s = zero;
        }
        else  // E01
        {
          _s = -d / a;
        }
      }
    }
    else  //else if (t1 < zero)  region 1
    {
      numer = c + e - b - d;
      if (numer <= zero)  // V2
      {
        _s = zero;
        _t = one;
      }
      else
      {
        denom = a - ((float)2)*b + c;
        if (numer >= denom)  // V1
        {
          _s = one;
          _t = zero;
        }
        else  // 12
        {
          _s = numer / denom;
          _t = one - _s;
        }
      }
    }
  }

  Result result;
  //result.parameter[0] = one - _s - _t;
  //result.parameter[1] = _s;
  //result.parameter[2] = _t;
  result.closest = triangle.v[0] + _s *edge0 + _t * edge1;
  diff = point - result.closest;
  result.sqrDistance = dot(diff, diff);
  return result;
}
