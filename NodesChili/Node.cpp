#include <numeric>
#include <cctype>
#include <algorithm>
#include "Node.h"
#include <iostream>

std::string ToUpper( std::string s )
{
	std::transform( s.begin(), s.end(), s.begin(), []( unsigned char c ) {
		return std::toupper( c );
		} );

	return s;
}

Node* Node::Print( const Node * node )
{
	if ( node )
	{
		if ( node->GetType() == NodeType::Branch )
		{
			// It's a branch!
			BranchNode* branch = (BranchNode*)node;

			std::cout << branch->GetName() << ", " << branch->GetTypeName()
				<< ": $ " << branch->GetTotal() << std::endl;

			if ( branch->Size() > 0 )
			{
				for ( size_t i = 0; i < branch->Size(); ++i )
				{
					std::cout << "..";

					Print( branch->Child( i ) );
				}
			}

			return nullptr;
		}
		else
		{
			// It's a leaf!
			LeafNode* leaf = (LeafNode*)node;

			std::cout << ".." << leaf->GetData() << " / " << leaf->GetName() << ": $" << leaf->GetTotal() << std::endl;

			return nullptr;
		}
	}

	return nullptr;
}

Node* Node::Print( )
{
	if ( this != nullptr )
	{
		if ( GetType() == NodeType::Branch )
		{
			// It's a branch!

			std::cout << GetName() << ", " << GetTypeName()
				<< ": $ " << GetTotal() << std::endl;

			if ( ((BranchNode*)this)->Size() > 0 )
			{
				for ( size_t i = 0; i < ((BranchNode*)this)->Size(); ++i )
				{
					std::cout << "..";

					Child( i )->Print();
				}
			}

			return nullptr;
		}
		else
		{
			// It's a leaf!

			std::cout << ".." << ((LeafNode*)this)->GetData() << " / " << ((LeafNode*)this)->GetName() 
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

// LeafNode
LeafNode::LeafNode( const std::string& name, int total, const std::string& data )
{
	type = NodeType::Leaf;
	this->name = name;
	this->total = total;
	this->data = data;
}