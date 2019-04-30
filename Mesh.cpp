#include "Mesh.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Mesh::Mesh(string path)
{
  generateMeshFromOff(path);
}

Mesh::~Mesh()
{
}

void Mesh::generateMeshFromOff(string filename)
{
  // Container holding last line read
  string readLine;
  // Containers for delimiter positions
  int delimiterPos_1, delimiterPos_2, delimiterPos_3, delimiterPos_4;
  
  // Open file for reading
  ifstream in(filename.c_str());
  if (!in)
  {
    cout << filename
      << "\n error: Open file failed." << endl;
    exit(0);
    return;
  }
  // Check if file is in OFF format
  getline(in, readLine);
  if (readLine != "OFF")
  {
    cout << filename 
      << "\n error: The file to read is not in OFF format." << endl;
    exit(0);
    return;
  }

  // Read values for Nv and Nf
  getline(in, readLine);
  delimiterPos_1 = readLine.find(" ", 0);
  nv = atoi(readLine.substr(0, delimiterPos_1 + 1).c_str());
  delimiterPos_2 = readLine.find(" ", delimiterPos_1);
  nf = atoi(readLine.substr(delimiterPos_1, delimiterPos_2 + 1).c_str());

  // Read the vertices
  vertices = new vec3[nv];

  for (int n = 0; n < nv; n++)
  {
    getline(in, readLine);
    delimiterPos_1 = readLine.find(" ", 0);
    vertices[n].set_x(atof(readLine.substr(0, delimiterPos_1).c_str()));
    delimiterPos_2 = readLine.find(" ", delimiterPos_1 + 1);
    vertices[n].set_y(atof(readLine.substr(delimiterPos_1, delimiterPos_2).c_str()));
    delimiterPos_3 = readLine.find(" ", delimiterPos_2 + 1);
    vertices[n].set_z(atof(readLine.substr(delimiterPos_2, delimiterPos_3).c_str()));
  }

  // Read the faces
  faces = new face[nf];

  for (int n = 0; n < nf; n++)
  {
    getline(in, readLine);
    delimiterPos_1 = readLine.find(" ", 0);
    delimiterPos_2 = readLine.find(" ", delimiterPos_1 + 1);
    delimiterPos_3 = readLine.find(" ", delimiterPos_2 + 1);
    delimiterPos_4 = readLine.find(" ", delimiterPos_3 + 1);

    if (atoi(readLine.substr(0, delimiterPos_1).c_str()) != 3)
    {
      cout << filename 
        << "\n error: Polygon of OFF file must be triangle." << endl;
      exit(0);
    }

    faces[n].v1 = atoi(readLine.substr(delimiterPos_1, delimiterPos_2).c_str());
    faces[n].v2 = atoi(readLine.substr(delimiterPos_2, delimiterPos_3).c_str());
    faces[n].v3 = atoi(readLine.substr(delimiterPos_3, delimiterPos_4).c_str());
  }
}