#include "distance_detect.hpp"

DistanceDetect::DistanceDetect(const cv::Mat &intrisicm,const float body_height,const float camera_f,const float device2ground)
    :m_intrisic(intrisicm),m_intrisic_inv(intrisicm.inv()),m_body_height(body_height),m_camera_f(camera_f),m_device2ground(device2ground)
{

}

float DistanceDetect::CalPerson2Ground(const cv::Point2i &avg_top,const cv::Point2i &avg_bottom)
{
    cv::Mat pts;

    cv::Mat pt_top = (cv::Mat_<float>(3,1) << static_cast<float>(avg_top.x) * m_camera_f,static_cast<float>(avg_top.y) * m_camera_f,m_camera_f);
    cv::Mat pt_bottom = (cv::Mat_<float>(3,1) << static_cast<float>(avg_bottom.x) * m_camera_f,static_cast<float>(avg_bottom.y) * m_camera_f,m_camera_f);

    std::cout << "pt_top = " << pt_top << std::endl;
    std::cout << "pt_bottom = " << pt_bottom << std::endl;

    cv::hconcat(pt_top, pt_bottom, pts);

    cv::Mat pt_camera = m_intrisic_inv * pts;

    std::cout << "pt_camera = " << pt_camera << std::endl;

    // float top_y= static_cast<float>(avg_top.y),bottom_y= static_cast<float>(avg_bottom.y);
    float top_x = pt_camera.at<float>(0,0),top_y = pt_camera.at<float>(1,0);
    float bottom_x = pt_camera.at<float>(0,1),bottom_y = pt_camera.at<float>(1,1);
    float y = 99999;

    if(top_y == bottom_y)
    {
        return y;
    }
    else
    {
        float proportion = m_body_height / (top_y - bottom_y);
        float z_distance = std::abs(m_camera_f * proportion);

        std::cout << "z_distance = " << z_distance << std::endl;

        y = bottom_y * proportion;
    }

    return (y + m_device2ground);
}

cv::Mat intrisicm = (cv::Mat_<float>(3,3) << 2150.93f,0.0f,1966.35f,0.0f,2144.71f,1036.51f,0.0f,0.0f,1.0f);

int main()
{
    cv::Point2i top(1140,1256),bottom(1140,1329);

    DistanceDetect distance_detect(intrisicm,1.7f,0.0042f,1.6f);

    float height = distance_detect.CalPerson2Ground(top,bottom);

    std::cout << "height = " << height << std::endl;

    return 0;
}