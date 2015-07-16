#ifndef CANNY_H
#define CANNY_H

#include <cv.h>

#include <QtCore/QObject>

namespace mcv
{

class Canny : public QObject
{
		Q_OBJECT
		Q_PROPERTY( double threshold1 READ get_Threshold1 WRITE set_Threshold1 );
		Q_PROPERTY( double threshold2 READ get_Threshold2 WRITE set_Threshold2 );
		Q_PROPERTY( int apertureSize READ get_apertureSize WRITE set_apertureSize );
		Q_PROPERTY( bool L2gradient READ get_L2gradient WRITE set_L2gradient RESET reset_L2gradient );

	public slots:
		void imageRecived( const cv::Mat& image );
	  
	signals:
		void imageProduced( const cv::Mat& image );

	public:
		
		Canny( QObject* parent = 0 );
		virtual ~Canny();

		double get_Threshold1() const { return m_threshold1; };
		void set_Threshold1( double value ) { m_threshold1 = value; }

		double get_Threshold2() const { return m_threshold2; };
		void set_Threshold2( double value ) { m_threshold2 = value; };

		int get_apertureSize() const { return m_apertureSize; };
		void set_apertureSize( int value ) { m_apertureSize = value; };

		bool get_L2gradient() const { return m_L2gradient; };
		void set_L2gradient( bool value ) { m_L2gradient = value; }
		void reset_L2gradient() { m_L2gradient = false; };

	private:
		double  m_threshold1;
		double  m_threshold2;
		int     m_apertureSize;
		bool    m_L2gradient;
};

}; // namespace mcv

#endif // CANNY_H
