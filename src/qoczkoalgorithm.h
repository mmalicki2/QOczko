#ifndef QOCZKOALGORITHM_H
#define QOCZKOALGORITHM_H

#include <QtCore/QObject>
#include <QtGui/QImage>

#include <mcv/videograbber.h>
#include <mcv/histogram.h>
#include <mcv/backproject.h>
#include <mcv/camshift.h>
#include <mcv/equalizehist.h>
#include <mcv/pointtracker.h>
#include <mcv/matchshapes.h>

#include <opencvconnector.h>

class QOczkoAlgorithm : public QObject
{
	Q_OBJECT
	public:
		enum ObjectDetectMethod {
			DetectHistogram
		};
		
		enum ObjectChooseMethod {
			DetectCenter,
			DetectGreatest
		};
		
	public:  
		QOczkoAlgorithm( QObject* parent = 0 );
		virtual ~QOczkoAlgorithm();

		void setObjectDetectMethod(const ObjectDetectMethod method);
		void setObjectChooseMethod(const ObjectChooseMethod method);
		
		void setDetectingEnabled(const bool enabled) { m_detecting = enabled; }
		void setProducingBackProjectEnabled(const bool enabled) { m_producing_backproject = enabled; }
		void setProducingMovmentsEnabled(const bool enabled) { m_producing_movments = enabled; }
	
	public slots:	
		void setHistogram(const QImage& image, const QImage& mask);
		void stop();
		void start();
		void open();
		void close();
		void resetTrack();
		void matchShape();
		void addShape(const int id, const QImage& image);

	signals:
		void started();
		void stopped();
		void closed();
		void opened();
		void frameProduced_raw(const QImage& image);
		void frameProduced_backproject(const QImage& image);
		void frameProduced_movements(const QImage& image);
		void frameProduced_equalized(const QImage& image);
		void frameProduced_track(const QImage& image);
		void detectedHotPoint(const QPoint& point);
		void detectedHotPolygon(const QPolygon& polygon);
		void detectedPolygons(const QVector<QPolygon>& polygons);
		void detectedShape(const int id, const double value);

	private:
		bool m_detecting;
		bool m_producing_backproject;
		bool m_producing_movments;
		
		QThread* m_thread;
		QThread* m_thread_grabber;
		
		mcv::VideoGrabber*    m_grabber;
		mcv::OpenCVConverter* m_grabber_converter;
		
		mcv::Histogram*       m_histogram;
		mcv::OpenCVConverter* m_histogram_converter;
		
		mcv::BackProject*     m_backproject;
		mcv::OpenCVConverter* m_backproject_converter;
		
		mcv::CamShift*        m_camshift;
		
		mcv::EqualizeHist*    m_equalizehist;
		mcv::OpenCVConverter* m_equalizehist_converter;

		mcv::PointTracker*    m_pointTracker;
		mcv::OpenCVConverter* m_pointTracker_converter;

		mcv::MatchShapes*     m_matchshapes;
		mcv::OpenCVConverter* m_matchshapes_converter;

};

#endif // QOCZKOALGORITHM_H
