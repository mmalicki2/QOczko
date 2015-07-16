#include "qoczkoalgorithm.h"

#include <iostream>
#include <QtCore/QThread>
#include <QtCore/QMetaType>
#include <QDebug>

QOczkoAlgorithm::QOczkoAlgorithm( QObject* parent ): QObject( parent )
{
	if (QMetaType::type("cv::Mat") == 0) {
		qRegisterMetaType<cv::Mat>("cv::Mat");
	}
	if (QMetaType::type("QVector<QPolygon>") == 0) {
		qRegisterMetaType< QVector<QPolygon> >("QVector<QPolygon>");
	}
	
	m_thread = new QThread();
	m_thread_grabber = new QThread();
	
	m_grabber = new mcv::VideoGrabber();
	m_grabber_converter = new mcv::OpenCVConverter();
	
	m_histogram = new mcv::Histogram();
	m_histogram_converter = new mcv::OpenCVConverter();
	
	m_backproject = new mcv::BackProject();
	m_backproject_converter = new mcv::OpenCVConverter();
	
	m_camshift = new mcv::CamShift();
	
	m_equalizehist = new mcv::EqualizeHist();
	m_equalizehist_converter = new mcv::OpenCVConverter();

	m_pointTracker = new mcv::PointTracker(640, 480);
	m_pointTracker_converter = new mcv::OpenCVConverter();
	
	m_matchshapes = new mcv::MatchShapes();
	m_matchshapes_converter = new mcv::OpenCVConverter();
		
	m_thread->start();
	m_thread_grabber->start();
	
	m_grabber->moveToThread(m_thread_grabber);
	m_grabber_converter->moveToThread(m_thread_grabber);
	
	m_histogram->moveToThread(m_thread);
	m_histogram_converter->moveToThread(m_thread);
	
	m_backproject->moveToThread(m_thread);
	m_backproject_converter->moveToThread(m_thread);
	
	m_camshift->moveToThread(m_thread);
	
	m_equalizehist->moveToThread(m_thread);
	m_equalizehist_converter->moveToThread(m_thread);
	
	m_pointTracker->moveToThread(m_thread);
	m_pointTracker_converter->moveToThread(m_thread);

	m_matchshapes->moveToThread(m_thread);
	m_matchshapes_converter->moveToThread(m_thread);
	
	QObject::connect(m_grabber, SIGNAL(imageProduced(cv::Mat)), m_grabber_converter, SLOT(imageRecived(cv::Mat)));
	QObject::connect(m_grabber_converter, SIGNAL(imageProduced(QImage)), this, SIGNAL(frameProduced_raw(QImage)), Qt::QueuedConnection );
	
	QObject::connect(m_histogram_converter, SIGNAL( imageProduced(cv::Mat,cv::Mat)), m_histogram, SLOT(dataRecived(cv::Mat,cv::Mat)));
	QObject::connect(m_histogram, SIGNAL(histProduced(cv::MatND)), m_backproject, SLOT(setHistogram(cv::MatND)) );
	QObject::connect(m_backproject, SIGNAL(imageProduced(cv::Mat)), m_backproject_converter, SLOT(imageRecived(cv::Mat)));
	QObject::connect(m_backproject_converter, SIGNAL(imageProduced(QImage)), this, SIGNAL(frameProduced_backproject(QImage)), Qt::QueuedConnection);
	QObject::connect(m_grabber, SIGNAL(imageProduced(cv::Mat)), m_backproject, SLOT(imageRecived(cv::Mat)));
	//TODO: mozliwosc dynamicznej zmiany polaczen
	//QObject::connect(m_equalizehist, SIGNAL(imageProduced(cv::Mat)), m_backproject, SLOT(imageRecived(cv::Mat)));
	
	QObject::connect(m_backproject, SIGNAL(imageProduced(cv::Mat)), m_camshift, SLOT(imageRecived(cv::Mat)));
	QObject::connect(m_camshift, SIGNAL(detected(QVector<QPolygon>)), this, SIGNAL(detectedPolygons(QVector<QPolygon>)), Qt::QueuedConnection);
	QObject::connect(m_camshift, SIGNAL(detectedHotPoint(QPoint)), this, SIGNAL(detectedHotPoint(QPoint)), Qt::QueuedConnection);

	QObject::connect(m_grabber, SIGNAL(imageProduced(cv::Mat)), m_equalizehist, SLOT(imageRecived(cv::Mat)));
	QObject::connect(m_equalizehist, SIGNAL(imageProduced(cv::Mat)), m_equalizehist_converter, SLOT(imageRecived(cv::Mat)));
	QObject::connect(m_equalizehist_converter, SIGNAL(imageProduced(QImage)), this, SIGNAL(frameProduced_equalized(QImage)), Qt::QueuedConnection);

	QObject::connect(m_camshift, SIGNAL(detectedHotPoint(QPoint)), m_pointTracker, SLOT(pointRecived(QPoint)));
	QObject::connect(m_pointTracker, SIGNAL(imageProduced(cv::Mat)), m_pointTracker_converter, SLOT(imageRecived(cv::Mat)));
	QObject::connect(m_pointTracker_converter, SIGNAL(imageProduced(QImage)), this, SIGNAL(frameProduced_track(QImage)), Qt::QueuedConnection);

	QObject::connect(m_matchshapes_converter, SIGNAL(imageProduced(int, cv::Mat)), m_matchshapes, SLOT(addShape(int, cv::Mat)));
	QObject::connect(m_matchshapes, SIGNAL(matched(int, double)), this, SIGNAL(detectedShape(int, double)), Qt::QueuedConnection);
}


