#ifndef BPTREE_H_
#define BPTREE_H_

#include <vector>
#include <string>
#include "../BufferManager/BufferManager.h"
#include "../BufferManager/File.h"


template<class T>
class bpTree
{
    using string = std::string;
    template<typename K>
    using vector = std::vector<K>;
    using pos_type = File::pos_type;
    constexpr static int N = 7;
public:
    struct node
    {
        int no;                         //���ڵ�����ݸ���
        int isLeaf;                     //Ҷ�ڵ�ı�־
        pos_type dataPos[N];            //Ҷ�ڵ��������ַ
        T key[N];                       //��Źؼ���
        node* childNode[N + 1];             //��Ҷ�ڵ��������ַ
        node* fatherNode;               //��Ÿ��ڵ��ַ
        node* nextNode;                 //�ڵ��ź����ַ
        node* brother;                  //ɾ��ʱ�õ����ֵܽڵ�

        node()
        {
            nextNode = nullptr;
            brother = nullptr;
            fatherNode = nullptr;
            no = 0;
            isLeaf = 0;
            for (int i = 0; i < N; i++)
            {
                childNode[i] = nullptr;
                dataPos[i] = 0;
                //key[i] = 0;
            }
            childNode[N] = nullptr;
        }
    };

    struct tnode
    {
        int no;                     //���ڵ�����ݸ���
        pos_type dataPos[N];         //Ҷ�ڵ��������ַ
        T key[N];                   //��Źؼ���
    };

    //constructor
    bpTree();
    ~bpTree();

    //others
    bool Isleaf(node* & node) const;                      //����Ƿ�Ҷ�ڵ�
    bool Isroot(node* & nodeposition) const;        //����Ƿ�����
    void findLeaf(const T & the_key);                   //Ҷ�����Һ���

    vector<pos_type> Eqsearch(const T & key);
    vector<pos_type> Neqsearch(const T & key);
    vector<pos_type> Besearch(const T & key);
    vector<pos_type> Bsearch(const T & key);
    vector<pos_type> Ssearch(const T & key);
    vector<pos_type> Sesearch(const T & key);

    void Insert_node(const T &, const pos_type &);            //���ݲ���
    void Resize_leaf();                             //����Ҷ�ڵ�
    void Resize_nleaf();                            //���ѷ�Ҷ�ڵ�

    bool Del_data(const T & ckey);                        //ɾ��
    void del(const T & k);                                //
    void Merge();                                   //ɾ���е����ϲ�
    void MergeLeaf();

    template <typename It> int compare(const It &, const It &);

    void Index(const string &);                   //���������ļ�
    void Buildtree(const string &);               //����b����
#ifdef TEST
    void Show();
#endif
private:
    node* headNode;
    node* treeRoot;                               //ʵ���ĸ����
    node* posNode;
    int totalData;                                    //��¼���ݵ�����
    bool opFlag;                                     //��־�Ƿ������
};




//������������������������������������������������������������������������������������
//������������������������������������������������������������������������������������
//������������������������������������������������������������������������������������
//����������������������ģ����ĳ�Ա��������������������������������������������������
//������������������������������������������������������������������������������������
//������������������������������������������������������������������������������������
//������������������������������������������������������������������������������������


//�������������������������캯����������������������������

template<class T>
bpTree<T>::bpTree()
{
    totalData = 0;
    headNode = new node;
    opFlag = false;
    headNode->isLeaf = 1;
    treeRoot = headNode;
    posNode = headNode;
}

//��������������������������������������������������������

template<class T>
bpTree<T>::~bpTree()
{
    node* temp = treeRoot;
    node* temp1; node* temp2;
    for (; Isleaf(temp) == 0;)
    {
        temp1 = temp;
        temp = temp->childNode[0];
        for (; temp1->nextNode != nullptr;)
        {
            temp2 = temp1;
            temp1 = temp1->nextNode;
            delete temp2;
        }
        delete temp1;
    }
    for (; temp->nextNode != nullptr;)
    {
        temp1 = temp;
        temp = temp->nextNode;
        delete temp1;
    }
    delete temp;
    temp = nullptr;
}


//����������������������������������������������������������������������������
//����������������������ģ�����������Ա��������������������������������������
//����������������������������������������������������������������������������

//����������������������������Ƚϴ�С����������������������������������������
template <class T>
template <typename It>
int bpTree<T>::compare(const It & a, const It & b)
{
    if (a == b)         return 0;
    else if (a > b)     return 1;
    else                return -1;
}

