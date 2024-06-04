#include<iostream>
#include<fstream>
using namespace std;
struct node
{
    int data;
    char alpha;
};
struct codeNode
{
    int data;
    char alpha;
    codeNode* left;
    codeNode* right;
};

node* charFrequency(string text , int *num) 
{
    node* N1 = new node[100];
    int numOfNode = 0;
    int frequency = 0;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .?!abcdefghijklmnopqrstuvwxyz";
    for(int i=0;i<alphabet.length();i++)
    {
        frequency = 0;
        for(int j=0;j<text.length();j++)
        {
            if(text[j] == alphabet[i])
            {
                frequency++;
            }
        }
        if(frequency != 0)
        {
            N1[numOfNode].data = frequency;
            N1[numOfNode].alpha = alphabet[i];
            numOfNode++;
        }
        
    }
    *num = numOfNode;
    return N1;
}
node* sortNodes(node* N1, int num)
{
    for (int i = 0; i < num - 1; ++i) 
    {
        for (int j = 0; j < num - i - 1; ++j) 
        {
            if (N1[j].data > N1[j + 1].data) 
            {
                node temp = N1[j];
                N1[j].alpha = N1[j+1].alpha;
                N1[j].data = N1[j+1].data;
                N1[j+1].alpha = temp.alpha;
                N1[j+1].data = temp.data;
            }
        }
    }
    return N1;
}
class generateCode
{
    private:
        codeNode* head;
        string codeText;
    public:
    generateCode()
    {
        head = NULL;
        codeText = "";
    }
    void insert(char alpha,int freq)
    {
        codeNode* C1 = new codeNode;
        codeNode* C2 = new codeNode;
        if(head == NULL)
        {
            C1->alpha = alpha;
            C1->data = freq;
            C1->left = NULL;
            C1->right = NULL;
            head = C1;
        }
        else
        {
            C1->alpha = alpha;
            C1->data = freq;
            C1->left = NULL;
            C1->right = NULL;
            C2->data = freq+head->data;
            C2->alpha = '-';
            C2->left = C1;
            C2->right = head;
            head = C2;
        }
    }
    void display(codeNode* root) 
    {
        if (root != nullptr) 
        {
            display(root->left);
            if(root->alpha != '-')
            {
                codeText+=root->alpha;
            }
            display(root->right);
        }
    }    
    codeNode* getNode(){return head;}
    string txt(){return codeText;}
};
void codeTextFile(string codedText, int numOfNodes)
{
 fstream file1;
    file1.open("code.txt");
    for(int i=0;i<numOfNodes;i++)
    {
        char alphabet = codedText[i];

        file1<<alphabet;
        for(int j=0;j<i;j++)
        {
            file1 << "1";
        }
        if(i == numOfNodes-1)
        {
            file1 << "1";
        }
        else
        {
            file1<<"0";
        }
    }

file1.close();

}
void encodedMsg(string msg)
{
    fstream file1("code.txt");
    fstream file2;
    file2.open("encodedMsg.txt");
    string line;
    int num = 0;
    string code = "" ;
    char alpha[60];
    while(getline(file1,line))
    {code+= line;}
    for(int i=0;i<code.length();i++)
    {
        if(code[i] != '0' && code[i] != '1')
        {
            alpha[num] = code[i];
            num++;
        }
    }
    for(int i=0;i<msg.length();i++)
    {
        char letter = msg[i];
        int num1 = 0;
        for(int j=0;j<num;j++)
        {
            if(alpha[j] == letter)
            {
                num1 = j;
            }
        }
        for(int j=0;j<num1;j++ )
        {
            file2<<"1";
        }
         if(i == msg.length()-1)
        {
            file2 << "1";
        }
        else
        {
            file2<<"0";
        }
    }
}
int main()
{
    fstream file("msg.txt");
    string line;
    string msg = "";
    int numOfNodes = 0;
    while(getline(file,line))
    {msg+= line+"\n";}
    node *N1 = charFrequency(msg,&numOfNodes);
    N1 = sortNodes(N1,numOfNodes);
    generateCode G1;
    for(int i=0;i<numOfNodes;i++)
    {G1.insert(N1[i].alpha,N1[i].data);}
    G1.display(G1.getNode());
    string codedText = G1.txt();
    codeTextFile(codedText,numOfNodes);
    encodedMsg(msg);
   
}
