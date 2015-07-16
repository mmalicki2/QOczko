#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cv.h>

#include <QtCore/QObject>

namespace mcv
{

class Histogram : public QObject
{
		Q_OBJECT

	public slots:
		void dataRecived( const cv::Mat& image, const cv::Mat& mask );
  
	signals:
		void histProduced( const cv::MatND& hist );

	public:
		
		Histogram( QObject* parent = 0 );
		virtual ~Histogram();
		
	private:
		int*    m_channels;
		int*    m_histSize;
		float** m_ranges;
		

};

}; // namespace mcv

#endif // HISTOGRAM_H
