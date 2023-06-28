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
        std::vector<int*> _psorted; // Vector of pointers to cross elements. 

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
    //                    Iterator 
    // ==================================================

        class Iterator {

        protected:
            MagicalContainer& container;
            std::vector<int*>::iterator iter;

        public:
            // Constructors and assignment operator
            Iterator() = delete;
            Iterator(MagicalContainer& cont, std::vector<int*>::iterator iter ) : container(cont), iter(iter) {}
            Iterator(const Iterator& other) : container(other.container), iter(other.iter) {}
            Iterator& operator=(const Iterator& other);
            virtual ~Iterator() = default;

            // Operators: ==, !=, >, <, *, ++
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
            bool operator<(const Iterator& other) const;
            bool operator>(const Iterator& other) const;
            virtual int operator*(); // The dynamic cast need a v-table so the decleration of virtual forces to make one for the object 
            Iterator& operator++();

            // Begin and end iterators
            Iterator begin();
            Iterator end();
        };



    // ==================================================
    //              AscendingIterator 
    // ==================================================

        class AscendingIterator: public Iterator{

            public:
                AscendingIterator(MagicalContainer& container) : Iterator(container, container._psorted.begin()) {}
        };


    // ==================================================
    //              PrimteIterator 
    // ==================================================

        class PrimeIterator: public Iterator{

            public:
                PrimeIterator(MagicalContainer& cont) : Iterator(cont, cont._pprime.begin()) {}
        };


    // ==================================================
    //              SideIterator 
    // ==================================================

        class SideCrossIterator: public Iterator {

        public:
            SideCrossIterator(MagicalContainer& cont) : Iterator(cont, cont._pcross.begin()) {}
        };
    };



    bool isPrime(int);

}
