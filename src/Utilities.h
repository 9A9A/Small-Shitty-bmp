#include <iostream>
#include <vector>
#include <ctime>
#include <functional>
#include <assert.h>
using namespace std;
#pragma once
#define _Type template<typename _Ty>
#define abstract_class class
enum bit_depth
{
	bit_depth_1 = 1 ,
	bit_depth_2 = 2 ,
	bit_depth_4 = 4 ,
	bit_depth_8 = 8 ,
	bit_depth_16 = 16 ,
	bit_depth_24 = 24 ,
	bit_depth_32 = 32 ,
	bit_depth_64 = 64 ,
	bit_depth_128 = 128
};
enum Color
{
	Red = 0 ,
	Green = 1 ,
	Blue = 2
};
enum DPCM_Mode
{
	Left = 0,
	Top = 1,
	TopLeft = 2,
	Average_Neib = 3
};
enum Decimation_ratio
{
	None = 0,
	Double = 2,
	Quad = 4
};
enum Decimation_Type
{
	Direct_point = 0 ,
	Average_value = 1
};
struct rgbD
{
	short Red;
	short Green;
	short Blue;
	explicit rgbD ( const RGBTRIPLE &obj ) : Red ( obj.rgbtRed ) ,Green ( obj.rgbtGreen ) ,Blue ( obj.rgbtBlue )
	{
	};
	rgbD ( int A ,int B ,int C ) : Red ( A ) ,Green ( B ) ,Blue ( C )
	{
	};
	rgbD ( ) : Red ( 0 ) ,Green ( 0 ) ,Blue ( 0 )
	{
	};
	void destroy_component ( int component)
	{
		switch ( component )
		{
			case 0:
				Blue = 0;
				Green = 0;
				break;
			case 1:
				Red = 0;
				Blue = 0;
				break;
			case 2:
				Red = 0;
				Green = 0;
				break;
			default:
				break;
		}
	}
	rgbD &operator = ( double in)
	{
		Red = in;
		Blue = in;
		Green = in;
		return *this;
	}
	friend rgbD operator + ( const rgbD &lhs ,const rgbD &rhs )
	{
		return rgbD ( lhs.Red + rhs.Red ,lhs.Green + rhs.Green ,lhs.Blue + rhs.Blue );
	}
	friend rgbD operator / ( const rgbD &lhs ,const int rhs )
	{
		return rgbD ( lhs.Red / rhs ,lhs.Green / rhs ,lhs.Blue / rhs );
	}
	friend ostream &operator << ( ostream &os ,const rgbD &obj )
	{
		os << "(" << ( int ) obj.Red << "," << ( int ) obj.Green << "," << ( int ) obj.Blue << ")";
		return os;
	}
	operator RGBTRIPLE()
	{
		return RGBTRIPLE{ static_cast<BYTE>( Blue ) ,static_cast<BYTE>( Green ) ,static_cast<BYTE>( Red ) };
	}
};
_Type _Ty AVG ( vector<_Ty> &list )
{
	_Ty temp ( );
	for ( auto &i : list )
	{
		temp += i;
	}
	return temp;
}
struct rgbA
{
	double Red;
	double Green;
	double Blue;
	explicit rgbA ( const RGBTRIPLE &obj )
	{
		*this = static_cast<rgbA>(static_cast< rgbD >( obj ));
	};
	rgbA ( const rgbD &obj ) : Red ( static_cast< double >( obj.Red ) / 256 ) ,Green ( static_cast< double >( obj.Green ) / 256 ) ,Blue ( static_cast< double >( obj.Blue ) / 256 )
	{
	};
	rgbA ( double A ,double B ,double C ) : Red ( A ) ,Green ( B ) ,Blue ( C )
	{
	};
	rgbA ( ) : Red ( 0 ) ,Green ( 0 ) ,Blue ( 0 )
	{
	};
	friend ostream &operator << ( ostream &os ,const rgbA &obj )
	{
		os << "(" << obj.Red << "," << obj.Green << "," << obj.Blue << ")";
		return os;
	}
};
inline int linewidth_calc ( int width )
{
	return ( ( width*sizeof ( RGBTRIPLE ) ) % 4 == 0 ) ? ( width*sizeof ( RGBTRIPLE ) ) : ( ( 4 - ( ( width*sizeof ( RGBTRIPLE ) ) % 4 ) ) + width*sizeof ( RGBTRIPLE ) );
}
inline void check_bounds ( short &value )
{
	( value > 255 ) ? value = 255 : value;
	( value < 0 ) ? value = 0 : value;
}
inline void check_bounds ( int &value )
{
	( value > 255 ) ? value = 255 : value;
	( value < 0 ) ? value = 0 : value;
}
_Type struct point
{
	_Ty m_First;
	_Ty m_Second;
};
//_Type struct mtrxinit
//{
//	initializer_list<_Ty> mtrx_initlist;
//};
_Type class CMatrix2D // basic matrix and operations
{
private:
	_Ty abs ( _Ty );
	unsigned m_uRowCount;
	unsigned m_uColumnCount;
	vector<_Ty> m_data;
	void swap ( CMatrix2D<_Ty> &src );
public:

	CMatrix2D<_Ty> ( ); // default 0 element matrix
	CMatrix2D<_Ty> ( const CMatrix2D<_Ty> & ); // copy constructor
	CMatrix2D<_Ty> ( CMatrix2D<_Ty> && ); // move constructor
	CMatrix2D<_Ty> ( unsigned Rows ,unsigned Column ); // Row x Column 0 valued matrix
	CMatrix2D<_Ty> ( unsigned Rows ,unsigned Column ,_Ty value ); // Row x Column matrix with all values = Value;
	CMatrix2D<_Ty> ( initializer_list<_Ty> list ); // build one-line matrix
	//CMatrix2D<_Ty> ( initializer_list<mtrxinit<_Ty>> list );
	CMatrix2D<_Ty> ( vector<_Ty> &vec ); // build one-line matrix
	CMatrix2D<_Ty> ( vector<_Ty> &vec ,unsigned Rows ,unsigned Column );
	CMatrix2D<_Ty> ( _Ty value ); // 1x1 matrix;
	~CMatrix2D<_Ty> ( );


	//basic functions
	auto begin ( ) -> decltype( m_data.begin ( ) )
	{
		return m_data.begin ( );
	}
	auto end ( ) -> decltype( m_data.end ( ) )
	{
		return m_data.end ( );
	}
	auto operator[]( int i ) -> decltype( m_data[i] )
	{
		return m_data[ i ];
	}
	void for_each ( function<void ( int & )> f )
	{
		for ( auto &i : m_data )
		{
			f ( i );
		}
	}
	bool isSquare ( ); // if matrix size = n x n returns true, else false;
	void clear ( );	 // clear matrix
	void fill ( _Ty value ); // fill matrix with value
	void fill_rnd ( );
	void set ( unsigned row ,unsigned column ,_Ty value ); // set value
	void resize ( unsigned new_row ,unsigned new_column ); // resize matrix
	void remove_row ( unsigned row ); // remove row
	void remove_column ( unsigned column ); // remove_column
	void insert_row ( const vector<_Ty> &vec ,unsigned row ); // adding new row to matirx (increase size matrix by 1)
	void insert_column ( const vector<_Ty> &vec ,unsigned column ); // adding new column to matrix (increase size matrix by 1)
	void replace_row ( const vector<_Ty> &vec ,unsigned row );
	void replace_column ( const vector<_Ty> &vec ,unsigned column );
	void reverse_row ( unsigned row );
	void reverse_rows_all ( );
	void reverse_column ( unsigned column );
	void reverse_column_all ( );
	void transpose ( );
	void normalize ( );
	void decimation (unsigned ratio,bool type);
	void upscaling ( unsigned ratio );
	void y_axis_shift ( int y );
	void x_axis_shift ( int x );
	void DPCM ( unsigned Mode );
	vector<_Ty> get_row ( unsigned row );
	vector<_Ty> get_column ( unsigned column );
	vector<_Ty> get_all ( );
	_Ty *get_max ( );
	point<_Ty> get_max_pos ( );
	_Ty *get_min ( );
	point<_Ty> get_min_pos ( );
	_Ty *at ( unsigned row ,unsigned column );
	point<unsigned> get_size ( );
	unsigned size ( );
	void get_memory_size ( );
	//static functions
	static CMatrix2D<_Ty> Hadamard ( const CMatrix2D<_Ty> &lhs ,const CMatrix2D<_Ty> &rhs );

	//operators
	CMatrix2D<_Ty> & operator = ( const CMatrix2D<_Ty> & );
	CMatrix2D<_Ty> & operator = ( CMatrix2D<_Ty> && );
	_Type friend ostream & operator << ( ostream & ,const CMatrix2D<_Ty> & );
	_Type friend CMatrix2D<_Ty> operator + ( const CMatrix2D<_Ty> & ,const _Ty );
	_Type friend CMatrix2D<_Ty> operator + ( const CMatrix2D<_Ty> & ,const CMatrix2D<_Ty> & );
	_Type friend CMatrix2D<_Ty> operator - ( const CMatrix2D<_Ty> & ,const _Ty );
	_Type friend CMatrix2D<_Ty> operator - ( const CMatrix2D<_Ty> & ,const CMatrix2D<_Ty> & );
	_Type friend CMatrix2D<_Ty> operator * ( const CMatrix2D<_Ty> & ,const _Ty );
	_Type friend CMatrix2D<_Ty> operator * ( const CMatrix2D<_Ty> & ,const CMatrix2D<_Ty> & );
	_Type friend CMatrix2D<_Ty> operator / ( const CMatrix2D<_Ty> & ,const _Ty );
	
	
	_Ty& operator ()( unsigned,unsigned );
	operator vector<_Ty> ( );// vector<_Ty> cast operator
	//_Type friend CMatrix2D<_Ty> operator / ( const CMatrix2D<_Ty> & ,const CMatrix2D<_Ty> & ); it's not implemented yet TO DO : calculating determinant func
	//inline functions
	bool bSizeEqual ( const CMatrix2D<_Ty> &,const CMatrix2D<_Ty> & );
	bool bSize ( unsigned row ,unsigned column );
};
_Type CMatrix2D<_Ty>::CMatrix2D ( )
{
	m_uRowCount = 0;
	m_uColumnCount = 0;
}
//_Type CMatrix2D<_Ty>::CMatrix2D ( initializer_list<mtrxinit<_Ty>> list )
//{
//	for ( auto &i : list )
//	{
//		if ( i.mtrx_initlist.size ( ) )
//	}
//}
_Type CMatrix2D<_Ty>::CMatrix2D ( const CMatrix2D<_Ty> &obj )
{
	m_uRowCount = obj.m_uRowCount;
	m_uColumnCount = obj.m_uColumnCount;
	m_data = obj.m_data;
}
_Type CMatrix2D<_Ty>::CMatrix2D ( unsigned Rows ,unsigned Column ) : m_uRowCount ( Rows ) ,m_uColumnCount ( Column )
{
	vector<_Ty> tmp ( Rows*Column );
	m_data = tmp;
}
_Type CMatrix2D<_Ty>::CMatrix2D ( unsigned Rows ,unsigned Column ,_Ty value ) : m_uRowCount ( Rows ) ,m_uColumnCount ( Column )
{
	vector<_Ty> tmp ( Rows*Column ,value );
	m_data = tmp;
}
_Type CMatrix2D<_Ty>::CMatrix2D ( _Ty value ) : m_uRowCount ( 1 ) ,m_uColumnCount ( 1 )
{
	m_data.push_back ( value );
}

