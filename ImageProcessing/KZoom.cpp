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
 * File name:    ImageRegistration/kzoom.cpp
 * Date created: Sunday, March 26, 2017
 * Written by Bach Nguyen Sy
 */


#include "kzoom.h"

KZoom::KZoom() {
	values.push_back(0.1);
	values.push_back(0.2);
	values.push_back(0.4);
	values.push_back(0.5);
	values.push_back(0.8);
	values.push_back(1.0);
	values.push_back(1.5);
	values.push_back(2.0);
	values.push_back(2.5);
	values.push_back(3.0);
	values.push_back(4.0);
	values.push_back(5.0);
	values.push_back(8.0);
	values.push_back(10.0);
	idx = 5;
}

void KZoom::zoom_in() {
	if (idx < values.size() - 1) {
		idx++;
	}
}

void KZoom::zoom_out() {
	if (idx > 0) {
		idx--;
	}
}

double KZoom::getValue() const {
	return values[idx];
}
