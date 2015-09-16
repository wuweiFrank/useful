#include "StdAfx.h"
#include "Layers.h"
#include "ILayer.h"
#include "maplayer.h"

Layers::Layers()
      : m_nActiveIndex(-1)
{
}


Layers::~Layers()
{
	ILayer *player;
	int i;
	for( i = 0; i < m_vectorLayers.size(); i++ )
	{
		player = m_vectorLayers[ i ];
		if( player->GetLayerType() == 1 )
		{
			delete (MapLayer *)player;
		}
	}
	m_vectorLayers.clear();
}



void Layers::Add (ILayer* layer)
{
	m_vectorLayers.push_back( layer );
	if( m_vectorLayers.capacity() - m_vectorLayers.size() > 10 )
	{
		m_vectorLayers.reserve( m_vectorLayers.size() + 9 );
	}
}

ILayer* Layers::GetLayer (int index)
{
	return m_vectorLayers[ index ];
}

int Layers::Count ()
{
	return m_vectorLayers.size();
}

int Layers::GetActive ()
{
	return m_nActiveIndex;
}

ILayer* Layers::GetActiveLayer ()
{
	return m_vectorLayers[ m_nActiveIndex ];
}

void Layers::SetActive (int index)
{
	m_nActiveIndex = index;
}

bool Layers::MoveTo (int fromIndex, int toIndex)
{
	ILayer *player;
	player = m_vectorLayers[ fromIndex ];
	m_vectorLayers[ fromIndex ] = m_vectorLayers[ toIndex ];
	m_vectorLayers[ toIndex ] = player;
	return true;
}

bool Layers::MoveToBottom (int index)
{
	ILayer *player;
	int n = m_vectorLayers.size() - 1;
	player = m_vectorLayers[ n ] ;
	m_vectorLayers[ n ] = m_vectorLayers[ index ];
	m_vectorLayers[ index ] = player;
	return true;
}

bool Layers::MoveToTop (int index)
{
	ILayer *player;
	player = m_vectorLayers[ 0 ];
	m_vectorLayers[ 0 ] = m_vectorLayers[ index ];
	m_vectorLayers[ index ] = player;
	return true;
}

void Layers::Remove (int index)
{
	ILayer *player = m_vectorLayers[ index ];
	m_vectorLayers.erase( m_vectorLayers.begin() + index );

	if( player->GetLayerType() == 1 )
	{
		delete (MapLayer*)player;
	}
}

void Layers::Clear ()
{
	ILayer *player;
	int i, count;
	count = m_vectorLayers.size();
	for( i = 0; i < count; i++ )
	{
		player = m_vectorLayers[ i ];
		delete player;
	}
	m_vectorLayers.clear();
}
