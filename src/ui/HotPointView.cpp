#include "HotPointView.h"
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QFormLayout>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <Qt/qevent.h>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QPainter>

#include <iostream>
#include <cassert>

HotPointView::HotPointView( QWidget* parent ) : ParametrizedView( parent )
{
	if ( this->objectName().isEmpty() ) {
		setObjectName( QString::fromUtf8( "HotPointView" ) );
	}

	verticalLayout = new QVBoxLayout( parametersBox );
	verticalLayout->setObjectName( QString::fromUtf8( "verticalLayout" ) );

	formLayout = new QFormLayout();
	formLayout->setObjectName( QString::fromUtf8( "formLayout" ) );
	label = new QLabel( parametersBox );
	label->setObjectName( QString::fromUtf8( "label" ) );

	formLayout->setWidget( 2, QFormLayout::LabelRole, label );

	m_comboBox = new QComboBox( parametersBox );
	m_comboBox->setObjectName( QString::fromUtf8( "comboBox") );
	m_comboBox->addItem(QString::fromUtf8("wyjście"));
	m_comboBox->addItem(QString::fromUtf8("back projection"));
	m_comboBox->addItem(QString::fromUtf8("equalized hist"));
	
	formLayout->setWidget( 2, QFormLayout::FieldRole, m_comboBox );

	verticalLayout->addLayout( formLayout );

	//checkBox_2 = new QCheckBox( parametersBox );
	//checkBox_2->setObjectName( QString::fromUtf8( "checkBox_2" ) );

	//verticalLayout->addWidget( checkBox_2 );

	//checkBox = new QCheckBox( parametersBox );
	//checkBox->setObjectName( QString::fromUtf8( "checkBox" ) );

	//verticalLayout->addWidget( checkBox );
	createActions();
	graphicsView->scene()->installEventFilter( &m_drawEvent );

	m_selection = 0;
	m_polygon_selected = 0;
	m_polygons = 0;
	m_hotpoint = 0;

	//checkBox_2->setText( QApplication::translate( "Form", "CheckBox", 0, QApplication::UnicodeUTF8 ) );
	//checkBox->setText( QApplication::translate( "Form", "CheckBox", 0, QApplication::UnicodeUTF8 ) );
	label->setText( QApplication::translate( "Form", "przetwarzanie:", 0, QApplication::UnicodeUTF8 ) );

	QObject::connect( &m_drawEvent, SIGNAL( selectionChanged( QRectF ) ), this, SLOT( selectionChanged( QRectF ) ) );
	QObject::connect( m_comboBox, SIGNAL( currentIndexChanged(int)), this, SLOT(comboBox_currentIndexChanged(int)));
}


void HotPointView::addcustomMenuActions( QMenu& menu )
{
	menu.addSeparator();
	if (item) {
		menu.addAction( beginSelectionAct );
	}
	menu.addAction( resetSelectionAct );

}

void HotPointView::createActions()
{
	resetSelectionAct = new QAction( QString::fromUtf8( "Resetuj zaznaczenie" ), this );
	connect( resetSelectionAct, SIGNAL( triggered() ), this, SLOT( resetSelection() ) );

	beginSelectionAct = new QAction( QString::fromUtf8( "Wyznacz histogram" ), this );
	connect( beginSelectionAct, SIGNAL( triggered() ), this, SLOT( beginSelection() ) );
}

void HotPointView::resetSelection()
{
	m_drawEvent.clear();
}

/** @brief Tworzy histogram
 *
 *  Wyznacza histogram na podstawie zaznaczonego obszaru i wielkości obrazka
 */ 
void HotPointView::beginSelection()
{
	assert(item);
	QRect rect;
	if (m_selection) {
	  rect = m_selection->rect().toAlignedRect();
	} else {
	  rect = item->boundingRect().toAlignedRect();
	}
	QImage mask(m_image.width(), m_image.height(), QImage::Format_RGB888);
	mask.fill(0);
	QPainter painter(&mask);
	painter.fillRect(rect, Qt::white);
	painter.end();
	emit histogramChanged(m_image, mask);
	
}

void HotPointView::comboBox_currentIndexChanged(int index)
{
	
}

