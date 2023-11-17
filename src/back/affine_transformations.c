#include "affine_transformations.h"

void moveX(Data *data, double distance) {
  for (int i = 0; i < data->vertexCount * 3; i += 3) {
    data->m.mtrx[i] += distance;
  }
}

void moveY(Data *data, double distance) {
  for (int i = 1; i < data->vertexCount * 3; i += 3) {
    data->m.mtrx[i] += distance;
  }
}

void moveZ(Data *data, double distance) {
  for (int i = 2; i < data->vertexCount * 3; i += 3) {
    data->m.mtrx[i] += distance;
  }
}

void rotateOX(Data *data, double angle) {
  angle = angle * M_PI / 180;
  for (int i = 0; i < data->vertexCount * 3; i += 3) {
    double tempY = data->m.mtrx[i + 1];
    double tempZ = data->m.mtrx[i + 2];
    data->m.mtrx[i * 3 + 1] = cos(angle) * tempY - sin(angle) * tempZ;
    data->m.mtrx[i * 3 + 2] = sin(angle) * tempY + cos(angle) * tempZ;
  }
}

void rotateOY(Data *data, double angle) {
  angle = angle * M_PI / 180;
  for (int i = 0; i < data->vertexCount * 3; i += 3) {
    double tempX = data->m.mtrx[i];
    double tempZ = data->m.mtrx[i + 2];
    data->m.mtrx[i * 3] = cos(angle) * tempX + sin(angle) * tempZ;
    data->m.mtrx[i * 3 + 2] = -sin(angle) * tempX + cos(angle) * tempZ;
  }
}

void rotateOZ(Data *data, double angle) {
  angle = angle * M_PI / 180;
  for (int i = 0; i < data->vertexCount * 3; i += 3) {
    double tempX = data->m.mtrx[i];
    double tempY = data->m.mtrx[i + 1];
    data->m.mtrx[i * 3] = cos(angle) * tempX - sin(angle) * tempX;
    data->m.mtrx[i * 3 + 1] = sin(angle) * tempX + cos(angle) * tempY;
  }
}

void centeringModel(Data *data) {
  findMinMaxValue(data);
  calculateCentre(data);
  double scale = calculateScale(data);
  setScale(data, scale);
}

void findMinMaxValue(Data *data) {
  for (int i = 0; i < data->vertexCount; i++) {
    if (data->m.mtrx[i * 3] < data->mnmx.xMin) {
      data->mnmx.xMin = data->m.mtrx[i * 3];
    }
    if (data->m.mtrx[i * 3] > data->mnmx.xMax) {
      data->mnmx.xMax = data->m.mtrx[i * 3];
    }
    if (data->m.mtrx[i * 3 + 1] < data->mnmx.yMin) {
      data->mnmx.yMin = data->m.mtrx[i * 3 + 1];
    }
    if (data->m.mtrx[i * 3 + 1] > data->mnmx.yMax) {
      data->mnmx.yMax = data->m.mtrx[i * 3 + 1];
    }
    if (data->m.mtrx[i * 3 + 2] < data->mnmx.zMin) {
      data->mnmx.zMin = data->m.mtrx[i * 3 + 2];
    }
    if (data->m.mtrx[i * 3 + 2] > data->mnmx.zMax) {
      data->mnmx.zMax = data->m.mtrx[i * 3 + 2];
    }
  }
}

void calculateCentre(Data *data) {
  double centreX = data->mnmx.xMin + (data->mnmx.xMax - data->mnmx.xMin) / 2;
  double centreY = data->mnmx.yMin + (data->mnmx.yMax - data->mnmx.yMin) / 2;
  double centreZ = data->mnmx.zMin + (data->mnmx.zMax - data->mnmx.zMin) / 2;
  for (int i = 0; i < data->vertexCount; i++) {
    data->m.mtrx[i * 3] -= centreX;
    data->m.mtrx[i * 3 + 1] -= centreY;
    data->m.mtrx[i * 3 + 2] -= centreZ;
  }
}

double calculateScale(Data *data) {
  double x = data->mnmx.xMax - data->mnmx.xMin;
  double y = data->mnmx.yMax - data->mnmx.yMin;
  double z = data->mnmx.zMax - data->mnmx.zMin;
  double dMax = findMaxOfTree(x, y, z);
  double modelScale = 0.5;
  double k = 2 * modelScale / dMax;
  return k;
}

double findMaxOfTree(double x, double y, double z) {
  double max = fmax(fmax(x, y), z);
  return max;
}

void setScale(Data *data, double scale) {
  for (int i = 0; i < data->m.rows + 1; i++) {
    data->m.mtrx[i * 3] *= scale;
    data->m.mtrx[i * 3 + 1] *= scale;
    data->m.mtrx[i * 3 + 2] *= scale;
  }
}