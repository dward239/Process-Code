#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
// Define erf function if not available
#include <cmath>
using namespace std;
// Custom erf implementation if needed
double custom_erf(double x) {
   // Use std::erf if available
   return erf(x);
}
double ra(double Ca) {
   double Cb = 1 - 0.5 * Ca;
   return (Ca * pow(Cb, 2)) / (1 + Ca + pow(Cb, 2));
}
double d2radCa(double Cab) {
   double Cb = 1 - 0.5 * Cab;
   double num1 = 2 * Cab * pow(Cb, 2);
   double denom1 = pow(pow(Cb, 2) + Cab + 1, 3);
   double num2 = 2 * pow(Cb, 2);
   double denom2 = pow(pow(Cb, 2) + Cab + 1, 2);
   return -(num1 / denom1 - num2 / denom2);
}
int main() {
   vector<double> x;
   vector<double> y;
   vector<double> erfunc;
   double start = -4.0;
   double end = 4.0;
   double step = 0.01;
   for (double i = start; i <= end; i += step) {
       x.push_back(i);
       y.push_back(custom_erf(i));
   }
   // Coefficients
   double a[] = {1.213, -0.09476, -13.94, -0.1488, -13.96, -0.2845, -3.579e-05, -0.002665};
   double b[] = {0.4524, 1.972, 2.935, 2.152, 2.935, 1.383, 8.485, 4.001};
   double c[] = {7.816e-10, -3.286e-07, -2.073e-07, -3.142, -3.142, -3.142, 9.5e-07, -3.142};
   for (size_t i = 0; i < x.size(); ++i) {
       double val = 0.0;
       for (int j = 0; j < 8; ++j) {
           val += a[j] * sin(b[j] * x[i] + c[j]);
       }
       erfunc.push_back(val);
   }
   // Optional: Output to file for plotting (e.g., with Python or GNUPlot)
   ofstream outfile("erf_data.csv");
   outfile << "x,y,erfunc\n";
   for (size_t i = 0; i < x.size(); ++i) {
       outfile << x[i] << "," << y[i] << "," << erfunc[i] << "\n";
   }
   outfile.close();
   // Test symbolic part approximation
   double Ca_test = 0.5;
   cout << "ra(Ca_test) = " << ra(Ca_test) << endl;
   cout << "d2radCa(Ca_test) = " << d2radCa(Ca_test) << endl;
   return 0;
