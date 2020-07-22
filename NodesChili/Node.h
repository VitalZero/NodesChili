#pragma once
#include <vector>
#include <memory>
#include <string>

class Node
{
public:
	enum class NodeType { Branch, Leaf };

public:
	virtual void AddChild( std::unique_ptr<Node> node ) {}
	virtual Node* GetChild( size_t index ) const { return nullptr; }
	virtual int GetTotal() = 0;
	std::string GetName() const { return name; }
	std::string GetTypeName() const { return typeName[(int)type]; }
	NodeType GetType() const { return type; }

protected:
	NodeType type;
	std::string name;
	const std::string typeName[2] = { "Branch", "Leaf" };
};

class BranchNode : public Node
{
public:
	BranchNode( const std::string& name );
	void AddChild( std::unique_ptr<Node> node );
	int GetTotal() override;
	Node* GetChild( size_t index ) const { return children.at( index ).get(); }
	size_t Size() const { return children.size(); }

private:
	std::vector< std::unique_ptr<Node> > children;
};

class LeafNode : public Node
{
public:
	LeafNode( const std::string& name, int total, const std::string& data );
	int GetTotal() override { return total; }
	std::string GetData() const { return data; }

private:
	int total;
	std::string data;
};