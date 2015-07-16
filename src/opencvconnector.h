#ifndef OPENCVCONNECTOR_H
#define OPENCVCONNECTOR_H
#include <qimage.h>
#include <cv.h>

class OpenCVConnector
{
	public:
		static void OpenCVToQImage(QImage& _image, const IplImage& opencv_image);
		static void OpenCVToQImage(QImage& _image, const cv::Mat& opencv_image);
		
		static void QImageToOpenCV(IplImage& _opencv_image, const QImage& image);
		static void QImageToOpenCV(cv::Mat& _opencv_image, const QImage& image );
		
		static IplImage* CreateLinkedOpenCV(const QImage& image);
		static void CreateLinkedQImage(QImage& _image, IplImage& opencv_image);
		static void createPipedImages(QImage& _image, IplImage*& opencv_image, const QSize& size);
		static void createPipedImages(QImage& _image, cv::Mat& _opencv_image, const QSize& size);
};


namespace mcv
{

class OpenCVConverter : public QObject
{
		Q_OBJECT
		
	public slots:
		void imageRecived( const cv::Mat& image );
		void imageRecived( const QImage& image1, const QImage& image2);
		void imageRecived( const int id, const QImage& image);
	  
	signals:
		void imageProduced( const QImage& image );
		void imageProduced( const cv::Mat& image1, const cv::Mat& image2 );
		void imageProduced( const int id, const cv::Mat& image);
		
};


};

#endif // OPENCVCONNECTOR_H
