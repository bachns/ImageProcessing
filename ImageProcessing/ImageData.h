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
 * File name:    ImageRegistration/ImageData.h
 * Date created: Monday, March 27, 2017
 * Written by Bach Nguyen Sy
 */


#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <opencv2/core/mat.hpp>
#include <QImage>
#include <memory>

class ImageData {
public:
	explicit ImageData();
	explicit ImageData(const cv::Mat& image, const std::string& title);
	void setImage(const cv::Mat& image, const std::string& title);
	~ImageData();
	std::unique_ptr<cv::Mat> image_ptr;
	std::unique_ptr<QImage> q_image_ptr;
	std::string title;
};

#endif
