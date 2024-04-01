// Copyright 2024 Semenova Veronika
#include "seq\semenova_v_image_filter_ver_Gauss\include\fvG.hpp"

#include <cstring>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

namespace {

uint8_t get_byte_val(double val, size_t byte_num) {
  char bytes[sizeof(double)];
  std::memcpy(bytes, &val, sizeof(double));
  return bytes[byte_num];
}

}  // namespace

/*
int main() {
  // Пример входных данных (значения пикселей и ядра Гаусса)
  std::vector<std::vector<int>> image = {{...}};  // Заполните значениями пикселей
  std::vector<std::vector<int>> kernel = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

  pre_processing(image);

  if (validation(image, kernel)) {
    run(image, kernel);
    post_processing(image);
  } else {
    std::cout << "Invalid image or kernel dimensions." << std::endl;
  }

  return 0;
}
*/



bool ImageFilterVerGauss::validation() {

  internal_order_test();

  return !taskData->inputs_count.empty() 
      && !taskData->inputs.empty() 
      && !taskData->inputs_count.empty() 
      && !taskData->inputs.empty() 

      && taskData->inputs[0] != nullptr 
      && taskData->outputs[0] != nullptr 

      && taskData->outputs_count[0] == taskData->inputs_count[0] 
      && taskData->outputs_count[1] == taskData->inputs_count[1];

  // return (imageRows >= kernelRows && imageCols >= kernelCols);
     
}


bool ImageFilterVerGauss::pre_processing() {

  internal_order_test(); // Init value for input and output

  /*
  for (auto& row : image) {
    for (int& pixel : row) {
      // Преобразование в оттенки серого (например, среднее значение RGB)
      int gray_value = (pixel.r + pixel.g + pixel.b) / 3;
      pixel.r = pixel.g = pixel.b = gray_value;
    }
  }
  */
  
  

  //data_size = taskData->inputs_count[0];
  //data_ptr = reinterpret_cast<double*>(taskData->inputs[0]);

  //return data_size == 0 || data_ptr != nullptr;
  return true;
}

bool ImageFilterVerGauss::run() { // Функция для применения линейной фильтрации
  internal_order_test();

  /*
  try {
    for (size_t byte_num = 0; byte_num < sizeof(double); byte_num++) {
      for (size_t i = 0; i < data_size; i++) {
        bucket_arr[get_byte_val(data_ptr[i], byte_num)].emplace_back(data_ptr[i]);
      }

      size_t i = 0;
      for (auto& vec : bucket_arr) {
        for (double val : vec) {
          data_ptr[i++] = val;
        }
        vec.clear();
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Double Radix sort Exception error: " << e.what() << std::endl;
    return false;
  }

  return true;

  /*int rows = image.size();
  int cols = image[0].size();

  // Создание новой матрицы для обработанного изображения
  std::vector<std::vector<int>> filteredImage(rows, std::vector<int>(cols, 0));

  // Проход по каждому пикселю изображения
  for (int i = 1; i < rows - 1; ++i) {
    for (int j = 1; j < cols - 1; ++j) {
      int sum = 0;
      // Применение ядра
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          sum += image[i + x][j + y] * kernel[x + 1][y + 1];
        }
      }
      // Установка нового значения пикселя
      filteredImage[i][j] = sum;
    }
  }

  // Вывод обработанного изображения
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << filteredImage[i][j] << " ";
    }
    std::cout << std::endl;
  }*/
  return true;
}

bool ImageFilterVerGauss::post_processing() {
  internal_order_test();
  //*reinterpret_cast<double**>(taskData->outputs[0]) = data_ptr;
  return true;

  /*for (auto& row : filteredImage) {
    for (int& pixel : row) {
      // Ограничение значений пикселей в диапазоне [0, 255]
      pixel = std::max(0, std::min(255, pixel));
    }
  }*/
}

