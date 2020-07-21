#include <iostream>
#include "Node.h"

Node* PrintNode(const Node* node, int index )
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
				for ( int i = 0; i < branch->Size(); ++i )
				{
					std::cout << "\t\treturn node and print next\n";
					PrintNode( branch->GetChild( i ), i );
				}
			}
			std::cout << "\t\treturn null after for loop\n";
			return nullptr;
		}
		else
		{
			// It's a leaf, for sure
			LeafNode* leaf = (LeafNode*)node;

			std::cout << leaf->GetData() << " / " << leaf->GetName()  << ": $" << leaf->GetTotal() << std::endl;
			std::cout << "\t\treturn null after leaf\n";
			return nullptr;
		}
	}
	else
	{
		std::cout << "\t\treturn null because node is null\n";
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
	item = std::make_unique<LeafNode>( "22413", 6000, "some data 1 from cat 2" );
	subCategory->AddChild( std::move( item ) );
	item = std::make_unique<LeafNode>( "22520", 7000, "some data 2 from cat 2" );
	subCategory->AddChild( std::move( item ) );

	category->AddChild( std::move( subCategory ) );
	subCategory = std::make_unique<BranchNode>( "Third subcategory" );
	item = std::make_unique<LeafNode>( "22421", 3114, "some data 1 from cat 3" );
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
