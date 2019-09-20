#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

#define CVUI_IMPLEMENTATION
#include "cvui2.7.0/cvui.h"
#include "CartoonizerDT.h"
#include "CartoonizerBilateral.h"


int main()
{
    using std::cout;

//    --- INITIALIZE VIDEO CAPTURE
    cv::VideoCapture cap;
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    cap.open(deviceID, apiID);
    if (!cap.isOpened())
    {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    cv::Mat frame;

//    --- CREATE UI
    cv::Mat ctrl_panel = cv::Mat(200, 500, CV_8UC3);
    cv::namedWindow("control panel");
    cvui::init("control panel");


    bool c1_checked{false};
    bool c2_checked{false};
    CartoonizerDT *cartDT{nullptr};
    CartoonizerBilateral *cartBilateral{nullptr};


    for(;;)
    {
//        --- READ FRAME FROM CAMERA
        cap.read(frame);
        if(frame.empty())
        {
            std::cerr << "ERROR blank frame grabbed \n";
            break;
        }

//        --- UPDATE UI
        ctrl_panel = cv::Scalar(49, 52, 49);

        cvui::context("control panel");
        cvui::beginRow(ctrl_panel, 10, 10, -1, -1, 20);
        cvui::checkbox("Bilateral filter", &c1_checked, 0xFFFFFF);
        cvui::checkbox("Domain Transform filter", &c2_checked, 0xFFFFFF);
        cvui::endRow();

        cvui::update();
        cvui::imshow("control panel", ctrl_panel);



//        --- DOMAIN TRANSFORM FILTER
//        Create DT filter if does not exist and DT is ON.
        if(cartDT == nullptr && c2_checked)
        {
            cartDT = new CartoonizerDT(frame);
            cout << "tworzenie DT \n";
        }
//        Update DT.
        if(cartDT != nullptr && c2_checked)
        {
            cartDT->update(frame);
        }
//        Delete DT if exists and DT is turned OFF.
        else if(cartDT != nullptr)
        {
            delete cartDT;
            cartDT = nullptr;
            cout << "niszczenie DT \n";
        }


//        --- BILATERAL FILTER
//        Create Bilateral filter if does not exist and Bilateral is ON.
        if(cartBilateral == nullptr && c1_checked)
        {
            cartBilateral = new CartoonizerBilateral(frame);
            cout << "tworzenie Bilateral \n";
        }
//        Update Bilateral.
        if(cartBilateral != nullptr && c1_checked)
        {
            cartBilateral->update(frame);
        }
//        Delete Bilateral if exists and Bilateral is turned OFF.
        else if(cartBilateral != nullptr)
        {
            delete cartBilateral;
            cartBilateral = nullptr;
            cout << "niszczenie Bilateral \n";
        }


//        --- Exit if ESC
        if (cv::waitKey(10) == 27) {
            break;
        }
    }


    return 0;
}