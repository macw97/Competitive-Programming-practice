#include <vector>
using namespace std;
class Solution
{
  public:
    static void insert(TreeNode** root,vector<int> arr,int index)
    {
       if(index<arr.size())
       {
       *root=new TreeNode(arr[index],nullptr,nullptr); 
       insert(&(*root)->m_left,arr,2*index+1);
       insert(&(*root)->m_right,arr,2*index+2);
       }
    }
    static TreeNode* arrayToTree(std::vector<int> arr) 
    {
        if(arr.size()==0)
        return nullptr;
        
        TreeNode* root;
        insert(&root,arr,0);
        return root;
    }
};
