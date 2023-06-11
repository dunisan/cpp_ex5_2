#pragma once 

#include <vector>
#include <string>
#include <iterator>
#include <set>
#include <math.h>
#include <algorithm>
#include <iostream> 


namespace ariel{
    bool isPrime(int);

    class MagicalContainer {

    private:
        std::vector<int> elements;
        std::vector<int*> sortedElements;  
        std::vector<int*> primeElements; 
        std::vector<int*> crossElements; 

    public:

        // default and copy constructors, distructor and assignment operator  
        MagicalContainer() = default;
        MagicalContainer(const MagicalContainer& other) : elements(other.elements) {}
        ~MagicalContainer() = default;
        MagicalContainer& operator=(const MagicalContainer& other) {
            if (this != &other) {
                elements = other.elements;
            }
            return *this;
        }

        // container functions
        void addElement(int element);
        void removeElement(int element);
        int size();
        void crossFix();
        void primeFix();
        void sortedFix();
        void originalElementSort();



        class AscendingIterator {

            private:
                MagicalContainer &container;
                int position;
                std::vector<int*>::iterator iter;

            public:
                // Default constructor, constructor, Copy constructor, Destructor, Assignment operator
                
                AscendingIterator():container(*(new MagicalContainer)),iter(container.sortedElements.begin()), position(0){};
                AscendingIterator(MagicalContainer& container) : container(container),iter(container.sortedElements.begin()), position(0) {}
                ~AscendingIterator() = default;
                AscendingIterator(AscendingIterator& other):container(other.container),iter(other.iter), position(other.position){};
                AscendingIterator& operator=(const AscendingIterator& other){
                    if (this != &other){
                        throw std::runtime_error("you cant '=' they are not the same container");
                    }
                    container = other.container;
                    iter = other.iter; 
                    position = other.position;
                    
                    return *this;
                };

                // operators- == , != , > , < , * , ++ 
                bool operator==(const AscendingIterator& other) const {
                    if(&container != &other.container)
                        throw std::invalid_argument("you cant '==' they are not the same container");
                    return position == other.position;
                }
                
                bool operator!=(const AscendingIterator& other) const {
                    return !(*this == other);
                }
                bool operator<(const AscendingIterator& other) const{
                    if (&container != &other.container) {
                        throw std::invalid_argument("Comparing iterators from different containers");
                    }
                    return position < other.position;
                }
                bool operator>(const AscendingIterator& other) const{
                    if (&container != &other.container) {
                     
                        throw std::invalid_argument("Comparing iterators from different containers");
                    }
                    return position > other.position;
                }

                int operator*() const {
                    if (iter == container.sortedElements.end()) 
                        throw std::out_of_range("Iterator out of range");

                    return **iter;

                }

                AscendingIterator& operator++() {
                    if (iter == container.sortedElements.end())
                        throw std::runtime_error("out of range");
                    ++iter;
                    ++position;
                    return *this;
                }

                // Begin and end of iterator
                AscendingIterator begin() {
                    iter = container.sortedElements.begin();
                    position = 0;
                    return *this;
                }

                AscendingIterator end() {
                    
                    iter = container.sortedElements.end();
                    position = container.sortedElements.size();
                    return *this;
                }
            };


        

        class PrimeIterator {

            private:
                MagicalContainer& container;
                int position;
                std::vector<int*>::iterator iter;

            public:
                
                // Default constructor, constructor, Copy constructor, Destructor, Assignment operator
                PrimeIterator():container(*(new MagicalContainer())),iter(container.primeElements.begin()),position(1){};
                PrimeIterator(MagicalContainer& cont) : container(cont),iter(container.primeElements.begin()),position(1){}
                PrimeIterator(const PrimeIterator& other):container(other.container),position(other.position){};
                ~PrimeIterator() = default;
                PrimeIterator& operator=(const PrimeIterator& other){
                    if(&container != &other.container)
                        throw std::runtime_error("you cant '=' they are not the same container");
                    iter = other.iter;
                    position = other.position;
                    return *this;  
                }

                // operators- == , != , > , < , * , ++ 
                bool operator==(const PrimeIterator& other) const {
                    if(&container != &other.container)
                        throw std::invalid_argument("you cant '==' they are not the same container");
                    return position == other.position;
                }

                bool operator!=(const PrimeIterator& other) const {
                    return !(*this == other);
                }

                bool operator<(const PrimeIterator& other) const{
                    if (&container != &other.container) {
                        throw std::invalid_argument("Comparing iterators from different containers");
                    }
                    return position < other.position;
                }

                bool operator>(const PrimeIterator& other) const{
                    if (&container != &other.container) {
                    throw std::invalid_argument("Comparing iterators from different containers");
                }
                return position > other.position;
                }

                int operator*() const {
                    if (iter == container.crossElements.end()) 
                        throw std::out_of_range("Iterator out of range");
            
                    return **iter;
                }

                PrimeIterator& operator++() {
                    if (iter == container.primeElements.end())
                        throw std::runtime_error("out of range");
                    ++iter;
                    ++position;
                    return *this;
                }

                // Begin and end iterators
                PrimeIterator begin() {
                    iter = container.primeElements.begin();
                    position = 0;
                    return *this;
                }

                PrimeIterator end() {
                    iter = container.primeElements.end();
                    position = container.primeElements.size();
                    return *this;
                }
            };



        class SideCrossIterator {

        private:
            MagicalContainer& container;
            int position;
            std::vector<int*>::iterator iter;


        public:
            // Default constructor, constructor, Copy constructor, Destructor, Assignment operator
            SideCrossIterator():container(*(new MagicalContainer())), iter(container.crossElements.begin()), position(1){};
            SideCrossIterator(MagicalContainer& cont) : container(cont), iter(container.crossElements.begin()), position(1) {}
            SideCrossIterator(const SideCrossIterator& other):container(other.container), position(other.position){};
            ~SideCrossIterator() = default;
            SideCrossIterator& operator=(const SideCrossIterator& other) {
                if(&container != &other.container)
                throw std::runtime_error("you cant '=' they are not the same container");
                iter = other.iter;
                position = other.position;
                return *this;
            };

            // operators- == , != , > , < , * , ++ 
            bool operator==(const SideCrossIterator& other) const {
                if(&container != &other.container)
                    throw std::invalid_argument("you cant '==' they are not the same container");
                return position == other.position;
            }

            bool operator!=(const SideCrossIterator& other) const {
                return !(*this == other);
            }

            bool operator<(const SideCrossIterator& other) const{
                if (&container != &other.container) {
                    throw std::invalid_argument("Comparing iterators from different containers");
                }
                return position < other.position;
            }

            bool operator>(const SideCrossIterator& other) const{
                if (&container != &other.container) {
                    throw std::invalid_argument("Comparing iterators from different containers");
                }
                return position > other.position;
            }

            int operator*() const {
                if (iter == container.crossElements.end()) 
                    throw std::out_of_range("Iterator out of range");
            
                return **iter;
            }

            SideCrossIterator& operator++() {
                if (iter == container.crossElements.end())
                    throw std::runtime_error("out of range");
                ++iter;
                ++position;
                return *this;
            }

            // Begin adn end iterators 
            SideCrossIterator begin() {
                iter = container.crossElements.begin();
                position = 0;
                return *this; 
            }

            SideCrossIterator end() {
                
                iter = container.crossElements.end();
                position = container.crossElements.size();
                return *this;
            }
        };
    };
}