//���������������������������������ڵ��жϣ�����������������������������������

template<class T>
bool bpTree<T>::Isroot(node* & nodeposition) const
{
    if (nodeposition->fatherNode == nullptr)
        return 1;
    else
        return 0;
}

//��������������������������������Ҷ�ڵ��жϣ���������������������������������

template<class T>
bool bpTree<T>::Isleaf(node* & cnode) const
{
    if (cnode->isLeaf == 0)
        return false;
    else
        return true;
}

//����������������������������Ѱ��Ҷ�ڵ㣭����������������������������

template<class T>
void bpTree<T>::findLeaf(const T & the_key)
{
    int i;
    posNode = treeRoot;

    while (Isleaf(posNode) == 0)                     //��û��Ҷ�ڵ�����������ҵ�Ҷ�ڵ����ֹ
    {
        for (i = 0; i < posNode->no; i++)              //�ڸ���ڵ���Ѱ����Ӧ��λ��
            if (compare(the_key, posNode->key[i]) == -1)//�ҵ�������ѭ��
                break;
        posNode = posNode->childNode[i];
    }
}


//����������������������������Ѱ����ȵ�ֵ��������������������������������


template<class T>
auto bpTree<T>::Eqsearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;

    findLeaf(key);
    for (int i = 0; i < posNode->no; i++)              //�ҵ��ڽڵ��е�λ��
    {
        if (compare(key, posNode->key[i]) == 0)
        {
            pos.push_back(posNode->dataPos[i]);
            break;
        }
    }
    return pos;
}


//����������������������������Ѱ�Ҳ���ȣ���������������������������������


template<class T>
auto bpTree<T>::Neqsearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;
    for(headNode = treeRoot; headNode != nullptr; headNode = headNode->childNode[0])
        posNode = headNode;
    for(; posNode != nullptr; posNode = posNode->nextNode)
    {
        for(int i = 0; i < posNode->no; i++)
        {
            if(posNode->key[i] != key)
                pos.push_back(posNode->dataPos[i]);
        }
    }
    return pos;
}


//������������������������Ѱ��>=��������������������������������������������


template<class T>
auto bpTree<T>::Besearch(const T & key) -> vector<pos_type>
{
    int i;
    vector<pos_type> pos;
    findLeaf(key);
    for(i = 0; i < posNode->no; i++)				//�ҵ��ڽڵ��е�λ��
    {
        if(compare(posNode->key[i], key) >= 0)
        {
            break;
        }
    }
    for(; i < posNode->no; i++)
    {
        pos.push_back(posNode->dataPos[i]);
    }
    for(posNode = posNode->nextNode; posNode != nullptr; posNode = posNode->nextNode)
    {
        for(int j = 0; j < posNode->no; j++)
            pos.push_back(posNode->dataPos[j]);
    }
    return pos;
}


//��������������������������Ѱ��>��������������������������������������

template<class T>
auto bpTree<T>::Bsearch(const T & key) -> vector<pos_type>
{
    int i;
    vector<pos_type> pos;
    findLeaf(key);
    for(i = 0; i < posNode->no; i++)				//�ҵ��ڽڵ��е�λ��
    {
        if(compare(posNode->key[i], key) > 0)
        {
            break;
        }
    }
    for(; i < posNode->no; i++)
    {
        pos.push_back(posNode->dataPos[i]);
    }
    for(posNode = posNode->nextNode; posNode != nullptr; posNode = posNode->nextNode)
    {
        for(int j = 0; j < posNode->no; j++)
            pos.push_back(posNode->dataPos[j]);
    }
    return pos;
}


//��������������������������������Ѱ��<����������������������������������

template<class T>
auto bpTree<T>::Ssearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;
    findLeaf(key);
    node *tmp = posNode;

    for(headNode = treeRoot; headNode != nullptr; headNode = headNode->childNode[0])
        posNode = headNode;

    while(posNode != tmp)
    {
        for(int i = 0; i < posNode->no; i++)
            pos.push_back(posNode->dataPos[i]);
        posNode = posNode->nextNode;
    }

    for(int i = 0; compare(posNode->key[i], key) < 0; i++)
        pos.push_back(posNode->dataPos[i]);
    return pos;
}


//��������������������������������Ѱ��<=����������������������������������

