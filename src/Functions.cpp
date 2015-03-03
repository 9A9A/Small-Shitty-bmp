#include "BMP.h"
double Correlation ( CMatrix2D<int> &lhs ,CMatrix2D<int> &rhs )
{
	assert ( lhs.size ( ) == rhs.size ( ) );
	vector<double> multiply ( rhs.size ( ) );
	double ExpVal_lhs = ExpectedValue ( lhs.get_all ( ) );
	double ExpVal_rhs = ExpectedValue ( rhs.get_all ( ) );
	for ( auto i = 0; i<multiply.size(); i++ )
	{
		multiply[ i ] = ( lhs[ i ] - ExpVal_lhs )*( rhs[ i ] - ExpVal_rhs );
	}
	return ( ExpectedValue ( multiply ) / ( MeanSquareDisplacement ( lhs )*MeanSquareDisplacement ( rhs ) ));
}
double MeanSquareDisplacement ( CMatrix2D<int> &obj )
{
	assert ( obj.size ( ) > 0 );
	double MeanVal = ExpectedValue ( obj.get_all() );
	double Summary = 0;
	for ( auto i = 0; i < obj.size();i++ )
	{
		Summary  += pow ( obj[ i ] - MeanVal ,2 )  ;
	}
	double Size = 1.0f / static_cast<double>(( ( obj.get_size ( ).m_First - 1 )*obj.get_size ( ).m_Second ));
	return sqrt ( Size * Summary );
}
double PSNR ( CMatrix2D<int> &lhs ,CMatrix2D<int> &rhs )
{
	assert ( lhs.size ( ) == rhs.size ( ) );
	double MSE = 0;
	for ( auto i = 0; i < lhs.size ( ); i++ )
	{
		MSE += pow ( lhs[ i ] - rhs[ i ] ,2 );
	}
	MSE *= ( 1.0 / static_cast< double >( lhs.get_size ( ).m_First*lhs.get_size ( ).m_Second ) );
	return ( 10.0 * log10 (( pow ( 255.0 ,2 ) ) / MSE));
}
void PSNR_PIC ( CBMP &lhs ,CBMP &rhs )
{
	assert ( ( lhs.GetHeight() == rhs.GetHeight ( ) ) && ( lhs.GetWidth ( ) == rhs.GetWidth ( ) ) );
	if ( &lhs == &rhs )
	{
		cout << "This is lossy image PSNR cannot be computed!\n";
	}
	else
	{
		cout << lhs.GetFilename ( ) << " - " << rhs.GetFilename ( ) << " Red Channel PSNR  dB : " << PSNR ( lhs.GetComponentPixmap ( Red ) ,rhs.GetComponentPixmap ( Red ) ) << endl;
		cout << lhs.GetFilename ( ) << " - " << rhs.GetFilename ( ) << " Green Channel PSNR  dB : " << PSNR ( lhs.GetComponentPixmap ( Green ) ,rhs.GetComponentPixmap ( Green ) ) << endl;
		cout << lhs.GetFilename ( ) << " - " << rhs.GetFilename ( ) << " Blue Channel PSNR  dB : " << PSNR ( lhs.GetComponentPixmap ( Blue ) ,rhs.GetComponentPixmap ( Blue ) ) << endl;
	}
}