void HotPointView::selectionChanged( const QRectF& rect )
{
	if (!item) return;	  
	if ( rect.isNull() && m_selection ) {
		graphicsView->scene()->removeItem( m_selection );
		delete m_selection;
		m_selection = 0;
	}

	if ( !rect.isNull() && !m_selection ) {
		m_selection = graphicsView->scene()->addRect( rect.intersected(item->boundingRect()).normalized(), QPen(Qt::DashDotLine), QBrush::QBrush(Qt::DiagCrossPattern));
		m_selection->setParentItem(item);
	}

	if ( !rect.isNull() && m_selection ) {
		m_selection->setRect( rect.intersected(item->boundingRect()).normalized() );
	}
}

void HotPointView::setBackProject(const QImage& image)
{
	if (m_comboBox->currentIndex() == 1) {
		viewChanged(image);
	}	
}

void HotPointView::setRaw(const QImage& image)
{
	if (m_comboBox->currentIndex() == 0) {
		viewChanged(image);
	}
}

void HotPointView::setDetectedPolygons( const QVector<QPolygon>& polygons)
{
	assert(item);

	if (m_polygons) {
		graphicsView->scene()->removeItem(m_polygons);
		delete m_polygons;
	}

	m_polygons = new QGraphicsItemGroup(item, graphicsView->scene()); 
	for (QVector< QPolygon >::const_iterator it = polygons.begin(); it != polygons.end(); ++it) {
		m_polygons->addToGroup(new QGraphicsPolygonItem(*it, m_polygons));
	}
}

void HotPointView::setDetectedHotPolygon( const QPolygon& polygon)
{
	assert(item);
	if (! m_polygon_selected) {
		m_polygon_selected = graphicsView->scene()->addPolygon(polygon, QPen(Qt::white));
		m_polygon_selected->setZValue(100);
	} else {
		m_polygon_selected->setPolygon(polygon);
	}
}

void HotPointView::setDetectedHotPoint(const QPoint& point) 
{
	assert(item);
	if (! m_hotpoint) {
		m_hotpoint = new QGraphicsEllipseItem(item, graphicsView->scene());
		m_hotpoint->setBrush(QBrush(QColor::fromRgb(255, 0, 0)));
		m_hotpoint->setPen(QPen(QColor::fromRgb(255, 0, 0)));
	}

	m_hotpoint->setRect(point.x()-4, point.y()-4, 8, 8);
}

void HotPointView::setEqualized( const QImage& image) 
{
	if (m_comboBox->currentIndex() == 2) {
		viewChanged(image);
	}
}

DrawEvents::DrawEvents( QObject* parent ): QObject( parent ), m_drawing( false )
{

}


void DrawEvents::clear()
{
	m_rect = QRectF();
	m_drawing = false;
	emit selectionChanged( m_rect );
}


bool DrawEvents::eventFilter( QObject *obj, QEvent *event )
{
	if ( !m_drawing && ( event->type() == QEvent::GraphicsSceneMousePress ) ) {
		const QGraphicsSceneMouseEvent* const me = dynamic_cast<const QGraphicsSceneMouseEvent * const>( event );
		if ( me->button() == Qt::LeftButton ) {
			m_rect = QRectF( me->scenePos(), QSizeF( 1, 1 ) );
			m_drawing = true;
			emit selectionChanged( m_rect );
			return true;
		}
	}

	if ( m_drawing && ( event->type() == QEvent::GraphicsSceneMouseRelease ) ) {
		const QGraphicsSceneMouseEvent* const me = dynamic_cast<const QGraphicsSceneMouseEvent * const>( event );
		if ( me->button() == Qt::LeftButton ) {
			m_rect.setBottomRight( me->scenePos() );
			m_drawing = false;
			emit selectionChanged( m_rect );
			return true;
		}
	}

	if ( m_drawing && ( event->type() == QEvent::GraphicsSceneMouseMove ) ) {
		const QGraphicsSceneMouseEvent* const me = dynamic_cast<const QGraphicsSceneMouseEvent * const>( event );
		if ( me->buttons() & Qt::LeftButton ) {
			m_rect.setBottomRight( me->scenePos() );
		} else {
			m_drawing = false;
		}
		emit selectionChanged( m_rect );
		return true;
	}

	return QObject::eventFilter( obj, event );

}

#include "HotPointView.moc"
