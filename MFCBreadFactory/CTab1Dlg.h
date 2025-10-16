#pragma once
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

#define TIMER_UPDATE_CAMERA 100

// CTab1View 폼 보기

class CTab1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab1Dlg)

public:
	CTab1Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1Dlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB1_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog(); // 다이얼로그 초기화를 위해 추가

	// OpenCV 및 스레드 관련 멤버 변수
	std::vector<cv::VideoCapture> m_caps;
	std::vector<cv::Mat> m_frames;
	std::vector<std::thread> m_threads;
	std::atomic<bool> m_bThreadRunning;
	std::vector<std::mutex> m_mutexes;

	// 카메라 스트리밍 URL
	const std::vector<std::string> m_cameraUrls = {
		"http://192.168.0.118:18081", // CAM 1
		"http://192.168.0.91:18081",  // CAM 2
		"http://192.168.0.84:18081",  // CAM 3
		"http://192.168.0.108:18081"  // CAM 4
	};

	// 카메라 영상을 표시할 CStatic 컨트롤 멤버 변수
	CStatic m_picCam1, m_picCam2, m_picCam3, m_picCam4;

	void CameraThread(int index);
	void DrawFrame(int index);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
