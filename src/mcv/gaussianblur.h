#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <cv.h>

#include <QtCore/QObject>
#include <QtCore/QSize>

namespace mcv
{

class GaussianBlur : public QObject
{
		Q_OBJECT

	public slots:
		void imageRecived( const cv::Mat& image );

	signals:
		void imageProduced( const cv::Mat& image );


	public:
		
		GaussianBlur( QObject* parent = 0 );
		virtual ~GaussianBlur();


	private:
		QSize  m_size;
		double m_sigmaX;
		double m_sigmaY;
		int    m_borderType;
};

};


#endif // GAUSSIANBLUR_H
