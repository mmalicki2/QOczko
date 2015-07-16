#ifndef EQUALIZEHIST_H
#define EQUALIZEHIST_H

#include <cv.h>

#include <QtCore/QObject>

namespace mcv {
class EqualizeHist : public QObject
{
	Q_OBJECT
	public slots:
		void imageRecived(const cv::Mat& image);
	signals:
		void imageProduced(const cv::Mat& image);
		
	public:
		
		EqualizeHist( QObject* parent = 0 );
		virtual ~EqualizeHist();
};
};

#endif // EQUALIZEHIST_H
