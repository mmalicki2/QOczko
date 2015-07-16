#ifndef PARAMETRIZEDVIEW_H
#define PARAMETRIZEDVIEW_H

#include <QtGui/QGroupBox>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QMenu>


class ZoomEvents : public QObject
{
		Q_OBJECT
	signals:
		void zoomIn();
		void zoomOut();
		void zoomToView();

	public:
		ZoomEvents( QObject* parent = 0 );
		void setZoomToViewEnabled(bool enable) { m_zoomToView = enable; };	
	protected:
		bool eventFilter( QObject *obj, QEvent *event );
	private:
		bool m_zoomToView;	
};

class ParametrizedView : public QWidget
{
		Q_OBJECT
	public:
		ParametrizedView( QWidget* parent = 0 );

	public slots:
		void viewChanged( const QImage& image );

	private slots:
		void customContextMenuRequested( const QPoint & pos ) ;
		void zoomIn();
		void zoomOut();
		void zoomReset();
		void zoomToView();
		
	protected:
		virtual void addcustomMenuActions(QMenu& menu) {};

	private:
		void createActions();

	public:
		QVBoxLayout *topLayout;
		QGraphicsView *graphicsView;
		QGroupBox *parametersBox;
		QGraphicsPixmapItem* item;
		QImage m_image;

	protected:
		int scale;
		QGraphicsScene* scene;
		
		QAction* zoomInAct;
		QAction* zoomOutAct;
		QAction* zoomResetAct;
		QAction* zoomToViewAct;
		
		ZoomEvents m_zoomEvent;
};

#endif // PARAMETRIZEDVIEW_H
