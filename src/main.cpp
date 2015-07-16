#include "ui/QOczko.h"
#include "qoczkoalgorithm.h"

#include <QtGui/QApplication>
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QOczko* qOczko = new QOczko();
	QOczkoAlgorithm* alg = new QOczkoAlgorithm();
	
	QObject::connect( qOczko, SIGNAL( open() ), alg, SLOT( open()) );
	QObject::connect( qOczko, SIGNAL( close() ), alg, SLOT( close() ) );
	QObject::connect( qOczko, SIGNAL( resume() ), alg, SLOT( start()) );
	QObject::connect( qOczko, SIGNAL( suspend() ), alg, SLOT( stop() ) );
	QObject::connect( qOczko, SIGNAL( histogramChanged(QImage,QImage)), alg, SLOT(setHistogram(QImage,QImage)) );
	QObject::connect( qOczko, SIGNAL( clearShape()), alg, SLOT(resetTrack()));
	QObject::connect( qOczko, SIGNAL( matchShape()), alg, SLOT(matchShape()));
	QObject::connect( qOczko, SIGNAL( addPatternImage(int, QImage) ), alg, SLOT(addShape(int, QImage)));

	QObject::connect( alg, SIGNAL( frameProduced_raw(QImage)), qOczko, SLOT(leftViewChanged(QImage) ));
	QObject::connect( alg, SIGNAL( frameProduced_raw(QImage)), qOczko, SLOT(rightViewChanged(QImage) ));
	QObject::connect( alg, SIGNAL( frameProduced_track(QImage)), qOczko, SLOT( trackViewChanged(QImage)));
	QObject::connect( alg, SIGNAL( frameProduced_backproject(QImage)), qOczko, SLOT(setBackProject(QImage)));
	QObject::connect( alg, SIGNAL( frameProduced_equalized(QImage)), qOczko, SLOT(setEqualized(QImage)));
	QObject::connect( alg, SIGNAL( detectedPolygons(QVector<QPolygon>)), qOczko, SLOT(setDetectedPolygons(QVector<QPolygon>)));
	QObject::connect( alg, SIGNAL( detectedHotPoint(QPoint)), qOczko, SLOT(setDetectedHotPoint(QPoint)));
	QObject::connect( alg, SIGNAL( detectedShape(int, double)), qOczko, SLOT(setDetectedShape(int, double)));
	qOczko->show();

	return app.exec();
}
