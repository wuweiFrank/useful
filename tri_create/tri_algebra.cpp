#include "stdafx.h"
#include <iostream>
#include <vector>                      
#include <algorithm>

#include "tricommon.h"


void PixMiniMax(
		vector<Cp_dbl2> *points, 
		Cp_dbl2			*pmin, 
		Cp_dbl2			*pmax )
{
	int npoints = (int)points->size( );
	PixMiniMax( npoints, points, pmin, pmax );
	return;
}

void PixMiniMax(
		int				npoints, 
		vector<Cp_dbl2> *points, 
		Cp_dbl2			*pmin, 
		Cp_dbl2			*pmax )
{
	Cp_dbl2 *ep;

	ep = &points->at( 0 );
	pmin->x = ep->x;
	pmin->y = ep->y;
	pmax->x = ep->x;
	pmax->y = ep->y;
	
	for( int i = 1 ; i < npoints; i++ ) {
		ep = &points->at( i );
		pmin->x = min( pmin->x, ep->x );
		pmin->y = min( pmin->y, ep->y );
		pmax->x = max( pmax->x, ep->x );
		pmax->y = max( pmax->y, ep->y );
	}

	return;
}


double dbl2_distance( 	Cp_dbl2	*point0,
						Cp_dbl2	*point1 )
{
	return dbl2_distance( point0->x, point0->y, point1->x, point1->y );
}


double dbl2_distance( 	double	dX0,
						double	dY0,
						double	dX1,
						double	dY1 )
{
	double dX = ( dX0 - dX1 );
	double dY = ( dY1 - dY0 );
	return sqrt( dX * dX + dY * dY );
}


bool ConvertPntList(	vector<Cp_dbl2> *Pnt2List, 
						vector<Cp_dbl3> *Pnt3List )
{
	bool bRetCode = false;
	int nPoints, i;
	Cp_dbl3 ep3;

	Pnt3List->clear( );
	nPoints = (int)Pnt2List->size( );
	for( i = 0 ; i < nPoints ; i++ ) {
		ep3.Set( &Pnt2List->at( i ) );
		Pnt3List->push_back( ep3 );
	}

	// --- Done ---
	bRetCode = true;
	return bRetCode;
}


bool ConvertPntList(	vector<Cp_dbl3> *Pnt3List, 
						vector<Cp_dbl2> *Pnt2List )
{
	bool bRetCode = false;
	int nPoints, i;
	Cp_dbl2 ep2;

	Pnt2List->clear( );
	nPoints = (int)Pnt3List->size( );
	for( i = 0 ; i < nPoints ; i++ ) {
		ep2.Set( &Pnt3List->at( i ) );
		Pnt2List->push_back( ep2 );
	}

	// --- Done ---
	bRetCode = true;
	return bRetCode;
}


int iPolygonRotDirection( vector<Cp_dbl2> *PntList )
{
	int iRot, i;
	int nPoints = (int)PntList->size( );
	Cp_dbl2	*work = new Cp_dbl2[nPoints];
	if( !work ) {
		iRot = ROTATION_UNKNOWN;
		goto PIX_EXIT;
	}

	for( i = 0 ; i < nPoints ; i++ ) {
		work[i] = PntList->at( i );
	}

	iRot = iPolygonRotDirection( nPoints, work );

	// --- DOne ---
	
PIX_EXIT:

	if( work ) delete[] work;
	return iRot;
}


