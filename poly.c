#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX_TERMS 100
# define MAX_POLYS 10

// Structures
typedef struct 
{
    char name[5];
    int start;
    int end;
    int total_terms;

}polys_info;


typedef struct 
{
    float coef;
    int expon;

}polynomial;


polynomial terms[MAX_TERMS];
int avail = 0;
polys_info info[MAX_POLYS];
int total_polys = 0;

// Functions

void Action()
{
    printf("\n------------------------------------------------\n");
    printf("Options:\n\n");
    printf("\tc\t\t\tCreate new polynomials\n");
    printf("\ta\t\t\tAdd specific term to a specific polynomial\n");
    printf("\td\t\t\tDelete specific term from a specific polynomial\n");
    printf("\tp\t\t\tPrint specific polynomial\n");
    printf("\ts\t\t\tShow specific term of a polynomial\n");

    printf("\tA\t\t\tArithmetic Calculation\n");
    printf("\tr\t\t\tStop\n");
    printf("\n\nYour Option:");

    
}
void CreatePoly()
{
    //printf("Size of poly:%lu\n", sizeof(polys)/sizeof(Poly));
    char name[5];
    int total_terms;
    

    printf("------> You need to create all the Polynomials at ONCE! <-------\n\n");
    printf("How many Polynomials do you want to store?:");
    scanf("%d", &total_polys);

    

    for(int j=0; j<total_polys; j++)
    {
        //get info of poly
        printf("------> Input the information of the %d Polynomial <-------\n\n", j+1);
        printf("Name:");
        scanf("%s", name);
        printf("Numbers of terms:");
        scanf("%d", &total_terms);
        printf("\n");
        
        // Store poly's info
        strcpy(info[j].name, name);
        info[j].start = avail;
        info[j].end = avail+total_terms - 1;
        info[j].total_terms = total_terms;

        // Input Polynomial
        for(int i=avail; i<avail+total_terms; i++)
        {
            printf("Coefficient:");
            scanf("%f", &terms[i].coef);
            printf("Exponent:");
            scanf("%d", &terms[i].expon);
            printf("\n");
        }

        // Change avail
        avail += total_terms;
    }
    
    
}
int SearchPoly()
{
    char name[5];
    printf("------> Input the Name of the Polynomial <-------\n\n");
    printf("Name:");
    scanf("%s", name);

    // Find head
    int index = -1;
    for(int i=0; i<total_polys; i++)
    {
        if(strcmp(info[i].name, name) == 0)
        {
            index = i;
            break;
        }
    }
    return index;
}
void Print()
{
    int index = SearchPoly();

    //Poly not found
    if(index == -1)
    {
        printf("Polynomial Not Found!\n");
        return;
    }

    printf("Polynomial %s: ", info[index].name);
    for(int i=info[index].start; i<=info[index].end; i++)
    {
        // First term
        if(i == info[index].start)
        {
            printf("%.2fx^%d ", terms[i].coef, terms[i].expon);
        }
        else
        {
            if(terms[i].coef > 0)
            {
                printf("+ ");
            }
            printf("%.2fx^%d ", terms[i].coef, terms[i].expon);
        }
    }
}
void ShowCoef()
{
    // Find Poly
    int index = SearchPoly();

    //Poly not found
    if(index == -1)
    {
        printf("Polynomial Not Found!\n");
        return;
    }
    
    // Input exponent
    int expon;
    printf("\n------> Input the Exponent of the desired coefficient <-------\n\n");
    printf("Exponent: ");
    scanf("%d", &expon);

    // Find coef
    int s_p = info[index].start;
    int e_p = info[index].end;

    for(int i=s_p; i<=e_p; i++)
    {
        if(expon == terms[i].expon)
        {
            printf("Coefficient: %.2f\n", terms[i].coef);
            return;
        }
    }
    printf("Coefficient: 0\n");
}
/*
void Test()
{
    for(int i=0; i<total_polys; i++)
    {
        Print(i);
        printf("\n");
    }
}*/
void Plus_Minus(int index_p2, int index_p1, char ao)
{
    // Create memory for answer
    int max_terms = info[index_p2].total_terms + info[index_p1].total_terms;
    polynomial *ans = (polynomial *)malloc(sizeof(polynomial) * max_terms);
    if(ans == NULL)
    {
        printf("There is insufficient memory available!\n");
        return;
    }
    int ans_index = 0; 

    // Get the strat and end index of each poly
    int s_p2 = info[index_p2].start;
    int e_p2 = info[index_p2].end;
    int s_p1 = info[index_p1].start;
    int e_p1 = info[index_p1].end;

    // Plus (P2+P1)
    if(ao == '+')
    {
        while(s_p1 <= e_p1 && s_p2 <= e_p2)
        {
            // ex: P1 > P2
            if(terms[s_p1].expon > terms[s_p2].expon)
            {
                // Attach P1
                ans[ans_index].coef = terms[s_p1].coef;
                ans[ans_index].expon = terms[s_p1].expon;

                ans_index++;
                s_p1++;

            }
            // ex: P2 > P1
            else if(terms[s_p1].expon < terms[s_p2].expon)
            {
                // Attach P2
                ans[ans_index].coef = terms[s_p2].coef;
                ans[ans_index].expon = terms[s_p2].expon;

                ans_index++;
                s_p2++;
            }
            // ex: P1 = P2
            else
            {
                int total_coef = terms[s_p1].coef + terms[s_p2].coef;
                if(total_coef != 0)
                {
                    // Attach total
                    ans[ans_index].coef = total_coef;
                    ans[ans_index].expon = terms[s_p2].expon;
                    ans_index++;
                }
                
                s_p1++;
                s_p2++;
            }
            
        }

        // Remaning terms
        if(s_p1 <= e_p1)
        {
            for(int i=s_p1; i<=e_p1; i++)
            {
                ans[ans_index].coef = terms[i].coef;
                ans[ans_index].expon = terms[i].expon;
                ans_index++;
            }
        }
        else if(s_p2 <= e_p2)
        {
            for(int i=s_p2; i<=e_p2; i++)
            {
                ans[ans_index].coef = terms[i].coef;
                ans[ans_index].expon = terms[i].expon;
                ans_index++;
            }
        }
    }
    // Minus (P2-P1)
    else
    {
        while(s_p1 <= e_p1 && s_p2 <= e_p2)
        {
            // ex: P1 > P2
            if(terms[s_p1].expon > terms[s_p2].expon)
            {
                // Attach P1
                ans[ans_index].coef = -terms[s_p1].coef;
                ans[ans_index].expon = terms[s_p1].expon;

                ans_index++;
                s_p1++;

            }
            // ex: P2 > P1
            else if(terms[s_p1].expon < terms[s_p2].expon)
            {
                // Attach P2
                ans[ans_index].coef = terms[s_p2].coef;
                ans[ans_index].expon = terms[s_p2].expon;

                ans_index++;
                s_p2++;
            }
            // ex: P1 = P2
            else
            {
                int total_coef = terms[s_p2].coef - terms[s_p1].coef;
                if(total_coef != 0)
                {
                    // Attach total
                    ans[ans_index].coef = total_coef;
                    ans[ans_index].expon = terms[s_p2].expon;
                    ans_index++;
                }
                
                s_p1++;
                s_p2++;
            }
            
        }

        // Remaning terms
        if(s_p1 <= e_p1)
        {
            for(int i=s_p1; i<=e_p1; i++)
            {
                ans[ans_index].coef = -terms[i].coef;
                ans[ans_index].expon = terms[i].expon;
                ans_index++;
            }
        }
        else if(s_p2 <= e_p2)
        {
            for(int i=s_p2; i<=e_p2; i++)
            {
                ans[ans_index].coef = terms[i].coef;
                ans[ans_index].expon = terms[i].expon;
                ans_index++;
            }
        }
    }

    // Print ans
    printf("------> Answer of P2 %c P1 <-------\n\n", ao);

    // No non-zero term
    if(ans_index == 0)
    {
        printf("0\n");
        return;
    }

    for(int i=0; i<ans_index; i++)
    {
        // First term
        if(i == 0)
        {
            printf("%.2fx^%d ", ans[i].coef, ans[i].expon);
        }
        else
        {
            if(ans[i].coef > 0)
            {
                printf("+ ");
            }
            printf("%.2fx^%d ", ans[i].coef, ans[i].expon);
        }
    }
    printf("\n");
    
}
void Mutiplication(index_p2, index_p1)
{
    int p2_s = info[index_p2].start;
    int p2_e = info[index_p2].end;

    int p1_s = info[index_p1].start;
    int p1_e = info[index_p1].end;

    int max_terms = info[index_p2].total_terms * info[index_p1].total_terms;

    polynomial *ans = (polynomial*)malloc(sizeof(polynomial) * max_terms);
    int ans_ind = 0;

    // start mutiplication
    for(int i=p2_s; i<=p2_e; i++)
    {
        for(int j=p1_s; j<=p1_e; j++)
        {
            float coef = terms[i].coef * terms[j].coef;
            int expon = terms[i].expon + terms[j].expon;

            if(ans_ind == 0)//first term
            {
                ans[ans_ind].coef = coef;
                ans[ans_ind].expon = expon;
                ans_ind++;
            }
            else
            {   
                // Check for duplicate
                int dup = 0;
                
                // muti of first term in each poly will be the maximum, no need to check for duplication of the first term
                for(int k=1; k<ans_ind; k++)
                {
                    //Same exponent
                    if(ans[k].expon == expon)
                    {
                        ans[k].coef += coef;
                        dup = 1;
                        break;
                        
                    }
                }

                // Different exponent
                if(!dup)
                {
                    ans[ans_ind].coef = coef;
                    ans[ans_ind].expon = expon;
                    ans_ind++;
                }
            }
        }
    }

    // Sort ans
    for(int i=1; i<ans_ind; i++)
    {
        for(int j=i+1; j<ans_ind; j++)
        {
            if(ans[j].expon > ans[i].expon)
            {
                // Change
                int per = ans[j].expon;
                ans[j].expon = ans[i].expon;
                ans[i].expon = per;

                float temp = ans[j].coef;
                ans[j].coef = ans[i].coef;
                ans[i].coef = temp;
            }
        }
    }

    //Print answer
    printf("------> Answer of P2 * P1 <-------\n\n");
    printf("%.2fx^%d ", ans[0].coef, ans[0].expon);
    for(int i=1; i<ans_ind; i++)
    {
        if(ans[i].coef > 0)
        {
            printf("+");
        }
        printf("%.2fx^%d ", ans[i].coef, ans[i].expon);
    }
    printf("\n\n");




    free(ans);
}
void Arithmetic()
{
    // Find P2 P1
    printf("------> Calculate P2 _ P1 <-------\n\n");
    printf("Infomation of Polynomial 2\n\n");

    int index_p2 = SearchPoly();
    if(index_p2 == -1)
    {
        printf("Polynomial 2 Not Found!\n");
        return;
    }
    printf("\n------------------------------------------------\n");
    printf("\nInfomation of Polynomial 1\n\n");
    int index_p1 = SearchPoly();
    if(index_p1 == -1)
    {
        printf("Polynomial 1 Not Found!\n");
        return;
    }

    // Input Arithmetic
    printf("------> Input the Arithmetic Operator (+, -, *) <-------\n\n");
    char arith[2];
    printf("Operator: ");
    scanf("%s", arith);

    switch(arith[0])
    {
        case '+':
            
            Plus_Minus(index_p2, index_p1, '+');
            break;

        case '-':
            Plus_Minus(index_p2, index_p1, '-');
            break;
        case '*':
            Mutiplication(index_p2, index_p1);
            break;
        /*case '/':
            break;*/
        default:
            printf("Error! Arithmetic Operator is not correct.\n\n");
    }

}

