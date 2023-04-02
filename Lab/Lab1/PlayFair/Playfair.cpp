#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
//figure5
/*
char Matrix[5][5]={{'K','C','D','E','F'},
                      {'U','N','P','Q','S'},
                      {'Z','V','W','X','Y'},
                      {'R','A','L','G','O'},
                      {'B','I','T','H','M'}}; // 5x5  matrix to encipher or decipher
*/
char keyword[26]; // cypher key
char msg[100]; // message
int mark[130],len,r,c; // necessary variables
char Matrix[5][5];
//Function
void createMatrix();
void encipher();
void decipher();

void createMatrix()
{
    cout<<"Keyword: ";
    cin>>keyword; // key of the cypher
    getchar();
    len=strlen(keyword);  // size of input string O(n) :3
    mark['J']=1; // ignore J
    r=0,c=0; //initialize row and column

    // first populate the keyword
    for(int i=0;i<len;i++)
    {
        if(!mark[toupper(keyword[i])]) // ignore duplicates
        {
            mark[toupper(keyword[i])]=1;
            Matrix[r][c++]=toupper(keyword[i]);
            if(c%5==0) //increase row column
            {
                c=0;
                r++;
            }
        }
    }

    // complete rest of the matrix from unused characters starting from A
    for(int i='A';i<='Z';i++)
    {
        if(mark[i]==0) // taking values that are not in the matrix already
        {
            Matrix[r][c++]=i;
            mark[i]=1;
            if(c%5==0)
            {
                if(r==4 && c==5) break; //matrix populated

                // else increase row column
                r++;
                c=0;
            }
        }
    }
}

void decipher()
{
    createMatrix();
    cout<<"\nDecode : ";
    char cypText[150]; // cypher text
    cin>>cypText;
    getchar(); // flush buffer
    int l=strlen(cypText); //take length

    int P,Q,R,S,f1,f2;
    char x,y;
    for(int i=0;i<l;i+=2)
    {
        x=cypText[i];
        y=cypText[i+1];
        f1=f2=0;
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(x==Matrix[j][k])
                {
                    P=j;
                    Q=k;
                    f1=1;
                }
                if(y==Matrix[j][k])
                {
                    R=j;
                    S=k;
                    f2=1;
                }
                if(f1 && f2) break;
            }
             if(f1 && f2) break;
        }
        if(P==R) //same row
        {
            if(Q==0) cout<<Matrix[P][4];
            else cout<<Matrix[P][Q-1];
            if(S==0) cout<<Matrix[R][4];
            else cout<<Matrix[R][S-1];
        }
        else if(Q==S ) // same column
        {
            if(P==0) cout<<Matrix[4][Q];
            else cout<<Matrix[P-1][Q];
            if(R==0) cout<<Matrix[4][S];
            else cout<<Matrix[R-1][S];
        }
        else //opposite corner
        {
            cout<<Matrix[P][S]<<Matrix[R][Q];
        }
    }
    cout<<endl<<endl;
}


void encipher()
{
    createMatrix();
    gets(msg);
    int l=strlen(msg); // msg length
    char reqText[150]; //generate required text to encipher
    int in=0,j=0;
    for(int i=0;i<l;i++)
    {
        j=i+1;
        if(msg[i]==' ') //ignore all space from string
        {
            i++;
            j++;
        }
        if(msg[j]==' ') j++; //ignore space
        if(toupper(msg[i])=='J') msg[i]='k'; // ignore J
        if(toupper(msg[i])==toupper(msg[j])) // if duplicate add 'X' after the first letter
        {
            reqText[in]=toupper(msg[i]);
            reqText[in+1]='X';
            in++;
        }
        else
        {
            reqText[in]=toupper(msg[i]);
        }
        in++;
    }
    if(in%2!=0) reqText[in]='X'; // if one character left, add 'X' after it

    cout<<"\nEncode text : ";
    //encipher starts
    int P,Q,R,S,f1,f2;
    char x,y;
    for(int i=0;i<in;i+=2)
    {
        x=reqText[i];
        y=reqText[i+1];
        f1=f2=0;
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(x==Matrix[j][k])
                {
                    P=j;
                    Q=k;
                    f1=1;
                }
                if(y==Matrix[j][k])
                {
                    R=j;
                    S=k;
                    f2=1;
                }
                if(f1 && f2) break;
            }
             if(f1 && f2) break;
        }
        if(P==R) //same row
        {
            if(Q==4) cout<<Matrix[P][0];
            else cout<<Matrix[P][Q+1];
            if(S==4) cout<<Matrix[R][0];
            else cout<<Matrix[R][S+1];
        }
        else if(Q==S ) // same column
        {
            if(P==4) cout<<Matrix[0][Q];
            else cout<<Matrix[P+1][Q];
            if(R==4) cout<<Matrix[0][S];
            else cout<<Matrix[R+1][S];
        }
        else //opposite corner
        {
            cout<<Matrix[P][S]<<Matrix[R][Q];
        }
    }
    cout<<endl<<endl;
}
//main
int main()
{   
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    //option
    encipher();
    decipher();
    //
    fclose(stdin);
    fclose(stdout);
    return 0;
}