
// lena02Doc.h: Clena02Doc 클래스의 인터페이스
//


#pragma once


class Clena02Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	Clena02Doc() noexcept;
	DECLARE_DYNCREATE(Clena02Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~Clena02Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

	BITMAPFILEHEADER dibHf;
	BITMAPINFOHEADER dibHi;
	RGBQUAD palRGB[256];

	unsigned char* m_InputImage;
	unsigned char* m_OutputImage;
	int m_width;
	int m_height;
	int m_size;
};
