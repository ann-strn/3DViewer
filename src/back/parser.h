/**
 * @file parser.h
 * @version 1.0.1
 * @brief Заголовочный файл для парсера 3D моделей в формате OBJ
 */

#ifndef C8_3DVIEWER_V1_0_1_SRC_BACK_PARSER_H
#define C8_3DVIEWER_V1_0_1_SRC_BACK_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief Структура, представляющая полигон 3D модели
 */
typedef struct Polygon
{
    int *vertices;                 /**< Массив индексов вершин полигона */
    int numberOfVerticesInPolygon; /**< Количество вершин в полигоне */
} Polygon;

/**
 * @brief Структура, представляющая матрицу
 */
typedef struct Matrix
{
    double *mtrx; /**< Указатель на массив элементов матрицы */
    int rows;     /**< Количество строк в матрице */
    int cols;     /**< Количество столбцов в матрице */
} Matrix;

/**
 * @brief Структура, представляющая минимальные и максимальные значения координат 3D модели
 */
typedef struct MinMax
{
    double xMin; /**< Минимальное значение координаты X */
    double xMax; /**< Максимальное значение координаты X */
    double yMin; /**< Минимальное значение координаты Y */
    double yMax; /**< Максимальное значение координаты Y */
    double zMin; /**< Минимальное значение координаты Z */
    double zMax; /**< Максимальное значение координаты Z */
} MinMax;

/**
 * @brief Структура, представляющая данные 3D модели
 */
typedef struct Data
{
    int vertexCount;  /**< Количество вершин в 3D модели */
    int polygonCount; /**< Количество полигонов в 3D модели */
    Matrix m;         /**< Матрица координат вершин 3D модели */
    Polygon *polygon; /**< Массив полигонов 3D модели */
    MinMax mnmx;      /**< Минимальные и максимальные значения координат 3D модели */
} Data;

/**
 * @brief Открыть файл 3D модели в формате OBJ и прочитать его содержимое
 * @param fileName Имя файла 3D модели
 * @return Указатель на структуру Data, содержащую данные 3D модели
 */
Data *openObjFile(const char *fileName);

/**
 * @brief Инициализировать структуру Data
 * @return Указатель на структуру Data
 */
Data *initializeData();

/**
 * @brief Инициализировать матрицу координат вершин 3D модели
 * @param data Указатель на структуру Data
 */
void initMatrix(Data *data);

/**
 * @brief Посчитать количество вершин и полигонов в файле 3D модели
 * @param objFile Указатель на файл 3D модели
 * @param data Указатель на структуру Data
 */
void countVerticesAndPolygons(FILE *objFile, Data *data);

/**
 * @brief Разобрать содержимое файла 3D модели и заполнить структуру Data
 * @param objFile Указатель на файл 3D модели
 * @param data Указатель на структуру Data
 */
void parseVerticesAndPolygons(FILE *objFile, Data *data);

/**
 * @brief Освободить выделенную память, занятую структурой Data
 * @param data Указатель на структуру Data
 */
void destructData(Data *data);

#endif // C8_3DVIEWER_V1_0_1_SRC_BACK_PARSER_H