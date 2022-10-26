#ifndef regressionh
#define regressionh

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using Data = std::vector<std::vector<double>>;

namespace regression {

Data read_database(std::string filepath);
double hypothesis(const std::vector<double> &theta, std::vector<double> x);
double cost_function(Data &dataset, const std::vector<double> &theta);
std::vector<double> update(Data &dataset, std::vector<double> &theta,
                           double lr);
std::vector<double> linear_regression(Data &dataset,
                                      const std::vector<double> init_theta,
                                      const double lr);
} // namespace regression

#endif