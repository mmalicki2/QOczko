#include "camshift.h"

#include <cv.h>
#include <QtGui/QTransform>

using namespace mcv;

CamShift::CamShift(QObject* parent) : QObject(parent)
{
	m_criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER  , 10, 1);
}

CamShift::~CamShift()
{
}

void CamShift::imageRecived(const cv::Mat& image) 
{
	cv::Rect l_rect = (m_rect.height > 0) ? m_rect : cv::Rect(0, 0, image.cols, image.rows);
	
	cv::RotatedRect rrect =  cv::CamShift(image, l_rect, m_criteria);
	
	emit detectedHotPoint(QPoint(rrect.center.x, rrect.center.y));

	const QRect rect(-rrect.size.height/2, -rrect.size.width/2, rrect.size.height, rrect.size.width);
	QTransform transform;
	transform.rotate(rrect.angle, Qt::ZAxis);
	QVector<QPolygon> ret;
	QPolygon polygon = transform.map(QPolygon(rect, true));
	polygon.translate(rrect.center.x , rrect.center.y);
	ret.append(polygon);
	
		
	emit detected(ret);
}
  
#include "camshift.moc"
