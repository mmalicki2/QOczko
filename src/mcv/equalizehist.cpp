#include "equalizehist.h"
#include <cv.h>

using namespace mcv;

EqualizeHist::EqualizeHist(QObject* parent) : QObject(parent)
{
}

EqualizeHist::~EqualizeHist()
{
}

void EqualizeHist::imageRecived(const cv::Mat& image)
{
	cv::Mat oimage;
	std::vector<cv::Mat> oimages(image.channels());
	
	cv::split(image, oimages);
	for (int i = 0; i < oimages.size(); ++i) {
		cv::equalizeHist(oimages[i], oimages[i]);
	}
	cv::merge(oimages, oimage);
	emit imageProduced(oimage);
}

#include "equalizehist.moc"