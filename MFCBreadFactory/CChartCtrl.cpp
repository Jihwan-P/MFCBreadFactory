// ChartCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "CChartCtrl.h"

// CChartCtrl

IMPLEMENT_DYNAMIC(CChartCtrl, CStatic)

CChartCtrl::CChartCtrl() : m_minTemp(0), m_maxTemp(0), m_minHumidity(0), m_maxHumidity(0)
{
	// 24시간 데이터를 0으로 초기화
	m_tempData.resize(24, 0.0f);
	m_humidityData.resize(24, 0.0f);
}

CChartCtrl::~CChartCtrl()
{
}

BEGIN_MESSAGE_MAP(CChartCtrl, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CChartCtrl 메시지 처리기
void CChartCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	// Double Buffering을 사용하여 깜박임 방지
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bmp);

	// GDI+ Graphics 객체 생성
	Gdiplus::Graphics graphics(memDC.GetSafeHdc());
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	// 배경을 흰색으로 채우기
	graphics.Clear(Gdiplus::Color::White);

	// 그래프 그리기
	DrawGrid(graphics, rect);
	DrawRanges(graphics, rect);
	DrawData(graphics, rect);

	// 화면에 출력
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
}


void CChartCtrl::SetData(const std::vector<float>& tempData, const std::vector<float>& humidityData)
{
	m_tempData = tempData;
	m_humidityData = humidityData;
	Invalidate(); // 컨트롤을 다시 그리도록 요청
}

void CChartCtrl::SetRanges(float minTemp, float maxTemp, float minHumidity, float maxHumidity)
{
	m_minTemp = minTemp;
	m_maxTemp = maxTemp;
	m_minHumidity = minHumidity;
	m_maxHumidity = maxHumidity;
	Invalidate();
}

void CChartCtrl::DrawGrid(Gdiplus::Graphics& graphics, const CRect& rect)
{
	Gdiplus::Pen gridPen(Gdiplus::Color(200, 200, 200)); // 회색
	Gdiplus::Font axisFont(L"Malgun Gothic", 8);
	Gdiplus::SolidBrush axisBrush(Gdiplus::Color::Black);

	int padding = 30;
	int chartWidth = rect.Width() - padding * 2;
	int chartHeight = rect.Height() - padding * 2;

	// X축 (시간)
	for (int i = 0; i <= 24; i += 2) {
		int x = padding + (chartWidth * i) / 24;
		graphics.DrawLine(&gridPen, x, padding, x, padding + chartHeight);

		CString str;
		str.Format(_T("%d"), i);
		Gdiplus::PointF pointF(x - 5, padding + chartHeight + 5);
		graphics.DrawString(str, -1, &axisFont, pointF, &axisBrush);
	}

	// Y축 (온도/습도)
	for (int i = 0; i <= 10; i++) {
		int y = padding + (chartHeight * i) / 10;
		graphics.DrawLine(&gridPen, padding, y, padding + chartWidth, y);

		CString str;
		str.Format(_T("%d"), 100 - i * 10); // 100부터 0까지
		Gdiplus::PointF pointF(padding - 25, y - 8);
		graphics.DrawString(str, -1, &axisFont, pointF, &axisBrush);
	}
}

void CChartCtrl::DrawRanges(Gdiplus::Graphics& graphics, const CRect& rect)
{
	int padding = 30;
	int chartWidth = rect.Width() - padding * 2;
	int chartHeight = rect.Height() - padding * 2;

	// 적정 온도 범위
	if (m_maxTemp > m_minTemp) {
		Gdiplus::SolidBrush tempBrush(Gdiplus::Color(50, 255, 0, 0)); // 반투명 빨강
		float y_max = padding + chartHeight * (1.0f - m_maxTemp / 100.0f);
		float y_min = padding + chartHeight * (1.0f - m_minTemp / 100.0f);
		graphics.FillRectangle(&tempBrush, padding, (int)y_max, chartWidth, (int)(y_min - y_max));
	}

	// 적정 습도 범위
	if (m_maxHumidity > m_minHumidity) {
		Gdiplus::SolidBrush humidityBrush(Gdiplus::Color(50, 0, 0, 255)); // 반투명 파랑
		float y_max = padding + chartHeight * (1.0f - m_maxHumidity / 100.0f);
		float y_min = padding + chartHeight * (1.0f - m_minHumidity / 100.0f);
		graphics.FillRectangle(&humidityBrush, padding, (int)y_max, chartWidth, (int)(y_min - y_max));
	}
}

void CChartCtrl::DrawData(Gdiplus::Graphics& graphics, const CRect& rect)
{
	if (m_tempData.empty() || m_humidityData.empty()) return;

	Gdiplus::Pen tempPen(Gdiplus::Color::Red, 2);
	Gdiplus::Pen humidityPen(Gdiplus::Color::Blue, 2);

	int padding = 30;
	int chartWidth = rect.Width() - padding * 2;
	int chartHeight = rect.Height() - padding * 2;

	std::vector<Gdiplus::PointF> tempPoints;
	std::vector<Gdiplus::PointF> humidityPoints;

	for (int i = 0; i < 24; ++i) {
		float x = (float)padding + (float)(chartWidth * i) / 23.0f;

		// 온도 데이터 포인트
		float y_temp = (float)padding + chartHeight * (1.0f - m_tempData[i] / 100.0f);
		tempPoints.push_back(Gdiplus::PointF(x, y_temp));

		// 습도 데이터 포인트
		float y_humidity = (float)padding + chartHeight * (1.0f - m_humidityData[i] / 100.0f);
		humidityPoints.push_back(Gdiplus::PointF(x, y_humidity));
	}

	// 선 그리기
	if (tempPoints.size() > 1) {
		graphics.DrawLines(&tempPen, tempPoints.data(), tempPoints.size());
	}
	if (humidityPoints.size() > 1) {
		graphics.DrawLines(&humidityPen, humidityPoints.data(), humidityPoints.size());
	}
}