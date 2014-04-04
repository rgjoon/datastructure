#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHILD_TYPE_EMPTY 0
#define CHILD_TYPE_LEFT 1
#define CHILD_TYPE_RIGHT 2
#define CHILD_TYPE_BOTH (CHILD_TYPE_LEFT | CHILD_TYPE_RIGHT)

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

static void notifyChanged(Node * parent, Node * me, Node * proxy)
{
    Node ** pp = 0;
    
    if( !parent )
    {
        return;
    }
    
    if( parent->left && parent->left == me )
    {
        pp = &(parent->left);
    }
    else
    if( parent->right && parent->right == me )
    {
        pp = &(parent->right);
    }
    
    if( pp )
    {
        *pp = proxy;
    }
}

static void copyData(Node * n1, Node * n2)
{
    if( n1 && n2 )
    {
        n1->key = n2->key;
    }
}

static int checkChildType(Node * node)
{
    int children = CHILD_TYPE_EMPTY;
    
    if( node )
    {
        if( node->left )
        {
            children += CHILD_TYPE_LEFT;
        }
        
        if( node->right )
        {
            children += CHILD_TYPE_RIGHT;
        }
    }
    
    return children;
}

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

    while( parent && !pp )
    {
        if( node->key < parent->key )
        {
            if( !parent->left )
            {
                pp = &(parent->left);
            }
            else
            {
                parent = parent->left;
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
                parent = parent->right;
            }
        }
        else
        {
            // duplicated
            copyData(parent, node);
            free(node);
            
            break;
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
	while( node && node->key != key )
	{
		if( node->key < key )
		{
            node = node->right;
		}
		else
		if( node->key > key )
		{
            node = node->left;
		}
	}

	return node;
}

static Node * findLargestNode(Node * node)
{
	while( node && node->right )
	{
		node = node->right;
	}

	return node;
}

static void removeNode(Node * node)
{
    int childType = checkChildType(node);

    if( childType == CHILD_TYPE_EMPTY )
    {
    	notifyChanged(node->parent, node, 0);
    	free(node);
    }
    else
    if( childType == CHILD_TYPE_LEFT )
    {
    	notifyChanged(node->parent, node, node->left);
    	free(node);
    }
    else
    if( childType == CHILD_TYPE_RIGHT )
    {
    	notifyChanged(node->parent, node, node->right);
    	free(node);
    }
    else
    if( childType == CHILD_TYPE_BOTH )
    {

    }
}

static void removeKey(BST * bst, int key)
{
	Node * cursor = findNode(bst->root, key);

	if( cursor )
	{
        removeNode(cursor);
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
			printf("    ");
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

static int getKey()
{
    int key;
    
    printf(" : ");
    scanf("%d", &key);
    
    return key;
}

int main()
{
	int i;
    int key;

	BST * b = createEmptyTree();

	srand((unsigned int)time(NULL));

	for( i = 0; i < 10; i++ )
	{
		int r = rand() % 20 + 1;
		add(b, r);
	}

    print(b);
    
    key = getKey();
    removeKey(b, key);
    
    print(b);

	destroyTree(b);
	return 0;
}