#ifndef BACKPROJECT_H
#define BACKPROJECT_H

#include <cv.h>

#include <QtCore/QObject>
namespace mcv
{

class BackProject : public QObject
{
		Q_OBJECT
	public slots:
		void imageRecived( const cv::Mat& image );
		void setHistogram(const cv::MatND& mask);

	signals:
		void imageProduced( const cv::Mat& image );

	public:

		
		BackProject( QObject* parent = 0 );
		virtual ~BackProject();
		
	private:
		cv::MatND m_hist;
		int*      m_channels;
		float**   m_ranges;
};

}; // namespace mcv

#endif // BACKPROJECT_H
