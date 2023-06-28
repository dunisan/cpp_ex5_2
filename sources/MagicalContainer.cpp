#include "MagicalContainer.hpp"

namespace ariel {

// ==================================================
// Magical Container functions
// ==================================================


    MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }

    void MagicalContainer::addElement(int element) {
        elements.push_back(element);
        sortElements();
        updateCross();
        updatePrime();
        updateSorted();
        
    }

    void MagicalContainer::removeElement(int element) {
        // Check if the element exists in the list
        auto itr = std::find(elements.begin(), elements.end(), element);
        if (itr == elements.end()) {
            throw std::runtime_error("The element doesn't exist.");
        }
        // Remove the element
        elements.erase(itr);

        // Update the vectors of pointers (all updates runtime is O(n)!)
        updatePrime();
        updateCross();
    }

    int MagicalContainer::size() {
        return elements.size();
    }

// *****************************
// update function 
// *****************************

    void MagicalContainer::updateCross() {
        _pcross.clear();
        auto begin = elements.begin();
        auto end = --elements.end();


        while (begin < end) {
            _pcross.push_back(&(*begin));
            _pcross.push_back(&(*end));
            ++begin;
            --end;
        }
        if (begin == end) {
            _pcross.push_back(&(*begin));
        }
    }
    
    void MagicalContainer::updatePrime() {
        _pprime.clear();
        for (auto itr = elements.begin(); itr != elements.end(); ++itr) {
            if (isPrime(*itr)) {
                _pprime.push_back(&(*itr));
            }
        }
    }

        
    void MagicalContainer::updateSorted() {
        _psorted.clear();
        for (auto itr = elements.begin(); itr != elements.end(); ++itr) {
            _psorted.push_back(&(*itr));
        }
    }



    void MagicalContainer::sortElements() {
        
        std::size_t length = elements.size(); // get size of vector 

        // bubble sort - every time we run it - we run it on a sorted vector.
        // except for the first - so we need at most n comperisions. O(N) 
        for (std::size_t i = 0; i < length; ++i) {
            bool swapped = false;
            
            for (std::size_t j = 0; j < length - i - 1; j++) {
                if (elements[j] > elements[j + 1]) {
                    std::swap(elements[j], elements[j + 1]);
                    swapped = true;
                }
            }
            
            // If no swaps were made in the inner loop, the array is already sorted
            if (!swapped) {
                break;
            }
        }
    }
// ==================================================
// Iterator functions
// ==================================================

    // ***************
    // oprators
    // ***************

    MagicalContainer::Iterator& MagicalContainer::Iterator::operator=(const Iterator& other) {
        if (&container != &other.container) {
            throw std::runtime_error("assignment is not valid - different containers");
        }

        iter = other.iter;
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const Iterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }

        return iter == other.iter;
    }

    bool MagicalContainer::Iterator::operator!=(const Iterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }
        return !(*this == other);
    }

    bool MagicalContainer::Iterator::operator<(const Iterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }

        return iter < other.iter;
    }

    bool MagicalContainer::Iterator::operator>(const Iterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }

        return iter > other.iter;
    }

    int MagicalContainer::Iterator::operator*() {

        if (dynamic_cast<AscendingIterator*>(this)) {
            if (iter == container._psorted.end()) {
                throw std::out_of_range("Iterator out of range");
            }           

        } else if (dynamic_cast<PrimeIterator*>(this)) {
            if (iter == container._pprime.end()) {
                throw std::out_of_range("Iterator out of range");
            }
        } else{

            if (iter == container._pcross.end()) {
                throw std::out_of_range("Iterator out of range");
            }
        }

        return **iter; 
    }

    MagicalContainer::Iterator& MagicalContainer::Iterator::operator++() {


        if (dynamic_cast<AscendingIterator*>(this)) {
            if (iter == container._psorted.end()) {
                throw std::runtime_error("Iterator out of range");
            }

        } else if (dynamic_cast<PrimeIterator*>(this)) {
            if (iter == container._pprime.end()) {
                throw std::runtime_error("Iterator out of range");
            }
        } else{

            if (iter == container._pcross.end()) {
                throw std::runtime_error("Iterator out of range");
            }
        }

        ++iter;
        return *this;
    }
    // ***********************
    // Begin and end functions 
    // ***********************

    MagicalContainer::Iterator MagicalContainer::Iterator::begin() {

        if (dynamic_cast<AscendingIterator*>(this)) {
            iter = container._psorted.begin();

        } else if (dynamic_cast<PrimeIterator*>(this)) {
            iter = container._pprime.begin();
       
        } else{
            iter = container._pcross.begin();
        }
        return *this;
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::end() {
        if (dynamic_cast<AscendingIterator*>(this)) {
            iter = container._psorted.end();

        } else if (dynamic_cast<PrimeIterator*>(this)) {
            iter = container._pprime.end();
       
        } else{
            iter = container._pcross.end();
        }
        return *this;
    }





// ==================================================
// help  functions
// ==================================================
    bool isPrime(int num) {
        if (num < 2) {
            return false;
        }

        if (num == 2) {
            return true;
        }

        if (num % 2 == 0) {
            return false;
        }

        for (int i = 3; i * i <= num; i += 2) {
            if (num % i == 0) {
                return false;
            }
        }

        return true;
    }

}  