template<class T>
auto bpTree<T>::Sesearch(const T & key) -> vector<pos_type>
{
    vector<pos_type> pos;
    findLeaf(key);
    node *tmp = posNode;

    for(headNode = treeRoot; headNode != nullptr; headNode = headNode->childNode[0])
        posNode = headNode;

    while(posNode != tmp)
    {
        for(int i = 0; i < posNode->no; i++)
            pos.push_back(posNode->dataPos[i]);
        posNode = posNode->nextNode;
    }

    for(int i = 0; compare(posNode->key[i], key) <= 0; i++)
        pos.push_back(posNode->dataPos[i]);
    return pos;
}



//���������������������������������ݲ��뺯��������������������������������

template<class T>
void bpTree<T>::Insert_node(const T & key, const pos_type & n)
{
    findLeaf(key);
    bool f = false;

    if (totalData == 0)                                       //�����ݱ�ɾ��ʱ�����
    {
        treeRoot->key[0] = key;
        treeRoot->dataPos[0] = n;
        treeRoot->no = 1;
        totalData = 1;
    }
    else                                                //��������
    {
        for (int i = 0; i < posNode->no; i++)          //�������ݱ����ֵС���ҵ���Ҷ�ڵ��е�λ��
        {
            if (compare(key, posNode->key[i]) == -1)   //�ҵ��󣬺�������ݺ���
            {
                for (int j = posNode->no; j > i; j--)
                {
                    posNode->key[j] = posNode->key[j - 1];
                    posNode->dataPos[j] = posNode->dataPos[j - 1];
                }
                posNode->key[i] = key;
                posNode->dataPos[i] = n;
                f = true;
                break;
            }
        }
        if (f == false)                                     //���ݱ����ֵ��ֱ�Ӳ嵽���
        {
            posNode->key[posNode->no] = key;
            posNode->dataPos[posNode->no] = n;
        }
        if (posNode->no < N - 1)                           //�ڵ�δ�����ڵ�����ݸ�����1���˳�
            posNode->no += 1;
        else                                                //�ڵ����������нڵ����
            Resize_leaf();
        totalData++;
    }
    opFlag = true;
}


//��������������������������������Ҷ�ڵ㣭������������������������������
template<class T>
void bpTree<T>::Resize_leaf()
{
    node* new_node = new node;

    //��Ϊ����Ҷ�ڵ�
    for (int i = N / 2; i < N; i++)
    {
        new_node->key[i - N / 2] = posNode->key[i];
        new_node->dataPos[i - N / 2] = posNode->dataPos[i];
    }

    //����������Ӽ�������ֵ
    if (posNode->nextNode != nullptr)
    {
        if (posNode->nextNode->nextNode != nullptr)
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
        }
        else
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
            posNode->nextNode->brother = new_node;
        }
    }
    else
    {
        posNode->brother = new_node;
        new_node->brother = posNode;
    }
    new_node->nextNode = posNode->nextNode;
    posNode->nextNode = new_node;
    new_node->isLeaf = 1;
    posNode->no = N / 2;
    new_node->no = N - N / 2;
    new_node->fatherNode = posNode->fatherNode;

    for (int i = N / 2; i < N; i++)     //���ݸ�λ
    {
        //posNode->key[i] = 0;
        posNode->dataPos[i] = 0;
    }
    // ��������������һ��ķ�Ҷ�ڵ��ֵ�ͺ���ָ��

    // �Լ��Ǹ��������
    int i = 0;
    if (Isroot(posNode) == 1)
    {
        node* root = new node;
        root->key[0] = new_node->key[0];
        root->childNode[0] = posNode;
        root->childNode[1] = new_node;
        root->no = 1;
        posNode->fatherNode = new_node->fatherNode = root;
        treeRoot = root;
    }
    //�Ǹ��������
    else
    {
        node* po = posNode->fatherNode;
        for (i = 0; i < po->no; i++)
        {// �ҵ����ڵ�ָ����Ҷ�ڵ��ָ��
            if (compare(new_node->key[0], po->key[i]) == -1)
                break;
        }
        // �����������ֵ�ͺ���ָ�붼���ƣ�Ϊ�½ڵ��ڳ�λ��
        for (int j = po->no; j > i + 1; j--)
            po->key[j] = po->key[j - 1];

        for (int j = po->no + 1; j > i + 1; j--)
            po->childNode[j] = po->childNode[j - 1];
        // ��i + 1��ָ��ָ���µĽڵ�
        po->key[i] = new_node->key[0];
        po->childNode[i] = posNode;
        po->childNode[i + 1] = new_node;

        //���ڵ�����δ����no����һ
        if (posNode->fatherNode->no < N - 1)
            posNode->fatherNode->no++;

        //���ڵ���������
        else
        {
            posNode = posNode->fatherNode;
            Resize_nleaf();//���ѷ�Ҷ�ڵ㣨�漰�ݹ飩
        }
    }
}

