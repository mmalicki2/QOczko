#ifndef PATTERNSVIEW_H
#define PATTERNSVIEW_H

#include <QtGui/QGroupBox>
#include <QtGui/QWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

class PatternsView : public QWidget
{
		Q_OBJECT
	public:
		PatternsView( QWidget* parent = 0 );
		
	private slots:
		void addPattern(bool checked);
		
	public slots:	
		void setMatch(const int id, const double value);

	signals:
		void addPatternImage(int id, const QImage& image);

	public:
		QTableWidget* tableWidget;
		QPushButton* addPatternButton;
		QVBoxLayout *topLayout;
		QGroupBox *parametersBox;
		QHBoxLayout* parametersTopLayout;

};

#endif // PATTERNSVIEW_H
