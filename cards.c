#include <stdio.h>
#include <stdlib.h>

typedef struct card
{
    char suit;
    int num;
}Card;

typedef struct record_card
{
    Card card;
    // card in record_card
    int in ;
}Record_Card;

typedef struct card_node
{
    Card card;
    struct card_node *next;
}Card_Node;

Card_Node *player_1[4];
Card_Node *player_2[4];
Record_Card record[52];
int player = 1;

void Action()
{
    printf("\n------------------------------------------------\n");
    printf("Options:\n\n");
    printf("\tp\t\t\tPrint Cards\n");
    printf("\td\t\t\tDelete Cards\n");
    printf("\tt\t\t\tPrint all the Cards\n");
    printf("\tg\t\t\tPlay Game\n");
   
    printf("\ts\t\t\tStop\n");
    printf("\n\nYour Option:");

    
    
}
int suit_index(char suit)
{
    if(suit == 'c')
    {
       return 0;
    }
    else if(suit == 'd')
    {
       return 1;
    }
    else if(suit == 'h')
    {
        return 2;
    }
    return 3;
}

void insert_node(int rec_ind)
{
    // Create new_node
    Card_Node *new_card_node = (Card_Node *)malloc(sizeof(Card_Node));
    
    // assign data to new_card_node
    char suit = record[rec_ind].card.suit;
    new_card_node -> card.num = record[rec_ind].card.num;
    new_card_node -> card.suit = suit;
    new_card_node -> next = NULL;

    // check the suit for index of insertion
    Card_Node *temp;
    int suit_ind = suit_index(suit);
    //printf("%d\n", suit_ind);
    
    if(player%2 == 1)
    {
        temp = player_1[suit_ind];
        if(temp == NULL)
        {
            player_1[suit_ind] = new_card_node;
            return;
        }
    }
    else
    {
        temp = player_2[suit_ind];
        if(temp == NULL)
        {
            player_2[suit_ind] = new_card_node;
            return ;
        }
       
    }

    // temp isn't the last node
    while(temp -> next != NULL)
    {
        temp = temp -> next;
    }

    //insert
    temp -> next = new_card_node;
    
    
}

