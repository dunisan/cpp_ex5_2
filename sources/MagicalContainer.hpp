#pragma once

#include <vector>
#include <iostream> 
#include <cmath>

namespace ariel {




// ==================================================
//              Magical Container
// ==================================================


    class MagicalContainer {

    private:
        std::vector<int> elements; // The vector of the elements
        std::vector<int*> _pprime; // Vector of pointers to prime elements. 
        std::vector<int*> _pcross; // Vector of pointers to cross elements. 

    public:

        // Default and copy constructors, destructor, and assignment operator  
        MagicalContainer() = default;
        MagicalContainer(const MagicalContainer& other) : elements(other.elements) {}
        ~MagicalContainer() = default;
        MagicalContainer& operator=(const MagicalContainer& other);

        // Container functions
        void addElement(int element);
        void removeElement(int element);
        int size();

        void updateCross();
        void updatePrime();
        void updateSorted();
        void sortElements();



    // ==================================================
    //              AscendingIterator 
    // ==================================================

        class AscendingIterator {

        private:
            MagicalContainer &container;
            std::vector<int>::iterator iter;

        public:
            // Constructors and assignment operator
            AscendingIterator() = delete;
            AscendingIterator(MagicalContainer& container) : container(container), iter(container.elements.begin()) {}
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


    // ==================================================
    //              PrimteIterator 
    // ==================================================

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


    // ==================================================
    //              SideIterator 
    // ==================================================

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



    bool isPrime(int);

}

