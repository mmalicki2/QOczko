#include "matchshapes.h"

#include <QtCore/QVector>
#include <QtCore/QFuture>
#include <QtCore/QtConcurrentRun>

#include <QDebug>
#include <highgui.h>

#include <iostream>
using namespace mcv;
MatchShape::MatchShape(const cv::Mat& shape, QObject* parent) : 
  QObject(parent), m_shape(shape), m_method(CV_CONTOURS_MATCH_I1)
{
#if 0	
	static bool s = false;
	std::cerr << "shape\n";
	if (!s) {
		std::cerr << "false " << CV_WINDOW_AUTOSIZE;
		s = true;
		cvNamedWindow("ok", CV_WINDOW_AUTOSIZE);
	} else {
		std::cerr << "true";
	}
	std::cerr << "read";
	CvMat c1 = cv::Mat(m_shape);
	cvShowImage("ok", &c1);
	cv::waitKey(10000);
	std::cerr << "..ok\n";
#endif	
}

MatchShape::~MatchShape()
{
}

double MatchShape::match(const cv::Mat& shape)
{
#if 0
	qDebug() << "double MatchShape::match{ depth:" << m_shape.depth() << " - " << shape.depth() 
		<< ", channels: " << m_shape.channels() << " - "  << shape.channels() 
		<< ", cols: " << m_shape.cols << " - " << shape.cols 
		<< ", rows: " << m_shape.rows << " . " << shape.rows << "\n";
#endif
	CvMat c1 = cv::Mat(m_shape), c2 = cv::Mat(shape);
	double res = cvMatchShapes(&c1, &c2, m_method);
//	qDebug() << "MatchShape::match return = " << res << "\n";
	return res;
}

MatchShapes::MatchShapes(QObject* parent) : QObject(parent)
{
}

MatchShapes::~MatchShapes()
{
	for ( shapes_type::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it) {
		delete it->second;
	}
}

void MatchShapes::addShape(const int id, const cv::Mat& shape)
{
	int fromTo[] = {0,0};
	cv::Mat l_shape(shape.rows, shape.cols, CV_8UC1);
	cv::mixChannels(&shape, 1, &l_shape, 1, fromTo, 1);
	m_shapes.push_back( shape_data_type(id, new MatchShape(l_shape) ) );		
}

void MatchShapes::match(const cv::Mat& shape)
{
	//qDebug() << "MatchShapes::match\n";
	typedef QVector< QPair< int, QFuture<double> > > results_type;
	results_type results;
	int fromTo[] = {0,0};
	cv::Mat l_shape(shape.rows, shape.cols, CV_8UC1);
	cv::mixChannels(&shape, 1, &l_shape, 1, fromTo, 1);

	results.reserve(m_shapes.size());
	for (shapes_type::iterator it = m_shapes.begin(); it != m_shapes.end(); ++it) {
		results.push_back(results_type::value_type(it->first, QtConcurrent::run(it->second, &MatchShape::match, l_shape)));	
	}

	for (results_type::iterator it = results.begin(); it != results.end(); ++it) {
		emit matched(it->first, it->second.result());
	}
}

#include "matchshapes.moc"