int iPolygonRotDirection(
		int		nver, 
		Cp_dbl2	*vers )
{
int	i, j, k, int_det, clock, nver2, counter;
double	angle_sum, curve;

 	if( nver <= 2 ) return ROTATION_CLOCKWISE;

	/*------------------------------------------------------------------
	#### angle_sum
	#### 各頂点において反時計回りに計られた角度の和。ひとつで頂点での
	#### 屈曲角が0または2*PIEなら回転方向が求められない（捻れているま
	#### たは、全ての頂点が直線上にある）のでROTATION_CLOCKWISEを返す
	-----------------------------------------------------------------*/
	angle_sum = 0;
	nver2 = nver - 1;
	for( j = 0 ; j < nver ; j++ ) {
		i = ( j==0 ) ? nver2 : j - 1;
		k = ( j==nver2 ) ? 0 : j + 1;
		curve = get_3angle( &vers[i], &vers[j], &vers[k] );

		if( curve == 0.0 || curve == PIE2 ) return ROTATION_UNKNOWN;
		angle_sum += curve;
	}

	/*------------------------------------------------------------------
	#### 多角形が反時計回りなら angle_sum = 180 X ( nver + 2 )
	#### 時計回りなら# angle_sum = 180 X ( nver - 2 )
	#### が成り立つ。従って、int_det = angle_sum / PIEは、図形が時計回
	#### りの場合は( nver - 2 )、反時計回りの場合は( nver + 2 )になる
	-----------------------------------------------------------------*/
	int_det = ( int )( angle_sum / PIE + 0.5 );
	clock = nver - 2;

	if( int_det == clock ) {
		return ROTATION_CLOCKWISE;
	} else {
		counter = nver + 2;
		if( int_det == counter ) {
			return ROTATION_COUNTER;
		} else {
			return ROTATION_UNKNOWN;
		}
	}	
}


double get_anglex_diff( double		angle1, 
						double		angle2 )
{
	double          ang;
	/* ang = angle2 - angle1 + PIE + PIE; */
	ang = angle2 - angle1 + PIE;
	ang = GoodRadian( ang );
	return ang;
}


double get_3angle(	Cp_dbl2	*	a, 
					Cp_dbl2	*	b, 
					Cp_dbl2	*	c )
{	
	double ang1 = get_angle_atan( a, b );
	double ang2 = get_angle_atan( b, c );
	double ang = get_anglex_diff( ang1, ang2 );
	return ang;
}


double get_angle_atan( 
		Cp_dbl2	*pnt_a, 
		Cp_dbl2	*pnt_b )
{
	double x0 = pnt_a->x;
	double y0 = pnt_a->y;
	double x1 = pnt_b->x;
	double y1 = pnt_b->y;
	return get_angle_atan( x0, y0, x1, y1 );
}


double get_angle_atan( 
		double x0,
		double y0,
		double x1,
		double y1 )
{
	double ang, ang1;
	if( x0 == x1 ) {
		ang = ( y1 == y0 ) ? 0.0 : ( y1 < y0 ) ? PIE15 : PIE05;
		ang = GoodRadian( ang );
		return ang;
	}

	ang1 = atan( ( y1 - y0 ) / ( x1 - x0 ) );	
	ang = ( y0 < y1 ) ?
					( x0 < x1 ) ? ang1 : ang1 + PIE:
					( x0 < x1 ) ? ang1 + PIE2 : ang1 + PIE;
	ang = GoodRadian( ang );
	return ang;
}


bool bPolygonSwapRotation( 	vector<Cp_dbl2>	*vers, 
							bool			bClosed )
{
	bool bRet, bRetCode = false;
	int	i;
	int nPoints = (int)vers->size( );
	Cp_dbl2	*work = new Cp_dbl2[nPoints];
	if( !work ) goto PIX_EXIT;

	for( i = 0 ; i < nPoints ; i++ ) {
		work[i] = vers->at( i );
	}

	bRet = bPolygonSwapRotation( nPoints, work, bClosed );
	if( !bRet ) goto PIX_EXIT;

	vers->clear( );
	for( i = 0 ; i < nPoints ; i++ ) {
		vers->push_back( work[i] );
	}

	// --- DOne ---
	
	bRetCode = true;

PIX_EXIT:

	if( work ) delete[] work;
	return bRetCode;
}


