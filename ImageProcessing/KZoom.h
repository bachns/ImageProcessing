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
 * File name:    ImageRegistration/kzoom.h
 * Date created: Sunday, March 26, 2017
 * Written by Bach Nguyen Sy
 */


#ifndef KZOOM_H
#define KZOOM_H
#include <vector>

//Các tham số thu phóng ảnh
class KZoom {
public:
	KZoom();
	void zoom_in();
	void zoom_out();
	double getValue() const;

private:
	std::vector<double> values;
	size_t idx;
};

#endif
