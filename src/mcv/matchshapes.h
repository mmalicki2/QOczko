#ifndef MATCHSHAPES_H
#define MATCHSHAPES_H


#include <QtCore/QObject>
#include <QtCore/QLinkedList>
#include <QtCore/QPair>

#include <cv.h>

namespace mcv {
  
class MatchShape : public QObject
{
	public:
		double match(const cv::Mat& shape);
		
	public:
		MatchShape(const cv::Mat& shape, QObject* parent = 0 );
		virtual ~MatchShape();
	
	private:
		const cv::Mat m_shape;
		int           m_method;
};
  
  
class MatchShapes : public QObject
{
	Q_OBJECT
	public slots:
	  
		void addShape(const int id, const cv::Mat& shape);
		void match(const cv::Mat& shape);
		
	signals:
		void matched(const int id, const double value);
		
	public:
		
		MatchShapes( QObject* parent = 0 );
		virtual ~MatchShapes();

	private:

		typedef QPair<int, MatchShape*> shape_data_type;
		typedef QLinkedList< shape_data_type > shapes_type;

		shapes_type m_shapes;	
};

};

#endif // MATCHSHAPES_H
