#include "VideoController.h"
 
VideoController::VideoController(const std::string &filenameInput,const std::string &filenameOutput)
{
	m_filenameInput=filenameInput;
	m_filenameOutput=filenameOutput;
	m_capture= cv::VideoCapture(m_filenameInput);
	// cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE );
	if (!m_capture.isOpened()) {
    	std::cout<< "ERROR! Unable to open the video\n"<<std::endl;
	}
	cv::Mat frame;
	for(;;) {
		if (m_capture.read(frame))
		{
			m_disorderedImages.push_back(frame.clone());
		}
		else
		{
			break;
		}
		if( cv::waitKey(33) >= 0 ) ;
	}
	// std::cout<<m_disorderedImages.size()<<std::endl;
	// cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE );
	// for (int i=0;i<m_disorderedImages.size();i++)
	// {
	// 	cv::imshow( "Example3",m_disorderedImages[i]);
	// }
	// m_capture.release();
}
VideoController::~VideoController()
{
	m_capture.release();
}

void VideoController::getDisorderedImages(std::vector<cv::Mat> &disorderedImages)
{
	// description:: get from the videoController instance the set of images red by the video
	disorderedImages.resize(m_disorderedImages.size());
	for (int i=0;i<m_disorderedImages.size();i++)
	{
		disorderedImages[i]=m_disorderedImages[i];
	}
}

void VideoController::setOrderedImages(const std::vector<cv::Mat> &orderedImages)
{
	m_orderedImages.resize(orderedImages.size());
	for (int i=0;i<m_orderedImages.size();i++)
	{
		m_orderedImages[i]=orderedImages[i];
	}
}
void VideoController::writeVideo()
{
	// std::string filenameOutput="corrupted_video_copie.mp4";
	double fps = m_capture.get( cv::CAP_PROP_FPS );
	int a= m_disorderedImages.size();
	// std::cout<<m_capture.get(cv::CAP_PROP_FOURCC)<<std::endl;
	cv::Size size((int)m_capture.get( cv::CAP_PROP_FRAME_WIDTH ),(int)m_capture.get( cv::CAP_PROP_FRAME_HEIGHT ));
	// std::cout<<m_disorderedImages.size()<<std::endl;

	unsigned f = (unsigned)m_capture.get( cv::CAP_PROP_FOURCC );
	char fourcc[] = {
		(char) f, // First character is lowest bits
		(char)(f >> 8), // Next character is bits 8-15
		(char)(f >> 16), // Next character is bits 16-23
		(char)(f >> 24), // Last character is bits 24-31
		'\0' // and don't forget to terminate
		};

	cv::VideoWriter writer;writer.open( m_filenameOutput,CV_FOURCC(fourcc[0],fourcc[1],fourcc[2],fourcc[3]), fps, size );
	for (int i=0;i<m_disorderedImages.size();i++)
		{
			writer<<m_disorderedImages[i];
		}
	writer.release();
}

// std::vector<cv::Mat> VideoController::castDequeToVector(const std::deque<cv::Mat> theDeque )
// {
// 	std::vector<cv::Mat> theVector(theDeque.size());
// 	for (int i=0;i<theDeque.size();i++)
// 	{
// 	   // theDeque[i].copyTo(theVector[i])	;
// 	   theVector[i]=theDeque[i];
// 	}
// 	return theVector;
// }