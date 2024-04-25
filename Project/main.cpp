#include <afxwin.h>
#include <vector>
#include <algorithm>

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

private:
	std::vector<double> m_values;
	COLORREF m_bgColor;
};

BOOL CMainWindow::OnEraseBkgnd(CDC* pDC) {
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, m_bgColor);
	return TRUE;
}

CMyApp myApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMainWindow::CMainWindow()
{
	Create(NULL, _T("MFC Application"));
	m_bgColor = RGB(135, 206, 250);

	for (int i = 1; i <= 4; ++i)
		m_values.push_back(static_cast<double>(i));
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	dc.SetBkMode(TRANSPARENT);

	int width = rect.Width() / (m_values.size() * 2 + 1);
	int height = width;

	width *= 1;
	height *= 1;

	int spacing = width;

	int totalWidth = m_values.size() * (width + spacing) - spacing;

	for (size_t i = 0; i < m_values.size(); ++i)
	{
		CString str;
		if (m_values[i] == static_cast<int>(m_values[i]))
			str.Format(_T("%.0f"), m_values[i]);
		else
			str.Format(_T("%.2f"), m_values[i]);

		CRect r(rect.left + (rect.Width() - totalWidth) / 2 + i * (width + spacing), rect.top + (rect.Height() - height) / 2,
			rect.left + (rect.Width() - totalWidth) / 2 + i * (width + spacing) + width, rect.top + (rect.Height() - height) / 2 + height);

		dc.Rectangle(r);

		COLORREF color = RGB(255 * i / m_values.size(), 0, 255 * (m_values.size() - i - 1) / m_values.size());
		dc.FillSolidRect(r, color);

		dc.SetTextColor(RGB(255, 255, 255));

		dc.DrawText(str, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
}


void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	int width = rect.Width() / (m_values.size() * 2 + 1);
	int height = width;

	width *= 1;
	height *= 1;

	int spacing = width;

	int index = -1;
	int totalWidth = m_values.size() * (width + spacing) - spacing;
	for (size_t i = 0; i < m_values.size(); ++i)
	{
		int left = rect.left + (rect.Width() - totalWidth) / 2 + i * (width + spacing);
		int right = left + width;
		if (point.x >= left && point.x <= right)
		{
			index = i;
			break;
		}
	}

	if (index >= 0 && index <static_cast<int>(m_values.size()) && static_cast<int>(m_values.size()) > 1) {
		m_values.erase(m_values.begin() + index);
	}

	Invalidate();
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width() / m_values.size();
	int index = static_cast<int>(std::floor(static_cast<double>(point.x) / width + 0.5));
	double avg = 0;

	if (index == 0) {
		//TRACE(_T("ok index: %d"), index);
		m_values.insert(m_values.begin(), m_values.front() - 1);
	}
	else if (index == m_values.size())
		m_values.push_back(m_values.back() + 1); 
	else {
		double avg = static_cast<double>(m_values[index - 1] + m_values[index]) / 2;
		m_values.insert(m_values.begin() + index, avg); 
														
	}
	TRACE(_T("index: %.2f\n"), index);
	TRACE(_T("point.x: %d\n"), point.x);
	if (index > 0 && index < static_cast<int>(m_values.size())) {
		TRACE(_T("m_values[index - 1]: %.2f\n"), m_values[index - 1]);
		TRACE(_T("m_values[index]: %.2f\n"), m_values[index]);
	}
	Invalidate();
	
}
