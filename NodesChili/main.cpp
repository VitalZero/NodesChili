#include <iostream>
#include "Node.h"

Node* PrintTree(const Node* node)
{
	if ( node )
	{
		if ( node->GetType() == Node::NodeType::Branch )
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

					PrintTree( branch->Child( i ));
				}
			}

			return nullptr;
		}
		else
		{
			// It's a leaf!
			LeafNode* leaf = (LeafNode*)node;

			std::cout << ".." << leaf->GetData() << " / " << leaf->GetName()  << ": $" << leaf->GetTotal() << std::endl;

			return nullptr;
		}
	}

	return nullptr;
}

int main()
{
	std::unique_ptr<Node> root = std::make_unique<BranchNode>( "THIS IS THE ROOT" );
	std::unique_ptr<Node> category = std::make_unique<BranchNode>( "FIRST CATEGORY" );
	std::unique_ptr<Node> subCategory = std::make_unique<BranchNode>( "First subcategory" );
	std::unique_ptr<Node> item;

	item = std::make_unique<LeafNode>( "22587", 1618, "some data 1 from subcat 1" );
	subCategory->AddChild( std::move( item ) );
	category->AddChild( std::move( subCategory ) );

	subCategory = std::make_unique<BranchNode>( "Second subcategory" );
	item = std::make_unique<LeafNode>( "22413", 6000, "some data 1 from subcat 2" );
	subCategory->AddChild( std::move( item ) );
	item = std::make_unique<LeafNode>( "22520", 7000, "some data 2 from subcat 2" );
	subCategory->AddChild( std::move( item ) );

	category->AddChild( std::move( subCategory ) );
	subCategory = std::make_unique<BranchNode>( "Third subcategory" );
	item = std::make_unique<LeafNode>( "22421", 3114, "some data 1 from subcat 3" );
	subCategory->AddChild( std::move( item ) );
	category->AddChild( std::move( subCategory ) );
	root->AddChild( std::move( category ) );

	category = std::make_unique<BranchNode>( "SECOND CATEGORY" );
	subCategory = std::make_unique<BranchNode>( "First subcategory" );
	item = std::make_unique<LeafNode>( "123456789", 10000, "some data 1 from subcat 1" );

	subCategory->AddChild( std::move( item ) );
	category->AddChild( std::move( subCategory ) );
	root->AddChild( std::move( category ) );

	PrintTree( root.get());

	std::cout << "\nAhora sin manos!:" << std::endl;

	root->Print();

	std::cout << "\nAhora desde el primer descendiente:" << std::endl;

	root->Child( 0 )->Print();

	std::cout << "\nAhora desde el segundo descendiente:" << std::endl;

	root->Child( "second category" )->Print();

	std::cin.get();

	return 0;
}
