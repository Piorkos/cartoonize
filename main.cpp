#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

int main()
{
    using cv::Mat;

    using std::cout;
    using std::cin;
    using std::cerr;
    using std::string;

    cout << "Select option:" << "\n";
    cout << "1 - to capture image from camer" << "\n";
    cout << "2 - to read image from file" << "\n";
    char mode{'1'};
//    cin >> mode;
    mode = '1';

    if(mode == '1')
    {
        Mat frame;
        int sigma_s{50};
        int sigma_r{4};
        int sigma_s_max{200};
        int sigma_r_max{10};



//        --- INITIALIZE VIDEOCAPTURE
        cv::VideoCapture cap;
        int deviceID = 0;             // 0 = open default camera
        int apiID = cv::CAP_ANY;      // 0 = autodetect default API
        cap.open(deviceID + apiID);
        if (!cap.isOpened()) {
            cerr << "ERROR! Unable to open camera\n";
            return -1;
        }
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

//        ---CREATE TRACKBARS
        cv::namedWindow("cartoonize", cv::WINDOW_AUTOSIZE);
        cv::createTrackbar("Trackbar sigma_s", "cartoonize", &sigma_s, sigma_s_max);
        cv::createTrackbar("Trackbar sigma_r", "cartoonize", &sigma_r, sigma_r_max);

//        --- GRAB AND WRITE LOOP
        cout << "Start grabbing" << "\n"
             << "Press any key to terminate" << "\n";
        for (;;)
        {
            cap.read(frame);
            if (frame.empty()) {
                cerr << "ERROR! blank frame grabbed\n";
                break;
            }

            imshow("camera", frame);

//            --- CARTOONIZE USING DOMAIN TRANSFORM FILTER
//            Mat cartoonize;
//            cv::stylization(frame, cartoonize, static_cast<float>(sigma_s), static_cast<float>(sigma_r)/sigma_r_max);
//            imshow("cartoonize", cartoonize);

//            ---CARTOONIZE USING BILATERAL FILTER
            Mat tmp = frame.clone();
            Mat img_sampled_down = tmp.clone();
            Mat img_bilat = tmp.clone();
            Mat img_sampled_up = tmp.clone();
            int bilateral_count = 7;

            cv::pyrDown(tmp, img_sampled_down, cv::Size(tmp.cols/2, tmp.rows/2));

            for( int i = 0; i < bilateral_count; ++i)
            {
                cv::bilateralFilter(img_sampled_down, img_bilat, 9, 9, 7);
                img_sampled_down = img_bilat.clone();
            }

            cv::pyrUp(img_bilat, img_sampled_up, cv::Size(tmp.cols, tmp.rows));

            Mat img_gray;
            Mat img_median;
            cv::cvtColor(img_sampled_up, img_gray, cv::COLOR_RGB2GRAY);
            cv::medianBlur(img_gray, img_median, 17);

            Mat img_edge;
            cv::adaptiveThreshold(img_median, img_edge, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 9, 2);

            Mat img_edge_color;
            Mat img_cartoon;
            cv::cvtColor(img_edge, img_edge_color, cv::COLOR_GRAY2BGR);
            cv::bitwise_and(img_edge_color, img_sampled_up, img_cartoon);

            imshow("cartoonize", img_cartoon);

            if (cv::waitKey(5) >= 0)
                break;
        }
    }
    else if(mode == '2')
    {
        cout << "Provide path to image file." << "\n";
        cin.ignore(32767, '\n');
        string path{" "};
        std::getline(cin, path);

    }

    return 0;
}