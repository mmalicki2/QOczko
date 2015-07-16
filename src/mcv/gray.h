#ifndef GRAY_H
#define GRAY_H

#include <cv.h>

#include <QtCore/QObject>


namespace mcv
{

class Gray : public QObject
{
		Q_OBJECT
		
	public slots:
		void imageRecived( const cv::Mat& image );
	  
	signals:
		void imageProduced( const cv::Mat& image );
		
	public:
		
		Gray( QObject* parent = 0 );
		virtual ~Gray();
		
};

};

#endif // GRAY_H
