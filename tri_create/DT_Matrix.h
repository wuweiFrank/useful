#ifndef _DT_MATRIX_H_
#define _DT_MATRIX_H_

template <class T> class CDT_Matrix
{
private:
	int   m_iNrows;
	int   m_iNcols; 
	T	   **m_Data;

public:
	CDT_Matrix( void );
	~CDT_Matrix( void );

	int   ColSize( ) { return this->m_iNcols; }
	int	RowSize( ) { return this->m_iNrows; }
	int	Alloc( int nrows, int ncols );
	void	Free( void );
	void	Set( int row, int col, T Value );
	T		Get( int row, int col );
	void	ClearOut( T value );
	void	Statistics( T *vmin, T *vmax, T *mean );

   short sCopyBuff( CDT_Matrix<T> *InBuff, int, int );
};


template <class T> CDT_Matrix<T>::CDT_Matrix( void )
{
	m_iNrows = 0;
	m_iNcols = 0;
	m_Data = NULL;
}


template <class T> CDT_Matrix<T>::~CDT_Matrix( void )
{
	m_iNrows = 0;
	m_iNcols = 0;
	m_Data = NULL;
}


template <class T> int CDT_Matrix<T>::Alloc( 
int	nrows, 
int	ncols )
{
	m_iNrows = nrows;
	m_iNcols = ncols;

	m_Data = new T*[nrows];
	if( NULL == m_Data ) return false;

	for( int i = 0 ; i < nrows ; i++ ) {
		m_Data[i] = new T[ncols];
		if( NULL == m_Data[i] ) return false;
	}

	return true;
}


template <class T> void CDT_Matrix<T>::Free( void )
{
	for( int i = 0 ; i < m_iNrows ; i++ ) {
		if( NULL != m_Data[i] ) delete[] m_Data[i];
	}
	
	if( NULL != m_Data ) delete[] m_Data;
	m_Data = NULL;
	return;
}


template <class T> void CDT_Matrix<T>::Set(
int	row,	   // [i] row
int   col,	   // [i] col
T	   value )	// [i] value
{
	m_Data[row][col] = value;
	return;
}


template <class T> T CDT_Matrix<T>::Get(
int	row,	// [i] row
int   col )	// [i] col
{
	return m_Data[row][col];
}


template <class T> void CDT_Matrix<T>::ClearOut(
T value  )	// [i] value
{
	for( int i = 0 ; i < m_iNrows ; i++ ) {
		for( int j = 0 ; j < m_iNcols ; j++ ) {
			this->Set( i, j, value );
		}
	}

   return;
}


template <class T> void	CDT_Matrix<T>::Statistics( 
T *vmin, 
T *vmax, 
T *vmean )
{
	double dSum = 0.0;
	T value;
	T pmin = this->Get( 0, 0 );
	T pmax = this->Get( 0, 0 );
	for( int i = 0 ; i < m_iNrows ; i++ ) {
		for( int j = 0 ; j < m_iNcols ; j++ ) {
			value = this->Get( i, j );
			pmin = min( value, pmin );
			pmax = max( value, pmax );
			dSum = dSum + (double)value;
		}
	}

	double dCount = (double)m_iNrows * (double)m_iNcols;
	double dMean = dSum / dCount;

	*vmin = pmin;
	*vmax = pmax;
	*vmean = (T)dMean;

	return;
}

template <class T> short CDT_Matrix<T>::sCopyBuff( 
   CDT_Matrix     *InBuff,       
   int            iStartRow,     
   int            iStartCol )   
{
   short sErrCode = 0;
   
   int i, j, iRowLoc, iColLoc;
   
   for( i = 0 ; i < InBuff->m_iNrows ; i++ ) {
      iRowLoc = i + iStartRow;
      if( iRowLoc >= this->m_iNrows ) continue;
      for( j = 0 ; j < InBuff->m_iNcols ; j++ ) {
         iColLoc = j + iStartCol;
         if( iColLoc >= this->m_iNcols ) continue;
         this->Set( iRowLoc, iColLoc, InBuff->Get( i, j ) );
      }
   }

   return sErrCode;
}

#endif _DT_MATRIX_H_