void Autocorrelation ( int y_offset ,unsigned step_by_x ,CBMP &image )
{
	vector<CMatrix2D<int>> color_vec;
	color_vec.push_back ( image.GetComponentPixmap ( Red ) );
	color_vec.push_back ( image.GetComponentPixmap ( Green ) );
	color_vec.push_back ( image.GetComponentPixmap ( Blue ) );
	int y_size = image.GetHeight ( );
	y_size /= 4;
	int x_size = image.GetWidth ( );
	x_size /= 4;
	fstream outputStream ( image.GetFilename ( ) + "_" + to_string ( y_offset ) + "y.txt" ,ios::out );
	for ( auto i = 0; i < 3; i++ )
	{
		vector<int> temp_2 = color_vec[ i ].get_all ( );
		for ( int j = -1 * y_size ; j < y_size ; j += 5 )
		{
			for ( int k = -1 * x_size; k < x_size; k += step_by_x )
			{
				int offset = j * image.GetWidth ( ) + k;
				vector<int> temp;
				if ( offset < 0 )
				{
					for ( auto it = temp_2.end ( ) - abs ( offset ); it != temp_2.end ( ); ++it )
					{
						temp.push_back ( *it );
					}
					for ( auto it = temp_2.begin ( ); it != temp_2.end ( ) - abs(offset); ++it )
					{
						temp.push_back ( *it );
					}
				}
				else
				{
					for ( auto it = temp_2.begin ( ) + abs ( offset ); it != temp_2.end ( ); ++it )
					{
						temp.push_back ( *it );
					}
					for ( auto it = temp_2.begin ( ); it != temp_2.begin() + abs ( offset ); ++it )
					{
						temp.push_back ( *it );
					}
				}
				outputStream << Correlation ( CMatrix2D<int> ( temp ) ,color_vec[ i ] ) << "\t";
			}
			outputStream << endl;
		}
		outputStream << endl;
	}
	outputStream.close ( );
}
void ComputeAutocorrelation ( BMP24 &image ,unsigned step_by_x )
{
	thread a1 ( Autocorrelation ,-10 ,step_by_x ,image ) ;
	thread a2 ( Autocorrelation ,-5 ,step_by_x ,image );
	thread a3 ( Autocorrelation ,0 ,step_by_x ,image );
	thread a4 ( Autocorrelation ,5 ,step_by_x ,image );
	thread a5 ( Autocorrelation ,10 ,step_by_x ,image );
	a1.join ( );
	a2.join ( );
	a3.join ( );
	a4.join ( );
	a5.join ( );
}
double Entropy ( CMatrix2D<int> &mtrx )
{
	assert ( mtrx.size ( )>0 );
	vector<double> values ( 256 ,0 );
	double ImageSize = mtrx.get_size ( ).m_First*mtrx.get_size ( ).m_Second;
	double Summary = 0;
	int counter = 0;
	for ( auto &i : mtrx )
	{
		values[ i ]++;
	}
	for ( auto &i : values )
	{
		if ( i != 0 )
		{
			Summary += ( i / ImageSize ) * log2 ( i / ImageSize );
		}
	}
	return Summary * ( -1 );
}
void ShowEntropy ( CBMP &image )
{
	cout << image.GetFilename ( ) + " - Entropy R: " << Entropy ( image.GetComponentPixmap ( Red ) ) << endl;
	cout << image.GetFilename ( ) + " - Entropy G: " << Entropy ( image.GetComponentPixmap ( Green ) ) << endl;
	cout << image.GetFilename ( ) + " - Entropy B: " << Entropy ( image.GetComponentPixmap ( Blue ) ) << endl;
}
void ShowCorrelation ( CBMP &lhs ,CBMP &rhs )
{
	cout << lhs.GetFilename ( ) + " - " + rhs.GetFilename ( ) + " - Correlation ( R - R ) : " << Correlation ( lhs.GetComponentPixmap ( Red ) ,rhs.GetComponentPixmap ( Red ) ) << endl;
	cout << lhs.GetFilename ( ) + " - " + rhs.GetFilename ( ) + " - Correlation ( G - G ) : " << Correlation ( lhs.GetComponentPixmap ( Green ) ,rhs.GetComponentPixmap ( Green ) ) << endl;
	cout << lhs.GetFilename ( ) + " - " + rhs.GetFilename ( ) + " - Correlation ( B - B ) : " << Correlation ( lhs.GetComponentPixmap ( Blue ) ,rhs.GetComponentPixmap ( Blue ) ) << endl;
}
void DPCM_Encoder ( unsigned Mode ,BMP24 &image )
{
	CMatrix2D<int> R = image.GetComponentPixmap ( Red );
	CMatrix2D<int> G = image.GetComponentPixmap ( Green );
	CMatrix2D<int> B = image.GetComponentPixmap ( Blue );
	R.DPCM ( Mode );
	G.DPCM ( Mode );
	B.DPCM ( Mode );
	auto func =  [Mode](CMatrix2D<int> &obj,string &filename) -> void
	{
			fstream newoutputstream ( filename + "_" + to_string ( Mode ) + "_mode.txt",ios::out );
			vector<int> newvec (512,0);
			for ( auto &j : obj )
			{
				newvec[ j + 255 ]++;
			}
			for ( auto k = 0; k < newvec.size ( ); k++ )
			{
				newoutputstream << k-255 << "\t";
			}
			newoutputstream << endl;
			for ( auto &j : newvec )
			{
				newoutputstream << j << "\t";
			}
			newoutputstream.close ( );
	};
	func ( R ,image.GetFilename ( ) );
	func ( G ,image.GetFilename ( ) );
	func ( B ,image.GetFilename ( ) );
	auto entropy = [] ( CMatrix2D<int> &a )
	{
		assert ( a.size ( )>0 );
		vector<double> values ( 512 ,0 );
		double ImageSize = a.size ( );
		double Summary = 0;
		int counter = 0;
		for ( auto &i : a )
		{
			values[ i+255 ]++;
		}
		for ( auto &i : values )
		{
			if ( i != 0 )
			{
				Summary += ( i / ImageSize ) * log2 ( i / ImageSize );
			}
		}
		return Summary * ( -1 );
	};
	cout << "DPCM Red Channel Entropy : " << entropy ( R ) << endl;
	cout << "DPCM Green Channel Entropy : " << entropy ( G ) << endl;
	cout << "DPCM Blue Channel Entropy : " << entropy ( B ) << endl;
}
