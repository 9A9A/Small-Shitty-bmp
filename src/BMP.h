#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <Windows.h>
#include <thread>
#include "Utilities.h"
using namespace std;

const string Cb_Postfix ( "_Cb" );
const string Cr_Postfix ( "_Cr" );
const string Y_Postfix ( "_Y" );
const string Red_Postfix ( "_red" );
const string Green_Postfix ( "_green" );
const string Blue_Postfix ( "_blue" );
const string Restored_Postfix ( "_restored" );
abstract_class CBMP
{
public:
	CBMP ( );
	CBMP ( string &filename );
	virtual ~CBMP ( );
	virtual void LoadFile ( );
	virtual void LoadFile ( string &filename );
	virtual void SaveFile ( );
	virtual void SaveFile ( string &filename );
	virtual void SetName ( string &filename );
	virtual void SetFileHeader ( BITMAPFILEHEADER &FileHeader );
	virtual void SetInfoHeader ( BITMAPINFOHEADER &InfoHeader );
	virtual void ShowInfo ( );
	virtual RGBTRIPLE GetPixel ( unsigned y ,unsigned x ) = 0;
	virtual CMatrix2D<int> GetComponentPixmap ( int component ) = 0;
	unsigned GetHeight ( );
	unsigned GetWidth ( );
	virtual void Resize ( unsigned Height ,unsigned Width );
	virtual CMatrix2D<rgbD> GetPixelData ( )=0;
	BITMAPFILEHEADER GetFileHeader ( );
	BITMAPINFOHEADER GetInfoHeader ( );
	string GetFilename ( );
	void AddToFilename ( string &append );


protected:
	void FilenameCheck ( string &format );
	fstream m_fstFileInput;
	fstream m_fstFileOutput;
	bool m_bHeadersLoad;
	string m_Filename;
	BITMAPFILEHEADER m_sFileHeader;
	BITMAPINFOHEADER m_sInfoHeader;
};
class BMP8 : public CBMP
{
public:
	BMP8 ( );
	BMP8 ( const BMP8 & );
	BMP8 ( string & );
	virtual ~BMP8 ( );
	void LoadFile ( );
	void LoadFile ( string & );
	void SaveFile ( );
	void SaveFile ( string & );
	void ShowInfo ( );
	RGBTRIPLE GetPixel ( unsigned y ,unsigned x );
	CMatrix2D<int> GetComponentPixmap ( int component );
	CMatrix2D<rgbD> GetPixelData ( );
protected:
	CMatrix2D<BYTE> m_matData;
	vector<RGBQUAD> m_Palette;
};
class BMP24 : public CBMP
{
public:
	BMP24 ( );
	BMP24 ( const BMP24 &obj );
	BMP24 ( string &filename );
	virtual ~BMP24 ( );
	void LoadFile ( );
	void LoadFile ( string &filename );
	void SaveFile ( );
	void SaveFile ( string &filename );
	void ShowInfo ( );
	void Resize ( unsigned Height ,unsigned Width );
	static void SplitIntoColors ( BMP24 &src );
	static void BuildHistogramm ( string &filename ,CMatrix2D<int> &obj );
	static void BuildHistogramm ( BMP24 &src );
	static void ConvertToYCbCr ( BMP24 &src ,unsigned ratio ,bool type );
	static BMP24 ConvertToRGB ( BMP24 &Y_pic ,BMP24 &Cb_pic ,BMP24 &Cr_pic );
	void SetPixelData ( CMatrix2D<rgbD> &obj );
	RGBTRIPLE GetPixel ( unsigned y ,unsigned x );
	CMatrix2D<int> GetComponentPixmap ( int component );
	CMatrix2D<rgbD> GetPixelData ( );
protected:
	void recompute_headers ( );
	CMatrix2D<rgbD> m_matData;
};
_Type double ExpectedValue ( vector<_Ty> &vec )
{ 
	assert ( vec.size() > 0 );
	double temp = 0;
	for ( auto &i : vec )
	{
		temp += i;
	}
	return temp / (double)vec.size ( );
}
double Correlation ( CMatrix2D<int> &lhs ,CMatrix2D<int> &rhs );
double MeanSquareDisplacement ( CMatrix2D<int> &obj );
double PSNR ( CMatrix2D<int> &lhs,CMatrix2D<int> &rhs );
void PSNR_PIC ( CBMP &lhs ,CBMP &rhs );
void Autocorrelation ( int y_offset,unsigned step_by_x, CBMP &image );
void ComputeAutocorrelation ( BMP24 &image ,unsigned step_by_x );
double Entropy ( CMatrix2D<int> &mtrx );
void ShowEntropy ( CBMP &image );
void ShowCorrelation ( CBMP &lhs ,CBMP &rhs );
void DPCM_Encoder ( unsigned Mode ,BMP24 &image );
static CBMP *LoadBMP ( string &filename )
{
	if ( !strstr ( filename.c_str ( ) ,".bmp" ) )
	{
#ifdef _DEBUG
		cout << "Filename fixed\n";
#endif
		filename += ".bmp";
	}
	fstream input ( filename ,ios::in | ios::binary );
	if ( input.is_open ( ) )
	{
		BITMAPFILEHEADER fileheader;
		BITMAPINFOHEADER infoheader;
		input.read ( reinterpret_cast< char* >( &fileheader ) ,sizeof ( BITMAPFILEHEADER ) );
		input.read ( reinterpret_cast< char* >( &infoheader ) ,sizeof ( BITMAPINFOHEADER ) );
		switch ( infoheader.biBitCount )
		{
			case bit_depth_8:
				input.close ( );
				return new BMP8 ( filename );
			case bit_depth_24:
				input.close ( );
				return new BMP24 ( filename );
			default:
				input.close ( );
		}
	}
}