#pragma once
#include <string>
#include "vec3.h"
using std::string;

class Mesh
{
public:
  Mesh(string path);
  ~Mesh();
  void generateMeshFromOff(string path);
public:
  struct face
  {
    int v1;
    int v2;
    int v3;
  };
  vec3 *vertices;
  face *faces;
  int nv, nf; //numbers of vertices and faces
};

