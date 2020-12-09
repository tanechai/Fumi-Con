#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>


class selectedData{
public:
    std::vector<cv::Point2d> selectedPoints;
	int selectedNumber;
    selectedData():selectedPoints(std::vector<cv::Point2d>(4)),selectedNumber(0){};
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

    cv::Mat frame;
    cap.read(frame);
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
    while(true){
        cap.read(frame);
        for(int i = 0; i < 4; i++){
            cv::circle(frame,data.selectedPoints.at(i),3,cv::Scalar(255,255,255));
        }
        
        cv::imshow(selectWinName, frame);
        if(cv::waitKey(10) > 0){
            break;
        }
    }
    cv::destroyAllWindows();

    return 0;
}