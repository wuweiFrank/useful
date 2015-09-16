
#include "stdafx.h"
#include "tricommon.h"
void chr_translate( 
      char	*str, 
		char	chr0, 
		char	chr1 )
{
	char	*cp;
	cp = str;
	for ( ;; ) {
		cp = strchr( cp, chr0 );
		if ( cp == NULL ) return;
		*cp = chr1;
	}

   return;
}


int iDelimitStr_PIX(	
		char	*buff,			
		char	*str[], 	
		char	dli,	    
		int		iBuffSize )
{
	int i;
	char	*p;

	i = 0;
	p = buff;
	while( *p == ' ' || *p == '\t' ) p ++;
	if ( *p == 0 ) {
		str[i] = 0;
		return i;
	}

	str[i] = p;
	i++;
	while( *p != 0 ) {
		if ( *p == dli ) {
			*p = 0;
			p++;
			while( *p == ' ' || *p == '\t' ) p++;
		   if( i < iBuffSize ) str[i] = p;
			i++;
		} else {
			p++;
		}
	}

	if( i < iBuffSize ) str[i] = 0;
	return i;
}
