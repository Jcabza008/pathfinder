#pragma once

namespace PATHFINDER
{
    template <typename T>
    class PriorityQueue
    {
        public:
        PriorityQueue(uint16_t _capacity, std::function<bool(T, T)> _comparator = [](T lhs, T rhs){ return lhs < rhs; })
            : count(0), capacity(_capacity), comparator(_comparator)
        {
            this->data = new T[this->capacity];
        }

        ~PriorityQueue()
        {
            delete[] this->data;
        }

        bool push(T element)
        {
            if(this->count == this->capacity)
                return false;

            this->data[this->count] = element;
            heapifyUp(this->count);
            this->count++;
            return true;
        }

        T top()
        {
            return this->data[0];
        }

        void pop()
        {
            if(!this->count)
                return;

            this->data[0] = this->data[--this->count];
            this->heapifyDown(0);
        }

        uint16_t size()
        {
            return this->count;
        }

        bool empty()
        {
            return !this->size();
        }

        void reorder()
        {
            int start = (this->count / 2) / 1;
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

            if(left < this->count && this->comparator(this->data[left], this->data[largest]))
                largest = left;
            if(right < this->count && this->comparator(this->data[right], this->data[largest]))
                largest = right;

            if(index != largest)
            {
                std::swap(this->data[index], this->data[largest]);
                this->heapifyDown(largest);
            }
        }

        T* data;
        uint16_t count;
        uint16_t capacity;
        std::function<bool(T, T)> comparator;
    };
}