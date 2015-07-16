#include "pointtracker.h"

using namespace mcv;

PointTracker::PointTracker(int width, int height, bool autoProduce, QObject* parent) : QObject(parent), m_autoProduce(autoProduce)
{
	m_image = cv::Mat::zeros(height, width, CV_8UC3);
}

PointTracker::~PointTracker()
{
}

void PointTracker::pointRecived( const QPoint& point ) 
{
	cv::circle(m_image, cv::Point(point.x(), point.y()), 4, cv::Scalar::all(255), -1);
	if (!m_lastPoint.isNull()) {
	//	cv::circle(m_image, cv::Point(point.x(), point.y()), 4, cv::Scalar::all(255), -1);
	//} else {
		cv::line(m_image, cv::Point(m_lastPoint.x(), m_lastPoint.y()), cv::Point(point.x(), point.y()), cv::Scalar::all(255), 8);
	}
	if (m_autoProduce) {
		produce();
	}
	m_lastPoint = point;
}

void PointTracker::reset()
{
	m_image = cv::Mat::zeros(m_image.rows, m_image.cols, CV_8UC3);
	m_lastPoint = QPoint();
}

void PointTracker::produce()
{
	emit imageProduced(m_image);
}


#include "pointtracker.moc"

