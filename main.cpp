
#include <iostream>
using namespace std;

#include <ctime>
#include <omp.h>
#include <vector>

#include "Mesh.h"
#include "DistanceBetweenMeshs.h"
#include "TestExecutionTime.h"

#define t_start TestExecutionTime::start()
#define t_end TestExecutionTime::end("\nTotal time of computing Hausdorff Distance")

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Parameter error!" << endl;
        exit(0);
    }

    char *originMeshPath = argv[1], *destMeshPath = argv[2];
    Mesh *originMesh = new Mesh(originMeshPath), *destMesh = new Mesh(destMeshPath);

    DistanceBetweenMeshs runner;

    cout << originMesh->nf << endl
        << destMesh->nf << endl;
    cout << runner(originMesh, destMesh) << endl;

    delete originMesh;
    delete destMesh;

    return 0;
}
