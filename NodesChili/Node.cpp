#include <numeric>
#include <cctype>
#include <algorithm>
#include "Node.h"
#include <iostream>
#include <sstream>

std::string ToUpper( std::string s )
{
	std::transform( s.begin(), s.end(), s.begin(), []( unsigned char c ) {
		return std::toupper( c );
		} );

	return s;
}

Node* Node::Print( )
{
	if ( this != nullptr )
	{
		if ( GetType() == NodeType::Branch )
		{
			// It's a branch!
			std::cout << GetLevel() << ".-" << GetName() << ", "
				<< ": $ " << GetTotal() << std::endl;

			if ( ((BranchNode*)this)->Size() > 0 )
			{
				for ( size_t i = 0; i < ((BranchNode*)this)->Size(); ++i )
				{
					//std::cout << "..";

					Child( i )->Print();
				}
			}

			return nullptr;
		}
		else
		{
			// It's a leaf!
			std::cout << GetLevel() << ".-" << ((LeafNode*)this)->GetData() << " / " << ((LeafNode*)this)->GetName()
				<< ": $" << ((LeafNode*)this)->GetTotal() << std::endl;

			return nullptr;
		}
	}

	return nullptr;
}

// BranchNode
BranchNode::BranchNode( const std::string& name )
{
	type = NodeType::Branch;
	this->name = name;
}

void BranchNode::AddChild( std::unique_ptr<Node> node )
{
	node->Level(level + 1);

	children.emplace_back( std::move( node ) );
}

int BranchNode::GetTotal()
{
	return std::accumulate( children.begin(), children.end(), 0,
		[]( int accumulator, auto& c ) {
			return accumulator + c->GetTotal();
		} );
}

Node * BranchNode::Child( const std::string & name )
{
	for ( const auto& child : children )
	{
		if ( ToUpper( child->GetName() ) == ToUpper( name ) )
		{
			return child.get();
		}
	}

	return nullptr;
}

Node * BranchNode::URI( const std::string & path )
{
	std::istringstream iss(path);

	std::string tmp;
	std::vector<std::string> tokens;
	while ( std::getline( iss, tmp, '/' ) )
	{
		tokens.push_back( std::move( tmp ) );
	}

	if ( tokens.size() == 0 )
	{
		return nullptr;
	}

	Node* node = this;

	for ( auto& t : tokens )
	{
		node = node->Child( t );

		if ( !node )
		{
			break;
		}
	}

	return node;
}

// LeafNode
LeafNode::LeafNode( const std::string& name, int total, const std::string& data )
{
	type = NodeType::Leaf;
	this->name = name;
	this->total = total;
	this->data = data;
}