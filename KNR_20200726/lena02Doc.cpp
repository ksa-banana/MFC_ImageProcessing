
// lena02Doc.cpp: Clena02Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "lena02.h"
#endif

#include "lena02Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Clena02Doc

IMPLEMENT_DYNCREATE(Clena02Doc, CDocument)

BEGIN_MESSAGE_MAP(Clena02Doc, CDocument)
END_MESSAGE_MAP()


// Clena02Doc 생성/소멸

Clena02Doc::Clena02Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

Clena02Doc::~Clena02Doc()
{
}

BOOL Clena02Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// Clena02Doc serialization

void Clena02Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void Clena02Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void Clena02Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Clena02Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Clena02Doc 진단

#ifdef _DEBUG
void Clena02Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Clena02Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Clena02Doc 명령


BOOL Clena02Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	File.Read(&dibHf, sizeof(BITMAPFILEHEADER));

	//BMP파일인지 검사 
	if (dibHf.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP file!!");
		return FALSE;
	}


	//헤더 읽기
	File.Read(&dibHi, sizeof(BITMAPINFOHEADER));

	//8비트 혹은 24비트가 아닐 경우
	if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)                                //8,24비트가 아닐경우
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}

	//8비트의 경우 팔레트를 생성해 주어야 한다. 총 256가지 색이므로 그 길이만큼 읽어들인다
	if (dibHi.biBitCount == 8)
		File.Read(palRGB, sizeof(RGBQUAD) * 256);


	//영상의 크기 읽기
	m_size = dibHi.biSizeImage;

	//영상 가로,세로 길이 저장
	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;


	//이미지를 저장, 출력할 배열생성.
	m_InputImage = new unsigned char[m_size];
	m_OutputImage = new unsigned char[m_size];
	File.Read(m_InputImage, m_size);
	File.Close();


	return TRUE;
}


BOOL Clena02Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog SaveDlg(FALSE);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName() , CFile::modeCreate | CFile::modeWrite  | CFile::typeBinary);

		//정보저장
		File.Write(&dibHf, sizeof(BITMAPFILEHEADER));
		File.Write(&dibHi, sizeof(BITMAPINFOHEADER));
		if (dibHi.biBitCount == 8)
			File.Write(palRGB, sizeof(RGBQUAD) * 256);

		File.Write(m_InputImage, dibHi.biSizeImage);
		File.Close();
	}

	return CDocument::OnSaveDocument(lpszPathName);
}
