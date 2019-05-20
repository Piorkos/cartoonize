#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

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
    cin >> mode;

    if(mode == '1')
    {
        Mat frame;
//        --- INITIALIZE VIDEOCAPTURE
        cv::VideoCapture cap;
        int deviceID = 0;             // 0 = open default camera
        int apiID = cv::CAP_ANY;      // 0 = autodetect default API
        cap.open(deviceID + apiID);
        if (!cap.isOpened()) {
            cerr << "ERROR! Unable to open camera\n";
            return -1;
        }
//        cap.set(cv::CAP_PROP_FRAME_WIDTH, 400);
//        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 300);

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
//            show live and wait for a key with timeout long enough to show images
            imshow("Live", frame);
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