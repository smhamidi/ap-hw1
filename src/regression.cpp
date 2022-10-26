#include "regression.h"
using namespace regression;

Data regression::read_database(std::string filepath) {
  std::ifstream csvFile(filepath);
  Data fish_data{};
  if (!csvFile)
    throw std::runtime_error("your path is NOT valid");
  else {
    std::string line{};
    while (std::getline(csvFile, line)) {
      std::vector<double> row{};
      row.push_back(1);
      std::stringstream str(line);
      std::string separated{};
      while (std::getline(str, separated, ',')) {
        row.push_back(std::stod(separated));
      }
      fish_data.push_back(row);
    }
    return fish_data;
  }
  return fish_data;
}

double regression::hypothesis(const std::vector<double> &theta,
                              std::vector<double> x) {
  double hypothesis{};
  if (theta.size() != x.size())
    throw std::logic_error("sizes of the two vector does NOT match");
  for (size_t i = 0; i < theta.size(); i++) {
    hypothesis += (theta)[i] * x[i];
  }
  return hypothesis;
}

double regression::cost_function(Data &dataset,
                                 const std::vector<double> &theta) {
  double cost{};
  for (size_t i = 0; i < dataset.size(); i++) {
    cost += (std::pow(hypothesis(theta, {(dataset)[i][0], (dataset)[i][1],
                                         (dataset)[i][2], (dataset)[i][3]}) -
                          (dataset)[i][4],
                      2));
  }
  cost *= 0.5;
  return cost;
}

std::vector<double> regression::update(Data &dataset,
                                       std::vector<double> &theta, double lr) {

  double sum{};
  for (size_t j = 0; j < theta.size(); j++) {
    sum = 0;
    for (size_t i = 0; i < dataset.size(); i++) {

      sum += ((hypothesis(theta, {(dataset)[i][0], (dataset)[i][1],
                                  (dataset)[i][2], (dataset)[i][3]}) -
               (dataset)[i][4]) *
              (dataset)[i][j]);
    }
    (theta)[j] -= (lr * sum);
  }
  return theta;
}

std::vector<double> regression::linear_regression(
    Data &dataset, const std::vector<double> init_theta, const double lr) {
  std::vector<double> theta{init_theta};
  double cost{};
  double reduced{};
  double prv_cost{};
  for (size_t i = 0; i < 10000; i++) {
    prv_cost = cost;
    cost = regression::cost_function(dataset, theta);
    reduced = prv_cost - cost;
    regression::update(dataset, theta, lr);
    std::cout << std::left << std::setw(6) << i + 1
              << "-> cost:   " << std::setprecision(6) << std::setw(15) << cost
              << "    -reduced cost: " << std::setprecision(10) << std::setw(15)
              << std::left << std::fixed << reduced << std::endl;
  }
  return theta;
}