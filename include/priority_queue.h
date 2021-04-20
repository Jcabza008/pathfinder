#pragma once

namespace pathfinder
{
    template <typename T>
    class PriorityQueue
    {
        public:
        PriorityQueue(std::function<bool(T, T)> _comparator = [](T lhs, T rhs){ return lhs < rhs; })
            : comparator(_comparator) {}

        void push(T element)
        {
            this->data.push_back(element);
            this->map[element] = this->size() - 1;
            heapifyUp(this->size() - 1);
        }

        T top()
        {
            if(data.empty())
                throw std::runtime_error("illegal: queue is empty");

            return this->data[0];
        }

        void pop()
        {
            if(this->empty())
                throw std::runtime_error("illegal: queue is empty");

            this->data[0] = this->data[this->size() - 1];
            this->data.pop_back();
            this->map[this->data[0]] = 0;
            this->heapifyDown(0);
        }

        size_t size()
        {
            return this->data.size();
        }

        bool empty()
        {
            return this->data.empty();
        }

        void updateDecreased(T key)
        {
            auto index = this->map[key];
            this->heapifyUp(index);
        }

        private:
        void heapifyUp(int index)
        {
            while(index != 0 && this->comparator(this->data[index], this->data[(index - 1) / 2]))
            {
                std::swap(this->data[index], this->data[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
        }

        void heapifyDown(int index)
        {
            auto left = 2 * index + 1;
            auto right = 2 * index + 2;
            int largest = index;

            if(left < (int)this->size() && this->comparator(this->data[left], this->data[largest]))
                largest = left;
            if(right < (int)this->size() && this->comparator(this->data[right], this->data[largest]))
                largest = right;

            if(index != largest)
            {
                std::swap(this->data[index], this->data[largest]);
                this->heapifyDown(largest);
            }
        }

        void swap(int lhsIndex, int rhsIndex)
        {
            auto temp = this->data[lhsIndex];
            this->data[lhsIndex] = this->data[rhsIndex];
            this->data[rhsIndex] = temp;
            this->map[this->data[lhsIndex]] = lhsIndex;
            this->map[this->data[rhsIndex]] = rhsIndex;
        }

        std::function<bool(T, T)> comparator;
        std::vector<T> data;
        std::unordered_map<T, int> map;
    };

}