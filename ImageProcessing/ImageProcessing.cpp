#include "ImageProcessing.h"
#include "EnterDialog.h"
#include <signal.h>

ImageProcessing::ImageProcessing(QWidget *parent)
	: QMainWindow(parent), enter_dialog(new EnterDialog)
{
	ui.setupUi(this);
	connect();
}

void ImageProcessing::on_open_image() {
	QString file_name = QFileDialog::getOpenFileName(this, "Open image");
	if (!file_name.isEmpty()) {
		image = cv::imread(file_name.toStdString());
		if (image.data) {
			displayImage(image);
		}
		else {
			QMessageBox::critical(this, "Error open image", "Cannot read this image !");
		}
	}
}

void ImageProcessing::on_save_image() {
	if (!display_image.empty()) {
		QString file_name = QFileDialog::getSaveFileName(this, "Save image", QString(), "Images (*.png *.jpg)");
		if (!file_name.isEmpty()) {
			bool result = cv::imwrite(file_name.toStdString(), display_image);
			if (result) {
				QMessageBox::information(this, tr("Image Processing"), tr("Save image successfully !"));
			}
			else {
				QMessageBox::critical(this, tr("Image Processing"), tr("Save image unsuccessfully !"));
			}
		}
	}
}

void ImageProcessing::on_exit() {
	this->close();
}

void ImageProcessing::on_binary_image() {
	if (image.data) {
		enter_dialog->setWindowTitle("Binary Image");
		enter_dialog->setLabel("Threshold:");
		enter_dialog->setRange(1, 254);
		enter_dialog->setDefaultValue(128);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat binary_image = binary(enter_dialog->getValue());
			displayImage(binary_image);
		}
	}
}

void ImageProcessing::on_blur_image() {
	if (image.data) {
		enter_dialog->setWindowTitle("Blur Image");
		enter_dialog->setLabel("Level:");
		enter_dialog->setRange(0, 4);
		enter_dialog->setDefaultValue(0);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat blur_image = blur(enter_dialog->getValue());
			displayImage(blur_image);
		}
	}
}

void ImageProcessing::on_hsv_image() {
	if (image.data) {
		cv::Mat hsv_image;
		cv::cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);
		displayImage(hsv_image);
	}
}

void ImageProcessing::on_segment_image() {
	if(image.data) {
		cv::Mat src = image.clone();
		for (int x = 0; x < src.rows; x++) {
			for (int y = 0; y < src.cols; y++) {
				if (src.at<cv::Vec3b>(x, y) == cv::Vec3b(255, 255, 255)) {
					src.at<cv::Vec3b>(x, y)[0] = 0;
					src.at<cv::Vec3b>(x, y)[1] = 0;
					src.at<cv::Vec3b>(x, y)[2] = 0;
				}
			}
		}
		cv::Mat kernel = (cv::Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
		cv::Mat imgLaplacian;
		cv::Mat sharp = src; // copy source image to another temporary one
		filter2D(sharp, imgLaplacian, CV_32F, kernel);
		src.convertTo(sharp, CV_32F);
		cv::Mat imgResult = sharp - imgLaplacian;
		// convert back to 8bits gray scale
		imgResult.convertTo(imgResult, CV_8UC3);
		imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
		src = imgResult; // copy back
		cv::Mat bw;
		cvtColor(src, bw, CV_BGR2GRAY);
		threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		cv::Mat dist;
		distanceTransform(bw, dist, CV_DIST_L2, 3);
		normalize(dist, dist, 0, 1., cv::NORM_MINMAX);
		threshold(dist, dist, .4, 1., CV_THRESH_BINARY);
		cv::Mat kernel1 = cv::Mat::ones(3, 3, CV_8UC1);
		dilate(dist, dist, kernel1);
		cv::Mat dist_8u;
		dist.convertTo(dist_8u, CV_8U);
		std::vector<std::vector<cv::Point> > contours;
		findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		cv::Mat markers = cv::Mat::zeros(dist.size(), CV_32SC1);
		for (size_t i = 0; i < contours.size(); i++) {
			drawContours(markers, contours, static_cast<int>(i), cv::Scalar::all(static_cast<int>(i) + 1), -1);
		}
		circle(markers, cv::Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
		watershed(src, markers);
		cv::Mat mark = cv::Mat::zeros(markers.size(), CV_8UC1);
		markers.convertTo(mark, CV_8UC1);
		bitwise_not(mark, mark);

		std::vector<cv::Vec3b> colors;
		for (size_t i = 0; i < contours.size(); i++) {
			int b = cv::theRNG().uniform(0, 255);
			int g = cv::theRNG().uniform(0, 255);
			int r = cv::theRNG().uniform(0, 255);
			colors.push_back(cv::Vec3b(static_cast<uchar>(b), static_cast<uchar>(g), static_cast<uchar>(r)));
		}
		cv::Mat segmentation_image = cv::Mat::zeros(markers.size(), CV_8UC3);
		for (int i = 0; i < markers.rows; i++) {
			for (int j = 0; j < markers.cols; j++) {
				int index = markers.at<int>(i, j);
				if (index > 0 && index <= static_cast<int>(contours.size())) {
					segmentation_image.at<cv::Vec3b>(i, j) = colors[index - 1];
				}
				else {
					segmentation_image.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
				}
			}
		}
		displayImage(segmentation_image);
	}
}

void ImageProcessing::on_laplace_filter() {
	if (image.data) {
		cv::Mat laplace_image = laplaceFilter();
		displayImage(laplace_image);
	}
}

void ImageProcessing::on_flip_image() {
	if (image.data) {
		enter_dialog->setWindowTitle("Flipping Image");
		enter_dialog->setLabel("0:x-axis, 1:y-axis, -1:O-Center ");
		enter_dialog->setRange(-1, 1);
		enter_dialog->setDefaultValue(0);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat flip_image;
			cv::flip(image, flip_image, enter_dialog->getValue());
			displayImage(flip_image);
		}
	}
}

void ImageProcessing::on_rotate_image() {
	if (image.data) {
		enter_dialog->setWindowTitle("Rotation Image");
		enter_dialog->setLabel("Angle:");
		enter_dialog->setRange(1, 359);
		enter_dialog->setDefaultValue(180);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat rotation_image = rotate(enter_dialog->getValue());
			displayImage(rotation_image);
		}
	}
}

