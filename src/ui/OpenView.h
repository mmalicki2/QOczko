#ifndef OPENVIEW_H
#define OPENVIEW_H

#include "ParametrizedView.h"
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class OpenView : public ParametrizedView
{
		Q_OBJECT
	public:
		OpenView( QWidget* parent = 0 );

	signals:
		void open();
		void close();
		void resume();
		void suspend();

	private slots:
		void toggled( bool checked );

	public:
		QPushButton* closeButton;
		QPushButton* openButton;
		QPushButton* startstopButton;
		QHBoxLayout* parametersLayout;
		QVBoxLayout* parametersTopLayout;


};

#endif // OPENVIEW_H
