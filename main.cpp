#include <iostream>
#include <queue>
#include <deque>
#include <vector>

template <typename TValue>
class Node
{
public:
    Node(TValue i_value)
        : mp_left(nullptr)
        , mp_right(nullptr)
        , m_value(i_value)
    {
    }

    ~Node()
    {
        delete mp_left;
        delete mp_right;
    }

    void Add(TValue i_value)
    {
        Node<TValue>* next_node = this;
        Node<TValue>* current_node = this;
        while (next_node)
        {
            if (next_node->m_value == i_value)
                return;

            current_node = next_node;
            if (i_value < next_node->m_value)
                next_node = next_node->mp_left;
            else if (i_value > next_node->m_value)
                next_node = next_node->mp_right;
        }

        if (i_value < current_node->m_value)
            current_node->mp_left = new Node<TValue>(i_value);

        if (i_value > current_node->m_value)
            current_node->mp_right = new Node<TValue>(i_value);
    }

    bool Find(TValue i_value)
    {
        Node<TValue>* next_node = this;
        while(next_node)
        {
            if (i_value == next_node->m_value)
                return true;

            if (i_value < next_node->m_value)
                next_node = next_node->mp_left;
            else
                next_node = next_node->mp_right;
        }

        return false;
    }

    void PreOrder()
    {
        _PreOrder(this);
    }

    void PostOrder()
    {
        _PostOrder(this);
    }

    void InOrder()
    {
        _InOrder(this);
    }

    void BreadthFirstSearch()
    {
        std::queue<const Node<TValue>*> nodes_queue;
        nodes_queue.push(this);

        while(!nodes_queue.empty())
        {
            const Node<TValue>* node = nodes_queue.front();
            nodes_queue.pop();

            std::cout << node->m_value << " ";
            if (node->mp_left)
                nodes_queue.push(node->mp_left);

            if (node->mp_right)
                nodes_queue.push(node->mp_right);
        }
    }

private:
    void _PreOrder(const Node<TValue>* i_node)
    {
        if (!i_node)
            return;

        std::cout << i_node->m_value << " ";
        _PreOrder(i_node->mp_left);
        _PreOrder(i_node->mp_right);
    }

    void _PostOrder(const Node<TValue>* i_node)
    {
        if (!i_node)
            return;

        _PostOrder(i_node->mp_left);
        _PostOrder(i_node->mp_right);
        std::cout << i_node->m_value << " ";
    }

    void _InOrder(const Node<TValue>* i_node)
    {
        if (!i_node)
            return;

        _InOrder(i_node->mp_left);
        std::cout << i_node->m_value << " ";
        _InOrder(i_node->mp_right);
    }

private:
    Node<TValue>* mp_left;
    Node<TValue>* mp_right;
    TValue m_value;
};


int main(int, char**)
{
    Node<int> node(5);
    node.Add(9);
    node.Add(8);
    node.Add(10);
    node.Add(2);
    node.Add(1);
    node.Add(3);
    node.Add(4);

    for (const int i : {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20})
    {
        const auto result = node.Find(i) ? "found" : "not found";
        std::cout << i << " " << result << std::endl;
    }

    node.PreOrder();

    std::cout << std::endl;
    node.PostOrder();

    std::cout << std::endl;
    node.InOrder();

    std::cout << std::endl;
    node.BreadthFirstSearch();

    std::cout << std::endl;
    return 0;
}
