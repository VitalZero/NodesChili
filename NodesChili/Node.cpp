#include <numeric>
#include <cctype>
#include <algorithm>
#include "Node.h"

std::string ToUpper( std::string s )
{
	std::transform( s.begin(), s.end(), s.begin(), []( unsigned char c ) {
		return std::toupper( c );
		} );

	return s;
}

// BranchNode
BranchNode::BranchNode( const std::string& name )
{
	type = NodeType::Branch;
	this->name = name;
}

void BranchNode::AddChild( std::unique_ptr<Node> node )
{
	children.emplace_back( std::move( node ) );
}

int BranchNode::GetTotal()
{
	return std::accumulate( children.begin(), children.end(), 0,
		[]( int accumulator, auto& c ) {
			return accumulator + c->GetTotal();
		} );
}

Node* BranchNode::operator[]( const std::string & name )
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

// LeafNode
LeafNode::LeafNode( const std::string& name, int total, const std::string& data )
{
	type = NodeType::Leaf;
	this->name = name;
	this->total = total;
	this->data = data;
}
