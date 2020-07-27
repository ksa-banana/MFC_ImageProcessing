
// Lena01View.cpp: CLena01View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lena01.h"
#endif

#include "Lena01Doc.h"
#include "Lena01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLena01View

IMPLEMENT_DYNCREATE(CLena01View, CView)

BEGIN_MESSAGE_MAP(CLena01View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLena01View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BINARIZATION, &CLena01View::OnBinarization)
	ON_COMMAND(ID_FRAME_AND, &CLena01View::OnFrameAnd)
END_MESSAGE_MAP()

// CLena01View 생성/소멸

CLena01View::CLena01View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbReserved = 0;
	}

}

CLena01View::~CLena01View()
{
	if (BmInfo) delete BmInfo;
}

BOOL CLena01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CLena01View 그리기

void CLena01View::OnDraw(CDC* pDC)
{
	#define WIDTHBYTES(bits)	(((bits)+31)/32*4);
	CLena01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i, j;
	int rwsize;


	if (pDoc->m_InputImage == NULL)
		return;

	//입력 영상 출력
	//24비트 영상일 경우
	if (pDoc->dibHi.biBitCount == 24) {
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, pDoc->m_width, pDoc->m_height, 0, 0, 0, pDoc->m_height, pDoc->m_InputImage, BmInfo, DIB_RGB_COLORS);
	}
	//8비트 영상일 경우
	else {
		int index;
		//영상의 가로 길이를 4byte의 배수로 만듦
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);


		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++)
			for (int j = 0; j < pDoc->dibHi.biWidth; j++) {
				index = pDoc->m_InputImage[i * rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;
				BYTE B = pDoc->palRGB[index].rgbBlue;

				//pDC->SetPixel(j,i,RGB(R,G,B));

				 //영상 반전출력
				pDC->SetPixel(j, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));

			}
	}



	//영상 처리된 결과 출력
	if (pDoc->m_OutputImage == NULL)
		return;


	//24비트 영상일 경우
	if (pDoc->out_dibHi.biBitCount == 24) {
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), pDoc->m_width, 0, pDoc->m_width, pDoc->m_height, 0, 0, 0, pDoc->m_height, pDoc->m_OutputImage, BmInfo, DIB_RGB_COLORS);
	}
	//8비트 영상일 경우
	else {
		int index;
		//영상의 가로 길이를 4byte의 배수로 만듦
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount * pDoc->dibHi.biWidth);


		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++)
			for (int j = 0; j < pDoc->dibHi.biWidth; j++) {
				index = pDoc->m_OutputImage[i * rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;
				BYTE B = pDoc->palRGB[index].rgbBlue;

				//pDC->SetPixel(j,i,RGB(R,G,B));

				 //영상 반전출력
				pDC->SetPixel(j + pDoc->dibHi.biWidth, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));

			}
	}
}


// CLena01View 인쇄


void CLena01View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLena01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLena01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLena01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CLena01View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLena01View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLena01View 진단

#ifdef _DEBUG
void CLena01View::AssertValid() const
{
	CView::AssertValid();
}

void CLena01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLena01Doc* CLena01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLena01Doc)));
	return (CLena01Doc*)m_pDocument;
}
#endif //_DEBUG


// CLena01View 메시지 처리기


void CLena01View::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CLena01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();

	Invalidate(TRUE);
}


void CLena01View::OnFrameAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CLena01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameAnd();

	Invalidate(TRUE);
}