//�������������������������������ѷ�Ҷ�ڵ㣭����������������������������
template<class T>
void bpTree<T>::Resize_nleaf()
{
    node* new_node = new node;

    //�ѽڵ�ֿ�
    for (int i = (N + 1) / 2; i < N; i++)
    {
        new_node->key[i - (N + 1) / 2] = posNode->key[i];
        new_node->childNode[i - (N + 1) / 2] = posNode->childNode[i];
    }
    new_node->childNode[N / 2] = posNode->childNode[N];

    //��������������⼰������ֵ

    if (posNode->nextNode != nullptr)
    {
        if (posNode->nextNode->nextNode != nullptr)
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
        }
        else
        {
            new_node->brother = posNode->brother;
            posNode->brother = new_node;
            posNode->nextNode->brother = new_node;
        }
    }
    else
    {
        posNode->brother = new_node;
        new_node->brother = posNode;
    }
    new_node->nextNode = posNode->nextNode;
    posNode->nextNode = new_node;
    posNode->no = (N - 1) / 2;
    new_node->no = N / 2;
    new_node->fatherNode = posNode->fatherNode;


    for ( int i = 0; i < N - (N - 1) / 2; i++) //�ƶ���λ
    {
        //posNode->key[N - 1 - i] = 0;
        posNode->childNode[N - i] = nullptr;
    }

    for (int x = 0; x < new_node->no + 1; x++)
    {//���½ڵ���ӽڵ�ĸ��ڵ�Ĺ���
        new_node->childNode[x]->fatherNode = new_node;
    }

    //�����Լ��ǲ��Ǹ����
    if (Isroot(posNode) == 1)          //�Ǹ�������
    {
        node* root = new node;
        node* pos = new_node;
        while (Isleaf(pos) != 1)
            pos = pos->childNode[0];
        root->key[0] = pos->key[0];
        root->childNode[0] = posNode;
        root->childNode[1] = new_node;
        root->no = 1;
        posNode->fatherNode = new_node->fatherNode = root;
        treeRoot = root;
    }

    else   //�Ǹ��������
    {
        int i;
        node* po = posNode->fatherNode;
        for (i = 0; i < po->no; i++)
        {// �ҵ����ڵ�ָ����Ҷ�ڵ��ָ��
            if (compare(new_node->key[0], po->key[i]) == -1)
                break;
        }
        // �����������ֵ�ͺ���ָ�붼���ƣ�Ϊ�½ڵ��ڳ�λ��
        for (int j = po->no; j > i + 1; j--)
            po->key[j] = po->key[j - 1];

        for (int j = po->no + 1; j > i + 1; j--)
            po->childNode[j] = po->childNode[j - 1];
        // ��i + 1��ָ��ָ���µĽڵ�
        node* pos = new_node;
        while (Isleaf(pos) != 1)
            pos = pos->childNode[0];
        po->key[i] = pos->key[0];
        po->childNode[i] = posNode;
        po->childNode[i + 1] = new_node;

        //���ڵ�����δ����no����һ
        if (posNode->fatherNode->no < N - 1)
            posNode->fatherNode->no++;

        //���ڵ���������
        else
        {
            posNode = posNode->fatherNode;
            Resize_nleaf();//���ѷ�Ҷ�ڵ㣨�漰�ݹ飩
        }
    }
}


//����������������������������ɾ��Ҷ�ڵ����ݣ�����������������������������


template<class T>
bool bpTree<T>::Del_data(const T & ckey)
{
    bool f = false;

    findLeaf(ckey);                                   //���ڵ�Ҷ�ڵ�
    for (int i = 0; i < posNode->no; i++)              //�ҵ��ڽڵ��е�λ��
    {
        if (compare(ckey, posNode->key[i]) == 0)
        {
            f = true; break;
        }
    }
    if (f == true)    //���ݴ���
    {
        del(ckey);
        opFlag = true;
        return true;
    }
    else            return false;
}


//��������������������������������ɾ����������������������������������


