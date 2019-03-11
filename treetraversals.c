#include<stdio.h>
#include<stdlib.h>

struct tnode
{
	int data;
	struct tnode *left;
	struct tnode *right;
}*root=NULL;

struct snode
{
	struct tnode *t;
	struct snode *next;
}*in=NULL,*pre=NULL,*post1=NULL,*post2=NULL;

void insert(struct tnode ** );
void inorder(struct tnode * );
void preorder(struct tnode * );
void postorder(struct tnode * );
void push(struct snode ** ,struct tnode * );
struct tnode *pop(struct snode ** );

int main()
{
	while(1)
	{
		int choice;
		printf("1.insert\n2.inorder\n3.preorder\n4.postorder\n5.exit\n");
		printf("enter choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				insert(&root);
				break;
			case 2:
				inorder(root);
				printf("\n");
				break;
			case 3:
				preorder(root);
				printf("\n");
				break;
			case 4:
				postorder(root);
				printf("\n");
				break;
			case 5:
				exit(0);
			default:
				printf("enter valid choice\n");

		}
	}

	return 0;
}

void insert(struct tnode **root)
{
	int n;
	printf("enter element : ");
	scanf("%d",&n);
	struct tnode *new=(struct tnode *)malloc(sizeof(struct tnode));
	new->data=n;
	new->left=NULL;
	new->right=NULL;
	if(*root==NULL)
	{
		*root=new;
	}
	else
	{
		struct tnode *temp=*root,*parent=temp;
		while(temp!=NULL)
		{
			parent=temp;
			if(n>temp->data)
			{
				temp=temp->right;
			}
			else if(n<temp->data)
				temp=temp->left;
			else
			{
				printf("duplicate value\n");
				return;
			}			
		}
		if(n>parent->data)
			parent->right=new;
		else if(n<parent->data)
			parent->left=new;
	}
}

void inorder(struct tnode *root)
{
	struct tnode *temp=root;
	while(1)
	{	
		if(temp!=NULL)
		{
			push(&in,temp);
			temp=temp->left;
		}
		else
		{
			if(in!=NULL)
			{	
				temp=pop(&in);
				printf("%d\t",temp->data);
				temp=temp->right;
			}
			else
				break;
		}
	}
}

void preorder(struct tnode *root)
{
	struct tnode *temp,*p;
	temp=root;
	push(&pre,temp);
	while(pre!=NULL)
	{
		p=pop(&pre);	
		printf("%d\t",p->data);
		push(&pre,p->right);
		push(&pre,p->left);
	}
}

void postorder(struct tnode *root)
{
	struct tnode *temp=root,*p;
	push(&post1,root);
	while(post1!=NULL)
	{
		p=pop(&post1);
		push(&post2,p);
		push(&post1,p->left);
		push(&post1,p->right);
	}
	while(post2!=NULL)
	{
		p=pop(&post2);
		printf("%d\t",p->data);
	}
}

void push(struct snode **top,struct tnode *cur)
{
	if(cur==NULL)
		return;
	struct snode *new=(struct snode *)malloc(sizeof(struct snode));
	new->t=cur;
	if(*top==NULL)
	{
		new->next=NULL;
		*top=new;
	}
	else
	{
		new->next=*top;
		*top=new;
	}
}

struct tnode *pop(struct snode **top)
{
	struct snode *temp=*top;
	struct tnode *cur;
	cur=temp->t;
	*top=(*top)->next;
	free(temp);
	return cur;
}
