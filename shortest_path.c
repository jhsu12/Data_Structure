#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LINE_LENGTH 90
typedef struct edge
{
    int level;
    int weight;
    struct edge *next;
}Edge;
int ob_w[26];

void link_edge(int ind, int level, int weight, Edge **aja_list)
{
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge -> level = level;
    new_edge -> weight = weight;

    if(aja_list[ind] == NULL)
    {
        new_edge -> next = NULL;
        aja_list[ind] = new_edge;
    }
    else
    {
        new_edge -> next = aja_list[ind];
        aja_list[ind] = new_edge;
    }

}
void print_edge(int total_lv, Edge **aja_list)
{
    for(int i=0; i<total_lv; i++)
    {
        printf("L%d : ", i+1);
        Edge *temp = aja_list[i];
        while(temp)
        {
            printf("L%d W%d -> ", temp -> level, temp -> weight);
            temp =  temp -> next;
        }
        printf("Null\n");
    }
}
int main()
{
    char filename[20];
    printf("Input the file name: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");

    if(!file)
    {
        printf("File not found!\n");
        return 0;
    }

    char buf[MAX_LINE_LENGTH];

    // read total obstacles
    fgets(buf, MAX_LINE_LENGTH, file);
    int total_ob;
    if(buf[1] != '\n')
    {
        total_ob = (buf[0] - '0')*10 + buf[1] - '0';
    }
    else
    {
        total_ob = buf[0] - '0';
    }

    // read obstacles
    int ob_energy = 0;
    for(int i=0; i<total_ob; i++)
    {
        ob_energy = 0;
        fgets(buf, MAX_LINE_LENGTH, file);
        if(buf[3] != '\n')
        {
            ob_energy = (buf[2] - '0')*10 + buf[3] - '0';
        }
        else
        {
            ob_energy = buf[2] - '0';
        }
        ob_w[buf[0]-'A'] = ob_energy;
    }

    // read total levels and total edges
    fgets(buf, MAX_LINE_LENGTH, file);
    int total_lv, total_e ;
    if(buf[1] != 32)
    {
        total_lv = (buf[0] - '0')*10 + buf[1]-'0';
        if(buf[4]!='\n')
        {
            total_e = (buf[3] - '0')*10 + buf[4]-'0';
        }
        else
        {
            total_e = buf[3]-'0';
        }
    }
    else
    {
        total_lv = buf[0]-'0';
        if(buf[3]!='\n')
        {
            total_e = (buf[2] - '0')*10 + buf[3]-'0';
        }
        else
        {
            total_e = buf[2]-'0';
        }
    }
    
    int *found = (int *)malloc(sizeof(int) * total_lv);
    Edge **aja_list = (Edge **)malloc(sizeof(Edge*) * total_lv);

    for(int i=0; i<total_lv; i++)
    {
        found[i] = 0;
        aja_list[i] = NULL;
    }

    //read edges
    int l1, l2;
    int ob_ind, count;
    int weight = 0;
    int edge_w_ind;
    for(int i=0; i<total_e; i++)
    {
        weight = 0;
        fgets(buf, MAX_LINE_LENGTH, file);
        // read level
        // first level has twp digits
        if(buf[1] != 32)
        {
            l1 = (buf[0]-'0')*10 + buf[1]-'0';
            // second level has two digits
            if(buf[4] != 32)
            {
                l2 = (buf[3]-'0')*10 + buf[4]-'0';
                edge_w_ind = 6;
            }
            else
            {
                l2 = buf[3]-'0';
                edge_w_ind = 5;
            }
        }
        else
        {
            l1 = buf[0]-'0';
            // second level has two digits
            if(buf[3] != 32)
            {
                l2 = (buf[2]-'0')*10 + buf[3]-'0';
                edge_w_ind = 5;
            }
            else
            {
                l2 = buf[2]-'0';
                edge_w_ind = 4;
            }
        }
        
        
       //printf("%d %d start: %d\n", l1, l2, edge_w_ind);

        for(int j=edge_w_ind; buf[j]!='\0'; j+=3)
        {
            ob_ind = buf[j]-'A';
            count = buf[j+1]-'0';
            weight += ob_w[ob_ind]*count;
            
        }
        link_edge(l1-1, l2, weight, aja_list);
        link_edge(l2-1, l1, weight, aja_list);
        
    }
    
    //print_edge(total_lv, aja_list);
    fclose(file);

    // calculate minimum cost
    // start at level 1 (index 0)
    found[0] = 1;
    int min_cost ;
    int total_cost = 0;
    Edge *cur, *min= NULL;
    for(int i=1; i<total_lv; i++)
    {
        // find minimum cost edges that haven't visit from all found level
       
        cur = NULL;
        min = NULL;
        min_cost = INT_MAX;

        for(int j=0; j<total_lv; j++)
        {
            // found level
            if(found[j])
            {
                cur = aja_list[j];
                

                while(cur)
                {
                    // haven't find level and is minimum
                    if(!found[cur -> level-1] && cur -> weight < min_cost)
                    {
                        min_cost = cur -> weight;
                        min = cur;
                       
                    }
                    cur = cur -> next;
                    
                }
            }
        }

        //
        total_cost += min_cost;
        found[min -> level - 1 ] = 1;
        //printf("L%d W%d -> ", min -> level, min -> weight);
    }
    printf("%d\n", total_cost);
    return 0;
}