void Move(int insert_ind, char a)
{
    // Move front
    if(a == 'f')
    {
        for(int i=insert_ind; i<avail-1; i++)
        {
            terms[i] = terms[i+1];
        }
    }
    // Move back
    else if(a == 'b')
    {
        for(int i=avail-1; i>=insert_ind; i--)
        {
            terms[i+1] = terms[i];
        }
    }
    
}
void Refresh_Poly(int index, int insert_ind, char a)
{
    // Move front
    if(a == 'f')
    {   
        // Refresh other poly
        for(int i=0; i<total_polys; i++)
        {
            // skip if meets the inserted poly
            if(i == index)
            {
                continue;
            }

            if(info[i].start >= insert_ind)
            {
                info[i].start--;
                info[i].end--;
            }

        } 
    }
    // Move back
    else if(a == 'b')
    {
        // Refresh other poly
        for(int i=0; i<total_polys; i++)
        {
            // skip if meets the inserted poly
            if(i == index)
            {
                continue;
            }
            if(info[i].start >= insert_ind)
            {
                info[i].start++;
                info[i].end++;
            }
            else if(info[i].end >= insert_ind)
            {
                info[i].end++;
            }
        } 

    }
    
}
void Add_Del_Term(int act)
{
    int index = SearchPoly();

    //Poly not found
    if(index == -1)
    {
        printf("Polynomial Not Found!\n");
        return;
    }
    
    
    int find = 0, insert_ind = -1;
    int s_p = info[index].start;
    int e_p = info[index].end;
    int coef, expon;

    //Add
    if(act == 'a')
    {
        
        printf("\n------> Input the Coefficient and Exponent <-------\n\n");
        printf("Coefficient: ");
        scanf("%d", &coef);
        printf("Exponent: ");
        scanf("%d", &expon);

        // Whether the term exists or add a new term
        for(int i=s_p; i<=e_p; i++)
        {
            // Add coef
            if(terms[i].expon == expon)
            {
                find = 1;
                terms[i].coef += coef;
                break;
            }
            // Record insert index and Add 1 to total terms
            else if(terms[i].expon < expon)
            {
                insert_ind = i;
                printf("------------insert_ind: %d\n", insert_ind);
                break;
            }
        }

        // move terms array
        
        if(!find)
        {
            printf("IN !find\n");
            // add term to the last of the poly
            if(insert_ind == -1)
            {
                insert_ind = info[index].end + 1;
            }
            printf("------------insert_ind: %d\n", insert_ind);

            // terms is full
            if(avail > MAX_TERMS - 1)
            {
                printf("Terms is FULL!\n");
            }
            else
            {
                // move back and add the term
                Move(insert_ind, 'b');
                terms[insert_ind].coef = coef;
                terms[insert_ind].expon = expon;

                avail ++;

                // Change other polys' start end total_terms if needed
                Refresh_Poly(index, insert_ind, 'b');

                // Change current poly
                info[index].total_terms++;
                info[index].end++;

                
            }
            
        }
        
        return;
    }

    // delete
    
    printf("\n------> Input the Exponent <-------\n\n");
    printf("Exponent: ");
    scanf("%d", &expon);

    // Whether the term exists 
    for(int i=s_p; i<=e_p; i++)
    {
        // Find exponent
        if(terms[i].expon == expon)
        {
            find = 1;
            insert_ind = i;
            break;
        }
        // Exponent doesn't exist 
        else if(terms[i].expon < expon)
        {
            break;
        }
    }

    // move terms array
    if(find)
    {
       // printf("IN !find\n");
        //printf("------------insert_ind: %d\n", insert_ind);
        // move front 
        Move(insert_ind, 'f');
        
        avail --;

        // Change other polys' start end total_terms if needed
        Refresh_Poly(index, insert_ind, 'f');

        // Change current poly
        info[index].total_terms--;
        info[index].end--;

        
    }
    else
    {
        printf("Term not found!\n\n");
    }

    /*for(int i=0; i<total_polys; i++)
    {
        printf("new_start: %d, new_end: %d\n\n", info[i].start, info[i].end);
    }*/
    
}


int main()
{
    //option
    char opt[2];
    opt[0] = '1';

    while(opt[0]!='r')
    {
        
        Action();
        scanf("%s", opt);
        
        printf("\topt:%c\n\n", opt[0]);
        switch(opt[0])
        {
            case 'c':
                CreatePoly();
                
                break;

            case 'a':
                Add_Del_Term('a');
                break;

            case 'd':
                Add_Del_Term('d');
                break;

            case 'p':

                Print();
                break;

            case 's':
                ShowCoef();
                break;

            case 'A':
                Arithmetic();
                break;

            case 'r':
                
                break;
            case 't'://test
                //Test();
                break;

            default:
                printf("Error! Option is not correct.\n\n");
        }
    }

    
}