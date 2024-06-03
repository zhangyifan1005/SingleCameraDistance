#include <iostream>
#include <opencv2/opencv.hpp>

class DistanceDetect
{
    public:
    DistanceDetect() = delete;
    DistanceDetect(const cv::Mat &intrisicm,const float body_height,const float camera_f,const float device2ground);
    ~DistanceDetect() = default;

    float CalPerson2Ground(const cv::Point2i &avg_top,const cv::Point2i &avg_bottom);

    private:
    const cv::Mat m_intrisic;
    const cv::Mat m_intrisic_inv;
    const float m_body_height;
    const float m_camera_f;
    const float m_device2ground;
};