#include "parser.h"

#include "affine_transformations.h"

Data *openObjFile(const char *fileName) {
  FILE *objFile = fopen(fileName, "r");
  if (objFile == NULL) {
    printf("Failed to open file: %s\n", fileName);
    return 0;
  }

  Data *data = initializeData();
  countVerticesAndPolygons(objFile, data);
  initMatrix(data);
  parseVerticesAndPolygons(objFile, data);

  centeringModel(data);

  fclose(objFile);
  return data;
}

Data *initializeData() {
  Data *data = (Data *)malloc(sizeof(Data));
  data->polygon = NULL;
  data->vertexCount = 0;
  data->polygonCount = 0;
  data->m.cols = 0;
  data->m.rows = 0;
  data->mnmx.xMax = -INFINITY;
  data->mnmx.xMin = INFINITY;
  data->mnmx.yMax = -INFINITY;
  data->mnmx.yMin = INFINITY;
  data->mnmx.zMax = -INFINITY;
  data->mnmx.zMin = INFINITY;
  return data;
}

void countVerticesAndPolygons(FILE *objFile, Data *data) {
  char *line = NULL;
  size_t len = 1000000;
  line = (char *)malloc(sizeof(char) * len);

  if (objFile != NULL) {
    while ((getline(&line, &len, objFile)) != EOF) {
      if (strncmp(line, "v ", 2) == 0)
        data->vertexCount++;
      else if (strncmp(line, "f ", 2) == 0)
        data->polygonCount++;
    }
  }
  fseek(objFile, 0, SEEK_SET);
  free(line);
}

void initMatrix(Data *data) {
  data->m.rows = data->vertexCount;
  data->m.cols = 3;
  data->m.mtrx = NULL;
  data->m.mtrx =
      (double *)malloc((data->m.rows + 1) * data->m.cols * sizeof(double));
  if (data->m.mtrx != NULL) {
    data->m.mtrx[0] = 0;
    data->m.mtrx[1] = 0;
    data->m.mtrx[2] = 0;
  }
}

void parseVerticesAndPolygons(FILE *objFile, Data *data) {
  data->polygon = (Polygon *)malloc(sizeof(Polygon) * data->polygonCount);
  char *line = NULL;
  size_t len = 1000000;
  line = (char *)malloc(sizeof(char) * len);
  size_t indexVertex = 0, indexPolygon = 0;
  size_t vCount = 0;

  if (objFile != NULL) {
    while ((getline(&line, &len, objFile)) != EOF) {
      if (strncmp(line, "v ", 2) == 0) {
        double x = 0, y = 0, z = 0;
        sscanf(line, "v %lf %lf %lf", &x, &y, &z);
        data->m.mtrx[vCount++] = x;
        data->m.mtrx[vCount++] = y;
        data->m.mtrx[vCount++] = z;
        ++indexVertex;
      }

      else if (strncmp(line, "f ", 2) == 0) {
        Polygon polygon = {0};
        //
        int pvCount = 0, was_space = 0, sign = 1;
        while (*line != '\0' && *line != '\n') {
          if (*line == '-') {
            sign = -1;
            line++;
          }
          if (isdigit(*line) && was_space) {
            polygon.vertices =
                realloc(polygon.vertices, ((pvCount + 1) * 2) * sizeof(int));
            if (sign == -1) {
              polygon.vertices[pvCount] = vCount / 3 - atoi(line);
            } else {
              polygon.vertices[pvCount] = atoi(line) - 1;
            }
            if (pvCount != 0) {
              pvCount++;
              polygon.vertices[pvCount] = polygon.vertices[pvCount - 1];
            }
            pvCount++;
            line++;
            was_space = 0;
          }
          while (*line != ' ' && *line != '\0' && *line != '\n') line++;
          if (*line == ' ') {
            was_space = 1;
            line++;
          }
          sign = 1;
        }
        polygon.vertices[pvCount] = polygon.vertices[0];
        pvCount++;
        polygon.numberOfVerticesInPolygon = pvCount;
        //
        data->polygon[indexPolygon] = polygon;
        indexPolygon++;
      }
    }
  }
}

void destructData(Data *data) {
  for (int i = 0; i < data->polygonCount; i++) free(data->polygon[i].vertices);
  free(data->polygon);
  free(data->m.mtrx);
}
