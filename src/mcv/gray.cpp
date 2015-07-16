#include "gray.h"
#include <cv.h>


using namespace mcv;

Gray::Gray(QObject* parent) : QObject(parent) 
{
}

Gray::~Gray() 
{
}

void Gray::imageRecived( const cv::Mat& image )
{
	cv::Mat oimage;
	cv::cvtColor( image, oimage, CV_BGR2GRAY );
	emit imageProduced( oimage );
}

#include "gray.moc"

