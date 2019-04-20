/********************************************************************************
 *   Copyright (C) 2017 by Bach Nguyen Sy                                       *
 *   Unauthorized copying of this file via any medium is strictly prohibited    *
 *                                                                              *
 *   <bachns.dev@gmail.com>                                                     *
 *   https://bachns.wordpress.com                                               * 
 *   https://wwww.facebook.com/bachns.dev                                       *
 *                                                                              *
 ********************************************************************************/

/**
 * File name:    ImageRegistration/ConvertionImage.h
 * Date created: Sunday, March 26, 2017
 * Written by Bach Nguyen Sy
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>

class ConvertionImage {
	static QImage matToQimageRef(cv::Mat& mat, QImage::Format format);
	static cv::Mat qimageToMatRef(QImage& img, int format);
public:
	static QImage mat2QImageRef(cv::Mat& mat, bool swap = true);
	static QImage mat2QImageCpy(cv::Mat const& mat, bool swap = true);
	static cv::Mat qimage2MatRef(QImage& img, bool swap = true);
	static cv::Mat qimage2MatCpy(QImage const& img, bool swap = true);
};


class MouseEventInfo {
public:
	void setBeforePosition(int x, int y);
	void setAfterPosition(int x, int y);
	void release();
	QRect rect;
	bool pressed; //bấm giữ chuột
	int x_before, y_before;
	int x_after, y_after;
	int dx, dy; //thay đổi sau 2 sự kiện pressed và released 

};
#endif //DEFINES_H
