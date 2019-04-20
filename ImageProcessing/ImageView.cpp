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
 * File name:    ImageRegistration/ImageView.cpp
 * Date created: Sunday, March 26, 2017
 * Written by Bach Nguyen Sy
 */

#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <memory>
#include "ImageView.h"

ImageView::ImageView(QWidget* parent, Qt::WindowFlags f) :
	QLabel(parent, f), image_data_ptr(nullptr) {
	this->setStyleSheet("background-color: rgb(0, 0, 0);");
	setCursor(QCursor(Qt::OpenHandCursor));
	piece_of_image = std::make_unique<QRect>(
		0, 0,
		static_cast<int>(0.5 + width() / kzoom.getValue()),
		static_cast<int>(0.5 + height() / kzoom.getValue()));
	mouseEventInfo = std::make_shared<MouseEventInfo>();
	idx_selected_kp = -1;
}

void ImageView::updatePieceOfImage(int dx_on_overview, int dy_on_overview,
                                   int width_overview, int height_overview) {

	double new_x = piece_of_image->x() +
			1.0 * dx_on_overview * image_data_ptr->q_image_ptr->width() / width_overview;
	double new_y = piece_of_image->y() +
			1.0 * dy_on_overview * image_data_ptr->q_image_ptr->height() / height_overview;

	piece_of_image->setRect(
		static_cast<int>(0.5 + new_x),
		static_cast<int>(0.5 + new_y),
		static_cast<int>(0.5 + width() / kzoom.getValue()),
		static_cast<int>(0.5 + height() / kzoom.getValue())
	);
	repaint();
}

void ImageView::zoom_in() {
	QPointF center(
		piece_of_image->x() + 0.5 * width() / kzoom.getValue(),
		piece_of_image->y() + 0.5 * height() / kzoom.getValue()
	);
	kzoom.zoom_in();
	view_at(center.x(), center.y());
	update();
	emit updateView();
}

void ImageView::zoom_out() {
	QPointF center(
		piece_of_image->x() + 0.5 * width() / kzoom.getValue(),
		piece_of_image->y() + 0.5 * height() / kzoom.getValue()
	);
	kzoom.zoom_out();
	view_at(center.x(), center.y());
	update();
	emit updateView();
}

void ImageView::view_at(double x, double y) {
	piece_of_image->setRect(
		static_cast<int>(0.5 + x - 0.5 * width() / kzoom.getValue()),
		static_cast<int>(0.5 + y - 0.5 * height() / kzoom.getValue()),
		static_cast<int>(0.5 + width() / kzoom.getValue()),
		static_cast<int>(0.5 + height() / kzoom.getValue()));
	update();
	emit updateView();
}


void ImageView::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
	if (image_data_ptr && image_data_ptr->q_image_ptr) {
		QPainter painter(this);
		painter.drawImage(this->rect(),
		                  *image_data_ptr->q_image_ptr, *piece_of_image);
	}
}

void ImageView::resizeEvent(QResizeEvent* event) {
	Q_UNUSED(event);
	piece_of_image->setWidth(static_cast<int>(0.5 + width() / kzoom.getValue()));
	piece_of_image->setHeight(static_cast<int>(0.5 + height() / kzoom.getValue()));
	emit resize();
}

void ImageView::mousePressEvent(QMouseEvent* event) {
	mouseEventInfo->pressed = true;
	mouseEventInfo->setBeforePosition(event->x(), event->y());
	setCursor(QCursor(Qt::ClosedHandCursor));
}

void ImageView::mouseMoveEvent(QMouseEvent* event) {
	if (mouseEventInfo->pressed) {
		mouseEventInfo->setAfterPosition(event->x(), event->y());
		piece_of_image->setRect(
			piece_of_image->x() -
			static_cast<int>(0.5 + mouseEventInfo->dx / kzoom.getValue()),
			piece_of_image->y() -
			static_cast<int>(0.5 + mouseEventInfo->dy / kzoom.getValue()),
			piece_of_image->width(),
			piece_of_image->height()
		);
		mouseEventInfo->setBeforePosition(event->x(), event->y());
		update();
		emit updateView();
	}
}

void ImageView::mouseReleaseEvent(QMouseEvent* event) {
	if (mouseEventInfo->pressed) {
		mouseEventInfo->release();
		setCursor(QCursor(Qt::ArrowCursor));
	}
}

void ImageView::wheelEvent(QWheelEvent* event) {
	if (event->delta() > 0) {
		zoom_in();
	}
	else {
		zoom_out();
	}
}
