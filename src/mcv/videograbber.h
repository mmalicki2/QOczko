#ifndef VIDEOGRABBER_H
#define VIDEOGRABBER_H

#include <cv.h>
#include <highgui.h>

#include <QtCore/QTimer>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

namespace mcv {
  
class VideoGrabber : public QObject
{
	Q_OBJECT
	
	public slots:

		void start();
		void stop();
		void open();
		void close();
		
	private slots:
		void step();

		
	signals:
		void opened();
		void closed();
		void stopped();
		void started();
		void error();
		void imageProduced( const cv::Mat& image );
		
	public:
		
		VideoGrabber( QObject* parent = 0 );
		virtual ~VideoGrabber();
		
				
	private:
	  cv::VideoCapture m_capture;
	  QMutex           m_mutex;
	  bool             m_stopped;
	  bool             m_stop;

};

}

#endif // VIDEOGRABBER_H
