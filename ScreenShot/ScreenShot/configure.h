#pragma once

#define STRETCH_RECT_HEIGHT 10       // 拉伸小矩形的高度;
#define STRETCH_RECT_WIDTH 10        // 拉伸小矩形的宽度;

enum WindowStretchRectState
{
	NO_SELECT = 0,              // 鼠标未进入下方矩形区域;
	LEFT_TOP_RECT,              // 鼠标在左上角区域;
	TOP_BORDER,                 // 鼠标在上边框区域;
	RIGHT_TOP_RECT,             // 鼠标在右上角区域;
	RIGHT_BORDER,               // 鼠标在右边框区域;
	RIGHT_BOTTOM_RECT,          // 鼠标在右下角区域;
	BOTTOM_BORDER,              // 鼠标在下边框区域;
	LEFT_BOTTOM_RECT,           // 鼠标在左下角区域;
	LEFT_BORDER                 // 鼠标在左边框区域;
};

