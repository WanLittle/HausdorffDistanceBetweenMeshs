#include "DistanceBetweenMeshs.h"
#include "DistancePointTriangleExact.h"
#include <iostream>
#include <cmath>


DistanceBetweenMeshs::DistanceBetweenMeshs()
{
}

DistanceBetweenMeshs::~DistanceBetweenMeshs()
{
}

float DistanceBetweenMeshs::operator()(Mesh * mesh_1, Mesh * mesh_2)
{
  return symmetricHausdorffDistance(mesh_1, mesh_2);
}

float DistanceBetweenMeshs::symmetricHausdorffDistance(Mesh * mesh_1, Mesh * mesh_2)
{
  DistancePointTriangleExact runner;
  int nv_mesh_1 = mesh_1->nv, nf_mesh_1 = mesh_1->nf;
  int nv_mesh_2 = mesh_2->nv, nf_mesh_2 = mesh_2->nf;

  float result;

  float max_1 = FLT_MIN;
#pragma omp parallel for
  for (int i = 0; i < nv_mesh_1; i++)
  {
    float min = FLT_MAX;
    for (int j = 0; j < nf_mesh_2; j++)
    {
      float distance = runner(mesh_1->vertices[i], { mesh_2->vertices[mesh_2->faces[j].v1],
                                                  mesh_2->vertices[mesh_2->faces[j].v2],
                                                  mesh_2->vertices[mesh_2->faces[j].v3] }).sqrDistance;
      if (min > distance) min = distance;
    }
    if (max_1 < min) max_1 = min;
  }
  
  float max_2 = FLT_MIN;
#pragma omp parallel for
  for (int i = 0; i < nv_mesh_2; i++)
  {
    float min = FLT_MAX;
    for (int j = 0; j < nf_mesh_1; j++)
    {
      float distance = runner(mesh_2->vertices[i], { mesh_1->vertices[mesh_1->faces[j].v1],
                                                  mesh_1->vertices[mesh_1->faces[j].v2],
                                                  mesh_1->vertices[mesh_1->faces[j].v3] }).sqrDistance;
      if (min > distance) min = distance;
    }
    if (max_2 < min) max_2 = min;
  }

  result = max_1 > max_2 ? max_1 : max_2;

  return sqrt(result);
}


