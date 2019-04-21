
#include <iostream>
using namespace std;

#include <ctime>
#include <omp.h>
#include <vector>

#include "Mesh.h"
#include "DistanceBetweenMeshs.h"
#include "TestExecutionTime.h"

#define t_start TestExecutionTime::start()
#define t_end TestExecutionTime::end("\n\nTotal time of computing Hausdorff Distance")

int main()
{
  string meshPath = "../../res/";
  string originMeshName = "uniform";
  vector<string> destMeshNames = {
    "oct",
    "kd",
  };

  cout << "Loading .off files...\n";
  Mesh* originMesh = new Mesh(meshPath + originMeshName + ".off");
  vector<Mesh* > destMesh(destMeshNames.size());
  for (int i = 0; i < destMeshNames.size(); i++) {
    destMesh[i] = new Mesh(meshPath + destMeshNames[i] + ".off");
  }
  cout << "Loading success\n";

  DistanceBetweenMeshs runner;

  cout << "Computing symmetric Hausdorff Distance between following mesh pairs: \n\n";
  t_start;
  for (int i = 0; i < destMeshNames.size(); i++) {
    cout << originMeshName << originMesh->nf << " & " 
      << destMeshNames[i] << destMesh[i]->nf << " :  " 
      << runner(originMesh, destMesh[i]) << endl;
  }
  t_end;


  delete originMesh;
  for (auto it = destMesh.begin(); it != destMesh.end(); it++) {
    delete *it;
    *it = nullptr;
  }

  cout << "\n\n\n³ÌÐò½áÊø...\n";
  return 0;
}
