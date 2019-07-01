#pragma once

#define STRETCH_RECT_HEIGHT 10       // ����С���εĸ߶�;
#define STRETCH_RECT_WIDTH 10        // ����С���εĿ��;

enum WindowStretchRectState
{
	NO_SELECT = 0,              // ���δ�����·���������;
	LEFT_TOP_RECT,              // ��������Ͻ�����;
	TOP_BORDER,                 // ������ϱ߿�����;
	RIGHT_TOP_RECT,             // ��������Ͻ�����;
	RIGHT_BORDER,               // ������ұ߿�����;
	RIGHT_BOTTOM_RECT,          // ��������½�����;
	BOTTOM_BORDER,              // ������±߿�����;
	LEFT_BOTTOM_RECT,           // ��������½�����;
	LEFT_BORDER                 // �������߿�����;
};