void ImageProcessing::on_canny_image() {
	if (image.data) {
		enter_dialog->setWindowTitle("Canny Filter");
		enter_dialog->setLabel("Threshold:");
		enter_dialog->setRange(1, 254);
		enter_dialog->setDefaultValue(128);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat canny_image = canny(enter_dialog->getValue());
			displayImage(canny_image);
		}
	}
}

void ImageProcessing::on_histograms_image() {
	if (image.data) {
		cv::Mat histograms_image = histograms();
		displayImage(histograms_image);
	}
}

void ImageProcessing::on_equalize_histograms() {
	if (image.data) {
		cv::Mat equalize_histograms = equalizeHistograms();
		displayImage(equalize_histograms);
	}
}

void ImageProcessing::on_zoom_in() {
	if (image.data) {
		enter_dialog->setWindowTitle("Zoom In");
		enter_dialog->setLabel("Scale s:");
		enter_dialog->setRange(1, 4);
		enter_dialog->setDefaultValue(2);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat zoom_image = zoom(enter_dialog->getValue());
			displayImage(zoom_image);
		}
	}
}

void ImageProcessing::on_zoom_out() {
	if (image.data) {
		enter_dialog->setWindowTitle("Zoom Out");
		enter_dialog->setLabel("Scale (1:s), s: ");
		enter_dialog->setRange(1, 4);
		enter_dialog->setDefaultValue(2);
		if (enter_dialog->exec() == QDialog::Accepted) {
			cv::Mat zoom_image = zoom(1.0 / enter_dialog->getValue());
			displayImage(zoom_image);
		}
	}
}

void ImageProcessing::on_reset() {
	if (image.data) {
		displayImage(image);
	}
}

void ImageProcessing::on_information() const {
	QMessageBox::information(nullptr, tr("Imformation"), tr("Image processing program written in C++ using Qt and OpenCV\n Written by Bach Nguyen Sy"));
}

void ImageProcessing::on_about() const {
	
}

void ImageProcessing::displayImage(const cv::Mat & img) {
	display_image = img.clone();
	ui.imageLabel->setPixmap(QPixmap::fromImage(mat2QImageCpy(img)));
}

cv::Mat ImageProcessing::binary(int thresh) const {
	cv::Mat gray_image, binary_image;
	cv::cvtColor(image, gray_image, CV_BGR2GRAY);
	cv::threshold(gray_image, binary_image, thresh, 255, CV_THRESH_BINARY);
	return binary_image;
}

