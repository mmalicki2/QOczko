#ifndef POINTTRACKER_H
#define POINTTRACKER_H

#include <QtCore/QObject>
#include <QtCore/QPoint>


#include <cv.h>

namespace mcv
{

class PointTracker : public QObject
{
		Q_OBJECT
	signals:
		void imageProduced( const cv::Mat& image );

	public slots:
		void pointRecived( const QPoint& point );
		void reset();
		void produce();

	public:
		PointTracker( int width, int height, bool autoProduce = true, QObject* parent = 0 );
		virtual ~PointTracker();

	private:
		bool m_autoProduce;
		cv::Mat m_image;	
		QPoint m_lastPoint;
};

}; //namespace mcv

#endif // POINTTRACKER_H
