#include "3rdparty.h"

#include "tree.h"

// 二叉搜索树，排序的二叉树，并且没有重复值
// 下面的示例我没有特意去处理重复值

template <typename T>
class CBst {
    public:
        CBst() {}

        bool search(const T & v);

        void insert0(const T & v);
        void insert1(const T & v);
        void insert2(const T & v);

        void remove(const T & v);

        // 层次遍历，属于广度优先搜索
        void leverOrder();

        // 前中后遍历，属于深度优先搜索
        void preorder();
        void inorder();
        void postorder();

        T min();
        T max();

        int height();

    private:
        Node<T> *m_root = nullptr;
};

template <typename T>
void preorder(Node<T> * node)
{
    if (node == nullptr) return ;
    SPDLOG_INFO("value [{}]", node->value);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void inorder(Node<T> * node)
{
    if (node == nullptr) return ;
    inorder(node->left);
    SPDLOG_INFO("value [{}]", node->value);
    inorder(node->right);
}

template <typename T>
void postorder(Node<T> * node)
{
    if (node == nullptr) return ;
    postorder(node->left);
    postorder(node->right);
    SPDLOG_INFO("value [{}]", node->value);
}

template <typename T>
bool search(Node<T> * node, const T & v)
{
    if (node == nullptr) return false;
    if (node->value == v) return true;
    else if (node->value < v) return search(node->right, v);
    else return search(node->left, v);
}

template <typename T>
Node<T> * insertOther(Node<T> * root, Node<T> * node)
{
    if (root == nullptr) return node;
    if (root->value <= node->value)
        root->right = insertOther(root->right, node);
    else
        root->left = insertOther(root->left, node);
    return root;
}

template <typename T>
void insert(Node<T> * root, Node<T> * node)
{
    if (root->value > node->value) {
        if (root->left == nullptr) {
            root->left = node;
        } else {
            insert(root->left, node);
        }
    } else {
        if (root->right == nullptr) {
            root->right = node;
        } else {
            insert(root->right, node);
        }
    }
}

// 删除节点分三种情况
// 1. 没有子节点，直接删除就行
// 2. 只有一个子节点，返回子节点就行，删除当前的
// 3. 有两个子节点，将右节点侧最小值赋值到当前，然后删除最小值，或则将左节点最大值赋值到当前值，删除最大值
template <typename T>
Node<T> * remove(Node<T> * root, const T & v)
{
    if (root == nullptr) return nullptr;

    if (root->value == v) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->right == nullptr) {
            auto *p = root->left;
            delete root;
            return p;
        } else if (root->left == nullptr) {
            auto *p = root->right;
            delete root;
            return p;
        } else {
            // 查找右边最小值
            Node<T> * p = root->right;
            while (p->left) {
                p = p->left;
            }

            root->value = p->value;
            root->right = remove(root->right, p->value);
        }
    } else if (root->value < v) {
        root->left = remove(root->left, v);
    } else {
        root->right = remove(root->right, v);
    }

    return root;
}

template <typename T>
int height(Node<T> * node, int h)
{
    if (node == nullptr) {
        return h;
    }

    auto hl = height(node->left, h+1);
    auto hr = height(node->right, h+1);

    return hl > hr ? hl : hr;
}

template <typename T>
bool CBst<T>::search(const T & v)
{
    return ::search(m_root, v);
}

// 非递归方式
template <typename T>
void CBst<T>::insert0(const T & v)
{
    auto *pNode = new Node<T>{v};

    if (m_root == nullptr) {
        m_root = pNode;
        return ;
    }

    Node<T> * t = m_root;
    while(1) {
        if (t->value > pNode->value) {
            if (t->left == nullptr) {
                t->left = pNode;
                return ;
            } else {
                t = t->left;
            }
        } else {
            if (t->right == nullptr) {
                t->right = pNode;
                return ;
            } else {
                t = t->right;
            }
        }
    }
}

// 递归方式
template <typename T>
void CBst<T>::insert1(const T & v)
{
    auto *pNode = new Node<T>{v};

    if (m_root == nullptr) {
        m_root = pNode;
        return ;
    }

    insert(m_root, pNode);
}

// 别人的递归写法
template <typename T>
void CBst<T>::insert2(const T & v)
{
    m_root = insertOther(m_root, new Node<T>{v});
}

template <typename T>
void CBst<T>::remove(const T & v)
{
    m_root = ::remove(m_root, v);
}
        
// 层次遍历，关键的就是需要一个队列用来保存当前层的节点
// 还有一种递归方式，但是不推荐使用，递归方式必须在全部递归结束，才能再次遍历结果，需要借助二维数组
template <typename T>
void CBst<T>::leverOrder()
{
    SPDLOG_INFO("lever-order --------------------- ");

    if (m_root == nullptr) return;

    std::queue<Node<int> *> q;
    q.push(m_root);

    while (!q.empty()) {
        auto * pNode = q.front();

        SPDLOG_INFO("value [{}]", pNode->value);
        if (pNode->left) q.push(pNode->left);
        if (pNode->right) q.push(pNode->right);
        q.pop();
    }
}

template <typename T>
void CBst<T>::preorder()
{
    SPDLOG_INFO("preorder --------------------- ");
    // ::preorder(m_root);

    std::function<void(Node<T> *)> f = [&](Node<T> * node) {
        if (node == nullptr) return ;
        SPDLOG_INFO("value [{}]", node->value);
        f(node->left);
        f(node->right);
    };

    f(m_root);
}

template <typename T>
void CBst<T>::inorder()
{
    SPDLOG_INFO("inorder --------------------- ");
    ::inorder(m_root);
}

template <typename T>
void CBst<T>::postorder()
{
    SPDLOG_INFO("postorder --------------------- ");
    ::postorder(m_root);
}

template <typename T>
T CBst<T>::min()
{
    if (m_root == nullptr) THROW("empty");
    Node<T> * p = m_root;
    while (p->left) {
        p = p->left;
    }

    return p->value;
}

template <typename T>
T CBst<T>::max()
{
    if (m_root == nullptr) THROW("empty");
    Node<T> * p = m_root;
    while (p->right) {
        p = p->right;
    }

    return p->value;
}

template <typename T>
int CBst<T>::height()
{
    return ::height(m_root, 0);
}

int main()
{
    spdlog_init();

//                      10
//                   5      20
//                 4   9      30
//                3             40
    CBst<int> bst;

    bst.preorder();

    bst.insert0(10);
    bst.preorder();

    bst.insert0(20);
    bst.insert1(5);
    bst.insert1(4);
    bst.insert1(9);
    bst.insert2(3);
    bst.insert2(30);
    bst.insert2(40);
    bst.preorder();

    SPDLOG_INFO("search 3[{}]", bst.search(3) ? "found" : "not fount");
    SPDLOG_INFO("search 30[{}]", bst.search(30) ? "found" : "not fount");
    SPDLOG_INFO("search 300[{}]", bst.search(300) ? "found" : "not fount");
    SPDLOG_INFO("search 3000[{}]", bst.search(3000) ? "found" : "not fount");

    SPDLOG_INFO("min[{}]", bst.min());
    SPDLOG_INFO("min[{}]", bst.max());
    SPDLOG_INFO("height[{}]", bst.height());

    bst.leverOrder();

    bst.preorder();
    bst.inorder();
    bst.postorder();

    bst.remove(10);
    bst.preorder();

    return 0;
}