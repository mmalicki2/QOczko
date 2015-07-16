#ifndef CAMSHIFT_H
#define CAMSHIFT_H

#include <cv.h>

#include <QtCore/QObject>
#include <QtGui/QPolygon>

namespace mcv { 

class CamShift : public QObject
{
	Q_OBJECT
	signals:
		void detected(const QVector<QPolygon >& polygons);
		void detectedHotPoint(const QPoint& point);
		
	public slots:
		void imageRecived( const cv::Mat& image);
	
	public:
		
		CamShift( QObject* parent = 0 );
		virtual ~CamShift();
		
	private:
		cv::TermCriteria  m_criteria;
		cv::Rect          m_rect;
};

};

#endif // CAMSHIFT_H
