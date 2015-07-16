#include "gaussianblur.h"

#include <cv.h>

using namespace mcv;

GaussianBlur::GaussianBlur(QObject* parent)  : QObject(parent),  m_size( 17, 17 ), m_sigmaX( 0.5 ), m_sigmaY( 0.5 ), m_borderType( cv::BORDER_DEFAULT )
{
}

GaussianBlur::~GaussianBlur() {
}

void GaussianBlur::imageRecived( const cv::Mat& image )
{
	cv::Mat oimage;
	cv::GaussianBlur( image, oimage, cv::Size( m_size.width(), m_size.height() ), m_sigmaX, m_sigmaY, m_borderType );
	emit imageProduced( oimage );
}

#include "gaussianblur.moc"
