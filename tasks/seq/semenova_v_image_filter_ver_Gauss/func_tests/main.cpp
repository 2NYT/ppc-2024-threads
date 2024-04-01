// Copyright 2024 Semenova Veronika
#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "seq\semenova_v_image_filter_ver_Gauss\include\fvG.hpp"

TEST(semenova_v_image_filter_ver_Gauss, incorrect_matrix_sizes) {
 
  // Create data
  size_t n = 11, m = 10;
  std::vector<double> image(n * m), filteredImage(n * m);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(image.data()));
  taskDataSeq->inputs_count.emplace_back(n);
  taskDataSeq->inputs_count.emplace_back(m);

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(filteredImage.data()));
  taskDataSeq->outputs_count.emplace_back(n);
  taskDataSeq->outputs_count.emplace_back(m);

  // Create Task
  ImageFilterVerGauss ImageFilterVerGauss(taskDataSeq);
  ASSERT_FALSE(ImageFilterVerGauss.validation());
}

/*
TEST(semenova_v_image_filter_ver_Gauss, zero_rhs_matrix) {
  // Create data
  size_t p = 11;
  size_t q = 10;
  size_t r = 9;
  std::vector<double> lhs_in = getRandomMatrix(p, q);
  std::vector<double> rhs_in(q * r);
  std::vector<double> out(p * r);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], 0.0);
  }
}

TEST(semenova_v_image_filter_ver_Gauss, zero_lhs_matrix) {
  // Create data
  size_t p = 11;
  size_t q = 10;
  size_t r = 9;
  std::vector<double> lhs_in(p * q);
  std::vector<double> rhs_in = getRandomMatrix(q, r);
  std::vector<double> out(p * r);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], 0.0);
  }
}

TEST(semenova_v_image_filter_ver_Gauss, identity_rhs_matrix) {
  // Create data
  size_t p = 11;
  size_t q = 10;
  size_t r = q;
  std::vector<double> lhs_in = getRandomMatrix(p, q);
  std::vector<double> rhs_in = getIdentityMatrix(q);
  std::vector<double> out(p * r);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], lhs_in[i]);
  }
}

TEST(semenova_v_image_filter_ver_Gauss, identity_lhs_matrix) {
  // Create data
  size_t p = 11;
  size_t q = p;
  size_t r = 10;
  std::vector<double> lhs_in = getIdentityMatrix(p);
  std::vector<double> rhs_in = getRandomMatrix(q, r);
  std::vector<double> out(p * r);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], rhs_in[i]);
  }
}

TEST(semenova_v_image_filter_ver_Gauss, matmult_with_answer) {
  // Create data
  size_t p = 4;
  size_t q = 5;
  size_t r = 4;
  std::vector<double> lhs_in{
      0, 10, 0, 0, 0, 0, 5, 3, 0, 0, 1, -1, -1, 0, 0, 0, 0, -5, 0, 20,
  };
  std::vector<double> rhs_in{
      1, 1, 0, 0, 0, 5, 9, 9, 0, 0, 0, -1, 13, 7, 0, 0, 7, 0, 8, 0,
  };
  std::vector<double> ans{
      0, 50, 90, 90, 0, 25, 45, 42, 1, -4, -9, -8, 140, 0, 160, 5,
  };
  std::vector<double> out(p * r);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_DOUBLE_EQ(out[i], ans[i]);
  }
}

TEST(semenova_v_image_filter_ver_Gauss, special_matmult) {
  // Create data
  size_t p = 11;
  size_t q = 10;
  size_t r = 11;
  std::vector<double> lhs_in(p * q);
  for (size_t i = 0; i < p; ++i) {
    if (i % 2 == 0)
      for (size_t j = 0; j < q; ++j) {
        lhs_in[i * q + j] = 1.0;
      }
  }
  std::vector<double> rhs_in(q * r);
  for (size_t i = 0; i < q; ++i) {
    for (size_t j = 0; j < r; ++j) {
      if (j % 2 == 0) rhs_in[i * r + j] = 1.0;
    }
  }
  std::vector<double> out(p * r);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(lhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(p);
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(rhs_in.data()));
  taskDataSeq->inputs_count.emplace_back(q);
  taskDataSeq->inputs_count.emplace_back(r);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(p);
  taskDataSeq->outputs_count.emplace_back(r);

  // Create Task
  CRSMatMult crsMatMultSeq(taskDataSeq);
  ASSERT_TRUE(crsMatMultSeq.validation());
  ASSERT_TRUE(crsMatMultSeq.pre_processing());
  ASSERT_TRUE(crsMatMultSeq.run());
  ASSERT_TRUE(crsMatMultSeq.post_processing());
  for (size_t i = 0; i < p; ++i) {
    for (size_t j = 0; j < r; ++j) {
      if (i % 2 == 0 && j % 2 == 0)
        EXPECT_DOUBLE_EQ(out[i * r + j], q);
      else
        EXPECT_DOUBLE_EQ(out[i * r + j], 0.0);
    }
  }
}
*/