template<class T>
void bpTree<T>::del(const T & k)
{
    int i;
    for (i = 0; i < posNode->no; i++)          //�ҵ��ڽڵ��е�λ��
    {
        if (compare(k, posNode->key[i]) == 0)break;
    }

    if (Isroot(posNode) == 1)                    //��������
    {
        for (; i < posNode->no - 1; i++)
        {
            posNode->key[i] = posNode->key[i + 1];
            posNode->dataPos[i] = posNode->dataPos[i + 1];
        }
        //posNode->key[i] = 0;
        posNode->dataPos[i] = 0;
        posNode->no--;
        totalData--;
    }
    else                                         //Ҷ�ڵ�Ǹ����
    {
        for (; i<posNode->no - 1; i++)
        {
            posNode->key[i] = posNode->key[i + 1];
            posNode->dataPos[i] = posNode->dataPos[i + 1];
        }
        //posNode->key[i] = 0;
        posNode->dataPos[i] = 0;
        totalData--;
        posNode->no--;

        if (posNode->no < N / 2)                   //��Ҫ������
            MergeLeaf();
    }
}

//�������������������������������ϲ�leaf�ڵ㣭������������������������������

template<class T>
void bpTree<T>::MergeLeaf()
{
    node* brother = posNode->brother;
    int i;
    if (brother->no < N - posNode->no)           //���ڵ���Ժϲ�
    {
        if (posNode->nextNode != nullptr)         //�������ұߵĽڵ�
        {
            for (i = posNode->no; i < posNode->no + brother->no; i++)
            {
                posNode->key[i] = brother->key[i - posNode->no];
                posNode->dataPos[i] = brother->dataPos[i - posNode->no];
            }
            //����ϲ���ڵ��������ֵ

            // no
            posNode->no += brother->no;

            // brother
            if (brother->nextNode != nullptr)
            {
                if (brother->nextNode->nextNode != nullptr)posNode->brother = brother->brother;
                else
                {
                    posNode->brother = brother->brother;
                    brother->brother->brother = posNode;
                }
            }
            else
                posNode->brother = posNode->fatherNode->childNode[posNode->fatherNode->no - 2];

            posNode->nextNode = brother->nextNode;

            //�����ϼ��ڵ��е���ֵ

            node* tp = brother->fatherNode;

            i = 0;
            while(i < tp->no && compare(tp->key[i], brother->key[0]) < 0)
                i++;

            if(tp->key[i] == brother->key[0])
            {
                for (; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i + 1] = tp->childNode[i + 2];
                }
                //tp->key[i] = 0;
                tp->childNode[i + 1] = nullptr;
            }
            else    // fatherNodes are different
            {
                for (; i < tp->no; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i] = tp->childNode[i + 1];
                }
                //tp->key[i - 1] = 0;
                tp->childNode[i] = nullptr;

            }

            delete brother;
            brother = nullptr;

            posNode = tp;
            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //��Ҫ������
            {
                Merge();
            }
        }
        else                                     //���ұߵĽڵ�
        {
            //�ϲ�
            for (i = brother->no; i < brother->no + posNode->no; i++)
            {
                brother->key[i] = posNode->key[i - brother->no];
                brother->dataPos[i] = posNode->dataPos[i - brother->no];
            }

            //�ϲ����������ݴ���
            brother->no += posNode->no;
            brother->nextNode = nullptr;
            brother->brother = brother->fatherNode->childNode[brother->fatherNode->no - 2];

            //�滻�ϼ��ڵ��е�����
            node* tp = brother->fatherNode;
            //tp->key[tp->no - 1] = 0;
            tp->childNode[tp->no] = nullptr;

            delete posNode;
            posNode = tp;

            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //��Ҫ������
            {
                Merge();
            }
        }
    }
    else                                          //���ڵ㲻���Ժϲ�
    {
        if (posNode->nextNode != nullptr)            //�������ұߵĽڵ�
        {
            //���������ڵ�����ݸ���

            int w = posNode->no;
            posNode->key[w] = brother->key[0];
            posNode->dataPos[w] = brother->dataPos[0];

            posNode->no++;
            brother->no--;

            //����ǰ��

            for (i = 0; i < brother->no; i++)
            {
                brother->key[i] = brother->key[i + 1];
                brother->dataPos[i] = brother->dataPos[i + 1];
            }

            //����ת�ƺ��λ��
            brother->dataPos[i] = 0;
            //brother->key[i] = 0;
        }
        else             //���ұߵĽڵ�
        {
            //�������ݸ���
            for (i = posNode->no; i>0; i--)         //���ݺ���
            {
                posNode->key[i] = posNode->key[i - 1];
                posNode->dataPos[i] = posNode->dataPos[i - 1];
            }
            posNode->dataPos[0] = brother->dataPos[brother->no - 1];
            posNode->key[0] = brother->key[brother->no - 1];

            brother->no--;
            posNode->no++;

            //����ת�ƺ��λ����
            brother->dataPos[brother->no] = 0;
            //brother->key[brother->no] = 0;
        }
    }
}

