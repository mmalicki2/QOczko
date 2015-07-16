#include "PatternsView.h"

#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QtGui/QIcon>
#include <QtGui/QListWidget>
#include <QtGui/QTableWidget>
#include <QtCore/QDebug>

PatternsView::PatternsView( QWidget* parent ) : QWidget( parent )
{
	if ( this->objectName().isEmpty() ) {
		setObjectName( QString::fromUtf8( "PatternsView" ) );
	}
	topLayout = new QVBoxLayout( this );
	topLayout->setObjectName( QString::fromUtf8( "topLayout" ) );

	
	tableWidget = new QTableWidget( this );
	tableWidget->setObjectName( QString::fromUtf8( "tableWidget" ) );
	tableWidget->setColumnCount(3);
	QStringList labels;
	labels << QString::fromUtf8("Pogląd") << QString::fromUtf8("Plik") << QString::fromUtf8("Dopasowanie");
	tableWidget->setHorizontalHeaderLabels(labels);
	topLayout->addWidget(tableWidget );
	
	parametersBox = new QGroupBox( this );
	parametersBox->setObjectName( QString::fromUtf8( "parametersBox" ) );
	parametersTopLayout = new QHBoxLayout( parametersBox );
	parametersTopLayout->setObjectName( QString::fromUtf8( "parametersTopLayout" ) );
	
	addPatternButton = new QPushButton( this );
	addPatternButton->setObjectName( QString::fromUtf8( "addPatternButton" ) );
	parametersTopLayout->addWidget( addPatternButton );
	parametersTopLayout->addStretch();
	topLayout->addWidget(parametersBox);

	addPatternButton->setText( QApplication::translate( "PatternsView", "Dodaj", 0, QApplication::UnicodeUTF8 ));
	
	QObject::connect(addPatternButton, SIGNAL(clicked(bool)), this, SLOT(addPattern(bool)));
}


void PatternsView::addPattern( bool checked )
{
	QStringList errors;
	QStringList files = QFileDialog::getOpenFileNames(this, "Wybierz pliki wzorca", "/home/mateusz/dev/opencv/projekt/patterns", "Obarzki *.bmp(*.bmp)");
	for (QStringList::const_iterator it = files.begin(); it != files.end(); ++it) {
		QPixmap* pixmap = new QPixmap(*it, 0, Qt::MonoOnly);
		if (! pixmap->isNull()) {
			int id = tableWidget->rowCount();
			tableWidget->insertRow(id);
			tableWidget->setItem(id, 0, new QTableWidgetItem(QIcon(*pixmap), ""));
			tableWidget->setItem(id, 1, new QTableWidgetItem(*it) );
			tableWidget->setItem(id, 2, new QTableWidgetItem("0") );
			emit addPatternImage(id, pixmap->toImage().convertToFormat(QImage::Format_RGB888));
		} else {
			errors.push_back(*it);
		}
		delete pixmap;
	}

	if (! errors.empty()) {
		//TODO: komunikat o bledzie dla uzytownika
		qDebug() << " MatchPattern::addPattern: Nie udalo sie zaloadaowac plikow: " << errors << "\n"; 
	}
}

void PatternsView::setMatch(const int id, const double value)
{
	tableWidget->item(id, 2)->setText(QString::number(value));
}

#include "PatternsView.moc"
