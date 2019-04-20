#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QMainWindow>
#include "ui_ImageProcessing.h"
#include <QFileDialog>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QMessageBox>
#include "EnterDialog.h"

class ImageProcessing : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImageProcessing(QWidget *parent = Q_NULLPTR);

private slots:
	void on_open_image();
	void on_save_image();
	void on_exit();

	void on_binary_image();
	void on_blur_image();
	void on_hsv_image();
	void on_segment_image();
	void on_laplace_filter();
	void on_flip_image();
	void on_rotate_image();
	void on_canny_image();
	void on_histograms_image();
	void on_equalize_histograms();
	void on_zoom_in();
	void on_zoom_out();
	void on_reset();

	void on_information() const;
	void on_about() const;
	
private:
	Ui::ImageProcessingClass ui;
	EnterDialog *enter_dialog;

	cv::Mat image;
	cv::Mat display_image;
	void displayImage(const cv::Mat& img);
	
	cv::Mat binary(int thresh) const;
	cv::Mat laplaceFilter() const;
	cv::Mat blur(int level) const;
	cv::Mat rotate(int angle) const;
	cv::Mat canny(int threshold) const;
	cv::Mat histograms() const;
	cv::Mat equalizeHistograms() const;
	cv::Mat zoom(double scale) const;

	//kết nối các sự kiện
	void connect() const;
	//chuyen cv::Mat sang QImage
	static QImage matToQimageRef(cv::Mat& mat, QImage::Format format);
	static QImage mat2QImageRef(cv::Mat& mat, bool swap = true);
	static QImage mat2QImageCpy(cv::Mat const& mat, bool swap = true);
};

#endif