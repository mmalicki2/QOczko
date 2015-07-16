#include "ShapeView.h"

#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QtGui/QIcon>
#include <QtGui/QListWidget>
#include <QtCore/QDebug>

ShapeView::ShapeView( QWidget* parent ) : ParametrizedView( parent )
{
	if ( this->objectName().isEmpty() ) {
		setObjectName( QString::fromUtf8( "ShapeView" ) );
	}
	parametersTopLayout = new QHBoxLayout( parametersBox );
	parametersTopLayout->setObjectName( QString::fromUtf8( "parametersTopLayout" ) );
	matchButton = new QPushButton( this );
	parametersTopLayout->addWidget( matchButton );
	clearButton = new QPushButton( this );
	parametersTopLayout->addWidget( clearButton );
	parametersTopLayout->addStretch();

	matchButton->setText( QApplication::translate( "MatchPattern", "Dopasuj", 0, QApplication::UnicodeUTF8 ));
	clearButton->setText( QApplication::translate( "MatchPattern", "Wyczyść", 0, QApplication::UnicodeUTF8 ));
	
	QObject::connect(matchButton, SIGNAL(pressed()), this, SIGNAL(match()));
	QObject::connect(clearButton, SIGNAL(pressed()), this, SIGNAL(clear()));
}


#include "ShapeView.moc"