//�������������������������������ϲ�non-leaf�ڵ㣭������������������������������

template<class T>
void bpTree<T>::Merge()
{
    node* brother = posNode->brother;
    int i;

    if(Isroot(posNode))
    {
        if(posNode->no == 0)
        {
            node *tp = posNode;
            posNode = posNode->childNode[0];
            delete tp;
            posNode->fatherNode = nullptr;
        }
    }
    else if (brother->no < N - 1 - posNode->no)   //���ڵ���Ժϲ�
    {
        if (posNode->nextNode != nullptr)         //�������ұߵĽڵ�
        {
            for (i = posNode->no; i < posNode->no + brother->no; i++)
            {

                posNode->key[i + 1] = brother->key[i - posNode->no];
                posNode->childNode[i + 1] = brother->childNode[i - posNode->no];
                brother->childNode[i - posNode->no]->fatherNode = posNode;
            }
            posNode->childNode[i + 1] = brother->childNode[i - posNode->no];
            brother->childNode[i - posNode->no]->fatherNode = posNode;

            node *temp = posNode->childNode[posNode->no + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            posNode->key[posNode->no] = temp->key[0];
            //����ϲ���ڵ��������ֵ
            // no
            posNode->no += brother->no + 1;

            // brother
            if (brother->nextNode != nullptr)
            {
                if (brother->nextNode->nextNode != nullptr)posNode->brother = brother->brother;
                else
                {
                    posNode->brother = brother->brother;
                    brother->brother->brother = posNode;
                }
            }
            else
                posNode->brother = posNode->fatherNode->childNode[posNode->fatherNode->no - 2];

            posNode->nextNode = brother->nextNode;

            //�����ϼ��ڵ��е���ֵ

            node* tp = brother->fatherNode;

            i = 0;
            while(i < tp->no && compare(tp->key[i], brother->key[0]) < 0)
                i++;
            i--;
            if(posNode->fatherNode == brother->fatherNode)
            {
                for (; i < tp->no - 1; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i + 1] = tp->childNode[i + 2];
                }
                //tp->key[i] = 0;
                tp->childNode[i + 1] = nullptr;
            }
            else    // fatherNodes are different
            {
                for (; i < tp->no; i++)
                {
                    tp->key[i] = tp->key[i + 1];
                    tp->childNode[i] = tp->childNode[i + 1];
                }
                //tp->key[i - 1] = 0;
                tp->childNode[i] = nullptr;

            }

            delete brother;
            brother = nullptr;

            posNode = tp;
            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //��Ҫ������
            {
                Merge();
            }
        }
        else                 //���ұߵĽڵ�
        {
            //�ϲ�
            for (i = brother->no; i < brother->no + posNode->no; i++)
            {
                brother->key[i + 1] = posNode->key[i - brother->no];
                brother->childNode[i + 1] = posNode->childNode[i - brother->no];
                posNode->childNode[i - brother->no]->fatherNode = brother;
            }
            brother->childNode[i + 1] = posNode->childNode[i - brother->no];
            posNode->childNode[i - brother->no]->fatherNode = brother;

            node *temp = brother->childNode[brother->no + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            brother->key[brother->no] = temp->key[0];

            //�ϲ����������ݴ���
            brother->no += posNode->no + 1;
            brother->nextNode = nullptr;
            brother->brother = brother->fatherNode->childNode[brother->fatherNode->no - 2];

            //�滻�ϼ��ڵ��е�����
            node* tp = brother->fatherNode;
            //tp->key[tp->no - 1] = 0;
            tp->childNode[tp->no] = nullptr;

            delete posNode;
            posNode = tp;

            posNode->no--;
            if (posNode->no < (N + 1) / 2 - 1)   //��Ҫ������
            {
                Merge();
            }
        }
    }
    else                                          //���ڵ㲻���Ժϲ�
    {
        if (posNode->nextNode != nullptr)            //�������ұߵĽڵ�
        {
            //���������ڵ�����ݸ���
            int w = posNode->no;

            posNode->childNode[w + 1] = brother->childNode[0];
            posNode->childNode[w + 1]->fatherNode = posNode;

            node *temp = posNode->childNode[w + 1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            posNode->key[posNode->no] = temp->key[0];

            posNode->no++;
            brother->no--;

            //����ǰ��
            for (i = 0; i < brother->no + 1; i++)
            {
                brother->key[i] = brother->key[i + 1];
                brother->childNode[i] = brother->childNode[i + 1];
            }
            //����ת�ƺ��λ����
            brother->childNode[i] = nullptr;
            //brother->key[i - 1] = 0;
        }
        else           //���ұߵĽڵ�
        {
            //�������ݸ���
            for (i = posNode->no; i > 0; i--)              //���ݺ���
            {
                posNode->key[i] = posNode->key[i - 1];
                posNode->childNode[i + 1] = posNode->childNode[i];
            }
            posNode->childNode[1] = posNode->childNode[0];
            posNode->childNode[0] = brother->childNode[brother->no];
            posNode->childNode[0]->fatherNode = posNode;


            node *temp = posNode->childNode[1];
            while(Isleaf(temp) != 1)
                temp = temp->childNode[0];
            posNode->key[0] = temp->key[0];
            //posNode->key[0] = brother->key[brother->no];

            brother->no--;
            posNode->no++;

            //����ת�ƺ��λ����
            brother->childNode[brother->no + 1] = nullptr;
            //brother->key[brother->no] = 0;
        }
    }
}

template<class T>
void bpTree<T>::Index(const string & indexName)               //���������ļ�
{
    File &file = BufferManager::open(indexName);

    pos_type total = 0;
    for (headNode = treeRoot; headNode->isLeaf == 0; headNode = headNode->childNode[0])
        ;
    node* next = headNode;
    file.seekp(sizeof(pos_type));
    for (; next != nullptr;)
    {
        file << next->no;
        for (int i = 0; i < next->no; i++)
        {
            file << next->key[i];
            file << next->dataPos[i];
        }
        //file.flush();
        next = next->nextNode;
        total++;
    }
    file.seekp(0);
    file << total;
    file.flush();
}


//#include <iostream>
template<class T>
void bpTree<T>::Buildtree(const string & indexName)           //�������ļ��е�������b+��
{
    File &file = BufferManager::open(indexName);

    pos_type total;
    pos_type pos;
    T key;
    int i, num;
    file.seekg(0);
    file >> total;

    for (i = 0; i < total; i++)
    {
        file >> num;
        for (int j = 0; j < num; j++)
        {
            file >> key; file >> pos;
            Insert_node(key, pos);
        }

    }
}

#ifdef TEST
template<class T>
void bpTree<T>::Show()
{
    for (headNode = treeRoot; headNode->isLeaf == 0; headNode = headNode->childNode[0])
        ;
    node* p=headNode;
    if(p!=nullptr)
    {

        for(;Isleaf(p)==0;)
            p=p->childNode[0];
        int j=0;
        headNode = p->fatherNode;
        for(;;)
        {
            j=0;
            if(p != nullptr)
            {
                while(p->nextNode!=nullptr)
                {
                    for(int i = 0; i < p->no;i++)
                    {
                        std::cout<<p->key[i];
                        std::cout<<"    ";
                        j++;
                    }
                    p=p->nextNode;
                    std::cout<<"\n"<<"\n";
                }
                for(int i = 0; i < p->no; i++)
                {
                    std::cout<<p->key[i];
                    std::cout<<"    ";
                    j++;
                }
                std::cout<<"\n"<<"\n";
                std::cout<<j<<"\n";
                p=headNode;
                std::cout<<"-------------------------------------"<<"\n";
            }
            if(p != nullptr)
            {
                if(p->fatherNode!=nullptr)
                    headNode=p->fatherNode;
                else
                    break;
            }
            if(p==nullptr)break;
        }


        for(int i = 0;i < p->no; i++)
        {
            std::cout<<p->key[i];
            std::cout<<"    ";
            j++;
        }
        std::cout<<"\n"<<"\n";

    }
    else
        std::cout<<"no data is exist";
}
#endif

#endif //BPTREE_H_