void input_cards(int n)
{   
    printf("\n");
    for(int i=0; i<n; i++)
    {
        // random index between 0 and 51
        int re_ind = rand() % 52;

        // check if record[index] still in record card
        while(!record[re_ind].in)
        {
            re_ind = rand() % 52;

        }

        
        printf("INPUT: %c%d\n", record[re_ind].card.suit, record[re_ind].card.num);
        insert_node(re_ind);

        // update card status in record
        record[re_ind].in = 0; 

    }
    printf("\n");
    
}
void link_node(Card_Node *pre, Card c)
{
    // Create new node
    Card_Node *new_card = (Card_Node *)malloc(sizeof(Card_Node));
    new_card -> card = c;
    new_card -> next = NULL;

    pre -> next = new_card; 

}
Card_Node * reverse_print(Card_Node *head)
{
    /* Reverse Node and return new head */

    // copy cards
    Card copy[52];
    Card_Node *temp = head;

    int l = 0;
    for(l=0; temp != NULL; temp = temp -> next)
    {
        copy[l] = temp -> card;
        l++;
    }

    if(l == 0)
    {
        return NULL;
    }

    // link card in reverse order
    l--;
    Card_Node *re_head = (Card_Node *)malloc(sizeof(Card_Node));
    re_head -> card = copy[l];
    re_head -> next = NULL;

    l--;

    Card_Node *pre = re_head;
    

    for(;l>=0; l--)
    {
        link_node(pre, copy[l]);
        pre = pre -> next;
    }

    return re_head;

}
Card_Node * ascending_print(Card_Node *head)
{
    /* Sort Node and return new head */

    // copy cards
    Card copy[52];
    Card_Node *temp = head;

    int l = 0;
    for(l=0; temp != NULL; temp = temp -> next)
    {
        copy[l] = temp -> card;
        l++;
    }

    if(l == 0)
    {
        return NULL;
    }

    //Sort card in ascending order
    Card t;
    for(int i=0; i<l; i++)
    {
        for(int j=i+1; j<l; j++)
        {
            // A is the biggest
            if(copy[i].num == 1)
            {
                t = copy[i];
                copy[i] = copy[j];
                copy[j] = t;
                
            }
            else if(copy[j].num == 1)
            {
                continue;
            }
            else if(copy[i].num > copy[j].num)
            {
                t = copy[i];
                copy[i] = copy[j];
                copy[j] = t;
            }
        }
    }

    // link card in reverse order
    
    Card_Node *a_head = (Card_Node *)malloc(sizeof(Card_Node));
    a_head -> card = copy[0];
    a_head -> next = NULL;

    

    Card_Node *pre = a_head;
    

    for(int i=1; i<l; i++)
    {
        link_node(pre, copy[i]);
        pre = pre -> next;
    }

    return a_head;

}
void free_cards(Card_Node *temp)
{
    Card_Node *pre = temp;
    while(pre)
    {
        pre = pre -> next;
        free(temp);
        temp = pre;
    }
}
void print(Card_Node *head)
{
    Card_Node *temp = head;
    if(!temp)
    {
        printf("--");
    }
    while(temp != NULL)
    {
        if(temp -> card.num == 1)
        {
            printf("%cA ", temp -> card.suit);
        }
        else
        {
            printf("%c%d ", temp -> card.suit, temp -> card.num);
        }
        
        temp = temp -> next;
    }
    printf("\n");
}
void initial_setting()
{
    for(int i=0; i<52; i++)
    {
        // card status
        record[i].in = 1;

        // set number
        record[i].card.num = (i%13 + 1);

        //set suit
        //club
        if(i/13 == 0)
        {
            record[i].card.suit = 'c';
            
        }
        //diamond
        else if(i/13 == 1)
        {
            record[i].card.suit = 'd';
            
        }
        //heart
        else if(i/13 == 2)
        {
            record[i].card.suit = 'h';
            
        }
        //shades
        else
        {
            record[i].card.suit = 's';
            
        }

        // Set player_1 and player_2
        if(i%13 == 0)
        {
            player_1[i/13] = NULL;
            player_2[i/13] = NULL;
        }
    }

}
void print_cards()
{
    /* Get suits and players and suit's index and ways to print */

    printf("\n------------------------------------------------\n");
    //player
    int player;
    printf("Input which player's cards (1 or 2): ");
    scanf("%d", &player);
    getchar(); // discard '\n'

    //suit
    char suit;
    printf("\n------------------------------------------------\n");
    printf("Input the suit (in lowercase):");
    suit = getchar();
    printf("%c\n", suit);
    
    printf("\n");
    

    //suit's index
    int suit_ind = suit_index(suit);

    //head for the required suit
    Card_Node *head = NULL;
    if(player == 1)
    {
        head = player_1[suit_ind];
    }
    else if(player == 2)
    {
        head = player_2[suit_ind];
    }
    else
    {
        printf("Error! Player is invalid.\n\n");
        return ;
    }

    //ways to print
    char opt[2];
    opt[0] = '1';
    
    printf("Options:\n\n");
    printf("\tn\t\t\tPrint Cards in normal sequence\n");
    printf("\tr\t\t\tPrint Cards in reverse sequence\n");
    printf("\ta\t\t\tPrint Cards in ascending order\n");
    printf("\n\nYour Option:");

    scanf("%s", opt);
    printf("\topt:%c\n\n", opt[0]);

    switch(opt[0])
    {
        case 'n':
            print(head);
            break;

        case 'r':
            head = reverse_print(head);
            print(head);
            free_cards(head);
            break;

        case 'a':
            head = ascending_print(head);
            print(head);
            free_cards(head);
            break;

        default:
            printf("Error! Option is not correct.\n\n");
    }
}
Card_Node* delete_card(Card_Node *head, Card del)
{
    // No card in deck suit
    if(head == NULL)
    {
        printf("No card in %c\n", del.suit);
        return NULL;
    }
    
    Card_Node *max = NULL;
    int maxx = 15;

    Card_Node *min = NULL;
    int minn = 15;

    Card_Node *temp = head;
    
    

    while(temp)
    {
        int num = temp -> card.num;

        //del.num == A
        if(del.num == 1)
        {
            // Find min
            if(num != 1 && num < minn)
            {
                minn = num;
                min = temp;
            }
            else if(num == 1)
            {
                if(14 < minn)
                {
                    minn = num;
                    min = temp;
                }
            }
            
        }
        //del.num != A
        else
        {
            if(num == 1)
            {   
                //max
                if(14 < maxx)
                {
                    maxx = 14;
                    max = temp;
                }

            }
            //max
            else if(num > del.num)
            {
                if(num < maxx)
                {
                    maxx = num;
                    max = temp;
                }
            }
            //min
            else if(num < minn)
            {
                minn = num;
                min = temp;
            }
        }
        
        
        temp = temp -> next;
    }

    

    Card_Node *d;
    
    if(max)
    {
        
        if(max -> card.num == 1)
        {
            printf("Delete Card %cA\n", max->card.suit);
        }
        else
        {
          printf("Delete Card %c%d\n", max->card.suit, max->card.num);  
        }

        
        d = max;
        
    }
    else if(min)
    {
        if(min -> card.num == 1)
        {
            printf("Delete Card %cA\n", min->card.suit);
        }
        else
        {
          printf("Delete Card %c%d\n", min->card.suit, min->card.num);  
        }

        
        d = min;
    }

    //update record

    char suit = d -> card.suit;
    if(suit == 'c')
    {
        record[d -> card.num -1].in = 1;
    }
    else if(suit == 'd')
    {
        record[13+ d -> card.num -1].in = 1;
    }
    else if(suit == 'h')
    {
        record[26+ d -> card.num -1].in = 1;
    }
    else//shades
    {
        record[39+ d -> card.num -1].in = 1;
    }

    //delete card_node
    temp = head;
    Card_Node *pre = NULL;
    while(temp)
    {
        if(temp -> card.num == d -> card.num)
        {
            break;
        }
        pre = temp;
        temp = temp -> next;
    }

    if(pre == NULL)
    {
        head = head -> next;
    }
    else
    {
        pre -> next = temp -> next;
    }

    return head;

}
void delete_setting()
{
    /* Get suits and players and suit's index */

    printf("\n------------------------------------------------\n");
    //player
    int player;
    printf("Input which player's cards (1 or 2): ");
    scanf("%d", &player);
    getchar(); // discard '\n'

    //card
    Card del;
    printf("\n------------------------------------------------\n");
    printf("Input the number: ");
    scanf("%d", &del.num);
    getchar(); // discard '\n'
    printf("\n");

    printf("Input the suit (in lowercase): ");
    del.suit = getchar();
    printf("\n");
    

    //suit's index
    int suit_ind = suit_index(del.suit);

    //head for the required suit
    Card_Node *head = NULL;
    if(player == 1)
    {
        head = player_1[suit_ind];
        
        player_1[suit_ind] = delete_card(head, del);
    }
    else if(player == 2)
    {
        head = player_2[suit_ind];
        player_2[suit_ind] = delete_card(head, del);
    }
    else
    {
        printf("Error! Player is invalid.\n\n");
        return ;
    }

     

}
void print_all()
{
    printf("Player1\n");
    for(int i=0; i<4; i++)
    {
        print(player_1[i]);
    }
    
    printf("\nPlayer2\n");
    for(int i=0; i<4; i++)
    {
        print(player_2[i]);
    }
}
Card random_delete()
{
    Card random_card;
    Card_Node *temp = NULL;

    // player_2
    if(player%2 == 0)
    {
        // find the first card node and delete from head
        
        for(int i=0; i<4; i++)
        {
            temp = player_2[i];
            if(temp)
            {
                player_2[i] = temp -> next;
                break;
            }
        }
    }
    // player_1
    else
    {
        // find the first card node and delete from head
        
        for(int i=0; i<4; i++)
        {
            temp = player_1[i];
            if(temp)
            {
                player_1[i] = temp -> next;
                break;
            }
        }
    }

    //assign to random_card
    random_card.num = temp -> card.num;
    random_card.suit = temp -> card.suit;
    if(temp -> card.num == 1)
    {
        printf("Delete %cA\n", temp -> card.suit);
    }
    else
    {
        printf("Delete %c%d\n", temp -> card.suit, temp -> card.num);
    }
    

    free(temp);
    
   
    return random_card;
    

}
int no_one_win()
{
    int p1 = 0;
    int p2 = 0;

    for(int i=0; i<4; i++)
    {
        if(player_1[i])
        {
            p1 = 1;
        }

        if(player_2[i])
        {
            p2 = 1;
        }
    }

    // Game is still going
    if(p1 && p2)
    {
        return 1;
    }
    return 0;
    
}
void play_game()
{
    /*random delete player 1
    then player 2 deletes specific card according to player1's card
    then keep going
    if one of the player doesn't have the specific card to delete
    then it needs to take a card from record
    then the other player random delete*/

    // Game begins with random deletion
    print_all();
    
    Card random_card = random_delete();
    printf("--------Random Card:%c%d--------\n", random_card.suit, random_card.num);
    print_all();
    player++;

    int suit_ind = suit_index(random_card.suit);
    Card_Node *del_head = NULL;
    int no_card = 0;

    while(no_one_win())
    {
        
        printf("--------Random Card:%c%d--------\n", random_card.suit, random_card.num);

        del_head = NULL;
        no_card = 0;
        
        
        if(player%2 == 0)
        {
            del_head = player_2[suit_ind];

            // No card
            if(del_head == NULL)
            {
                printf("Player2 takes new card:");
                input_cards(1);
                no_card = 1;
            }
            else
            {
                player_2[suit_ind] = delete_card(del_head, random_card);
            }
        }
        else
        {
            del_head = player_1[suit_ind];

            // No card
            if(del_head == NULL)
            {
                printf("Player1 takes new card:");
                input_cards(1);
                no_card = 1;
            }
            else
            {
                player_1[suit_ind] = delete_card(del_head, random_card);
            }
           
        }
        

        player++;

        if(no_card)
        {
            printf("--------New Random Card--------\n");
            random_card = random_delete();
            suit_ind = suit_index(random_card.suit);
            
            player++;
        }
        print_all();
        
    }


}
int main()
{
    
    //setting

    //Set record's data and players data to NULL
    initial_setting();
    
    //Input cards for two players
    int n;
    for(int i=0; i<2; i++)
    {
        printf("Input the number of cards for player%d: ", i+1);
        scanf("%d", &n);
        input_cards(n);
        player++;
    }

    
    
    //option
    char opt[2];
    opt[0] = '1';

    
    while(opt[0]!='s')
    {
        
        Action();
        scanf("%s", opt);
        
        printf("\topt:%c\n\n", opt[0]);
        switch(opt[0])
        {
            case 'p':
                print_cards();
                break;

            case 'd':
                delete_setting();
                break;
            case 't':
                print_all();
                break;
            case 's':
               
                break;
            case 'g':
                play_game();
                break;
            default:
                printf("Error! Option is not correct.\n\n");
        }
    }
    
    
   
    

}