_Type CMatrix2D<_Ty>::CMatrix2D ( initializer_list<_Ty> list )
{
	for ( auto &i : list )
	{
		m_data.push_back ( i );
	}
	m_uColumnCount = m_data.size ( );
	m_uRowCount = 1;
}
_Type CMatrix2D<_Ty>::CMatrix2D ( vector<_Ty> &vec )
{
	m_data = vec;
	if ( (m_data.size ( ) % 2 == 0) && m_data.size() > 2 )
	{
		m_uColumnCount = m_data.size ( )/2;
		m_uRowCount = 2;
	}
	else
	{
		m_uColumnCount = m_data.size ( );
		m_uRowCount = 1;
	}
}
_Type CMatrix2D<_Ty>::CMatrix2D ( vector<_Ty> &vec ,unsigned Row ,unsigned Column )
{
	try
	{
		if ( ( Row * Column ) == vec.size ( ) )
		{
			m_uRowCount = Row;
			m_uColumnCount = Column;
			m_data = vec;
		}
		else
		{
			throw runtime_error ( "Object creation error : vec size mismatch!\n" );
		}
	}
	catch ( runtime_error &err )
	{
		err.what ( );
	}
}
_Type CMatrix2D<_Ty>::CMatrix2D ( CMatrix2D<_Ty> &&src )
{
	this->m_data = src.m_data;
	this->m_uColumnCount = src.m_uColumnCount;
	this->m_uRowCount = src.m_uRowCount;
	src.m_data.clear ( );
	src.m_uColumnCount = 0;
	src.m_uRowCount = 0;
}
_Type void CMatrix2D<_Ty>::swap ( CMatrix2D<_Ty> &src )
{
	std::swap ( this->m_uColumnCount ,src.m_uColumnCount );
	std::swap ( this->m_uRowCount ,src.m_uRowCount );
	std::swap ( this->m_data ,src.m_data );
}
_Type CMatrix2D<_Ty>& CMatrix2D<_Ty>::operator= ( const CMatrix2D<_Ty> &obj )
{
	if ( this != &obj )
	{
		this->swap ( CMatrix2D<_Ty> ( obj ) );
	}
	return *this;
}
_Type CMatrix2D<_Ty>& CMatrix2D<_Ty>::operator=( CMatrix2D<_Ty> &&obj )
{
	if ( this != &obj )
	{
		this->m_data.clear ( );
		this->m_data = obj.m_data;
		this->m_uColumnCount = obj.m_uColumnCount;
		this->m_uRowCount = obj.m_uRowCount;
		obj.m_data.clear ( );
		obj.m_uColumnCount = 0;
		obj.m_uRowCount = 0;
	}
	return *this;
}
_Type void CMatrix2D<_Ty>::clear ( )
{
	m_uColumnCount = 0;
	m_uRowCount = 0;
	m_data.clear ( );
}
_Type CMatrix2D<_Ty>::~CMatrix2D ( )
{
	this->clear ( );
}
_Type void CMatrix2D<_Ty>::fill ( _Ty value )
{
	for ( auto &i : m_data )
	{
		i = value;
	}
}
_Type ostream &operator <<( ostream &os ,const CMatrix2D<_Ty> &obj )
{
	for ( unsigned i = 0; i < obj.m_uRowCount; i++ )
	{
		for ( unsigned j = 0; j < obj.m_uColumnCount; j++ )
		{
			os << obj.m_data[ i*obj.m_uColumnCount + j ] << " ";
		}
		os << endl;
	}
	os << endl;
	return os;
}
_Type void CMatrix2D<_Ty>::resize ( unsigned uiNewrow ,unsigned uiNewcolumn )
{
	try
	{
		if ( uiNewcolumn > 0 && uiNewrow > 0 )
		{
			if ( this->m_uColumnCount == 0 && this->m_uRowCount == 0 )
			{
				m_data.resize ( uiNewcolumn*uiNewrow );
			}
			else
			{
				vector<_Ty> tmp;
				unsigned pos = 0;
				if ( uiNewrow <= this->m_uRowCount && uiNewcolumn <= this->m_uColumnCount )
				{
					for ( unsigned i = 0; i < m_uRowCount; i++ )
					{
						for ( unsigned j = 0; j < uiNewcolumn; j++ )
						{
							tmp.push_back ( this->m_data[ pos++ ] );
						}
						pos += m_uColumnCount - uiNewcolumn;
					}
					vector<_Ty>::iterator it = tmp.begin ( ) + uiNewrow*uiNewcolumn;
					tmp.erase ( it ,tmp.end ( ) );
				}
				if ( uiNewrow > this->m_uRowCount && uiNewcolumn > this->m_uColumnCount )
				{
					for ( unsigned i = 0; i < m_uRowCount; i++ )
					{
						for ( unsigned j = 0; j < uiNewcolumn; j++ )
						{
							( j < m_uColumnCount ) ? tmp.push_back ( this->m_data[ pos++ ] ) : tmp.push_back ( _Ty() );
						}
					}
					for ( unsigned i = m_uRowCount*uiNewcolumn; i < uiNewcolumn*uiNewrow; i++ )
					{
						tmp.push_back ( _Ty() );
					}
				}
				if ( uiNewrow > this->m_uRowCount && uiNewcolumn <= this->m_uColumnCount )
				{
					for ( unsigned i = 0; i < m_uRowCount; i++ )
					{
						for ( unsigned j = 0; j < uiNewcolumn; j++ )
						{
							tmp.push_back ( this->m_data[ pos++ ] );
						}
						pos += m_uColumnCount - uiNewcolumn;
					}
					for ( unsigned i = m_uRowCount*uiNewcolumn; i < uiNewcolumn*uiNewrow; i++ )
					{
						tmp.push_back ( _Ty() );
					}
				}
				if ( uiNewrow <= this->m_uRowCount && uiNewcolumn > this->m_uColumnCount )
				{
					for ( unsigned i = 0; i < m_uRowCount; i++ )
					{
						for ( unsigned j = 0; j < uiNewcolumn; j++ )
						{
							( j < m_uColumnCount ) ? tmp.push_back ( this->m_data[ pos++ ] ) : tmp.push_back ( _Ty() );
						}
					}
				}
				this->m_data = tmp;
			}
			this->m_uColumnCount = uiNewcolumn;
			this->m_uRowCount = uiNewrow;
		}
		else
		{
			throw runtime_error ( "Warning ! Attemp to resize to zero size! Resizing failed" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type _Ty &CMatrix2D<_Ty>::operator()(unsigned y,unsigned x)
{
	assert ( y < m_uRowCount && x < m_uColumnCount );
	return m_data[ y*m_uColumnCount + x ];
}
_Type void CMatrix2D<_Ty>::set ( unsigned row ,unsigned column ,_Ty value )
{
	try
	{
		if ( bSize ( row ,column ) )
		{
			m_data[ row * m_uColumnCount + column ] = value;
		}
		else
		{
			throw runtime_error ( "Warning ! Out of range! Modification isn't possible." );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type void CMatrix2D<_Ty>::fill_rnd ( )
{
	srand ( time ( NULL ) );
	for ( auto &i : m_data )
	{
		i = rand ( ) % ( m_data.size ( ) * 10 );
	}
}
_Type _Ty *CMatrix2D<_Ty>::get_max ( )
{
	try
	{
		if ( m_data.size ( ) )
		{
			_Ty *max = &m_data[ 0 ];
			for ( auto &i : m_data )
			{
				if ( i > *max )
				{
					max = &i;
				}
			}
			return max;
		}
		else
		{
			throw runtime_error ( "Fatal error! Empty Matrix" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type _Ty *CMatrix2D<_Ty>::get_min ( )
{
	try
	{
		if ( m_data.size ( ) )
		{
			_Ty *min = &m_data[ 0 ];
			for ( auto &i : m_data )
			{
				if ( i < *min )
				{
					min = &i;
				}
			}
			return min;
		}
		else
		{
			throw runtime_error ( "Fatal error! Empty Matrix" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type point<_Ty> CMatrix2D<_Ty>::get_max_pos ( )
{
	try
	{
		point<_Ty> tmp{ 0 ,0 };
		if ( m_data.size ( ) )
		{
			_Ty *max = &m_data[ 0 ];
			for ( unsigned i = 0; i < m_uRowCount; i++ )
			{
				for ( unsigned j = 0; j < m_uColumnCount; j++ )
				{
					if ( m_data[ i*m_uColumnCount + j ] > *max )
					{
						max = &m_data[ i*m_uColumnCount + j ];
						tmp.m_First = i;
						tmp.m_Second = j;
					}
				}
			}
			max = nullptr;
			delete max;
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Empty matrix!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type point<_Ty> CMatrix2D<_Ty>::get_min_pos ( )
{
	try
	{
		point<_Ty> tmp{ 0 ,0 };
		if ( m_data.size ( ) )
		{
			_Ty *min = &m_data[ 0 ];
			for ( unsigned i = 0; i < m_uRowCount; i++ )
			{
				for ( unsigned j = 0; j < m_uColumnCount; j++ )
				{
					if ( m_data[ i*m_uColumnCount + j ] < *min )
					{
						min = &m_data[ i*m_uColumnCount + j ];
						tmp.m_First = i;
						tmp.m_Second = j;
					}
				}
			}
			min = nullptr;
			delete min;
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Empty matrix!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type _Ty *CMatrix2D<_Ty>::at ( unsigned row ,unsigned column )
{
	try
	{
		_Ty *tmp = nullptr;
		if ( bSize ( row ,column ) )
		{
			tmp = &m_data[ row * m_uColumnCount + column ];
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Out of range! Modification isn't possible." );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type unsigned CMatrix2D<_Ty>::size ( )
{
	return m_data.size ( );
}
_Type inline bool CMatrix2D<_Ty>::bSize ( unsigned row ,unsigned column )
{
	if ( row < m_uRowCount && column < m_uColumnCount )
	{
		return true;
	}
	else
	{
		return false;
	}
}
_Type inline bool bSizeEqual ( const CMatrix2D<_Ty> &lhs ,const CMatrix2D<_Ty> &rhs )
{
	if ( lhs.m_uColumnCount == rhs.m_uColumnCount && lhs.m_uRowCount == rhs.m_uRowCount )
	{
		return true;
	}
	else
	{
		return false;
	}
}
_Type vector<_Ty> CMatrix2D<_Ty>::get_row ( unsigned row )
{
	try
	{
		vector<_Ty> tmp;
		if ( bSize ( row ,1 ) )
		{
			for ( unsigned i = row*m_uColumnCount; i < ( row + 1 )*m_uColumnCount; i++ )
			{
				tmp.push_back ( m_data[ i ] );
			}
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Out of range!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type vector<_Ty> CMatrix2D<_Ty>::get_column ( unsigned column )
{
	try
	{
		vector<_Ty> tmp;
		if ( bSize ( 1 ,column ) )
		{
			for ( unsigned i = 0; i < m_uRowCount; i++ )
			{
				tmp.push_back ( m_data[ i*m_uColumnCount + column ] );
			}
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Out of range!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type vector<_Ty> CMatrix2D<_Ty>::get_all ( )
{
	return m_data;
}
_Type CMatrix2D<_Ty> CMatrix2D<_Ty>::Hadamard ( const CMatrix2D<_Ty> &lhs ,const CMatrix2D<_Ty> &rhs )
{
	try
	{
		if ( lhs.m_uColumnCount == rhs.m_uColumnCount && lhs.m_uRowCount == rhs.m_uRowCount )
		{
			CMatrix2D<_Ty> tmp ( lhs.m_uRowCount ,lhs.m_uColumnCount );
			for ( unsigned i = 0; i < lhs.m_data.size ( ); i++ )
			{
				tmp.m_data[ i ] = lhs.m_data[ i ] * rhs.m_data[ i ];
			}
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Matrixes size mismatch!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type CMatrix2D<_Ty> operator + ( const CMatrix2D<_Ty> &lhs ,const CMatrix2D<_Ty> &rhs )
{
	try
	{
		if ( lhs.m_uColumnCount == rhs.m_uColumnCount && lhs.m_uRowCount == rhs.m_uRowCount )
		{
			CMatrix2D<_Ty> tmp ( lhs.m_uRowCount ,lhs.m_uColumnCount );
			for ( unsigned i = 0; i < lhs.m_data.size ( ); i++ )
			{
				tmp.m_data[ i ] = lhs.m_data[ i ] + rhs.m_data[ i ] ;
			}
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Matrixes size mismatch!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type CMatrix2D<_Ty> operator + ( const CMatrix2D<_Ty> &obj ,const _Ty value )
{
	CMatrix2D<_Ty> tmp ( obj.m_uRowCount ,obj.m_uColumnCount );
	for ( unsigned i = 0; i < obj.m_data.size ( ); i++ )
	{
		tmp.m_data[ i ] = obj.m_data[ i ] + value ;
	}
	return tmp;
}
_Type CMatrix2D<_Ty> operator - ( const CMatrix2D<_Ty> &lhs ,const CMatrix2D<_Ty> &rhs )
{
	try
	{
		if ( lhs.m_uColumnCount == rhs.m_uColumnCount && lhs.m_uRowCount == rhs.m_uRowCount )
		{
			CMatrix2D<_Ty> tmp ( lhs.m_uRowCount ,lhs.m_uColumnCount );
			for ( unsigned i = 0; i < lhs.m_data.size ( ); i++ )
			{
				tmp.m_data[ i ] = lhs.m_data[ i ] - rhs.m_data[ i ] ;
			}
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Matrixes size mismatch!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}

}
_Type CMatrix2D<_Ty> operator - ( const CMatrix2D<_Ty> &obj ,const _Ty value )
{
	CMatrix2D<_Ty> tmp ( obj.m_uRowCount ,obj.m_uColumnCount );
	for ( unsigned i = 0; i < obj.m_data.size ( ); i++ )
	{
		tmp.m_data[ i ] = obj.m_data[ i ] - value ;
	}
	return tmp;
}
_Type CMatrix2D<_Ty> operator * ( const CMatrix2D<_Ty> &lhs ,const CMatrix2D<_Ty> &rhs )
{
	try
	{
		if ( lhs.m_uColumnCount == rhs.m_uRowCount )
		{
			CMatrix2D<_Ty> tmp ( lhs.m_uRowCount ,rhs.m_uColumnCount );
			for ( unsigned i = 0; i < lhs.m_uRowCount; i++ )
			{
				for ( unsigned j = 0; j < rhs.m_uColumnCount; j++ )
				{
					tmp.m_data[ i*rhs.m_uColumnCount + j ] = 0;
					for ( unsigned k = 0; k < rhs.m_uRowCount; k++ )
					{
						tmp.m_data[ i*rhs.m_uColumnCount + j ] += lhs.m_data[ i*lhs.m_uColumnCount + k ] * rhs.m_data[ k * rhs.m_uColumnCount + j ];
					}
				}
			}
			return tmp;
		}
		else
		{
			throw runtime_error ( "Fatal Error ! Matrixes size mismatch!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
		system ( "pause" );
		exit ( 1 );
	}
}
_Type CMatrix2D<_Ty> operator * ( const CMatrix2D<_Ty> &obj ,const _Ty value )
{
	CMatrix2D<_Ty> tmp ( obj.m_uRowCount ,obj.m_uColumnCount );
	for ( unsigned i = 0; i < obj.m_data.size ( ); i++ )
	{
		tmp.m_data[ i ] = obj.m_data[ i ] * value ;
	}
	return tmp;
}
_Type CMatrix2D<_Ty> operator / ( const CMatrix2D<_Ty> &obj ,const _Ty value )
{
	CMatrix2D<_Ty> tmp ( obj.m_uRowCount ,obj.m_uColumnCount );
	for ( unsigned i = 0; i < obj.m_data.size ( ); i++ )
	{
		tmp.m_data[ i ] = obj.m_data[ i ] / value;
	}
	return tmp;
}
_Type void CMatrix2D<_Ty>::insert_row ( const vector<_Ty> &vec ,unsigned row )
{
	try
	{
		if ( vec.size ( ) == m_uColumnCount && row <= m_uRowCount )
		{
			for ( unsigned i = 0; i < vec.size ( ); i++ )
			{
				m_data.insert ( m_data.begin ( ) + i + row * m_uColumnCount ,vec[ i ] );
			}
			this->m_uRowCount++;
		}
		else
		{
			throw runtime_error ( "Warning ! Insertion size mismatch ! Insertion failed!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type void CMatrix2D<_Ty>::insert_column ( const vector<_Ty> &vec ,unsigned column )
{
	try
	{
		if ( vec.size ( ) == m_uRowCount && column <= m_uColumnCount )
		{
			for ( unsigned i = 0; i < vec.size ( ); i++ )
			{
				m_data.insert ( m_data.begin ( ) + column + m_uColumnCount * i + i ,vec[ i ] );
			}
			this->m_uColumnCount++;
		}
		else
		{
			throw runtime_error ( "Warning ! Insertion size mismatch ! Insertion failed!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type void CMatrix2D<_Ty>::replace_column ( const vector<_Ty> &vec ,unsigned column )
{
	try
	{
		if ( vec.size ( ) == m_uRowCount && column < m_uColumnCount )
		{
			for ( unsigned i = 0; i < vec.size ( ); i++ )
			{
				m_data[ column + m_uColumnCount * i ] = vec[ i ];
			}
		}
		else
		{
			throw runtime_error ( "Warning ! Replace size mismatch ! Replace failed!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type void CMatrix2D<_Ty>::replace_row ( const vector<_Ty> &vec ,unsigned row )
{
	try
	{
		if ( vec.size ( ) == m_uColumnCount && row < m_uRowCount )
		{
			for ( unsigned i = 0; i < vec.size ( ); i++ )
			{
				m_data[ row * m_uColumnCount + i ] = vec[ i ];
			}
		}
		else
		{
			throw runtime_error ( "Warning ! Replace size mismatch ! Replace failed!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type void CMatrix2D<_Ty>::transpose ( )
{
	vector<_Ty> tmp ( m_uColumnCount*m_uRowCount ,0 );
	for ( unsigned i = 0; i < m_uRowCount; i++ )
	{
		for ( unsigned j = 0; j < m_uColumnCount; j++ )
		{
			std::swap ( m_data[ i*m_uColumnCount + j ] ,tmp[ j*m_uRowCount + i ] );
		}
	}
	std::swap ( tmp ,this->m_data );
	std::swap ( this->m_uRowCount ,this->m_uColumnCount );
}
_Type bool CMatrix2D<_Ty>::isSquare ( )
{
	return ( m_uColumnCount == m_uRowCount ) ? true : false;
}
_Type void CMatrix2D<_Ty>::reverse_row ( unsigned row )
{
	try
	{
		if ( row < m_uRowCount )
		{
			std::reverse ( m_data.begin ( ) + m_uColumnCount * row ,m_data.begin ( ) + m_uColumnCount * ( row + 1 ) );
		}
		else
		{
			throw runtime_error ( "Warning !Incorrect Row ID !Reverse failed!\n" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type CMatrix2D<_Ty>::operator std::vector<_Ty ,std::allocator<_Ty>> ( )
{
	return m_data;
}
_Type void CMatrix2D<_Ty>::reverse_column ( unsigned column )
{
	try
	{
		if ( column < m_uColumnCount )
		{
			for ( unsigned i = 0; i < m_uRowCount / 2; i++ )
			{
				std::swap ( m_data[ column + i*m_uColumnCount ] ,m_data[ column + ( m_uRowCount - i - 1 )*m_uColumnCount ] );
			}
		}
		else
		{
			throw runtime_error ( "Warning ! Incorrect Column ID ! Reverse failed!" );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( ) << endl;
	}
}
_Type _Ty CMatrix2D<_Ty>::abs ( _Ty value )
{
	return ( value < 0 ) ? value * ( -1 ) : value;
}
_Type void CMatrix2D<_Ty>::get_memory_size ( )
{
	cout << "Matrix size : " << m_uRowCount << " x " << m_uColumnCount << endl;
	cout << "Memory using : " << sizeof ( _Ty ) * m_data.size ( ) << " bytes\n";
}
_Type void CMatrix2D<_Ty>::reverse_column_all ( )
{
	for ( unsigned i = 0; i < m_uColumnCount; i++ )
	{
		this->reverse_column ( i );
	}
}
_Type void CMatrix2D<_Ty>::reverse_rows_all ( )
{
	for ( unsigned i = 0; i < m_uRowCount; i++ )
	{
		this->reverse_row ( i );
	}
}
_Type point<unsigned> CMatrix2D<_Ty>::get_size ( )
{
	return point < unsigned > {m_uRowCount ,m_uColumnCount};
}
_Type void CMatrix2D<_Ty>::normalize ( )
{
	try
	{
		if ( m_data.size ( ) )
		{
			_Ty abs_max = this->abs ( m_data[ 0 ] );
			_Ty tmp;
			for ( auto &i : m_data )
			{
				tmp = this->abs ( i );
				if ( tmp > abs_max )
				{
					abs_max = tmp;
				}
			}
			for ( auto &i : m_data )
			{
				i /= abs_max;
			}
		}
		else
		{
			throw runtime_error ( "Warning ! Empty matrix! " );
		}
	}
	catch ( runtime_error &err )
	{
		cout << err.what ( );
	}
}
_Type void CMatrix2D<_Ty>::remove_column ( unsigned column )
{
	try
	{
		if ( column < m_uColumnCount )
		{
			for ( auto i = 0; i < m_uRowCount; i++ )
			{
				m_data.erase ( m_data.begin() + i*m_uColumnCount + column - i );
			}
			m_uColumnCount--;
			this->get_memory_size ( );
		}
		else
		{
			throw runtime_error ( "Out of range!\n" );
		}
	}
	catch ( runtime_error &err )
	{
		err.what ( );
	}
}
_Type void CMatrix2D<_Ty>::remove_row ( unsigned row )
{
	try
	{
		if ( row < m_uRowCount )
		{
			m_data.erase ( m_data.begin ( ) + row * m_uColumnCount,m_data.begin() + (row + 1)*(m_uColumnCount) );
			m_uRowCount--;
			this->get_memory_size ( );
		}
		else
		{
			throw runtime_error ( "Out of range!\n" );
		}
	}
	catch ( runtime_error &err )
	{
		err.what ( );
	}
}
_Type void CMatrix2D<_Ty>::decimation ( unsigned ratio,bool type )
{
	try
	{
		CMatrix2D<_Ty> temp;
		int counter = 0;
		switch ( ratio )
		{
			case Double:
				temp.resize ( m_uRowCount / 2 ,m_uColumnCount / 2 );
				for ( auto i = 0; i < m_uRowCount; i += 2 )
				{
					for ( auto j = 0; j < m_uColumnCount; j += 2 )
					{
						if ( ( i + 1 < m_uRowCount ) && ( j + 1 < m_uColumnCount ) )
						{
							if ( type )
							{
								temp[ counter++ ] = ( *at ( i ,j ) + *at ( i + 1 ,j ) + *at ( i ,j + 1 ) + *at ( i + 1 ,j + 1 ) ) / 4;
							}
							else
							{
								temp[ counter++ ] = *at ( i ,j );
							}
						}
					}
				}
				*this = std::move ( temp );
				break;
			case Quad:
				temp.resize ( m_uRowCount / 4 ,m_uColumnCount / 4 );
				for ( auto i = 0; i < m_uRowCount; i += 4 )
				{
					for ( auto j = 0; j < m_uColumnCount; j += 4 )
					{
						if ( ( i + 1 < m_uRowCount ) && ( j + 1 < m_uColumnCount ) )
						{
							if ( ( i + 3 < m_uRowCount ) && ( j + 3 < m_uColumnCount ) )
							{
								if ( type )
								{
									temp[ counter++ ] = (
										*at ( i ,j ) + *at ( i ,j + 1 ) + *at ( i ,j + 2 ) + *at ( i ,j + 3 ) +
										*at ( i + 1 ,j ) + *at ( i + 1 ,j + 1 ) + *at ( i + 1 ,j + 2 ) + *at ( i + 1 ,j + 3 ) +
										*at ( i + 2 ,j ) + *at ( i + 2 ,j + 1 ) + *at ( i + 2 ,j + 2 ) + *at ( i + 2 ,j + 3 ) +
										*at ( i + 3 ,j ) + *at ( i + 3 ,j + 1 ) + *at ( i + 3 ,j + 2 ) + *at ( i + 3 ,j + 3 ) ) / 16;
								}
								else
								{
									temp[ counter++ ] = *at ( i ,j );
								}
							}
						}
					}
				}
				*this = std::move ( temp );
				break;
			default:
				throw runtime_error ( "decimation wrong ratio\n" );
				break;
		}
	}
	catch ( runtime_error &err )
	{
		err.what ( );
	}

}
_Type void CMatrix2D<_Ty>::upscaling ( unsigned ratio )
{
	assert ( ratio > 0 );
	CMatrix2D<_Ty> temp;
	int counter = 0;
	temp.resize ( m_uRowCount * ratio ,m_uColumnCount * ratio );
	for ( auto i = 0; i < m_uRowCount * ratio; i += ratio )
	{
		for ( auto j = 0; j < m_uColumnCount * ratio; j += ratio )
		{
			for ( auto k = 0; k < ratio; k++ )
			{
				for ( auto l = 0; l < ratio; l++ )
				{
					temp.set ( i + k ,j + l ,m_data[ counter ] );
				}
			}
			counter++;
		}
	}
	*this = std::move ( temp );
}
_Type void CMatrix2D<_Ty>::y_axis_shift ( int y )
{
	if ( abs ( y ) < m_uRowCount )
	{
		CMatrix2D<_Ty> t_matrix ( m_uRowCount - abs ( y ) ,m_uColumnCount );
		for ( auto i = 0; i < m_uRowCount; i++ )
		{
			for ( auto j = 0; j < m_uColumnCount; j++ )
			{
				if ( y >= 0 )
				{
					if ( t_matrix.get_size ( ).m_First > i )
					{
						t_matrix.set ( i ,j ,*at ( i ,j ) );
					}
				}
				else
				{
					if ( i >= abs ( y ) )
					{
						t_matrix.set ( i + y ,j ,*at ( i ,j ) );
					}
				}
			}
		}
		*this = move ( t_matrix );
	}
	else
	{
		*this = CMatrix2D < _Ty >() ;
	}
}
_Type void CMatrix2D<_Ty>::x_axis_shift ( int x )
{
	if ( abs ( x ) < m_uColumnCount )
	{
		CMatrix2D<_Ty> t_matrix ( m_uRowCount ,m_uColumnCount - abs ( x ) );
		for ( auto i = 0; i < m_uRowCount; i++ )
		{
			for ( auto j = 0; j < m_uColumnCount; j++ )
			{
				if ( x >= 0 )
				{
					if ( t_matrix.get_size ( ).m_Second > j )
					{
						t_matrix.set ( i ,j ,*at ( i ,j ) );
					}
				}
				else
				{
					if ( j >= abs ( x ) )
					{
						t_matrix.set ( i ,j + x ,*at ( i ,j ) );
					}
				}
			}
		}
		*this = move ( t_matrix );
	}
	else
	{
		*this = CMatrix2D<_Ty> ( );
	}
}
_Type void CMatrix2D<_Ty>::DPCM ( unsigned Mode )
{
	assert (Mode < Average_Neib + 1);
	CMatrix2D<_Ty> temp(*this);
	for ( auto i = 1; i < m_uRowCount; i++ )
	{
		for ( auto j = 1; j < m_uColumnCount; j++ )
		{
			switch ( Mode )
			{
				case Left:
							*temp.at ( i ,j ) = *at ( i ,j ) - *at ( i ,j - 1 );
					break;
				case Top:
							*temp.at ( i ,j ) = *at ( i ,j ) - *at ( i - 1 ,j );
					break;
				case TopLeft:
							*temp.at ( i ,j ) = *at ( i ,j ) - *at ( i - 1 ,j - 1 );
					break;
				case Average_Neib:
							*temp.at ( i ,j ) = *at ( i ,j ) - ( ( *at ( i - 1 ,j ) + *at ( i - 1 ,j - 1 ) + *at ( i ,j - 1 ) ) / 3 );
					break;
				default:
					break;
			}
		}
	}
	*this = move ( temp );
}