#pragma once

#include <vector>
#include <iostream> 
#include <cmath>

namespace ariel {

    bool isPrime(int);

    class MagicalContainer {

    private:
        std::vector<int> elements;
        std::vector<int*> _psorted;  
        std::vector<int*> _pprime; 
        std::vector<int*> _pcross; 

    public:

        // Default and copy constructors, destructor, and assignment operator  
        MagicalContainer() = default;
        MagicalContainer(const MagicalContainer& other) : elements(other.elements) {}
        ~MagicalContainer() = default;
        MagicalContainer& operator=(const MagicalContainer& other) {
            if (this != &other) {
                elements = other.elements;
            }
            return *this;
        }

        // Container functions
        void addElement(int element);
        void removeElement(int element);
        int size();

        void updateCross();
        void updatePrime();
        void updateSorted();
        void sortElements();

        class AscendingIterator {

        private:
            MagicalContainer &container;
            std::vector<int*>::iterator iter;

        public:
            // Constructors and assignment operator
            AscendingIterator() = delete;
            AscendingIterator(MagicalContainer& container) : container(container), iter(container._psorted.begin()) {}
            AscendingIterator(const AscendingIterator& other) : container(other.container), iter(other.iter) {}
            AscendingIterator& operator=(const AscendingIterator& other);

            // Operators: ==, !=, >, <, *, ++
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;

            int operator*() const;

            AscendingIterator& operator++();

            // Begin and end of iterator
            AscendingIterator begin();
            AscendingIterator end();
        };

        class PrimeIterator {

        private:
            MagicalContainer& container;
            std::vector<int*>::iterator iter;

        public:
            // Constructors and assignment operator
            PrimeIterator() = delete;
            PrimeIterator(MagicalContainer& cont) : container(cont), iter(container._pprime.begin()) {}
            PrimeIterator(const PrimeIterator& other) : container(other.container), iter(other.iter) {}
            PrimeIterator& operator=(const PrimeIterator& other);

            // Operators: ==, !=, >, <, *, ++
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;

            int operator*() const;

            PrimeIterator& operator++();

            // Begin and end iterators
            PrimeIterator begin();
            PrimeIterator end();
        };

        class SideCrossIterator {

        private:
            MagicalContainer& container;
            std::vector<int*>::iterator iter;

        public:
            // Constructors and assignment operator
            SideCrossIterator() = delete;
            SideCrossIterator(MagicalContainer& cont) : container(cont), iter(cont._pcross.begin()) {}
            SideCrossIterator(const SideCrossIterator& other) : container(other.container), iter(other.iter) {}
            SideCrossIterator& operator=(const SideCrossIterator& other);

            // Operators: ==, !=, >, <, *, ++
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;

            int operator*() const;
            SideCrossIterator& operator++();

            // Begin and end iterators
            SideCrossIterator begin();
            SideCrossIterator end();
            };
    };
}
