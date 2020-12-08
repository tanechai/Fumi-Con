#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>


/*
void mouse_callback(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN && selectedPoints.size() < 4)
    {
        selectedPoints.push_back(cv::Point2f(x, y));

        std::cout << "Left mouse button is pressed." << std::endl;
    }
    if (event == cv::EVENT_MOUSEMOVE)
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
}*/

int main()
{
    cv::VideoCapture cap(0); //デバイスのオープン

    if (!cap.isOpened()) //カメラデバイスが正常にオープンしたか確認．
    {
        //読み込みに失敗したときの処理
        return -1;
    }
    std::vector<cv::Point2f> selectedPoints;
    cv::Mat frame;
    cap.read(frame);
    cv::imshow("example", frame);
    //cv::setMouseCallback("example", mouse_callback);
    while (selectedPoints.size() < 4)
    {
        
        for (const cv::Point2f& p : selectedPoints)
        {
            cv::drawMarker(frame, p, cv::Scalar(0, 255, 0));
        }
        std::cout << "(^^)" << std::endl;
        cv::imshow("example2", frame);
    }
    cv::destroyWindow("example");

    cv::waitKey();

    return 0;
}
/*
std::vector<cv::Point2f> selectPoints(int numberOfTime);

int main(int argc, char** argv)
{

    cv::Mat K = (cv::Mat_<double>(3,3) << 502.0371895909179, 0, 300.0349293832901, 0, 501.6613987605497, 240.5838189630333, 0, 0, 1);
    cv::Mat distCoeffs = (cv::Mat_<double>(1,5) << -0.4093166455082794, 0.2602125340365962, 0.0005732983044178636, 3.803626762254057e-05, -0.1121563761094383);

    std::vector<cv::Point2f> selectedPoints(4);
    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,20, 0.001);

    selectedPoints = selectPoints();

    while(true){

    }
    std::vector<cv::Mat> imgs;
    {
        util::camera cam(0);
        std::cout << "caputure image" << std::endl;
        while(1){
            cam.show();
            if(cv::waitKey(1)>0){
                break;
            }
        }
        cv::Mat img = cam.capture();
        cv::Mat img_;
        cv::undistort(img, img_, K, distCoeffs);
        imgs.push_back(img_);
        cv::cvtColor(imgs[0],img,cv::COLOR_RGB2GRAY);
        checkerImgs.push_back(img);
        std::cout << "Load image" << std::endl;
    }

    cv::Size2d imageSize(200.0,100.0);
    cv::Mat transformedImg;
    const std::vector<cv::Point2f> dst_pt{
        cv::Point2f(0,0),
        cv::Point2f(0,imageSize.height),
        cv::Point2f(imageSize.width,0),
        cv::Point2f(imageSize.width,imageSize.height)
    };
    
    
    cv::waitKey();
}

std::vector<cv::Point2f> selectPoints(int numberOfTime){

}
*/