#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

float body_height = 2.0f;
float camera_f = 1.0f;

int main()
{
    float x1 = 0.0f,y1 = 0.5f;
    float x2 = 0.0f,y2 = -0.5f;

    cv::Mat vetcor1 = (cv::Mat_<float>(1,3) << x1,y1,camera_f);
    cv::Mat vetcor2 = (cv::Mat_<float>(1,3) << x2,y2,camera_f);

    std::cout << "vector1 = " << vetcor1 << std::endl;
    std::cout << "vector2 = " << vetcor2 << std::endl;

    float pn_1 = camera_f / y1;
    float pn_2 = camera_f / y2;

    std::cout << "pn_1 = " << pn_1 << " ,pn_2 = " << pn_2 << std::endl;
      
    float y = (((y1 - body_height) * pn_1 - pn_2 * y2) / (pn_1 - pn_2));

    std::cout << "y = " << y << std::endl;

    return 0;
}