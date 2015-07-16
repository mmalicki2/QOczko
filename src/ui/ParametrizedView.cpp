#include "ParametrizedView.h"

#include <QtGui/QPixmap>
#include <QtGui/QMenu>
#include <QtGui/QGraphicsPixmapItem>
#include <QtCore/QEvent>
#include <QtGui/QWheelEvent>

#include <iostream>
#include <cassert>

ParametrizedView::ParametrizedView( QWidget* parent ) : QWidget( parent ), item( 0 )
{
	if ( this->objectName().isEmpty() ) {
		setObjectName( QString::fromUtf8( "ParametrizedView" ) );
	}
	resize( 331, 417 );
	topLayout = new QVBoxLayout( this );
	topLayout->setObjectName( QString::fromUtf8( "topLayout" ) );
	graphicsView = new QGraphicsView( this );
	scene = new QGraphicsScene( graphicsView );
	graphicsView->setObjectName( QString::fromUtf8( "graphicsView" ) );
	graphicsView->setScene( scene );
	topLayout->addWidget( graphicsView );
	parametersBox = new QGroupBox( this );
	parametersBox->setObjectName( QString::fromUtf8( "parametersBox" ) );

	topLayout->setStretch( 0, 1 );
	topLayout->setStretch( 1, 0 );
	topLayout->addWidget( parametersBox );
	scale = 100;
	createActions();
	graphicsView->setContextMenuPolicy( Qt::CustomContextMenu );
	m_zoomEvent.setZoomToViewEnabled(true);
	graphicsView->installEventFilter(&m_zoomEvent);
	connect( graphicsView, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( customContextMenuRequested( QPoint ) ) );
	connect( &m_zoomEvent, SIGNAL( zoomIn() ), this, SLOT(zoomIn()));
	connect( &m_zoomEvent, SIGNAL( zoomOut() ), this, SLOT(zoomOut()));
	connect( &m_zoomEvent, SIGNAL( zoomToView()), this, SLOT(zoomToView()));
}

void ParametrizedView::viewChanged( const QImage& image )
{
	m_image = image;
	QPixmap map = QPixmap::fromImage( image );
	if ( !item ) {
		item = scene->addPixmap( map );
	} else {
		item->setPixmap( map );
	}
	graphicsView->setSceneRect(item->sceneBoundingRect());
	graphicsView->update();
}

void ParametrizedView::customContextMenuRequested( const QPoint& pos )
{
	QMenu menu( this );
	menu.addAction( zoomInAct );
	menu.addAction( zoomOutAct );
	menu.addAction( zoomResetAct );
	menu.addAction( zoomToViewAct );
	addcustomMenuActions(menu);
	menu.exec( graphicsView->mapToGlobal( pos ) );
}

void ParametrizedView::zoomIn()
{
	if ( scale < 200 ) {
		scale += 10;
		graphicsView->setMatrix( QMatrix().scale((( qreal )scale ) / 100, (( qreal )scale ) / 100 ) );
	}
	zoomToViewAct->setChecked(false);
}
void ParametrizedView::zoomOut()
{
	if ( scale > 10 ) {
		scale -= 10;
		graphicsView->setMatrix( QMatrix().scale((( qreal )scale ) / 100, (( qreal )scale ) / 100 ) );
	}
	zoomToViewAct->setChecked(false);
}
void ParametrizedView::zoomReset()
{
	if ( scale != 100 ) {
		scale = 100;
		graphicsView->setMatrix( QMatrix() );
	}
	zoomToViewAct->setChecked(false);
}

void ParametrizedView::zoomToView()
{
	if ( item && zoomToViewAct->isChecked() ) {
		graphicsView->fitInView(item, Qt::KeepAspectRatio);
		scale = static_cast<int>(graphicsView->matrix().m11() * 10)*10;
		if (scale <  10) scale = 10;
	}
	m_zoomEvent.setZoomToViewEnabled(zoomToViewAct->isChecked());
}

void ParametrizedView::createActions()
{
	zoomInAct = new QAction( QString::fromUtf8( "&Powiększ" ), this );
	connect( zoomInAct, SIGNAL( triggered() ), this, SLOT( zoomIn() ) );

	zoomOutAct = new QAction( QString::fromUtf8( "&Pomniejsz" ) , this );
	connect( zoomOutAct, SIGNAL( triggered() ), this, SLOT( zoomOut() ) );

	zoomResetAct = new QAction( QString::fromUtf8( "Rozmiar orginalny" ), this );
	connect( zoomResetAct, SIGNAL( triggered() ), this, SLOT( zoomReset() ) );

	zoomToViewAct = new QAction( QString::fromUtf8( "Do okna" ), this );
	zoomToViewAct->setCheckable( true );
	zoomToViewAct->setChecked( true );
	connect( zoomToViewAct, SIGNAL( triggered() ), this, SLOT( zoomToView() ) );

}



ZoomEvents::ZoomEvents( QObject* parent ): QObject( parent ), m_zoomToView(true)
{

}

#include <QDebug>
bool ZoomEvents::eventFilter( QObject* obj, QEvent* event )
{
	if (event->type() == QEvent::Wheel) {
		const QWheelEvent* const e = dynamic_cast<const QWheelEvent* const>(event);
		int step = e->delta() / (15*8);
		if (step == 0) {
			return false;
		} else if (step > 0) {
			emit zoomIn();
		} else {
			assert(step < 0);
			emit zoomOut();
		}
	  	return true;
	}

	if (event->type() == QEvent::Resize) {
		if (m_zoomToView) {
			emit zoomToView();
		//	return true;
		}
	}

	return QObject::eventFilter( obj, event );
}



#include "ParametrizedView.moc"
