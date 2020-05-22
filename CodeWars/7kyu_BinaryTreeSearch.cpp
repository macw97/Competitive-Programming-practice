struct Node{
  int val;
  Node *left = nullptr;
  Node *right = nullptr;
};

bool search(int n, Node *root){
   
    if(root==nullptr)
    return false;
    if(root->val==n)
    return true;
   
  
   bool lefty=search(n,root->left);
   if(lefty)
   return lefty;
   
   bool righty=search(n,root->right);
   return righty;
}
