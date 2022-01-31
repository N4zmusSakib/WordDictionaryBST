#include<bits/stdc++.h>
using namespace std;
struct node
{
    string key,value;
    node *right;
    node *left;
}*root = NULL;
///Input start
node *insert_word(node *root2, string word, string meaning)
{
    if(root2 == NULL)
    {
        root2 = (node*)new node;
        root2->right = NULL;
        root2->left = NULL;
        root2->key = word;
        root2->value = meaning;
        return root2;
    }
    else if(word < root2->key)
        root2->left=insert_word(root2->left,word,meaning);
    else
        root2->right=insert_word(root2->right,word,meaning);
    return root2;
}
node *insert_new_word(node *root2, string data,string data2)
{
    if(root2 == NULL)
    {
        root2 = (node*)new node;
        root2->right = NULL;
        root2->left = NULL;
        root2->key = data;
        root2->value = data2;

        return root2;
    }
    else if(data < root2->key)
        root2->left=insert_new_word(root2->left, data,data2);
    else
        root2->right=insert_new_word(root2->right, data, data2);
    return root2;
}
void insert_new_word_main()
{
    string word,meaming;

    cout<<"Enter Word: ";
    cin>>word;
    cout<<"Enter meaning: ";
    cin>>meaming;
    root = insert_new_word(root,word,meaming);
    cout<<"Word inserted."<<endl;
}
void input_from_file()
{
    string line,meaning;
    ifstream myfile("New Text Document.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile,line) )
        {
            getline (myfile,meaning);
            root = insert_word(root,line,meaning);
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}
///Input End
///Search start
node* search_word_recursive(node* root2,string data)
{
    if (root2 == NULL || root2->key == data)
        return root2;
    if (root2->key < data)
        return search_word_recursive(root2->right, data);
    return search_word_recursive(root2->left, data);
}
int cnt_similar;
void search_similar_word_recursive(node* root2,string data,int n)
{
    if (root2 == NULL)
        return;
    int cnt = 0;
    for(int i=0; i<n; i++)
    {
        if(root2->key[i]==data[i])
            cnt++;
    }
    if(cnt == n)
    {
        cnt_similar++;
        if(cnt_similar ==1 )
            cout<<"\""<<root2->key<<"\"";
        else
            cout<<", \""<<root2->key<<"\"";
    }
    search_similar_word_recursive(root2->right, data,n);
    search_similar_word_recursive(root2->left, data,n);
}
void search_similar(node* root2,string word,string meaning)
{
    if(root2 == NULL)
        return;
    if(root2->value == meaning && root2->key != word)
   {
       if(!cnt_similar)
            cout<<"\""<<root2->key<<"\"";
        else
            cout<<", \""<<root2->key<<"\"";
       cnt_similar++;
    }

    search_similar(root2->left,word,meaning);
    search_similar(root2->right,word,meaning);
}
void search_word_main(node* root2)
{
    string data;
    cout<<"Enter word: ";
    cin>>data;
    node *temp = search_word_recursive(root2,data);
    if(temp == NULL)
    {
        cnt_similar = 0;
        cout<<"The word \""<<data<<"\""<<" was not found"<<endl;
        cout<<"Do you mean: ";
        search_similar_word_recursive(root2,data,1);
    }
    else
    {
        cnt_similar = 0;
        cout<<"\""<<temp->key<<"\" means \""<<temp->value<<"\""<<endl;
        cout<<"Similar word(s): ";
        search_similar(root2,temp->key,temp->value);
    }
    cout<<endl;
}
///Search end
///Delete start
node* search_min(node* root2)
{
    if(root2->left == NULL)
        return root2;
    else
        return search_min(root2->left);
}
node* del(node * head, string data)
{
    if(head == NULL)
        return  head;
    if(data < head->key)
    {
        head->left =  del(head->left, data);
        return head;
    }
    if (data > head->key)
    {
        head->right=  del(head->right, data);
        return head;
    }
    else
    {
        // case 1: no child
        if (head ->left == NULL && head->right == NULL)
        {
            delete head;
            head = NULL;
            return head;
        }
        // case 2: one child
        else   if (head ->left == NULL )
        {
            struct node *temp = head;
            head = head->right;
            delete temp;
            return head;
        }
        else   if (head ->right == NULL )
        {
            struct node *temp = head;
            head = head->left;
            delete temp;
            return head;
        }
        else
        {
            // case 3 two child
            struct node *temp = search_min( head->right);
            head->key = temp->key;
            head->value= temp->value;
            head->right = del (head->right, temp->key);
            return head;
        }

    }

}
void delete_()
{
    cout<<"Enter word: ";
    string s;
    cin>>s;
    root = del(root,s);
    cout<<"\""<<s<<"\" deleted"<<endl;
}
///Delete end
///Update file start
void preTraverse(node* root2,fstream &myfile)
{
    if(root2 == NULL)
        return;
    myfile<<root2->key<<"\n";
    myfile<<root2->value<<"\n";
    preTraverse(root2->left,myfile);
    preTraverse(root2->right,myfile);
}
void update(node *root2)
{
    fstream myfile;
    myfile.open ("New Text Document.txt");
    preTraverse(root2, myfile);
    myfile.close();
}
///Update file end
///Header
void header()
{
    system("CLS");
    cout<<"**************  English to English Dictionary *****************\n";
}
int main()
{
    input_from_file();
    int choose;
    while(1)
    {
        header();
        cout<<"1. Search meaning\n";
        cout<<"2. Insert new word\n";
        cout<<"3. Delete\n";
        cout<<"0. Exit\n";
        cin>>choose;
        header();
        switch(choose)
        {
        case 0:
            return 0;
        case 1:
            search_word_main(root);
            break;
        case 2:
            insert_new_word_main();
            break;
        case 3:
            delete_();
            break;
        }
        update(root);
        cout<<endl;
        system("pause");
    }
    return 0;
}
