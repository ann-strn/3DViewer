/**
 * @file affine_transformation.h
 * @version 1.0.1
 * @brief Заголовочный файл для аффинных преобразований 3D моделей
 */

#ifndef C8_3DVIEWER_V1_0_1_SRC_BACK_AFFINE_TRANSFORMATION_H
#define C8_3DVIEWER_V1_0_1_SRC_BACK_AFFINE_TRANSFORMATION_H

#include "parser.h"
#include <math.h>

/**
 * @brief Переместить 3D модель вдоль оси X на заданное расстояние
 * @param data Указатель на данные 3D модели
 * @param distance Расстояние для перемещения модели вдоль оси X
 */
void moveX(Data *data, double distance);

/**
 * @brief Переместить 3D модель вдоль оси Y на заданное расстояние
 * @param data Указатель на данные 3D модели
 * @param distance Расстояние для перемещения модели вдоль оси Y
 */
void moveY(Data *data, double distance);

/**
 * @brief Переместить 3D модель вдоль оси Z на заданное расстояние
 * @param data Указатель на данные 3D модели
 * @param distance Расстояние для перемещения модели вдоль оси Z
 */
void moveZ(Data *data, double distance);

/**
 * @brief Повернуть 3D модель вокруг оси X на заданный угол
 * @param data Указатель на данные 3D модели
 * @param angle Угол для поворота модели вокруг оси X
 */
void rotateOX(Data *data, double angle);

/**
 * @brief Повернуть 3D модель вокруг оси Y на заданный угол
 * @param data Указатель на данные 3D модели
 * @param angle Угол для поворота модели вокруг оси Y
 */
void rotateOY(Data *data, double angle);

/**
 * @brief Повернуть 3D модель вокруг оси Z на заданный угол
 * @param data Указатель на данные 3D модели
 * @param angle Угол для поворота модели вокруг оси Z
 */
void rotateOZ(Data *data, double angle);

/**
 * @brief Найти минимальное и максимальное значения координат 3D модели
 * @param data Указатель на данные 3D модели
 */
void findMinMaxValue(Data *data);

/**
 * @brief Рассчитать центр 3D модели
 * @param data Указатель на данные 3D модели
 */
void calculateCentre(Data *data);

/**
 * @brief Рассчитать коэффициент масштабирования для 3D модели
 * @param data Указатель на данные 3D модели
 * @return Коэффициент масштабирования для 3D модели
 */
double calculateScale(Data *data);

/**
 * @brief Найти максимальное значение из заданного набора координат
 * @param x Координата X
 * @param y Координата Y
 * @param z Координата Z
 * @return Максимальное значение из заданного набора координат
 */
double findMaxOfTree(double x, double y, double z);

/**
 * @brief Установить коэффициент масштабирования для 3D модели
 * @param data Указатель на данные 3D модели
 * @param scale Коэффициент масштабирования для 3D модели
 */
void setScale(Data *data, double scale);

/**
 * @brief Центрировать 3D модель в начале координат
 * @param data Указатель на данные 3D модели
 */
void centeringModel(Data *data);

#endif // C8_3DVIEWER_V1_0_1_SRC_BACK_AFFINE_TRANSFORMATION_H.