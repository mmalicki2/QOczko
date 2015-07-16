#include "QOczko.h"

QOczko::QOczko(QWidget* parent) : QDialog(parent)
{
	widget.setupUi( this );
	QObject::connect( widget.left, SIGNAL( open() ), this, SIGNAL( open() ) );
	QObject::connect( widget.left, SIGNAL( close() ), this, SIGNAL( close() ) );
	QObject::connect( widget.left, SIGNAL( resume() ), this, SIGNAL( resume() ) );
	QObject::connect( widget.left, SIGNAL( suspend() ), this, SIGNAL( suspend() ) );
	QObject::connect( widget.shape, SIGNAL( match() ), this, SIGNAL( matchShape() ) );
	QObject::connect( widget.shape, SIGNAL( clear() ), this, SIGNAL( clearShape() ));

	QObject::connect( widget.right, SIGNAL( histogramChanged(QImage,QImage)), this, SIGNAL( histogramChanged(QImage,QImage)));
	QObject::connect( widget.patterns, SIGNAL( addPatternImage(int, QImage) ), this, SIGNAL( addPatternImage(int, QImage)));
}

QOczko::~QOczko()
{
}

#include "QOczko.moc"
