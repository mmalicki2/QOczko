#include "backproject.h"

#include <cv.h>

using namespace mcv;

BackProject::BackProject(QObject* parent ) : QObject(parent)
{	
	m_channels = new int[3];
	m_channels[0] = 0;
	m_channels[1] = 1;
	m_channels[2] = 2;
	
	m_ranges = new float*[3];
	m_ranges[0] = new float[2];
	m_ranges[0][0] = 0;
	m_ranges[0][1] = 0x100;
	m_ranges[1] = new float[2];
	m_ranges[1][0] = 0;
	m_ranges[1][1] = 0x100;
	m_ranges[2] = new float[2];
	m_ranges[2][0] = 0;
	m_ranges[2][1] = 0x100;
};

BackProject::~BackProject()
{
	delete[] m_channels;
	delete[] m_ranges[0];
	delete[] m_ranges[1];
	delete[] m_ranges[2];
	delete[] m_ranges;
}

void BackProject::imageRecived( const cv::Mat& image )
{
	cv::Mat oimage;
	if (m_hist.dims > 0) {
		cv::calcBackProject(&image, 1, m_channels, m_hist, oimage, const_cast<const float**>(m_ranges), 10, true);
	} else {
	  	const int fromTo[] = {0,0};
		oimage = cv::Mat(image.size(), CV_8UC1);
		cv::mixChannels(&image, 1, &oimage, 1, fromTo,  1);
	}
	emit imageProduced( oimage );
}

void BackProject::setHistogram( const cv::MatND& mask )
{
	m_hist = mask;
}


#include "backproject.moc"



