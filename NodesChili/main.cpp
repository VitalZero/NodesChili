#include <iostream>
#include "Node.h"

Node* PrintNode( Node* node, int index )
{
	if ( node )
	{
		if ( node->GetType() == NodeType::Branch )
		{
			std::cout << node->GetName() << ", " << node->GetTypeName() << std::endl;
			if ( node->Size() > 0 )
			{
				for ( int i = 0; i < node->Size(); ++i )
				{
					PrintNode( node->GetChild( i ), i );
				}

				return nullptr;
			}
			return nullptr;
		}
		else
		{
			std::cout << node->GetName() << ": $" << node->GetTotal() << std::endl;
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

int main()
{
	std::unique_ptr<Node> root = std::make_unique<BranchNode>( "THIS IS THE ROOT" );
	std::unique_ptr<Node> category = std::make_unique<BranchNode>( "FIRST CATEGORY" );
	std::unique_ptr<Node> subCategory = std::make_unique<BranchNode>( "First subcategory" );
	std::unique_ptr<Node> item;

	category->AddChild( std::move( subCategory ) );

	subCategory = std::make_unique<BranchNode>( "Second subcategory" );
	item = std::make_unique<LeafNode>( "22413", 6000, "some data 1" );

	subCategory->AddChild( std::move( item ) );
	category->AddChild( std::move( subCategory ) );
	subCategory = std::make_unique<BranchNode>( "Third subcategory" );
	item = std::make_unique<LeafNode>( "22421", 3114, "some data 2" );
	subCategory->AddChild( std::move( item ) );
	category->AddChild( std::move( subCategory ) );
	root->AddChild( std::move( category ) );

	PrintNode( root.get(), 0 );
	// std::cout << root->GetName() << "->total: " << root->GetTotal() << std::endl;

	// Node* tmpNode = root->GetChild(0); // AGROQUIMICOS
	// std::cout << "\t";
	// std::cout << tmpNode->GetName() << "->total: " << tmpNode->GetTotal() << std::endl;
	// // std::cout << "Name: " << tmpNode->GetName() << ", type: " <<
	// //   tmpNode->GetTypeName() << ", total: " << tmpNode->GetTotal() << std::endl;

	// tmpNode = tmpNode->GetChild(0); // Plantas, pasto
	// std::cout << "\t";
	// std::cout << "\t";
	// std::cout << tmpNode->GetName() << "->total: " << tmpNode->GetTotal() << std::endl;

	// std::cout << "\t";
	// std::cout << "\t";
	// std::cout << "\t";
	// std::cout << tmpNode->GetChild(0)->GetName() << "->total: " << tmpNode->GetChild(0)->GetTotal() <<
	//   " |-> " << reinterpret_cast<LeafNode*>(tmpNode->GetChild(0))->GetData() << std::endl;

	// tmpNode = root->GetChild(0)->GetChild(1); // Riego
	// std::cout << "\t";
	// std::cout << "\t";
	// std::cout << tmpNode->GetName() << "->total: " << tmpNode->GetTotal() << std::endl;
	// std::cout << "\t";
	// std::cout << "\t";
	// std::cout << "\t";
	// std::cout << tmpNode->GetChild(0)->GetName() << "->total: " << tmpNode->GetChild(0)->GetTotal() <<
	//   " |-> " << reinterpret_cast<LeafNode*>(tmpNode->GetChild(0))->GetData() << std::endl;

	// LeafNode* leafRef = reinterpret_cast<LeafNode*>(root->GetChild(0)->GetChild(0)->GetChild(0));

	// std::cout << leafRef->GetName() << std::endl;
	// std::cout << leafRef->GetTotal() << std::endl;
	// std::cout << leafRef->GetData() << std::endl;

	std::cin.get();

	return 0;
}
