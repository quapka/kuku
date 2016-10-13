#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
// #include "opencv2/contrib/contrib.hpp"

#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{   
    // the original video
    VideoCapture capture("../vids/test_kuku.avi");
    // its resolution
    int frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    // output video
    VideoWriter video(
        "../vids/bw_test_kuku.mp4",CV_FOURCC('H','2','6','4'),
        10, Size(frame_width, frame_height),false
    );
    Mat frame;
    // threshold for bw filter
    int thresh = atoi(argv[1]);

    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    namedWindow( "w", 1);
    for(;;)
    {
        capture >> frame;
        if(frame.empty())
            break;
        // convert to grayscale
        cvtColor(frame, frame, CV_BGR2GRAY);
        // convert to bw only
        Mat bw = frame > thresh;

        // imshow("w", bw);
        // waitKey(100);
        video.write(bw);
    }
}