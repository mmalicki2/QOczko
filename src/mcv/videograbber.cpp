#include "videograbber.h"
#include <QtCore/QThread>
#include <iostream>
using namespace mcv;

VideoGrabber::VideoGrabber( QObject* parent ) : QObject( parent )
		, m_stop( false )
		, m_stopped( true )
{

}

VideoGrabber::~VideoGrabber()
{
}

void VideoGrabber::open()
{
	QMutexLocker locker( &m_mutex );
	if ( ! m_stopped ) {
		return;
	}

	if ( !m_capture.isOpened() ) {
		try {
			m_capture.open( 0 );
			emit opened();
		} catch ( ... ) {
			emit error();
		}
	}
}

void VideoGrabber::close()
{
	QMutexLocker locker( &m_mutex );
	m_stop = true;
	m_stopped = true;

	if ( m_capture.isOpened() ) {
		try {
			m_capture.release();
			emit closed();
		} catch ( ... ) {
			emit error();
		}
	}
}

void VideoGrabber::start()
{
	QMutexLocker locker( &m_mutex );
	emit started();
	m_stop = false;
	m_stopped = false;
	QMetaObject::invokeMethod(this, "step", Qt::QueuedConnection);
}

void VideoGrabber::stop()
{
	QMutexLocker locker( &m_mutex );
	if ( ! m_stopped ) {
		m_stop = true;
	}
}

void VideoGrabber::step()
{
	QMutexLocker locker( &m_mutex );
	if (m_stop) {
		m_stopped = true;
		return;
	}
	
	try {
		cv::Mat frame;
		m_capture >> frame;
		emit imageProduced( frame );
		QMetaObject::invokeMethod(this, "step", Qt::QueuedConnection);
	} catch ( ... ) {
		emit error();
		m_stopped = true;
		std::cerr << "error \n";
	}
}

#include "videograbber.moc"

