#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>


class selectedData{
public:
    std::vector<cv::Point2f> selectedPoints;
	int selectedNumber;
    selectedData():selectedPoints(std::vector<cv::Point2f>(4)),selectedNumber(0){};
};

void mouse_callback(int event, int x, int y, int flags, void *userdata)
{
    selectedData *p = (selectedData*)userdata;
    if (event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "Left mouse button is pressed." << std::endl;
        if(p->selectedNumber == 4){
            std::cout << "All points selected" << std::endl;
            return;
        }
        p->selectedPoints.at(p->selectedNumber) = cv::Point2d(x,y);
        p->selectedNumber++;
        std::cout << x << "," << y << std::endl;
    }
}

int main(int argc, char** argv)
{
    cv::VideoCapture cap(0);

    if(!cap.isOpened())
    {
        return -1;
    }
    cv::Mat K = (cv::Mat_<double>(3,3) << 502.0371895909179, 0, 300.0349293832901, 0, 501.6613987605497, 240.5838189630333, 0, 0, 1);
    cv::Mat distCoeffs = (cv::Mat_<double>(1,5) << -0.4093166455082794, 0.2602125340365962, 0.0005732983044178636, 3.803626762254057e-05, -0.1121563761094383);
    
    cv::Mat frame_;
    cv::Mat frame;
    cap.read(frame_);
    
    cv::Mat newK = cv::getOptimalNewCameraMatrix(K,distCoeffs,cv::Size2d(frame_.cols,frame_.rows),0.05);
    cv::Mat R = cv::Mat::eye(3,3,CV_32F);
    std::vector<cv::Mat> map(2);
    cv::initUndistortRectifyMap(K,distCoeffs,R,newK,cv::Size2d(frame_.cols,frame_.rows),CV_32FC1,map.at(0),map.at(1));
    cv::remap(frame_,frame,map.at(0),map.at(1),cv::INTER_AREA);
    
    //cv::undistort(frame_, frame, K, distCoeffs);
    const std::string selectWinName = "select window";
    selectedData data;
    cv::namedWindow(selectWinName);
    cv::imshow(selectWinName, frame);
    cv::setMouseCallback(selectWinName, mouse_callback,&data);
    cv::waitKey();
    
    if(data.selectedNumber < 4){
        std::cout << "click more points" << std::endl;
        return -1;
    }
    cv::Mat dst = cv::Mat::zeros(67*7, 67*10, CV_8UC3);
    double para = 1;
    double para2 = 30;
    const std::vector<cv::Point2f> dst_pt={
        cv::Point2f(dst.cols/2 - 3*para2/2,dst.rows/2 - 4*para2/2),
        cv::Point2f(dst.cols/2 - 3*para2/2,dst.rows/2 + 4*para2/2),
        cv::Point2f(dst.cols/2 + 3*para2/2,dst.rows/2 - 4*para2/2),
        cv::Point2f(dst.cols/2 + 3*para2/2,dst.rows/2 + 4*para2/2)
    };
    
    // homography 行列を計算
    const cv::Mat homography_matrix = cv::getPerspectiveTransform(data.selectedPoints,dst_pt);
    while(true){
        cap.read(frame_);
        cv::remap(frame_,frame,map.at(0),map.at(1),cv::INTER_AREA);
        //cv::undistort(frame_, frame, K, distCoeffs);
        for(int i = 0; i < 4; i++){
            cv::circle(frame,data.selectedPoints.at(i),3,cv::Scalar(255,255,255));
        }
        // 透視変換
        cv::warpPerspective( frame, dst, homography_matrix, dst.size());
        cv::imshow(selectWinName, frame);
        cv::imshow("result", dst);
        if(cv::waitKey(10) > 0){
            break;
        }
    }
    
    cv::destroyAllWindows();

    return 0;
}