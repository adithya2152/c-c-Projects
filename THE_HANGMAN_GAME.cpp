//!                                                                                  PROJECT 1
//!                                                                           CODE BY ADITHYA BHARADWAJ C
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class node
{
public:
    node *next;
    char data;
};

class hangman
{
private:
    int attempts;
    vector<string> Sport;
    vector<string> Countries;
    vector<string> Animals;
    vector<char>   guess;
    node *head;
    string target;
    float points;
    float pointsperentry;

   
  

public:
//* constructor defining all private variables
    hangman()
    {
        attempts = 8;           //? total game consists of 8 attempts
        Sport = {"table tennis","basketball","baseball","cricket","vollyball","throwball","badminton"};
        Countries={"india","america","africa","europe"};
        Animals={"elephant","tiger","lion","bear","chimpanzee","Cheetah"};
        head = nullptr;
        points=0.0;
       
        
    }
    void setpoints()
    {
        points=0;
    }
    void settattempts()
    {
        attempts=8;
    }
    void setguess()
    {
        guess.clear();
    }
    int check_win()
    {
        if(head!=NULL)
        {
            node*p=head;
            while(p!=NULL)
            {
                if(p->data=='-')
                {
                    return 0;
                }
                p=p->next;
            }
        }
        return 1;
    }
    int countwords()
    {
        int n=len();
        int count=1;

        for(int i=0;i<n;i++)
        {
            if(target[i]==' ')
            {
                count=count+1;
            }
        }
        return count;
    }
    void pointdiv()
    {
        int n=len();
        int x=countwords();
        float p=100/(n+(x-1));
        pointsperentry=p;
    }
    

    void settarget(int N)            //* setting the target string by randamising the possibilities
    {
        int index,n,x;

        if(N==1)
        {
            n=Sport.size();
            x=time(0);
            srand(x);
            index = rand() % n;
            target = Sport[index];
        }
        else if (N==2)
        {
            n=Countries.size();
            x=time(0);
            srand(x);
            index = rand() % n;
            target = Countries[index];
        }
        else if(N==3)
        {
            n=Animals.size();
            x=time(0);
            srand(x);
            index = rand() % n;
            target = Animals[index];
        }
        else
        {
            cout<<"Enter valid option"<<endl;
        }
      

    }

    void hint()
    {
        if (target == "table tennis")
        {
            cout << "An indoor sport with rapid rallies." << endl;
            cout << "In this game, a 'chop' isn't just for cooking, a 'loop' isn't just in programming, and 'spin' isn't just a laundry setting. What am I?" << endl;
        }
        else if (target == "basketball")
        {
            cout << "An Outdoor Sport with hoops." << endl;
            cout << "In this sport, the court is a canvas, the players are artists, and the ball is the brush. Points are painted with every graceful stroke. What am I?" << endl;
        }
        else if (target == "baseball")
        {
            cout << "A bat-and-ball game played on a diamond." << endl;

        }
        else if (target == "cricket")
        {
            cout << "A bat-and-ball game " << endl;
            cout << "Popular in many countries" << endl;
        }
        else if (target == "volleyball")
        {
            cout << "A team sport with a net." << endl;
        }
        else if (target == "throwball")
        {
            cout << "Teams score points by throwing a ball across the opponent's boundary. What am I?" << endl;
        }
        else if (target == "badminton")
        {
            cout << "Players strive for precision in smashes and agility on the court. What am I?" << endl;
        }
        else if (target == "india")
        {
            cout << "A country in South Asia with diverse cultures." << endl;
            cout << "This country is known for its rich history" << endl;
        }
        else if (target == "america")
        {
            cout << "A continent or a country with diverse landscapes." << endl;
        }
        else if (target == "africa")
        {
            cout << "A continent with diverse geography and wildlife." << endl;
        }
       
        else if (target == "europe")
        {
            cout << "A continent with rich history and diverse cultures." << endl;
        }
        else if (target == "elephant")
        {
            cout << "A large mammal " << endl;
            cout << "Known for its intelligence, long memory, and presence in savannas and forests. What am I?" << endl;
        }
        else if (target == "tiger")
        {
            cout << "Famous for its striking appearance and being the largest cat species. What am I?" << endl;
        }
        else if (target == "lion")
        {
            cout << "Known for its symbolism of strength and courage. What am I?" << endl;
        }
        else if (target == "bear")
        {
            cout << "Known for hibernation and diverse species like grizzly and polar bears. What am I?" << endl;
        }
        else if (target == "chimpanzee")
        {
            cout << "A highly intelligent primate species." << endl;
        }
        else if (target == "Cheetah")
        {
            cout<<"A master in the animal kingdom, utilizing calculated bursts of energy."<<endl;

        }
        else
        {
            cout << "No hint available for this category." << endl;
        }
    }



