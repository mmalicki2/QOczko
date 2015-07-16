#include "OpenView.h"
#include <QtGui/QApplication>

#include <iostream>

OpenView::OpenView( QWidget* parent ) : ParametrizedView( parent )
{
	if ( this->objectName().isEmpty() ) {
		setObjectName( QString::fromUtf8( "OpenView" ) );
	}
	parametersTopLayout = new QVBoxLayout( parametersBox );
	parametersTopLayout->setObjectName( QString::fromUtf8( "parametersTopLayout" ) );

	parametersLayout = new QHBoxLayout( );
	parametersLayout->setObjectName( QString::fromUtf8( "parametersLayout" ) );
	parametersTopLayout->addLayout( parametersLayout );
	parametersTopLayout->addStretch();
	
	openButton = new QPushButton( parametersBox );
	openButton->setObjectName( QString::fromUtf8( "openButton" ) );
	parametersLayout->addWidget( openButton );

	closeButton = new QPushButton( parametersBox );
	closeButton->setObjectName( QString::fromUtf8( "closeButton" ) );
	parametersLayout->addWidget( closeButton );

	parametersLayout->addStretch();
	startstopButton = new QPushButton( parametersBox );
	startstopButton->setObjectName( QString::fromUtf8( "startstopButton" ) );
	startstopButton->setCheckable( true );
	parametersLayout->addWidget( startstopButton );

	startstopButton->setChecked(true);
	QObject::connect( openButton, SIGNAL( clicked() ), this, SIGNAL( open() ) );
	QObject::connect( closeButton, SIGNAL( clicked() ), this, SIGNAL( close() ) );
	QObject::connect( startstopButton, SIGNAL( toggled( bool ) ), this, SLOT( toggled( bool ) ) );

	
	startstopButton->setText( QApplication::translate( "OpenView", "Uruchom", 0, QApplication::UnicodeUTF8 ) );
	openButton->setText( QApplication::translate( "OpenView", "Otwórz", 0, QApplication::UnicodeUTF8 ) );
	closeButton->setText( QApplication::translate( "OpenView", "Zamknij", 0, QApplication::UnicodeUTF8 ) );
}

void OpenView::toggled( bool checked )
{
	if ( checked ) {
		startstopButton->setText( QApplication::translate( "OpenView", "Wznów", 0, QApplication::UnicodeUTF8 ) );
		emit suspend();
	} else {
		startstopButton->setText( QApplication::translate( "OpenView", "Zatrzymaj", 0, QApplication::UnicodeUTF8 ) );
		emit resume();
	}
}

#include "OpenView.moc"
