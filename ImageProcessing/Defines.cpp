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
 * File name:    ImageRegistration/ConvertionImage.cpp
 * Date created: Sunday, March 26, 2017
 * Written by Bach Nguyen Sy
 */

#include "Defines.h"

inline QImage ConvertionImage::matToQimageRef(cv::Mat& mat, QImage::Format format) {
	return QImage(mat.data, mat.cols, mat.rows,
	              static_cast<int>(mat.step), format);
}

cv::Mat ConvertionImage::qimageToMatRef(QImage& img, int format) {
	return cv::Mat(img.height(), img.width(),
	               format, img.bits(), img.bytesPerLine());
}

QImage ConvertionImage::mat2QImageRef(cv::Mat& mat, bool swap) {
	if (!mat.empty()) {
		switch (mat.type()) {

			case CV_8UC3: {
				if (swap) {
					return matToQimageRef(mat, QImage::Format_RGB888).rgbSwapped();
				}
				else {
					return matToQimageRef(mat, QImage::Format_RGB888);
				}
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

	return {};
}

QImage ConvertionImage::mat2QImageCpy(cv::Mat const& mat, bool swap) {
	return mat2QImageRef(const_cast<cv::Mat&>(mat), swap).copy();
}

cv::Mat ConvertionImage::qimage2MatRef(QImage& img, bool swap) {
	if (img.isNull()) {
		return cv::Mat();
	}

	switch (img.format()) {
		case QImage::Format_RGB888: {
			auto result = qimageToMatRef(img, CV_8UC3);
			if (swap) {
				cv::cvtColor(result, result, CV_RGB2BGR);
			}
			return result;
		}
		case QImage::Format_Grayscale8:
		case QImage::Format_Indexed8: {
			return qimageToMatRef(img, CV_8U);
		}
		case QImage::Format_RGB32:
		case QImage::Format_ARGB32:
		case QImage::Format_ARGB32_Premultiplied: {
			return qimageToMatRef(img, CV_8UC4);
		}
		default:
			break;
	}

	return {};
}

cv::Mat ConvertionImage::qimage2MatCpy(QImage const& img, bool swap) {
	return qimage2MatRef(const_cast<QImage&>(img), swap).clone();
}


void MouseEventInfo::setBeforePosition(int x, int y) {
	x_before = x;
	y_before = y;
}

void MouseEventInfo::setAfterPosition(int x, int y) {
	x_after = x , y_after = y;
	rect.setX(std::min(x_before, x_after));
	rect.setY(std::min(y_before, y_after));
	dx = x_after - x_before;
	dy = y_after - y_before;
	rect.setWidth(std::abs(dx));
	rect.setHeight(std::abs(dy));
}

void MouseEventInfo::release() {
	pressed = false;
	setBeforePosition(0, 0);
	setAfterPosition(0, 0);
}