    int len()                   //*function for the length of the target string 
    {
        return target.length();
    }
   
    
    string gettarget()      //*function to get the targetted string 

    {
        return target;
    }

    void create_list(int n) //* creating an empty list to store resulting values
    {
        if (n <= 0)
        {
            cout << "Invalid size for linked list." << endl;
            return;
        }

        head = new node;
        node *temp = head;
        for (int i = 1; i < n; i++)
        {
            temp->data = '-';
            temp->next = new node;
            temp = temp->next;
        }
        temp->data = '-';
        temp->next = nullptr;

    }

    void word_display()         //*displaying the linked list
    {
        node *p = head;
        while (p != nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;

        cout<<"POINTS FOR EACH ENTRY -->"<<pointsperentry<<endl;
        cout<<"Attempts Left"<<"->"<<attempts<<endl;
        cout<<"POINTS"<<"->"<<points<<endl;

        if(check_win())
        {
            cout<<"You Won The Game"<<endl;
            cout<<"TOTAL POINTS"<<"--->"<<points<<endl;
        }
        else if(attempts<1)
        {
            cout<<"YOU RAN OUT OF ATTEMPTS"<<endl;
            cout<<"the word was "<<  target<<endl;      //?  display the targetted word if the attempts are exhausted 
        }
    }

    void insert(char x, int pos)    //*inserting in a linked list 
    {
        node *p = head;
        if (pos == 0)
        {
            p->data = x;
        }
        else
        {
            for (int i = 0; i < pos; i++) 
            {
                p = p->next;
            }
            p->data = x; 
        }
    }

    void game(char x)               //*the main function behind the game,...
    {
        pointdiv();
         
        
        if (find(guess.begin(), guess.end(), x) != guess.end())
        {
            cout << "You have already guessed the character '" << x << "'. Guess a different character." << std::endl;
            return;
        }
        guess.push_back(x);

        int flag=0;
        if(attempts>=1)
        {
            int n = len();
            for (int i = 0; i < n; i++)
            {
                if (target[i] == x )         //? searching the element in the string 
                {
                    flag=1; 
                    points=points+pointsperentry;
                    insert(x,i);             //?  if found flag it and insert it in the linked list at the same position of the string
                }
                else if(target[i]==' ')     //? if space are fount automatically insert space in linked list
                {
                    insert(' ',i);
                }
                
                
                continue;
            }
            if(flag==0)
            {
                points=points-pointsperentry;
                attempts=attempts-1;        //? if the element not in string this means that t=wrong guess so reduce one attemt
                
            }

        } 
        else if(attempts<1)
        {
            
        }
    
        
    }
    int getattempts()                             //*return the number of attempts
    {
        return attempts;
    }
    

    
};

int main()
{
    hangman hm;
    char ut;
    int ch,choice,count,length,att;
    while(1)
    {
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"                                                          WELCOME TO THE HANGMAN GAME                                                                        "<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

        cout<<"                                                            1. PLAY THE GAME                                                                                   "<<endl;
        cout<<"                                                            2. EXIT                                                                                              "<<endl;
        cout<<"                                                           Enter your choice                                                                                   "<<endl;
        cin>> choice;

        hm.setpoints();
        hm.settattempts();
        hm.setguess();
        switch(choice)
        {
            case 1:
                cout<<"                                                             CATEGORIES                                                                                  "<<endl;
                cout<<"                                                            1. SPORTS                                                                                    "<<endl;
                cout<<"                                                            2. COUNTRIES                                                                                 "<<endl;
                cout<<"                                                            3. ANIMALS                                                                                   "<<endl;

                cout<<"                                                           Enter your choice"<<"\t";
                cin>>ch;

                hm.settarget(ch);
                length=hm.len();
                cout<<"The length of the word is "<< length<<endl<<endl;
                
                hm.create_list(length);
                count=hm.countwords();
                hm.pointdiv();
                cout<<count<<endl;
                hm.hint();
                while(1)
                {
                    hm.word_display();
                    att=hm.getattempts();
                    
                    cout<<"Guess the letter"<<endl<<"-->";
                    
                    cin>>ut;    
                    hm.game(ut);

                    if(att==0 || hm.check_win())
                    {
                        cout<<endl;
                        hm.word_display();
                        cout<<endl;
                        break;
                    }
                }

                break;


                case 2:
                cout<<"Thanks For Playing come again"<<endl;
                exit(1);

      }
    }
    return 0;
}