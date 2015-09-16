#pragma  once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>

#include <iostream> 
#include <string> 
#include <vector>                   
#include <algorithm>
using namespace std;   



#ifndef _TRI_COMMON_H_
#define _TRI_COMMON_H_

#define DXPORT			__declspec(dllexport)
#define EXT_CLASS_TYPE  __declspec(dllexport)

#include "DT_Matrix.h"



#ifndef max
#define max( a, b )	(((double)(a) > (double)(b)) ? (a) : (b))
#endif max

#ifndef min
#define min(a,b)	(((double)(a) < (double)(b)) ? (a) : (b))
#endif min

#define PIE		( 3.14159265358979323846 )	
#define PIE05	( 1.57079632679489661923 )	
#define PIE2	( 6.28318530717958647692 )	
#define PIE15	( 4.71238898038468985769 )	

#define LEFT				( 0 )
#define RIGHT				( 1 )
#define UPPER				( 2 )
#define LOWER				( 3 )
#define ACCURACY			( 1.0e-8 )
#define NODATA				( -99999999.0 )

#define ROTATION_CLOCKWISE		( 0 )	// CLOCLWISE
#define ROTATION_COUNTER		( 1 )	// COUNTER_CLOCKWISE
#define ROTATION_UNKNOWN		( 2 )	// UNKNOWN

#define FILE_NAME_SIZE			( 256 )	
#define STANDARD_BUFFER_SIZE	( 256 )
#define DELIMITOUT_SIZE			( 2000 )  


class Cp_dbl3; 

class EXT_CLASS_TYPE Cp_dbl2 
{
private:
	int		id;
public:
	double	x;
	double	y;

public:
	Cp_dbl2( void ); 
	Cp_dbl2( int, double, double );
	void	Set( int, double, double );
	void	Set( Cp_dbl3* );
	void	Center( Cp_dbl2 *p0, Cp_dbl2 *p1 );
	Cp_dbl2 &operator=(const Cp_dbl2 &that);
	int GetID( void ) { return id; }
	double GetX( void ) { return x; }
	double GetY( void ) { return y; }
	void SetID( int i ) { id = i; }
};


class EXT_CLASS_TYPE Cp_dbl3 
{
private:
	int		id;
	double	x;
	double	y;
	double	z;

public:
	Cp_dbl3( void ); 
	Cp_dbl3( int, double, double, double );
	void Set( int, double, double, double  );
	void Set( Cp_dbl2* );
	Cp_dbl3 &operator=(const Cp_dbl3 &that);
	int GetID( void ) { return id; }
	double GetX( void ) { return x; }
	double GetY( void ) { return y; }
	double GetZ( void ) { return z; }
};


class EXT_CLASS_TYPE Cp_lin2 
{
private:
	int				id;
	unsigned char	type;
	double			x0;
	double			y0;
	double			ff;
	double			gg;
	double			gg_ff;	
							   
public:
	Cp_lin2( void );
	void		OnePointAngleLine( Cp_dbl2 *point, double angle );
	bool		PlaneLine( Cp_dbl2*, Cp_dbl2*, int normalize = true );
	void		SetParameters( );
	Cp_dbl2		PointFromLineStart( double );
	int			iWhichSideOfLine( Cp_dbl2 *pnt );
};



class EXT_CLASS_TYPE Cp_Circle2
{
private:
	int			m_iId;			// ID Number	
	Cp_dbl2		m_Center;		// coordinate of the center	
	double		m_dRadius;		// radius	
	Cp_dbl2		m_Cmin;			// lower left corner of the bounding box	
	Cp_dbl2		m_Cmax;			// upper right corner of the bounding box
	double		m_dSqRaduis;	// square of the radius

public:
	void Set( Cp_dbl2, double ); 	
	void GetCircleEnd( Cp_dbl2 *pnt0, Cp_dbl2 *pnt1 );
	void GetCircleEnd( Cp_dbl3 *pnt0, Cp_dbl3 *pnt1 );
	bool bPointInCircle( Cp_dbl2 *point );
	bool bPointInCircle( Cp_dbl3 *point );
};


class EXT_CLASS_TYPE Cp_dtri 
{
private:	
	int	id;	
	int	point[3];

public:
	int iGetID( void ) { return id; }
	int GetPnt( int i ) { return ( 0 > i || 3 <= i ) ? -1 : point[i]; }
	void SetID( int n ) { id = n; }
	void Set( int n, int p0, int p1, int p2 ) { id = n; point[0] = p0; point[1] = p1; point[2] = p2; }
	void Set( int p0, int p1, int p2 ) { Set( id, p0, p1, p2 ); }
};


/*======================================================================
**** pix_algebra.cpp
======================================================================*/

DXPORT double	GoodRadian( double );
DXPORT bool		ConvertPntList( vector<Cp_dbl2>*, vector<Cp_dbl3>* );
DXPORT bool		ConvertPntList( vector<Cp_dbl3>*, vector<Cp_dbl2>* );
DXPORT void		DoubleArrayQsort( double*, int, int* );
DXPORT void		DoubleQsx( double*, int, int, int* );
DXPORT int		iPolygonRotDirection( vector<Cp_dbl2>* );
DXPORT int		iPolygonRotDirection( int, Cp_dbl2* );

DXPORT double	get_3angle( Cp_dbl2*, Cp_dbl2*, Cp_dbl2* );
DXPORT double	get_anglex_diff( double, double );
DXPORT double	get_angle_atan( double, double, double, double );
DXPORT double	get_angle_atan( Cp_dbl2*, Cp_dbl2* );

