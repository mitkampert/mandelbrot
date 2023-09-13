#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

using namespace std;

int main() {

    std::ofstream outfile;

    // amount of images rendered
    int img_0 = 0;
    int img_limit = 150;


    // render settings
    int image_width = 1080;
    int image_height = 1080;

    int base_iterations = 100;
    bool dynamic_iterations = true;
    int iterations = base_iterations;

    int zoom_percent = 5;
    
    // zoom coordinates
    float zoom_re = -1.156369637;
    float zoom_im = 0.279170155;

    // initial window
    float x_min = -2.2;
    float x_max = 0.8;

    float y_min = -1.5;
    float y_max = 1.5;


    for (int img = img_0; img < img_limit; ++img) {

        std::cout << "Rendering image " << img - img_0 + 1 << '/' << img_limit - img_0 << '\n';

        int img_n = img;

        string filename = to_string(img_n) + ".ppm";

        outfile.open("images/" + filename, std::ios_base::app);

        float zoom = 1 - (float(zoom_percent)/100);

        x_min = zoom_re - zoom*(zoom_re-x_min);
        x_max = zoom_re + zoom*(x_max-zoom_re);

        y_min = zoom_im - zoom*(zoom_im-y_min);
        y_max = zoom_im + zoom*(y_max-zoom_im);

        if (dynamic_iterations == true) {
            iterations = base_iterations * pow(1.01, img);
        }
        else {
            iterations = base_iterations;
        }


        // Render

        outfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

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
                        r = 10 + n*(245.0/float(iterations));
                        g = 10 + n*(245.0/float(iterations));
                        b = 10 + n*(245.0/float(iterations));
                        break;
                    }
                }

                outfile << r << ' ' << g << ' ' << b << '\n';
            }
        }
        outfile.close();
    }
}