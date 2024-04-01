// Copyright 2024 Semenova Veronika
#pragma once

#include <vector>

#include "core/task/include/task.hpp"

class ImageFilterVerGauss : public ppc::core::Task {
 public:
  explicit ImageFilterVerGauss(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  //std::vector<std::vector<int>> kernel;
  std::vector<std::vector<int>> image;
  std::vector<std::vector<int>> filteredImage;
};
