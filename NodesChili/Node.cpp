#include <numeric>
#include "Node.h"

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

// LeafNode
LeafNode::LeafNode( const std::string& name, int total, const std::string& data )
{
	type = NodeType::Leaf;
	this->name = name;
	this->total = total;
	this->data = data;
}