DXPORT int		CreateConvexHull( vector<Cp_dbl2> *PntList, vector<int> *ConvHull );
DXPORT int		CreateConvexHull( int nPoints, vector<Cp_dbl2> *PntList, vector<int> *ConvHull );
DXPORT int		MinDicrionaryDbl2( int nPoints, vector<Cp_dbl2> *points );
DXPORT double	dbl2_distance( double, double, double, double );
DXPORT double	dbl2_distance( Cp_dbl2*, Cp_dbl2* );
DXPORT bool		bPolygonSwapRotation( vector<Cp_dbl2> *vers, bool );
DXPORT bool		bPolygonSwapRotation( int, Cp_dbl2*, bool );

DXPORT void		PixMiniMax( vector<Cp_dbl2>*, Cp_dbl2*, Cp_dbl2* );
DXPORT void		PixMiniMax( int, vector<Cp_dbl2>*, Cp_dbl2*, Cp_dbl2* );

/*======================================================================
#### pix_utility.cpp
======================================================================*/
			
DXPORT void		chr_translate( char*, char, char );
DXPORT int		iDelimitStr_PIX( char*, char *str[], char, int );

/*======================================================================
**** pix_triangulation.cpp
======================================================================*/
//this is the function to contruct the triangle file
DXPORT bool bLoadStart_TRI(char	*szNodeFile,			 // [i] input node file
					       char	*szTriFile,				 // [i] triangle file to be created
						   int iUseConvexHul);			 // [i] 1:YES,0:NO

DXPORT bool bStartTriangle_TRI(vector<Cp_dbl2> *Pnt2List,// [i] list of node
							   vector<Cp_dtri> *TriList, // [i] list of triangles
							   int iUseConvexHul );      // [i] 1:YES,0:NO

DXPORT int iPsuedoPointCount_TRI( void );
DXPORT bool bLoadNodeFile_TRI( char* szNodeFile, vector<Cp_dbl2>* );
DXPORT bool bLoadNodeFile_TRI( char* szNodeFile, vector<Cp_dbl3>* );
DXPORT bool bSaveNodeFile_TRI( char* szNodeFile, vector<Cp_dbl2> );
DXPORT bool bSaveNodeFile_TRI( char* szNodeFile, vector<Cp_dbl3> );
DXPORT bool bLoadTriFile_TRI ( char *szNodeFile, vector<Cp_dtri> *TriList );
DXPORT bool bSaveTriFile_TRI (char* szTriFile, vector<Cp_dtri> *TriList);
DXPORT void GenerateRandomSample_TRI( char *szFile );

DXPORT int iPointsRelation_TRI( Cp_dbl2 *p0, Cp_dbl2 *p1, Cp_dbl2 *p2 );
DXPORT int iPointsRelation_TRI( vector<Cp_dbl2> *Pnt2List, int i0, int i1, int i2 );
DXPORT bool bCheckPropIntersection_TRI( Cp_dbl2*, Cp_dbl2*, Cp_dbl2*, Cp_dbl2* );
DXPORT bool bBetweenSegments_TRI( Cp_dbl2 *p0, Cp_dbl2	*p1, Cp_dbl2 *p2 );	
DXPORT bool bCheckIntersection_TRI( Cp_dbl2 *p0, Cp_dbl2 *p1, Cp_dbl2 *p2, Cp_dbl2	*p3 );
DXPORT bool bCheckIntersection_TRI( vector<Cp_dbl2>*, int i0, int i1, int i2, int i3 );
DXPORT bool bCheckDiagonalie_TRI( vector<Cp_dbl2> *Pnt2List, int i, int j );
DXPORT bool bCheckCone_TRI( vector<Cp_dbl2> *Pnt2List, int i, int j );
DXPORT bool bCheckDiagonal_TRI( vector<Cp_dbl2> *Pnt2List, int i, int j );
DXPORT int	iTriangulatePolygon_TRI( vector<Cp_dbl2>*, vector<Cp_dtri>* );
DXPORT void StartPolygonTri_TRI( vector<Cp_dbl2> *Pnt2List, vector<Cp_dtri> *Tri2List );

DXPORT bool	bSetPseudoPoints_TRI( int, vector<Cp_dbl2>* );
DXPORT int	iListNeighbour_TRI( int, int, vector<Cp_dbl2>*, int*,   
				CDT_Matrix<int>*, CDT_Matrix<int>*, vector<Cp_dtri>* );
DXPORT int	iListConvex_TRI(int iPtr, int opoints, vector<Cp_dbl2>* Pnt2List, 
				vector<int>* Cnv2List, int*, CDT_Matrix<int>*, int*, CDT_Matrix<int>*, 
				vector<Cp_dtri>* );
DXPORT bool	bInitNeighbourList( int, CDT_Matrix<int>* );
DXPORT bool	bCmpNbrList( int, int, int, CDT_Matrix<int>* );	
DXPORT bool	bResetTriangleList_TRI( int, vector<int>*, vector<Cp_dtri>*, vector<Cp_dtri>* );
DXPORT bool	bCreateTriangleVector_TRI( int, vector<Cp_dtri>*, vector<Cp_dtri>* );
DXPORT bool	bInitBelongList_TRI( int, CDT_Matrix<int>* );
DXPORT bool	bSortByDistance( int, vector<Cp_dbl2>*, int* );
DXPORT bool	bBoxSortPoint_TRI( vector<Cp_dbl2>* PntList, int* iBoxSorted );
DXPORT bool	bBoxSortPoint_TRI( int, vector<Cp_dbl2>* PntList, int* iBoxSorted );


#endif _TRI_COMMON_H_
