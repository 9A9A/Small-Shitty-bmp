#include "BMP.h"
CBMP::CBMP ( )
{
	m_bHeadersLoad = false;
}
CBMP::CBMP ( string &filename ) : CBMP ( )
{
	CBMP::LoadFile ( filename );
}
CBMP::~CBMP ( )
{
	m_fstFileInput.close ( );
	m_fstFileOutput.close ( );
#ifdef _DEBUG
	cout << m_Filename << " - Abstract Base Object has been destroyed.\n";
#endif
	m_Filename.clear ( );
}
unsigned CBMP::GetHeight ( )
{
	return m_sInfoHeader.biHeight;
}
unsigned CBMP::GetWidth ( )
{
	return m_sInfoHeader.biWidth;
}
void CBMP::FilenameCheck ( string &format )
{
	if ( !strstr ( m_Filename.c_str ( ) ,format.c_str ( ) ) )
	{
#ifdef _DEBUG
		cout << "Filename fixed\n";
#endif
		m_Filename += format;
	}
}
string CBMP::GetFilename ( )
{
	return m_Filename;
}
void CBMP::ShowInfo ( )
{
	if ( m_bHeadersLoad )
	{
		cout << "Resolution : " << m_sInfoHeader.biWidth << "x" << m_sInfoHeader.biHeight << " \\ bit depth: " << m_sInfoHeader.biBitCount << endl;
		cout << "BITMAPFILEHEADER\n";
		cout << "\tOffBits: " << m_sFileHeader.bfOffBits << endl;
		cout << "\tReserved1: " << m_sFileHeader.bfReserved1 << endl;
		cout << "\tReserved2: " << m_sFileHeader.bfReserved2 << endl;
		cout << "\tSize: " << m_sFileHeader.bfSize << endl;
		cout << "\tType: " << m_sFileHeader.bfType << endl;
		cout << "BITMAPINFOHEADER\n";
		cout << "\tBitCount: " << m_sInfoHeader.biBitCount << endl;
		cout << "\tClrImportant: " << m_sInfoHeader.biClrImportant << endl;
		cout << "\tClrUsed: " << m_sInfoHeader.biClrUsed << endl;
		cout << "\tCompression: " << m_sInfoHeader.biCompression << endl;
		cout << "\tHeight: " << m_sInfoHeader.biHeight << endl;
		cout << "\tWidth: " << m_sInfoHeader.biWidth << endl;
		cout << "\tPlanes: " << m_sInfoHeader.biPlanes << endl;
		cout << "\tSize: " << m_sInfoHeader.biSize << endl;
		cout << "\tSizeImage: " << m_sInfoHeader.biSizeImage << endl;
		cout << "\tXPelsPerMeter: " << m_sInfoHeader.biXPelsPerMeter << endl;
		cout << "\tYPelsPerMeter: " << m_sInfoHeader.biYPelsPerMeter << endl;
	}
	else
	{
		cout << "File is empty\n";
	}
}
void CBMP::LoadFile ( string &filename )
{
	m_Filename = filename;
	FilenameCheck ( string ( ".bmp" ) );
	CBMP::LoadFile ( );
}
void CBMP::AddToFilename ( string &append )
{
	if ( strstr ( m_Filename.c_str ( ) ,".bmp" ) )
	{
#ifdef _DEBUG
		cout << "Adding\n";
#endif
		m_Filename.erase ( m_Filename.end ( ) - 4 ,m_Filename.end ( ) );
	}
	m_Filename += append;
	FilenameCheck ( string ( ".bmp" ) );
}
void CBMP::LoadFile ( )
{
	try
	{
		m_fstFileInput.open ( m_Filename ,ios::in | ios::binary );
		if ( m_fstFileInput.is_open ( ) )
		{
#ifdef _DEBUG
			cout << "File : " << m_Filename << " is opened, reading...\n";
#endif
			m_fstFileInput.read ( reinterpret_cast< char* >( &m_sFileHeader ) ,sizeof ( BITMAPFILEHEADER ) );
			if ( m_sFileHeader.bfType != 'MB' )
			{
				throw runtime_error ( "Error occured! This is not valid bmp file!\n" );
			}
			m_fstFileInput.read ( reinterpret_cast< char* >( &m_sInfoHeader ) ,sizeof ( BITMAPINFOHEADER ) );
			m_bHeadersLoad = true;
		}
		else
		{
			throw runtime_error ( string ( "Error! Couldn't open file : " ) + m_Filename );
		}
	}
	catch ( runtime_error &err )
	{
		err.what ( );
	}
}
void CBMP::SetName ( string &filename )
{
	m_Filename = filename;
	FilenameCheck ( string ( ".bmp" ) );
}
void CBMP::SetFileHeader ( BITMAPFILEHEADER &FileHeader )
{
	m_sFileHeader = FileHeader;
}
void CBMP::SetInfoHeader ( BITMAPINFOHEADER &InfoHeader )
{
	m_sInfoHeader = InfoHeader;
}
void CBMP::SaveFile ( string &filename )
{
	m_Filename = filename;
	FilenameCheck ( string ( ".bmp" ) );
	CBMP::SaveFile ( );
}
void CBMP::SaveFile ( )
{
	try
	{
		m_fstFileOutput.open ( m_Filename ,ios::out | ios::binary );
		if ( m_fstFileOutput.is_open ( ) && m_bHeadersLoad )
		{
#ifdef _DEBUG
			cout << m_Filename << " - Writing headers...\n";
#endif
			m_fstFileOutput.write ( reinterpret_cast< char* >( &m_sFileHeader ) ,sizeof ( BITMAPFILEHEADER ) );
			m_fstFileOutput.write ( reinterpret_cast< char* >( &m_sInfoHeader ) ,sizeof ( BITMAPINFOHEADER ) );
		}
		else
		{
			throw runtime_error ( "Error! Couldn't open file : " + m_Filename );
		}
	}
	catch ( runtime_error &err )
	{
		err.what ( );
	}
}
BITMAPFILEHEADER CBMP::GetFileHeader ( )
{
	return m_sFileHeader;
}
BITMAPINFOHEADER CBMP::GetInfoHeader ( )
{
	return m_sInfoHeader;
}
void CBMP::Resize ( unsigned height ,unsigned Width )
{
}
