#include "BMP.h"
int main ( )
{
	CBMP *lena = LoadBMP ( string("lena") );
	CBMP *lena_1 = LoadBMP ( string ( "lena_1" ) );
	PSNR_PIC ( *lena ,*lena_1 );
	Autocorrelation ( 0 ,32 ,*lena );
	//BMP24  a ( filename );
	//Autocorrelation ( 0 ,10 ,a );
	//cout << "DPCM Lossless image \n";
	//DPCM_Encoder ( Left ,a );
	//DPCM_Encoder ( Top ,a );
	//DPCM_Encoder ( TopLeft ,a );
	//DPCM_Encoder ( Average_Neib ,a );
	//BMP24::ConvertToYCbCr ( a ,None ,Average_value );
	//BMP24::ConvertToYCbCr ( a ,Double ,Average_value );
	//BMP24::ConvertToYCbCr ( a ,Quad ,Average_value );
	//BMP24::SplitIntoColors ( a );
	//BMP24 b ( BMP24::ConvertToRGB ( BMP24 ( filename + Y_Postfix ) ,BMP24 ( filename + Cb_Postfix ) ,BMP24 ( filename + Cr_Postfix ) ) );
	//BMP24 c ( BMP24::ConvertToRGB ( BMP24 ( filename + Y_Postfix ) ,BMP24 ( filename + Cb_Postfix + "_2X" ) ,BMP24 ( filename + Cr_Postfix + "_2X" ) ) );
	//BMP24 d ( BMP24::ConvertToRGB ( BMP24 ( filename + Y_Postfix ) ,BMP24 ( filename + Cb_Postfix + "_4X" ) ,BMP24 ( filename + Cr_Postfix + "_4X" ) ) );
	//BMP24 Cb ( filename + Cb_Postfix );
	//BMP24 Cr ( filename + Cr_Postfix );
	//cout << "DPCM Cb image \n";
	//DPCM_Encoder ( Left ,Cb );
	//DPCM_Encoder ( Top ,Cb );
	//DPCM_Encoder ( TopLeft ,Cb );
	//DPCM_Encoder ( Average_Neib ,Cb );
	//cout << "DPCM Cr image \n";
	//DPCM_Encoder ( Left ,Cr );
	//DPCM_Encoder ( Top ,Cr );
	//DPCM_Encoder ( TopLeft ,Cr );
	//DPCM_Encoder ( Average_Neib ,Cr );
	//PSNR_PIC ( a ,a );
	//PSNR_PIC ( a ,b );
	//PSNR_PIC ( a ,c );
	//PSNR_PIC ( a ,d );
	//ShowCorrelation ( a ,b );
	//ShowCorrelation ( a ,c );
	//ShowCorrelation ( a ,d );
	//ShowEntropy ( a );
	//ShowEntropy ( b );
	//ShowEntropy ( c );
	//ShowEntropy ( d );
	//b.SaveFile ( );
	//c.SaveFile ( );
	//d.SaveFile ( );
	system ( "pause" );
}