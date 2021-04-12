#pragma once

namespace pathfinder
{
    template <typename T>
    class PriorityQueue
    {
        public:
        PriorityQueue(std::function<bool(T, T)> _comparator = [](T lhs, T rhs){ return lhs < rhs; })
            : comparator(_comparator) {}

        bool push(T element)
        {
            this->data.push_back(element);
            heapifyUp(this->size() - 1);
            return true;
        }

        T top()
        {
            return this->data[0]; //TODO: throw if empty
        }

        void pop()
        {
            if(this->empty()) //TODO: throw if empty
                return;

            this->data[0] = this->data[this->size() - 1];
            this->data.pop_back();
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

        void reorder()
        {
            int start = (this->size() / 2) / 1;
            for(auto i = start; i >= 0; i--)
            {
                this->heapifyDown(i);
            }
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

        std::function<bool(T, T)> comparator;
        std::vector<T> data;
    };
}