QOczkoAlgorithm::~QOczkoAlgorithm()
{
	delete m_matchshapes_converter;
	delete m_matchshapes;
	delete m_pointTracker_converter;
	delete m_pointTracker;
	delete m_equalizehist_converter;
	delete m_equalizehist;
	delete m_camshift;
	delete m_backproject_converter;
	delete m_backproject;
	delete m_histogram_converter;
	delete m_histogram;
	delete m_grabber_converter;
	delete m_grabber;
	delete m_thread_grabber;
	delete m_thread;
	
}


void QOczkoAlgorithm::open()
{
	m_grabber->open();
	//QMetaObject::invokeMethod(m_grabber, "open", Qt::QueuedConnection);
}

void QOczkoAlgorithm::close()
{
	m_grabber->close();
	//QMetaObject::invokeMethod(m_grabber, "close", Qt::QueuedConnection);
}

void QOczkoAlgorithm::stop()
{
	//m_grabber->stop();
	QMetaObject::invokeMethod(m_grabber, "stop", Qt::QueuedConnection);
}

void QOczkoAlgorithm::start()
{	
	//m_grabber->start();
	QMetaObject::invokeMethod(m_grabber, "start", Qt::QueuedConnection);
}

void QOczkoAlgorithm::setHistogram(const QImage& image, const QImage& mask)
{
	QMetaObject::invokeMethod(m_histogram_converter, "imageRecived", Qt::QueuedConnection, Q_ARG(QImage, image), Q_ARG(QImage, mask));
}

void QOczkoAlgorithm::resetTrack()
{
	QMetaObject::invokeMethod(m_pointTracker, "reset", Qt::QueuedConnection);
};

void QOczkoAlgorithm::addShape(const int id, const QImage& image)
{
	QMetaObject::invokeMethod(m_matchshapes_converter, "imageRecived", Qt::QueuedConnection, Q_ARG(int, id), Q_ARG(QImage, image)); 
}

void QOczkoAlgorithm::matchShape()
{
	qDebug() << "QOczkoAlgorithm::matchShape()\n";
	QObject::connect(m_pointTracker, SIGNAL(imageProduced(cv::Mat)), m_matchshapes, SLOT(match(cv::Mat)));
	QMetaObject::invokeMethod(m_pointTracker, "produce", Qt::QueuedConnection);
	//XXX: usuwam polaczenie zanim sygnal zostanie dostarczony - sygnal nie zostanie dostarczony
	//QObject::disconnect(m_pointTracker, SIGNAL(imageProduced(cv::Mat)), m_matchshapes, SLOT(match(cv::Mat)));
}

#include "qoczkoalgorithm.moc"
