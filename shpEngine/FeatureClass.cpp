#include "StdAfx.h"
#include "FeatureClass.h"
FeatureClass::FeatureClass (int id, int type, const char *strName, DataSource* pDataSource )
      : Table( id, type, pDataSource, strName )
{
}


FeatureClass::~FeatureClass()
{
	Feature * pfeature;
	for( m_curRow = m_mapRow.begin(); m_curRow != m_mapRow.end(); m_curRow++ )
	{
		pfeature = ( Feature * )(*m_curRow).second;
		delete pfeature;
		(*m_curRow).second = 0;
	}
	m_mapRow.clear();
}


const char* FeatureClass::GetName ()
{
	return GetTableName();
}

void FeatureClass::GetBound (double& minx, double& miny, double& w, double& h)
{
	minx = m_dMinx;
	miny = m_dMiny;
	w    = m_dWidth;
	h    = m_dHeight;
}

void FeatureClass::CalculateBound ()
{
	double	minx = 0, miny = 0, maxx = 0, maxy = 0;
	double	x, y, w, h;
	bool	isfirst = true;
	Feature *pfeature = ( Feature * )GetFirst();
	while( pfeature )
	{
		pfeature->GetBound( x, y, w, h );
		if( isfirst )
		{
			minx = x;
			miny = y;
			maxx = x+w;
			maxy = y+h;
			isfirst = false ;
		}
		else
		{
			if( minx > x ) minx = x;
			if( miny > y ) miny = y;
			if( maxx < w+x ) maxx = x+w;
			if( maxy < y+h ) maxy = y+h;
		}
		pfeature = (Feature*)GetNext();
	}

	m_dMinx = minx;
	m_dMiny = miny;
	m_dWidth = maxx-minx;
	m_dHeight = maxy-miny;
}

int FeatureClass::GetFeatureSize ()
{
	return Size();
}

Feature* FeatureClass::GetFirstFeature ()
{
	return (Feature*)GetFirst();
}

Feature* FeatureClass::GetNextFeature ()
{
  //## begin FeatureClass::GetNextFeature%405BE7160251.body preserve=yes
	return (Feature*)GetNext();
  //## end FeatureClass::GetNextFeature%405BE7160251.body
}

Feature* FeatureClass::GetFeature (int fid)
{
  //## begin FeatureClass::GetFeature%405BE72B038A.body preserve=yes
	return (Feature*)GetRow(fid);
  //## end FeatureClass::GetFeature%405BE72B038A.body
}

// Additional Declarations
  //## begin FeatureClass%405A57DC00DF.declarations preserve=yes
  //## end FeatureClass%405A57DC00DF.declarations

//## begin module%405A57DC00DF.epilog preserve=yes
//## end module%405A57DC00DF.epilog
