#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

int main() {

    // Image

    int image_width = 2160*5;
    int image_height = 2160*5;

    // float x_min = -0.05;
    // float x_max = 0.05;

    // float y_min = 0.75;
    // float y_max = 0.85;

    float x_min = -2.2;
    float x_max = 0.8;

    float y_min = -1.5;
    float y_max = 1.5;

    int iterations = 150;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {

            std::complex<double> z(0, 0);
            std::complex<double> c((std::abs(x_max - x_min)/image_width)*i + x_min, -(std::abs(y_max - y_min)/image_height)*j + y_max);

            int r = 0;
            int g = 0;
            int b = 0;
            
            for (int n = 0; n < iterations; ++n) {
                z = pow(z, 2.0) + c;
                if (std::abs(z) > 2) {
                    r = 10 + n*(245/iterations);
                    g = 10 + n*(245/iterations);
                    b = 10 + n*(245/iterations);
                    break;
                }
            }

            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }
}