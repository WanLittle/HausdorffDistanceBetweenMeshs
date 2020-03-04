#pragma once

#include "Mesh.h"

class DistanceBetweenMeshs {
public:
  DistanceBetweenMeshs();
  ~DistanceBetweenMeshs();

  float operator()(Mesh *mesh_1, Mesh *mesh_2);
  float symmetricHausdorffDistance(Mesh *mesh_1, Mesh *mesh_2);
};
