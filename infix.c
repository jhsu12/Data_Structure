#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    char op;
    int val;
    struct tree *leftchild;
    struct tree *rightchild;
}Tree;
// Tree stack
typedef struct tree_stack
{
    Tree *array[22];
    int top;
}Tree_Stack;

int tree_stack_full(Tree_Stack *s)
{
    if(s -> top == 21)
    {
        return 1;
    }
    return 0;
}
int tree_stack_empty(Tree_Stack *s)
{
    if(s -> top == -1)
    {
        return 1;
    }
    return 0;
}

void tree_push(Tree_Stack *s, Tree *c)
{
    if(!tree_stack_full(s))
    {
        s -> array[++ s -> top] = c;
    }
}

Tree *tree_pop(Tree_Stack *s)
{
    if(!tree_stack_empty(s))
    {
        return s -> array[s -> top --];
    }
    return NULL;
}

// Normal Stack
typedef struct stack
{
    char array[22];
    int top;
}Stack;

int stack_full(Stack *s)
{
    if(s -> top == 21)
    {
        return 1;
    }
    return 0;
}
int stack_empty(Stack *s)
{
    if(s -> top == -1)
    {
        return 1;
    }
    return 0;
}

void push(Stack *s, char c)
{
    if(!stack_full(s))
    {
        s -> array[++ s -> top] = c;
    }
}

char pop(Stack *s)
{
    if(!stack_empty(s))
    {
        return s -> array[s -> top --];
    }
    return 'n';
}

// Tree_queue
void addq(Tree *queue[], int *front, int *rear, Tree *node)
{
    // queue full
    if((*rear + 1)%22 == *front)
    {
        return;
    }
    // add queue
    *rear = (*rear + 1)%22;
    queue[*rear] = node;
}
Tree *deleteq(Tree *queue[], int *front, int *rear)
{
    // queue is empty
    if(*front == *rear)
    {
        return NULL;
    }

    *front = (*front + 1)%22;
    return queue[*front];

}

// other func
int isp(char c)
{
    switch (c)
    {
        case '(':
            return 0;
        case ')':
            return 19;
        case '+':
            return 12;
        case '-':
            return 12;
        case '*':
            return 13;
        case '/':
            return 13;
        case '\0':
            return 0;
        
    }
    return -1;
}
int icp(char c)
{
    switch (c)
    {
        case '(':
            return 20;
        case ')':
            return 19;
        case '+':
            return 12;
        case '-':
            return 12;
        case '*':
            return 13;
        case '/':
            return 13;
        case '\0':
            return 0;
        
    }
    return -1;
}

char *infix_to_postfix(char *infix)
{
    // inital stack
    Stack exp;
    exp.top = -1;

    char *postfix = (char *)malloc(sizeof(char) * 22);
    int ind = 0;

    for(int i=0; infix[i]!='\0'; i++)
    {
        // Operand
        if(infix[i] >= 65 && infix[i] <= 90)
        {
            postfix[ind] = infix[i];
            ind++;
        }
        else if(infix[i] == ')')
        {
            while(exp.array[exp.top] != '(')
            {
                postfix[ind] = pop(&exp);
                ind++;
            }
            // discard '('
            pop(&exp);
        }
        else
        {
            
            while(isp(exp.array[exp.top]) >= icp(infix[i]))
            {
                
                postfix[ind] = pop(&exp);
                ind++;
            }  
           
            
            push(&exp, infix[i]);
        }
    }

    while(!stack_empty(&exp))
    {
        postfix[ind] = pop(&exp);
        ind++;
    }
    
    return postfix;
}

Tree *make_tree(char *postfix)
{
    //initial tree stack
    Tree_Stack exp;
    exp.top = -1;

    for(int i=0; postfix[i]!='\0'; i++)
    {
        Tree *new_node = (Tree *)malloc(sizeof(Tree));
        new_node -> op = postfix[i];
        new_node -> leftchild = NULL;
        new_node -> rightchild = NULL;


        if(postfix[i]>= 65 && postfix[i] <= 90)
        {
            tree_push(&exp, new_node);
        }
        else
        {
            Tree *rc = tree_pop(&exp);
            Tree *lc = tree_pop(&exp);

            new_node -> leftchild = lc;
            new_node -> rightchild = rc;

            tree_push(&exp, new_node);
        }
    }

    return tree_pop(&exp);
}
void preorder(Tree *root)
{
    if(root)
    {
        printf("%c", root -> op);
        preorder(root -> leftchild);
        preorder(root -> rightchild);   
    }
    
}

