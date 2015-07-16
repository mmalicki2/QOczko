#include "histogram.h"

#include <cv.h>

using namespace mcv;

Histogram::Histogram(QObject* parent) : QObject(parent)
{
	m_channels = new int[3];
	m_channels[0] = 0;
	m_channels[1] = 1;
	m_channels[2] = 2;
	
	m_histSize = new int[3];
	m_histSize[0] = 16;
	m_histSize[1] = 16;
	m_histSize[2] = 16;
	
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

Histogram::~Histogram()
{
	delete[] m_channels;
	delete[] m_histSize;
	delete[] m_ranges[0];
	delete[] m_ranges[1];
	delete[] m_ranges[2];
	delete[] m_ranges;
}

/** 
 * @brief Liczy histgram
 *
 * @param image obarazek w formacie BGR
 * @param mask  maska dla obrazka (współrzędne czarnych pubktów brane pod uwagę przy liczeni histogramu) 
 */
void Histogram::dataRecived( const cv::Mat& image, const cv::Mat& mask )
{
	cv::MatND ohist;
	const int fromTo[] = {0,0}; 
	cv::Mat mask8bit(mask.size(), CV_8UC1);
	cv::mixChannels(&mask, 1, &mask8bit, 1, fromTo,  1);
	
	cv::calcHist(&image, 1, m_channels, mask8bit, ohist, 3, m_histSize, const_cast<const float**>(m_ranges), true, false );
	emit histProduced(ohist);
}

#include "histogram.moc"



