

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
   // Start timer (optional)
   clock_t start = clock();
   //--------------------------------------------------------------------------
   // Constants
   const double a = 1151.29;
   const double b = 9287;
   const double c = 0.458682;
   const double phi = 0.247936;
   const double theta = 1.1432e-8;
   //--------------------------------------------------------------------------
   // Variables
   vector<double> Re;
   for (int i = 10; i <= 700; ++i) {
       Re.push_back(static_cast<double>(i));
   }
   const double Dh = 0.0833;
   int n = 50;
   vector<double> epsilon(n, 0.0);
   epsilon[0] = 0.00001;
   for (int i = 1; i < n; ++i) {
       epsilon[i] = epsilon[i - 1] + 0.0001;
   }
   //--------------------------------------------------------------------------
   // Friction factor calculation over meshgrid of Re and epsilon
   vector<vector<double>> Ff(Re.size(), vector<double>(n, 0.0));
   for (size_t i = 0; i < Re.size(); ++i) {
       for (int j = 0; j < n; ++j) {
           double top = theta * pow(Dh, 2);
           double alpha = a * Re[i] * epsilon[j];
           double beta = b * Dh;
           double lambert_input = phi * Re[i] * epsilon[j] / Dh;
           double inner = exp(lambert_input) * pow(Re[i], 2);
           double lambert = c * sqrt(inner);
           double denominator = pow(alpha - beta * lambert * exp(lambert), 2);
           Ff[i][j] = top / denominator;
       }
   }
   //--------------------------------------------------------------------------
   // Output to CSV for visualization
   ofstream outFile("fanning_friction.csv");
   outFile << "Re";
   for (int j = 0; j < n; ++j) {
       outFile << ",eps_" << j;
   }
   outFile << endl;
   for (size_t i = 0; i < Re.size(); ++i) {
       outFile << Re[i];
       for (int j = 0; j < n; ++j) {
           outFile << "," << Ff[i][j];
       }
       outFile << endl;
   }
   outFile.close();
   cout << "Fanning friction factor data written to 'fanning_friction.csv'" << endl;
   //--------------------------------------------------------------------------
   // End timer
   clock_t end = clock();
   double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
   cout << "Elapsed time: " << elapsed_secs << " seconds" << endl;
   return 0;
}
