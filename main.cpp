#include "VideoController.h"
// #include "VideoProcessor.h"
int main (int argc, char* argv[])
{
	VideoController videoController=VideoController("corrupted_video.mp4","corrupted_video_ordered.mp4");
	videoController.writeVideo();
	// std::vector<cv::Mat> disorderedImages=videoController.getDisorderedImages();
	// VideoProcessor videoProcessor=VideoProcessor(*disorderedImages);
	// videoProcessor.orderImages_exhaustiveResearch_WithPriorComputedCost();
	// std::deque<cv::Mat> orderedImages=videoProcessor.getOrderedImages();
	// videoController.writeVideo(std::vector<cv::Mat>(orderedImages.begin(),orderedImages.end()));
	//read options
	// std::string filename="corrupted_video_copie.avi";
	// cv::VideoCapture cap(filename);
	// std::vector<cv::Mat> disorderedImages;
	// ideoProcessor(const std::vector<cv::Mat> &disorderedImages)
// 	cv::VideoCapture cap;
// cap.open( string(argv[1]) );
// cv::Mat frame;
// for(;;) {
// cap >> frame;
// if( frame.empty() ) break; // Ran out of film
// cv::imshow( "Example3", frame );
// if( cv::waitKey(33) >= 0 ) break;
// }
	return 0;
}
