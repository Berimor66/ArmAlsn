// DIB.h   - ִכÿ נאבמעû c bmp פאיכאלט http://lib.zabspu.ru/computers/prg/c/mfc/lesson010.htm

#ifndef __DIB_H__
#define __DIB_H__

class CDib
{

public:
	CDib();
	~CDib();

	BOOL Load( const char * );
	BOOL Save( const char * );
	BOOL Draw( CDC *,int nX = 0,int nY = 0,int nWidth = -1,int nHeight = -1 );
	BOOL SetPalette( CDC * );

private:
	CPalette m_Palette;
	ULONGLONG *m_pDib;
	ULONGLONG	*m_pDibBits;	  //unsigned char
	DWORD m_dwDibSize;
	BITMAPINFOHEADER *m_pBIH;
	RGBQUAD *m_pPalette;
	DWORD m_nPaletteEntries;	   //int

};

#endif