void level_order(Tree *root)
{
    if(!root)
    {
        return;
    }

    Tree *queue[22];
    int front = 0;
    int rear = 0;

    
    addq(queue, &front, &rear, root);
    
    
    while(front != rear)
    {
        
        Tree *temp = deleteq(queue, &front, &rear);
        if(temp)
        {
            printf("%c", temp -> op);
            addq(queue, &front, &rear, temp -> leftchild);
            addq(queue, &front, &rear, temp -> rightchild); 
        }
        

    }


}

int find[26];
int val[26];
int error = 0;
void calculate(Tree *root)
{
    if(root)
    {
        calculate(root -> leftchild);
        calculate(root -> rightchild);
        
        switch(root -> op)
        {
            case '+':
                root -> val = root -> leftchild -> val + root -> rightchild -> val;
                break;
            case '-':
                root -> val = root -> leftchild -> val - root -> rightchild -> val;
                break;
            case '*':
                root -> val = root -> leftchild -> val * root -> rightchild -> val;
                break;
            case '/':
                if(root -> rightchild -> val == 0)
                {
                    printf("\nError! Can't divide by 0\n");
                    error = 1;
                    return;
                }
                root -> val = root -> leftchild -> val / root -> rightchild -> val;
                break;
            default:

                if(!error)
                {
                    if(find[root -> op - 65])
                    {
                        root -> val = val[root -> op - 65];
                    }
                    else
                    {
                        printf("Input the value of %c: ", root -> op);
                        scanf("%d", &root -> val);

                        val[root -> op - 65] = root -> val;
                        find[root -> op - 65] = 1;
                    } 
                }
                
                break;
        }
    }


}

int alph, oper, lp, rp = 0;
char operand(char c)
{
    char v;
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            v = 'o';
            oper++;
            break;
        case '(':
            v = 'l';
            lp++;
            break;
        case ')':
            v = 'r';
            rp++;
            break;
        default:
            v = 'a';
            alph++;
            break;
        
    }
    return v;
}
int valid(char *infix)
{
    char pre = operand(infix[0]);
    char cur;

    for(int i=1; infix[i]!='\0'; i++)
    {
        cur = operand(infix[i]);

        if(pre == 'o')
        {
            // ++, +)
            if(cur == 'o' || cur == 'r')
            {
                return 0;
            }
        }
        else if(pre == 'l')
        {
            // (+, ()
            if(cur == 'o' || cur == 'r')
            {
                return 0;
            }
        }
        else if(pre == 'r')
        {
            // )A, )(
            if(cur == 'a' || cur == 'l')
            {
                return 0;
            }
        }
        else if(pre == 'a')
        {
            // A(, AB
            if(cur == 'l' || cur == 'a')
            {
                return 0;
            }
        }
        pre = cur;
    }

    if(lp != rp || alph != oper + 1)
    {
        return 0;
    }
    return 1;
}



int main()
{
    
    char infix[22];
    printf("\nInput the Infix expression: ");
    scanf("%s", infix);
    
    if(!valid(infix))
    {
        printf("\nInvalid Infix expression!\n");
        return 0;
    }

    char *postfix = infix_to_postfix(infix);
    printf("The postfix expression: %s\n", postfix);

    Tree *root = make_tree(postfix);
    printf("The prefix expression: ");
    preorder(root);
    printf("\n");

    printf("The level-order of expression tree: ");
    level_order(root);
    printf("\n");

    printf("Tap esc to stop (or anykey to continue):");
    char act[2];
    scanf("%s", act);

    while(act[0]!=27)
    {
        // reset root's value , find and error
        error = 0;
        root -> val = 0;
        for(int i=0; i<26; i++)
        {
            find[i] = 0;
        }
        calculate(root);
        if(!error)
        {
          printf("The Evaluation of the expression %d\n", root -> val);  
        }
        

        printf("Tap esc to stop (or anykey to continue):");
        scanf("%s", act);
        printf("\n");
    }
    

    return 0;
}