bool bPolygonSwapRotation( 	
		int		nver, 
		Cp_dbl2	*vers, 
		bool	bClosed )
{
	bool bRetCode = false;
	int	nver2, i, j;
	Cp_dbl2	*work = NULL;

	work = new Cp_dbl2[nver];
	if( !work ) goto PIX_EXIT;

	switch( bClosed ) {
	case true:
		for( i = 1 ; i < nver ; i++ ) {
			j = nver - i;
			work[j] = vers[i];
		}

		for( i = 1 ; i < nver ; i++ ) {
			vers[i] = work[i];
		}
		break;
	case false:
		nver2 = nver - 1;
		for( i = 0 ; i < nver ; i++ ) {
			j = nver2 - i;
			work[j] = vers[i];
		}

		for( i = 0 ; i < nver ; i++ ) {
			vers[i] = work[i];
		}
		break;
	}

	// --- DOne ---
	
	bRetCode = true;

PIX_EXIT:

	if( work ) delete[] work;
	return bRetCode;
}


double GoodRadian( double angle0 )
{
	double angle1;
	angle1 = angle0;

	while( angle1 < 0 ) {
		angle1 += PIE2;
	}

	while( angle1 > PIE2 ) {
		angle1 -= PIE2;
	}

	return angle1;
}


void DoubleArrayQsort( 	double	*array, 
						int		n_data, 
						int		*seq )
{
	int i; 
	for( i = 0 ; i < n_data ; i++ ) seq[i] = i;
	DoubleQsx( array, 0, n_data - 1, seq );
}


void DoubleQsx( double	*array, 
				int		left, 
				int		right, 
				int		*seq )
{
int 	seqy;
double	y; 

	int i = left; 
	int j = right; 
	double x = array[( left + right ) / 2];
	do {
		while( ( array[i] < x ) && ( i < right ) ) i++;
		while( ( x < array[j] ) && ( j > left ) ) j--;

		if( i <= j ) {
			y = array[i];  
			array[i] = array[j]; 
			array[j] = y;    
			seqy = seq[i];
			seq[i] = seq[j];
			seq[j] = seqy;
			i++;
			j--;
		}
	} while( i <= j );

	if ( left < j ) DoubleQsx( array, left, j, seq );
	if ( i < right ) DoubleQsx( array, i, right, seq );
}


int	CreateConvexHull( 	
		vector<Cp_dbl2> *points,		// [i] input points
		vector<int>		*convh )	// [o] convex hull, list of point numbers
{
	int npoints = (int)points->size( ); 
	int nconvh = CreateConvexHull( npoints, points, convh );

	return nconvh;
}

