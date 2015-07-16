#ifndef UI_QOCZKO_H
#define UI_QOCZKO_H

#include <HotPointView.h>
#include <OpenView.h>
#include <ShapeView.h>
#include <PatternsView.h>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_QOczko
{
	public:
		QVBoxLayout *verticalLayout;
		OpenView *left;
		HotPointView *right;
		PatternsView* patterns;
		ShapeView* shape;
		QDialogButtonBox *buttonBox;
		QSplitter* vsplitter;
		QSplitter* hsplitter;

		void setupUi( QDialog *QOczko ) {
			if ( QOczko->objectName().isEmpty() )
				QOczko->setObjectName( QString::fromUtf8( "QOczko" ) );
			QOczko->resize( 399, 544 );
			verticalLayout = new QVBoxLayout( QOczko );
			verticalLayout->setObjectName( QString::fromUtf8( "verticalLayout" ) );
			
			hsplitter = new QSplitter( QOczko ); 
			left = new OpenView( hsplitter );
			left->setObjectName( QString::fromUtf8( "left" ) );

			hsplitter->addWidget( left );
				
			right = new HotPointView( hsplitter );
			right->setObjectName( QString::fromUtf8( "right" ) );

			hsplitter->addWidget( right );

			vsplitter = new QSplitter( hsplitter );
			vsplitter->setOrientation( Qt::Vertical );
			shape = new ShapeView( vsplitter );
			shape->setObjectName( QString::fromUtf8( "shape" ));

			vsplitter->addWidget(shape);

			patterns = new PatternsView( vsplitter );
			patterns->setObjectName( QString::fromUtf8( "patterns" ));

			vsplitter->addWidget( patterns );

			hsplitter->addWidget( vsplitter );

			verticalLayout->addWidget(hsplitter);

			buttonBox = new QDialogButtonBox( QOczko );
			buttonBox->setObjectName( QString::fromUtf8( "buttonBox" ) );
			buttonBox->setOrientation( Qt::Horizontal );
			buttonBox->setStandardButtons( QDialogButtonBox::Cancel | QDialogButtonBox::Ok );
			buttonBox->setCenterButtons( true );

			verticalLayout->addWidget( buttonBox );


			retranslateUi( QOczko );
			QObject::connect( buttonBox, SIGNAL( accepted() ), QOczko, SLOT( accept() ) );
			QObject::connect( buttonBox, SIGNAL( rejected() ), QOczko, SLOT( reject() ) );

			QMetaObject::connectSlotsByName( QOczko );
		} // setupUi

		void retranslateUi( QDialog *QOczko ) {
			QOczko->setWindowTitle( QApplication::translate( "QOczko", "QOczko", 0, QApplication::UnicodeUTF8 ) );
			Q_UNUSED( QOczko );
		} // retranslateUi

};

namespace Ui
{
class QOczko: public Ui_QOczko {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QOCZKO_H
