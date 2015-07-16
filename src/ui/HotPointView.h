#ifndef HOTPOINTVIEW_H
#define HOTPOINTVIEW_H

#include "ParametrizedView.h"
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QFormLayout>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>

class DrawEvents : public QObject
{
		Q_OBJECT

	signals:
		void selectionChanged( const QRectF& rect );

	public:

		DrawEvents( QObject* parent = 0 );

		bool isEmpty() const { return m_rect.isNull(); }
		void clear();
		const QRectF& getRectF() const { return m_rect; }

	protected:
		bool eventFilter( QObject *obj, QEvent *event );

	private:
		QRectF m_rect;
		bool m_drawing;
};


class HotPointView : public ParametrizedView
{
		Q_OBJECT
	signals:
		void histogramChanged(const QImage& image, const QImage& mask);
	
	public slots:
		void setBackProject(const QImage& image);
		void setRaw(const QImage& image);
		void setDetectedPolygons( const QVector<QPolygon>& polygons);
		void setDetectedHotPolygon( const QPolygon& polygon);
		void setDetectedHotPoint( const QPoint& point );
		void setEqualized( const QImage& image);
	
	private slots:
		void resetSelection();
		void beginSelection();
		void selectionChanged( const QRectF& rect );
		void comboBox_currentIndexChanged(int index);
		

	public:
		HotPointView( QWidget* parent = 0 );


	protected:
		void addcustomMenuActions( QMenu& menu );

	private:
		void createActions();

	private:
		QVBoxLayout *verticalLayout;
		//QCheckBox *checkBox_2;
		//QCheckBox *checkBox;
		QFormLayout *formLayout;
		QLabel *label;
		QComboBox*  m_comboBox;

		QGraphicsRectItem*    m_selection;
		
		QGraphicsPolygonItem* m_polygon_selected; 
		QGraphicsItemGroup*   m_polygons;
		QGraphicsEllipseItem* m_hotpoint; 

		QAction* resetSelectionAct;
		QAction* beginSelectionAct;

		DrawEvents m_drawEvent;
};




#endif // HOTPOINTVIEW_H
