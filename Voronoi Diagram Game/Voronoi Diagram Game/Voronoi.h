#pragma once

#include "stdafx.h"
#include "MyBitmap.h"
#include <windows.h>
#include <vector>
#include <string>

static int DistanceSqrd(const Point& point, int x, int y) {
	int xd = x - point.x;
	int yd = y - point.y;
	return (xd * xd) + (yd * yd);
}

class Voronoi {
public:
	void Make(MyBitmap* bmp, int count) {
		bmp_ = bmp;
		CreatePoints(count);
		CreateColors();
		CreateSites();
		SetSitesPoints();
	}

	void CreateSites() { //voronoi triangulation mathematics
		int w = bmp_->width(), h = bmp_->height(), d;

		for (int hh = 0; hh < h; hh++) {
			for (int ww = 0; ww < w; ww++) {

				int ind = -1, dist = INT_MAX;

				for (size_t it = 0; it < points_.size(); it++) {
					const Point& p = points_[it];
					d = DistanceSqrd(p, ww, hh); //lines between points
					if (d < dist) {
						dist = d;
						ind = it;
					}
				}

				if (ind > -1)
					SetPixel(bmp_->hdc(), ww, hh, colors_[ind]);
				else
					__asm nop // should never happen!
			}
		}
	}

	void SetSitesPoints() {
		for (const auto& point : points_) {
			int x = point.x, y = point.y;

			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					SetPixel(bmp_->hdc(), x + i, y + j, 0);
		}
	}

	void CreatePoints(int count) {
		const int w = bmp_->width() - 20, h = bmp_->height() - 20;

		for (int i = 0; i < count; i++) {
			points_.push_back({ rand() % w + 10, rand() % h + 10 }); //where the black points are placed.
			//add position of mouse
			//push back position of mouse and create a dot there
		}
	}

	void CreateColors() {
		for (size_t i = 0; i < points_.size(); i++) {
			DWORD c = RGB(255, 0,0); //red
			DWORD d = RGB(0, 0, 255); //blue

			colors_.push_back(c);
			colors_.push_back(d);
		}
	}

	vector<Point> points_;
	vector<DWORD> colors_;
	MyBitmap* bmp_;
};