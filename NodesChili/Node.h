#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Invoice.h"

class Node
{
public:
	enum class NodeType { NA = -1, Branch, Leaf };

public:
	virtual void AddChild( std::unique_ptr<Node> node ) {}
	virtual Node* Child( size_t index = 0) { return nullptr; }
	virtual Node* Child( const std::string& name ) { return nullptr; }
	virtual Node* URI( const std::string& path ) { return nullptr; }
	virtual double GetTotal() = 0;

public:
	std::string GetName() const { return name; }
	std::string GetTypeName() const { return typeName[(int)type]; }
	NodeType GetType() const { return type; }
	Node* Print();
	int GetLevel() { return level; }
	void Level( int level ) { this->level = level; }

protected:
	NodeType type = NodeType::NA;
	std::string name;
	const std::string typeName[2] = { "Branch", "Leaf" };
	int level = 0;
};

class BranchNode : public Node
{
public:
	BranchNode( const std::string& name );
	void AddChild( std::unique_ptr<Node> node );
	double GetTotal() override;
	Node* Child( size_t index = 0) override { return children.at( index ).get(); }
	Node* Child( const std::string& name ) override;
	Node* URI( const std::string& path ) override;
	size_t Size() const { return children.size(); }

private:
	std::vector< std::unique_ptr<Node> > children;
};

class LeafNode : public Node
{
public:
	LeafNode( const Invoice& invoice );
	double GetTotal() override { return invoice.GetAmount(); }
	const Invoice& GetData() const { return invoice; }
	const Invoice& GetInvoice() const { return invoice; }

private:
	Invoice invoice;
};