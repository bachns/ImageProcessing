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
 * File name:    ImageRegistration/ImageView.h
 * Date created: Sunday, March 26, 2017
 * Written by Bach Nguyen Sy
 */


#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>
#include "Defines.h"
#include "KZoom.h"
#include "ImageData.h"


class ImageView : public QLabel {
	Q_OBJECT

public:
	explicit ImageView(QWidget* parent = Q_NULLPTR,
	                   Qt::WindowFlags f = Qt::WindowFlags());
	std::shared_ptr<ImageData> image_data_ptr;
	std::unique_ptr<QRect> piece_of_image;
	void updatePieceOfImage(int dx_on_overview, int dy_on_overview,
	                        int width_overview, int height_overview);
	std::shared_ptr<MouseEventInfo> mouseEventInfo;
	KZoom kzoom;
	std::vector<cv::KeyPoint> keypoints;
	int idx_selected_kp;

private slots:
	void zoom_in();
	void zoom_out();

public slots:
	void view_at(double x, double y);

	signals :
	void resize();
	void updateView();

protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
};

#endif
