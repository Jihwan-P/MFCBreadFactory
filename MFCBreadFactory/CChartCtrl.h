#pragma once

#include <vector>

// CChartCtrl
class CChartCtrl : public CStatic
{
	DECLARE_DYNAMIC(CChartCtrl)

public:
	CChartCtrl();
	virtual ~CChartCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	// 데이터 설정을 위한 함수
	void SetData(const std::vector<float>& tempData, const std::vector<float>& humidityData);
	void SetRanges(float minTemp, float maxTemp, float minHumidity, float maxHumidity);

private:
	// 데이터
	std::vector<float> m_tempData;
	std::vector<float> m_humidityData;

	// 적정 범위
	float m_minTemp, m_maxTemp;
	float m_minHumidity, m_maxHumidity;

	// 그리기 관련 함수
	void DrawGrid(Gdiplus::Graphics& graphics, const CRect& rect);
	void DrawRanges(Gdiplus::Graphics& graphics, const CRect& rect);
	void DrawData(Gdiplus::Graphics& graphics, const CRect& rect);
};