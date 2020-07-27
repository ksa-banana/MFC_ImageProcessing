
// Lena01Doc.cpp: CLena01Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lena01.h"
#endif

#include "Lena01Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLena01Doc

IMPLEMENT_DYNCREATE(CLena01Doc, CDocument)

BEGIN_MESSAGE_MAP(CLena01Doc, CDocument)
END_MESSAGE_MAP()


// CLena01Doc 생성/소멸

CLena01Doc::CLena01Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CLena01Doc::~CLena01Doc()
{
}

BOOL CLena01Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CLena01Doc serialization

void CLena01Doc::Serialize(CArchive& ar)
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
void CLena01Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CLena01Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CLena01Doc::SetSearchContent(const CString& value)
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

// CLena01Doc 진단

#ifdef _DEBUG
void CLena01Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLena01Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLena01Doc 명령


BOOL CLena01Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CFile File;
	unsigned char* temp;
	int i, index;

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	File.Read(&dibHf, sizeof(BITMAPFILEHEADER));

	//BMP파일인지 검사 
	// raw 파일로 열기
	if (dibHf.bfType != 0x4D42) {
		if (File.GetLength() == 256 * 256) { // RAW 파일의 크기 결정
			m_height = 256;
			m_width = 256;
		}
		else if (File.GetLength() == 512 * 512) { // RAW 파일의 크기 결정
			m_height = 512;
			m_width = 512;
		}
		else if (File.GetLength() == 640 * 480) { // RAW 파일의 크기 결정
			m_height = 480;
			m_width = 640;
		}
		else {
			AfxMessageBox(L"Not Support Image Size"); // 해당 크기가 없는 경우
			return 0;
		}

		m_size = m_width * m_height; // 영상의 크기 계산

		// 입력 영상의 크기에 맞는 메모리 할당
		m_MaskImage = new unsigned char[m_size];
		

		// 초기화
		for (int i = 0; i < m_size; i++) {
			m_MaskImage[i] = 255; 
		}

		// 입력 영상 파일 읽기
		File.Read(m_MaskImage, m_size); 
		File.Close();
		return TRUE;

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
	temp = new unsigned char[m_size];
	m_InputImage = new unsigned char[m_size];
	m_OutputImage = new unsigned char[m_size];

	m_OutputImage = NULL;

	File.Read(m_InputImage, m_size);
	File.Close();


	//gray color의 경우 raw 파일화
	for (i = 0; i < m_size; i++) {
		m_InputImage[i] = palRGB[temp[i]].rgbRed;
	}



	return TRUE;
}


BOOL CLena01Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CFile File;
	CFileDialog SaveDlg(FALSE);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);


		//정보저장
		File.Write(&dibHf, sizeof(BITMAPFILEHEADER));
		File.Write(&dibHi, sizeof(BITMAPINFOHEADER));
		if (dibHi.biBitCount == 8)
			File.Write(palRGB, sizeof(RGBQUAD) * 256);

		if (m_OutputImage)
			File.Write(m_OutputImage, dibHi.biSizeImage);
		else
			File.Write(m_InputImage, dibHi.biSizeImage);
		File.Close();
	}

	return CDocument::OnSaveDocument(lpszPathName);
}


void CLena01Doc::OnBinarization()
{
	// TODO: 여기에 구현 코드 추가.

	if (dibHi.biBitCount == 24)
		m_size = m_size / 3;


	int i, index;
	//출력 이미지 배열
	m_OutputImage = new unsigned char[m_size];


	out_dibHf = dibHf;
	out_dibHi = dibHi;
	out_dibHi.biBitCount = 8;


	// 팔레트 작성
	for (int i = 0; i < 256; i++)
	{
		out_palRGB[i].rgbBlue = i;
		out_palRGB[i].rgbGreen = i;
		out_palRGB[i].rgbRed = i;
		out_palRGB[i].rgbReserved = 0;
	}


	//이진화
	if (dibHi.biBitCount == 24) {

		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] > 0)
				m_OutputImage[i] = 0x00FFFFFF;
			else
				m_OutputImage[i] = 0x00000000;

		}
	}
	else {
		//팔레트 인덱스 저장
		for (i = 0; i < m_size; i++) {
			index = m_InputImage[i];
			if (palRGB[index].rgbRed >= 100)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = 0;
		}
	}
}


void CLena01Doc::OnFrameAnd()
{
	// TODO: 여기에 구현 코드 추가.

	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i , index;
	unsigned char* temp1;
	unsigned char* temp2;


	m_OutputImage = new unsigned char[m_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);

		if (File.GetLength() == m_size) {
			temp1 = new unsigned char[m_size];
			temp2 = new unsigned char[m_size];
			File.Read(temp1, m_size);
			File.Close();

			// 영상 상하 반전
			// 입력 영상의 배열 값을 출력 영상을 위한 배열의 수평축 뒷자리부터 저장
			for (i = 0; i < m_height; i++) {
				for (int j = 0; j < m_width; j++) {
					temp2[(m_height - i - 1) * m_width + j] = temp1[i * m_width + j];
				}
			}

			// 프레임 간에 픽셀 대 픽셀로 AND 연산 실행
			for (i = 0; i < m_size; i++) {
				
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] & temp2[i]);
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}