cv::Mat ImageProcessing::laplaceFilter() const {
	cv::Mat gaussian_blur;
	cv::Mat gray_image, lap_image, lapabs_image;
	int kernel_size = 3, scale = 1, delta = 0, ddepth = CV_16S;
	cv::GaussianBlur(image, gaussian_blur, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	cv::cvtColor(gaussian_blur, gray_image, cv::COLOR_RGB2GRAY);
	cv::Laplacian(gray_image, lap_image, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	convertScaleAbs(lap_image, lapabs_image);
	return lapabs_image;
}

cv::Mat ImageProcessing::blur(int level) const {
	cv::Mat blur_image;
	cv::Point anchor = cv::Point(-1, -1);
	double delta = 0;
	int ddepth = -1, kernel_size = 3 + 2 * level;
	cv::Mat kernel = cv::Mat::ones(kernel_size, kernel_size, CV_32F) / static_cast<float>(kernel_size * kernel_size);
	cv::filter2D(image, blur_image, ddepth, kernel, anchor, delta, cv::BORDER_DEFAULT);
	return blur_image;
	
}

cv::Mat ImageProcessing::rotate(int angle) const {
	cv::Point2f center(image.cols / 2.0, image.rows / 2.0);
	cv::Mat affine = cv::getRotationMatrix2D(center, angle, 1.0);

	cv::Rect box = cv::RotatedRect(center, image.size(), angle).boundingRect();
	affine.at<double>(0, 2) += box.width / 2.0 - center.x;
	affine.at<double>(1, 2) += box.height / 2.0 - center.y;

	cv::Mat rotation_image;
	cv::warpAffine(image, rotation_image, affine, box.size());
	return rotation_image;
}

cv::Mat ImageProcessing::canny(int threshold) const {
	cv::Mat gray_image;
	cv::Mat detected_edges;
	int ratio = 3, kernel_size = 3;
	cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
	cv::blur(gray_image, detected_edges, cv::Size(3, 3));
	Canny(detected_edges, detected_edges, threshold, threshold*ratio, kernel_size);
	cv::Mat canny_image = cv::Mat::zeros(image.size(), image.type());
	image.copyTo(canny_image, detected_edges);
	return canny_image;
}

cv::Mat ImageProcessing::histograms() const {
	std::vector<cv::Mat> bgr_planes;
	cv::split(image, bgr_planes);
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	cv::Mat b_hist, g_hist, r_hist;
	cv::calcHist(&bgr_planes[0], 1, nullptr, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	cv::calcHist(&bgr_planes[1], 1, nullptr, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	cv::calcHist(&bgr_planes[2], 1, nullptr, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound(hist_w * 1.0 / histSize);

	cv::Mat hist_image(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(g_hist, g_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(r_hist, r_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < histSize; i++) {

		line(hist_image, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);

		line(hist_image, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			cv::Scalar(0, 255, 0), 2, 8, 0);

		line(hist_image, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);
	}
	return hist_image;
}

cv::Mat ImageProcessing::equalizeHistograms() const {
	cv::Mat hsv_image, rgb_image;
	cv::cvtColor(image, hsv_image, CV_BGR2HSV);
	std::vector<cv::Mat> hsv_channels;
	cv::split(hsv_image, hsv_channels);
	cv::equalizeHist(hsv_channels[2], hsv_channels[2]);
	cv::merge(hsv_channels, hsv_image);
	cv::cvtColor(hsv_image, rgb_image, CV_HSV2BGR);
	return rgb_image;
}

cv::Mat ImageProcessing::zoom(double scale) const {
	cv::Mat zoom_image;
	cv::resize(image, zoom_image, cv::Size(image.cols * scale, image.rows * scale));
	return zoom_image;
}

void ImageProcessing::connect() const {
	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(on_open_image()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(on_save_image()));
	QObject::connect(ui.actionBinary, SIGNAL(triggered()), this, SLOT(on_binary_image()));
	QObject::connect(ui.actionBlur_image, SIGNAL(triggered()), this, SLOT(on_blur_image()));
	QObject::connect(ui.actionHSV_Image, SIGNAL(triggered()), this, SLOT(on_hsv_image()));
	QObject::connect(ui.actionSegment_Image, SIGNAL(triggered()), this, SLOT(on_segment_image()));
	QObject::connect(ui.actionLaplace_filter, SIGNAL(triggered()), this, SLOT(on_laplace_filter()));
	QObject::connect(ui.actionFlip, SIGNAL(triggered()), this, SLOT(on_flip_image()));
	QObject::connect(ui.actionRotate, SIGNAL(triggered()), this, SLOT(on_rotate_image()));
	QObject::connect(ui.actionCanny_filter, SIGNAL(triggered()), this, SLOT(on_canny_image()));
	QObject::connect(ui.actionHistogram, SIGNAL(triggered()), this, SLOT(on_histograms_image()));
	QObject::connect(ui.actionEqualize_Histograms, SIGNAL(triggered()), this, SLOT(on_equalize_histograms()));
	QObject::connect(ui.actionZoom_In, SIGNAL(triggered()), this, SLOT(on_zoom_in()));
	QObject::connect(ui.actionZoom_out, SIGNAL(triggered()), this, SLOT(on_zoom_out()));
	QObject::connect(ui.actionReset, SIGNAL(triggered()), this, SLOT(on_reset()));
	QObject::connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(on_about()));
	QObject::connect(ui.actionInfomation, SIGNAL(triggered()), this, SLOT(on_information()));
	QObject::connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(on_exit()));

}

QImage ImageProcessing::matToQimageRef(cv::Mat& mat, QImage::Format format) {
	return QImage(mat.data, mat.cols, mat.rows,
		static_cast<int>(mat.step), format);
}

QImage ImageProcessing::mat2QImageRef(cv::Mat& mat, bool swap) {
	if (!mat.empty()) {
		switch (mat.type()) {
		case CV_8UC3: {
			if (swap) {
				return matToQimageRef(mat, QImage::Format_RGB888).rgbSwapped();
			}
			return matToQimageRef(mat, QImage::Format_RGB888);
		}
		case CV_8U: {
			return matToQimageRef(mat, QImage::Format_Indexed8);
		}
		case CV_8UC4: {
			return matToQimageRef(mat, QImage::Format_ARGB32);
		}
		default:
			break;
		}
	}
	return{};
}

QImage ImageProcessing::mat2QImageCpy(cv::Mat const& mat, bool swap) {
	return mat2QImageRef(const_cast<cv::Mat&>(mat), swap).copy();
}