int	CreateConvexHull( 	
		int				npoints,	// [i] number of points in "points" to use
		vector<Cp_dbl2> *Pnt2List,	// [i] input points
		vector<int>		*convh )	// [o] convex hull, list of point numbers
{	
	int j, i, k, imin, ptr, ptr1, ptr2, nconvh;
	double	angle;
	int	*seq = NULL;
	double	*angles = NULL;
	double dPie = PIE;
	Cp_dbl2	ep, base_point, *Pu, *Pv, *Pw;

	/*------------------------------------------------------------------
	#### find the minimum point in the dictionary order.
	------------------------------------------------------------------*/
	if ( NULL == convh ) return -1;
	if ( npoints < 3 ) return -1;
	imin = MinDicrionaryDbl2( npoints, Pnt2List );

	/*------------------------------------------------------------------
	#### set Base point which has the same x-coordinate as minimum
	#### dictionary point and negative infinite y.
	------------------------------------------------------------------*/
	ep = Pnt2List->at( imin );
	base_point.x = ep.x;
	base_point.y = -1000000000.0;

	/*--------------------------------------------------------------
	#### memory allocations. 
	--------------------------------------------------------------*/
	angles = new double[npoints];
	if( NULL == angles ) goto PIX_EXIT;

	seq = new int[npoints];
	if( NULL == seq ) goto PIX_EXIT;

	/*------------------------------------------------------------------
	#### get azimuths of each point measured from the base line measured 
	#### in the counter-clockwise direction.
	------------------------------------------------------------------*/
	for ( i = 0; i < npoints; i++ ) {
		if ( i == imin ) {
			angles[i] = 0.0;
		} else {
			angles[i] = get_3angle( &base_point, &Pnt2List->at( imin ), &Pnt2List->at( i ) );
		}
	}

	// --- sort points according to the angle. ---
	DoubleArrayQsort( angles, npoints, seq );

	// --- if there are points with identical angles, sort it acoording ---
	// --- to the distance from imin ---	
	for( i = 1 ; i < npoints - 1 ; i++ ) {
		if( angles[i] != angles[i+1] ) continue;

		int i0 = i;
		int i1 = (++i);
		int i2 = -1;
		for( j = i1+1 ; i2 < 0 && j < npoints ; j++ ) {
			if( angles[i0] != angles[j] ) {
				i2 = j-1;
			}
		}
		if( 0 > i2 ) i2 = npoints - 1;

		int npx = i2 - i0 + 1;
		
		double *dists = new double[npx];
		if( NULL == dists ) goto PIX_EXIT;
		int *seq2 = new int[npx];
		if( NULL == seq2 ) goto PIX_EXIT;
		int *tseq = new int[npx];
		if( NULL == tseq ) goto PIX_EXIT;

		for( j = i0 ; j <= i2 ; j++ ) {
			k = j - i0;
			dists[k] = dbl2_distance( &Pnt2List->at( imin ), &Pnt2List->at( seq[j] ) );
			tseq[k] = seq[j];
		}
		DoubleArrayQsort( dists, npx, seq2 );

		for( j = 0 ; j < npx ; j++ ) {
			seq[j+i0] = tseq[seq2[j]];
		}

		i = i2;
		delete[] seq2;
		delete[] tseq;
		delete[] dists;
	}

	/*------------------------------------------------------------------
	#### delete unnecessary points from the list 
	#### make a list of vertex of the convex full in convh.
	------------------------------------------------------------------*/
	nconvh = npoints;
	ptr = 1;
	while( true ) {
		ptr1 = ptr + 1;
		ptr2 = ptr + 2;
		Pu = &Pnt2List->at( seq[ptr] );
		Pv = &Pnt2List->at( seq[ptr1] );
		Pw = &Pnt2List->at( seq[ptr2] );
		angle = get_3angle( Pu, Pv, Pw );

		if( angle - dPie >= -ACCURACY ) {
			ptr++; 
		} else {
			for( i = ptr + 1 ; i < nconvh - 1 ; i++ ) seq[i]=seq[i+1];
			nconvh = nconvh - 1;
			ptr--;
			ptr = max( 0, ptr );
		}
	  	if( ( ptr + 2 ) == nconvh ) break;
	}

	convh->clear( );
	for( i = 0 ; i < nconvh ; i++ ) {
		convh->push_back( seq[i] );
	}

	/*------------------------------------------------------------------
	#### wash dishes.
	------------------------------------------------------------------*/
PIX_EXIT:
	delete[] angles;
	delete[] seq;

	return nconvh;
}


int MinDicrionaryDbl2( vector<Cp_dbl2> *points )
{
	int	npoints = (int)points->size( );
	return MinDicrionaryDbl2( npoints, points );
}


int MinDicrionaryDbl2( int npoints, vector<Cp_dbl2> *points )
{
	int	i, imin;
	double	xmin, ymin;
	Cp_dbl2 ep;

	imin = 0;
	xmin = points->at( 0 ).x;
	ymin = points->at( 0 ).y;

	for( i = 1 ; i < npoints ; i++ ) {
		ep = points->at( i );
		if( ep.x > xmin ) continue;

		if( ep.x < xmin ) {
			imin = i;
			xmin = ep.x;
			ymin = ep.y;
			continue;
		}

		if( ep.x == xmin && ep.y < ymin ) {
			imin = i;
			xmin = ep.x;
			ymin = ep.y;
			continue;
		}
	}

	return imin;
}