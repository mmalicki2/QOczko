#ifndef _QOCZKO_H
#define _QOCZKO_H

#include "ui_QOczko.h"
#include <QtCore/QObject>
#include <QtGui/QPushButton>
#include <QtGui/QImage>

class QOczko : public QDialog
{
		Q_OBJECT
	public:
		QOczko(QWidget* parent = 0);
		virtual ~QOczko();

	signals:
		void open();
		void close();
		void resume();
		void suspend();
		void matchShape();
		void clearShape();
		void addPatternImage(int id, const QImage& image);
		void histogramChanged(const QImage& image, const QImage& mask);
		

	public slots:
		void leftViewChanged( const QImage& image ) { widget.left->viewChanged( image ); };
		void rightViewChanged( const QImage& image ) {  widget.right->setRaw( image ); };
		void trackViewChanged( const QImage& image ) { widget.shape->viewChanged( image ); }
		void setBackProject( const QImage& image) { widget.right->setBackProject(image); }
		void setDetectedPolygons( const QVector<QPolygon>& polygons ) { widget.right->setDetectedPolygons( polygons ); }
		void setDetectedHotPolygon( const QPolygon& polygon ) { widget.right->setDetectedHotPolygon( polygon ); }
		void setDetectedHotPoint( const QPoint& point) { widget.right->setDetectedHotPoint( point );  }
		void setDetectedShape(const int id, const double value ) { widget.patterns->setMatch(id, value); }
		void setEqualized( const QImage& image) { widget.right->setEqualized(image); } 
		
	private:
		QPushButton* openButton;
		QPushButton* closeButton;
		QPushButton* startstopButton;
		QWidget*     buttonsWidget;
		Ui::QOczko   widget;
};

#endif /* _QOCZKO_H */
