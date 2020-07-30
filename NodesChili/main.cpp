#include <iostream>
#include "Node.h"

int main()
{
	BranchNode root( "PETTY CASH" );

	root.AddChild( std::make_unique<BranchNode>( "OPERACION MCDG" ) );

	{ // temp traversal variable
		Node* account = root.Child();

		account->AddChild( std::make_unique<LeafNode>(
			Invoice{ "ARTEFACTOS PERNOS Y SEGUROS", "APS841210IZA", "15/07/2020", 
			"130206", "REFACCIONES", "50-1-1-7", 67.40 }
		) );
		account->AddChild( std::make_unique<LeafNode>(
			Invoice{ "ADRIANA DOLORES ENCISO PLASCENCIA", "EIPA87078UC3", "15/07/2020",
			"83977", "REFACCIONES", "50-1-1-7", 195.18 }
		) );
		account->AddChild( std::make_unique<LeafNode>(
			Invoice{ "FERROSA CONSTRUCCION CENTER", "FCC100210BE1", "17/07/2020",
			"83977", "MATERIALES", "50-1-1-2", 126.41 }
		) );
	}

	root.AddChild( std::make_unique<BranchNode>( "DIR MNT CAMPO" ) );

	{ // temp traversal variable
		Node* account = root.Child("dir mnt campo");

		account->AddChild( std::make_unique<LeafNode>(
			Invoice{ "FARMACIA GUADALAJARA", "FGU830930PD3", "13/07/2020",
			"38783", "HIGIENE", "60-15-1-8", 141.29 }
		) );
		account->AddChild( std::make_unique<LeafNode>(
			Invoice{ "MRK SUPPLY", "MSU181113644", "14/07/2020",
			"38783", "MISCELANEOS", "60-11-1-7", 529.73 }
		) );
	}

	// print from root, all the way up
	root.Print();

	std::cin.get();

	return 0;
}


// commented code, past version tests:

	// Another way to add items and subitems
	//std::unique_ptr<Node> root = std::make_unique<BranchNode>( "THIS IS THE ROOT" );
	//std::unique_ptr<Node> category = std::make_unique<BranchNode>( "FIRST CATEGORY" );
	//std::unique_ptr<Node> subCategory = std::make_unique<BranchNode>( "First subcategory" );
	//std::unique_ptr<Node> item;

	//item = std::make_unique<LeafNode>( "22587", 1618, "some data 1 from subcat 1" );
	//subCategory->AddChild( std::move( item ) );
	//category->AddChild( std::move( subCategory ) );

	//subCategory = std::make_unique<BranchNode>( "Second subcategory" );
	//item = std::make_unique<LeafNode>( "22413", 6000, "some data 1 from subcat 2" );
	//subCategory->AddChild( std::move( item ) );
	//item = std::make_unique<LeafNode>( "22520", 7000, "some data 2 from subcat 2" );
	//subCategory->AddChild( std::move( item ) );

	//category->AddChild( std::move( subCategory ) );
	//subCategory = std::make_unique<BranchNode>( "Third subcategory" );
	//item = std::make_unique<LeafNode>( "22421", 3114, "some data 1 from subcat 3" );
	//subCategory->AddChild( std::move( item ) );
	//category->AddChild( std::move( subCategory ) );
	//root->AddChild( std::move( category ) );

	//category = std::make_unique<BranchNode>( "SECOND CATEGORY" );
	//subCategory = std::make_unique<BranchNode>( "First subcategory" );
	//item = std::make_unique<LeafNode>( "123456789", 10000, "some data 1 from subcat 1" );

	//subCategory->AddChild( std::move( item ) );
	//category->AddChild( std::move( subCategory ) );
	//root->AddChild( std::move( category ) );

	//std::unique_ptr<Node> root = std::make_unique<BranchNode>( "PETTY CASH" );

	//root->AddChild( std::make_unique<BranchNode>( "DIRECTION" ) );
	//root->AddChild( std::make_unique<BranchNode>( "OPERATION" ) );
	//root->AddChild( std::make_unique<BranchNode>( "TREATMENT P" ) );

	//Node* category = root->Child( "direction" );
	//category->AddChild( std::make_unique<BranchNode>( "Safety" ) );
	//category->AddChild( std::make_unique<BranchNode>( "Facility mnt" ) );
	//Node* subCategory = category->Child( "safety" );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F1020", 300, "Hand sanitizer" ) );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F200", 450, "Latex gloves" ) );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F20", 4000, "Overall tyveks" ) );
	//subCategory = category->Child( "facility mnt" );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F52310", 1750, "Beige paint, bucket" ) );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F1", 113, "Phillips 112 locks" ) );

	//category = root->Child( "operation" );
	//category->AddChild( std::make_unique<BranchNode>( "Materials" ) );
	//category->AddChild( std::make_unique<BranchNode>( "Spare parts" ) );
	//subCategory = category->Child( "materials" );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F4427", 12123, "Fungicides" ) );

	//category = root->Child( "treatment p" );
	//category->AddChild( std::make_unique<BranchNode>( "Chemicals" ) );
	//subCategory = category->Child( "chemicals" );
	//subCategory->AddChild( std::make_unique<LeafNode>( "F324", 19546, "Polymer and al. sulfate" ) );

	//category->AddChild( std::make_unique<BranchNode>( "Pumps" ) );
	//category = nullptr;
	//subCategory = nullptr;

	//// test URI handler
	//std::string uri = "direction/safety/f1020";
	//Node* test = root.URI( uri );

	//if ( test )
	//{
	//	if ( test->GetType() == Node::NodeType::Leaf )
	//	{
	//		std::cout << "\n\nYay!, found:\n" << ((LeafNode*)test)->GetName() << ", "
	//			<< ((LeafNode*)test)->GetData().GetConcept() << ": $ " 
	//			<< ((LeafNode*)test)->GetTotal() << std::endl;
	//	}
	//}
	//else
	//{
	//	std::cout << "didn't find URI: " << uri << std::endl;
	//}

//Node* PrintTree(const Node* node)
//{
//	if ( node )
//	{
//		if ( node->GetType() == Node::NodeType::Branch )
//		{
//			// It's a branch!
//			BranchNode* branch = (BranchNode*)node;
//
//			std::cout << branch->GetName() << ", " << branch->GetTypeName()
//				<< ": $ " << branch->GetTotal() << std::endl;
//
//			if ( branch->Size() > 0 )
//			{
//				for ( size_t i = 0; i < branch->Size(); ++i )
//				{
//					std::cout << "..";
//
//					PrintTree( branch->Child( i ));
//				}
//			}
//
//			return nullptr;
//		}
//		else
//		{
//			// It's a leaf!
//			LeafNode* leaf = (LeafNode*)node;
//
//			std::cout << ".." << leaf->GetData().GetConcept() << " / " << leaf->GetName()  
//				<< ": $" << leaf->GetTotal() << std::endl;
//
//			return nullptr;
//		}
//	}
//
//	return nullptr;
//}