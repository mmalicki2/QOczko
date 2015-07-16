#include "opencvconnector.h"
#include <cv.h>

//TODO: trzeba zadbac o zgodność formatów
/*
 if( frame->origin == IPL_ORIGIN_TL )
 20.cvCopy( frame, m_opencvimg, 0 );
 21.else
 22.cvFlip( frame, m_opencvimg, 0 );
 23.
 24.//images from cvQueryFrame come in BGR form and not what Qt expects - RGB
 25.
 26.//and since the buffers are shared - format should be consistent
 27.cvCvtColor(m_opencvimg,m_opencvimg,CV_BGR2RGB);
*/

void OpenCVConnector::OpenCVToQImage( QImage& _image, const IplImage& opencv_image )
{
	_image = QImage(( uchar* )opencv_image.imageData, opencv_image.width, opencv_image.height , QImage::Format_RGB888 );
}


void OpenCVConnector::OpenCVToQImage( QImage& _image, const cv::Mat& opencv_image )
{
	int f;
	switch ( opencv_image.channels() ) {
		case 3:
			f = CV_BGR2RGB;
			break;
		case 1:
			f = CV_GRAY2RGB;
			break;
		default:
			qFatal( "Nieobsługiwany format cv::Mat" );
	}
	_image = QImage( opencv_image.cols, opencv_image.rows , QImage::Format_RGB888 );
	cv::Mat m = cv::Mat( opencv_image.rows, opencv_image.cols, CV_8UC3, ( char* )_image.bits() );
	cv::cvtColor( opencv_image, m, f );
	//opencv_image.convertTo(m, CV_8UC3);
}



void OpenCVConnector::QImageToOpenCV( IplImage& _opencv_image, const QImage& image )
{
	qFatal("niezaimplementowana");
}

void OpenCVConnector::QImageToOpenCV( cv::Mat& _opencv_image, const QImage& image )
{
	if (image.format() == QImage::Format_RGB888) {
		cv::Mat m = cv::Mat( image.height(), image.width(), CV_8UC3, ( char* )image.bits() );
		_opencv_image = cv::Mat(image.height(), image.width(), CV_8UC3);
		cv::cvtColor(m, _opencv_image, CV_RGB2BGR);
		return;
	}
	
	if (image.format() == QImage::Format_Indexed8) {
		cv::Mat m = cv::Mat( image.height(), image.width(), CV_8UC1, ( char* )image.bits() );
		//_opencv_image = cv::Mat(image.height(), image.width(), CV_8UC1);
		m.copyTo(_opencv_image);
		return;
	}

	qWarning("Nieobsługiwany format danych (%d)", image.format());
	return;
}

IplImage* OpenCVConnector::CreateLinkedOpenCV( const QImage& image )
{
	IplImage* img = cvCreateImageHeader( cvSize( image.width(), image.height() ), 8, 3 );
	img->imageData = ( char* )image.bits();
	return img;
}


void OpenCVConnector::CreateLinkedQImage( QImage& _image, IplImage& opencv_image )
{
	_image = QImage( opencv_image.width, opencv_image.height, QImage::Format_RGB888 );
	opencv_image.imageData = ( char* )_image.bits();
	assert( opencv_image.imageData );
}

void OpenCVConnector::createPipedImages( QImage& _image, IplImage*& _opencv_image, const QSize& size )
{
	_opencv_image = cvCreateImageHeader( cvSize( size.width(), size.height() ), 8, 3 );
	_image = QImage( size, QImage::Format_RGB888 );
	_opencv_image->imageData = ( char* )_image.bits();
	assert( _opencv_image->imageData );
}


void OpenCVConnector::createPipedImages( QImage& _image, cv::Mat& _opencv_image, const QSize& size )
{
	_image = QImage( size, QImage::Format_RGB888 );
	_opencv_image = cv::Mat( size.width(), size.width(), CV_8UC3 , _image.bits() );
	assert( _opencv_image.data );
}

using namespace mcv;
void OpenCVConverter::imageRecived( const cv::Mat& image )
{
	QImage oimage;
	OpenCVConnector::OpenCVToQImage( oimage, image );
	emit imageProduced( oimage );
}

void OpenCVConverter::imageRecived( const QImage& image1, const QImage& image2 )
{
	cv::Mat m1, m2;
	OpenCVConnector::QImageToOpenCV(m1, image1);
	OpenCVConnector::QImageToOpenCV(m2, image2);
	emit imageProduced(m1,m2);
}


void OpenCVConverter::imageRecived( const int id, const QImage& image )
{
	cv::Mat m;
	OpenCVConnector::QImageToOpenCV( m, image );
	emit imageProduced( id, m );
}

#include "opencvconnector.moc"






