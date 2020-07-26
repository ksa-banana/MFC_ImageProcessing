
// lena02View.cpp: Clena02View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "lena02.h"
#endif

#include "lena02Doc.h"
#include "lena02View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clena02View

IMPLEMENT_DYNCREATE(Clena02View, CView)

BEGIN_MESSAGE_MAP(Clena02View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Clena02View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Clena02View 생성/소멸

Clena02View::Clena02View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

Clena02View::~Clena02View()
{
	if (BmInfo) delete BmInfo;
}

BOOL Clena02View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Clena02View 그리기

void Clena02View::OnDraw(CDC* pDC)
{
	#define WIDTHBYTES(bits)	(((bits)+31)/32*4);
	Clena02Doc* pDoc = GetDocument();
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

}


// Clena02View 인쇄


void Clena02View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Clena02View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Clena02View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Clena02View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Clena02View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Clena02View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Clena02View 진단

#ifdef _DEBUG
void Clena02View::AssertValid() const
{
	CView::AssertValid();
}

void Clena02View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clena02Doc* Clena02View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clena02Doc)));
	return (Clena02Doc*)m_pDocument;
}
#endif //_DEBUG


// Clena02View 메시지 처리기
