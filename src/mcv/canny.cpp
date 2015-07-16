#include "canny.h"

#include <cv.h>

using namespace mcv;

Canny::Canny(QObject* parent ) : QObject(parent), m_threshold1( 10 ), m_threshold2( 157 ), m_apertureSize( 3 ), m_L2gradient( false )
{
};

Canny::~Canny()
{
}

void Canny::imageRecived( const cv::Mat& image )
{
	cv::Mat oimage;
	cv::Canny( image, oimage, m_threshold1, m_threshold2, m_apertureSize, m_L2gradient );
	emit imageProduced( oimage );
}


#include "canny.moc"



