#ifndef SHAPEVIEW_H
#define SHAPEVIEW_H

#include "ParametrizedView.h"

#include <QtGui/QGroupBox>
#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>

class ShapeView : public ParametrizedView
{
		Q_OBJECT
	public:
		ShapeView( QWidget* parent = 0 );
		
	signals:
		void match();
		void clear();

	public:
		QPushButton* matchButton;
		QPushButton* clearButton;
		QHBoxLayout* parametersTopLayout;

	private:
};

#endif // SHAPEVIEW_H
