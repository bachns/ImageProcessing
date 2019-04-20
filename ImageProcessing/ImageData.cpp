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
 * File name:    ImageRegistration/ImageData.cpp
 * Date created: Monday, March 27, 2017
 * Written by Bach Nguyen Sy
 */


#include "ImageData.h"
#include "Defines.h"


ImageData::ImageData() {
	this->image_ptr = nullptr;
	this->q_image_ptr = nullptr;
}

ImageData::ImageData(const cv::Mat& image, const std::string& title) {
	this->image_ptr = std::make_unique<cv::Mat>(image);
	this->q_image_ptr = std::make_unique<QImage>(
		ConvertionImage::mat2QImageCpy(image));
	this->title = title;
}

void ImageData::setImage(const cv::Mat& image, const std::string& title) {
	this->image_ptr = std::make_unique<cv::Mat>(image);
	this->q_image_ptr = std::make_unique<QImage>(
		ConvertionImage::mat2QImageCpy(image));
	this->title = title;
}

ImageData::~ImageData() {
}
