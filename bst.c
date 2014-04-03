#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node
{
	int key;

	struct _node * parent;
	struct _node * left;
	struct _node * right;
} Node;

typedef struct _bst
{
	Node * root;
} BST;

static BST * createEmptyTree()
{
	BST * p = (BST *)malloc(sizeof(BST));
	p->root = 0;

	return p;
}

static void freeNode(Node * pnode)
{
	if( pnode )
	{
		freeNode(pnode->left);
		freeNode(pnode->right);

		free(pnode);
	}
}

static void destroyTree(BST * p)
{
	if( p && p->root )
	{
		freeNode(p->root);
	}
}

static void addNode(Node * parent, Node * node)
{
	Node ** pp = 0;

	if( node->key < parent->key )
	{
		if( !parent->left )
		{
			pp = &(parent->left);
		}
		else
		{
			addNode(parent->left, node);
		}
	}
	else
	if( node->key > parent->key )
	{
		if( !parent->right )
		{
			pp = &(parent->right);
		}
		else
		{
			addNode(parent->right, node);
		}
	}

	if( pp )
	{
		*pp = node;
		node->parent = parent;
	}
}

static void add(BST * ptree, int key)
{
	Node * node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->parent = node->left = node->right = 0;

	if( ptree->root )
	{
		addNode(ptree->root, node);
	}
	else
	{
		ptree->root = node;
	}
}

static Node * findNode(Node * node, int key)
{
	if( node )
	{
		if( node->key < key )
		{
			return findNode(node->right, key);
		}
		else
		if( node->key > key )
		{
			return findNode(node->left, key);
		}
		else
		{
			return node;
		}
	}

	return 0;
}

static Node * max(Node * node)
{
	while( node && node->right )
	{
		node = node->right;
	}

	return node;
}

static void removeNode(Node * node)
{
	if( node )
	{
		if( node->left )
		{
			node->key = node->left->key;
			removeNode(node->left);
			node->left = 0;
		}
		else
		{
			Node * parent = node->parent;
			removeNode(node);
			parent->left = 0;
		}
	}
}

static void rm(BST * bst, int key)
{
	Node * cursor = findNode(bst->root, key);

	if( cursor )
	{
		Node * node = max(cursor->left);
	}
}

static void printNode(Node * node, int indent)
{
	int i;

	if( node )
	{
		printNode(node->right, indent + 1);

		for( i = 0; i < indent; i++ )
		{
			printf("   ");
		}

		printf("%2d\n", node->key);

		printNode(node->left, indent + 1);
	}
}

static void print(BST * ptree)
{
	if( ptree->root )
	{
		printNode(ptree->root, 0);
	}
}

int main()
{
	int i;
	int key;
	BST * b = createEmptyTree();

	srand(time(NULL));

	for( i = 0; i < 10; i++ )
	{
		int r = rand() % 20 + 1;
		add(b, r);
	}

	print(b);

	printf(" : ");
	scanf("%d", &key);

	rm(b, key);
	print(b);

	destroyTree(b);
	return 0;
}