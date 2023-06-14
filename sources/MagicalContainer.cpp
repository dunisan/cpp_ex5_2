#include "MagicalContainer.hpp"

namespace ariel {

// ==================================================
// Magical Container functions
// ==================================================

    void MagicalContainer::addElement(int element) {
        elements.push_back(element);
        _psorted.insert(_psorted.begin(), elements.size() - 1);
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
        size_t position = static_cast<size_t>(std::distance(elements.begin(), itr));
        auto eraseIterator = _psorted.begin() + static_cast<std::ptrdiff_t>(position);
        _psorted.erase(eraseIterator);

        // Update the vectors of pointers 
        updateSorted();
        updatePrime();
        updateCross();
    }

    int MagicalContainer::size() {
        return elements.size();
    }

// *****************************
// update function 

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
        // _psorted.clear();
        // for (auto itr = elements.begin(); itr != elements.end(); ++itr) {
        //     _psorted.push_back(&(*itr));
        // }

        std::size_t length = _psorted.size(); // get size of vector 

        // bubble sort - every time we run it - we run it on a sorted vector.
        // except for the first - so we need at most n comperisions. O(N) 
        // for(std::size_t i=0; i <  _psorted.size();i++){
        //     std::cout<<*_psorted[i] << "  "; 
        // }
        //             std::cout<< std::endl; 


        for (std::size_t i = 0; i < length; ++i) {
            bool swapped = false;
            
            for (std::size_t j = 0; j < length - i - 1; j++) {
                if (elements[(_psorted[j])] > elements[(_psorted[j+1])]) {
                    size_t temp = _psorted[j];
                    _psorted[j] = _psorted[j+1]; 
                    _psorted[j+1] = temp; 
                    swapped = true;
                }
                else{
                    swapped = true; 
                    break; 
                }
            }
            
            // If no swaps were made in the inner loop, the array is already sorted
            if (!swapped) {
                break;
            }
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
//  AscendingIterator functions
// ==================================================

    // ***************
    // oprators

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
        if (&container != &other.container) {
            throw std::runtime_error("assignment is not valid - different containers");
        }

        iter = other.iter;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }

        return iter == other.iter;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }

        return iter < other.iter;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("compering is not valid - different containers");
        }

        return iter > other.iter;
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if (iter == container._psorted.end()) {
            throw std::out_of_range("Iterator out of range");
        }

        return this->container.elements[*iter];
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if (iter == container._psorted.end()) {
            throw std::runtime_error("Iterator out of range");
        }

        ++iter;
        return *this;
    }
    // ****************
    // Begin and end functions 

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        iter = container._psorted.begin();
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        iter = container._psorted.end();
        return *this;
    }

// ==================================================
// PrimeIterator functions
// ==================================================

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return iter == other.iter;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return iter < other.iter;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return iter > other.iter;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        if (iter == container._pprime.end()) {
            throw std::out_of_range("Iterator out of range");
        }

        return **iter;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if (iter == container._pprime.end()) {
            throw std::runtime_error("Iterator out of range");
        }

        ++iter;
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        iter = container._pprime.begin();
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        iter = container._pprime.end();
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
        if (&container != &other.container) {
            throw std::runtime_error("You can't assign iterators from different containers");
        }

        iter = other.iter;
        return *this;
    }



// ==================================================
// SideCrossIterator functions
// ==================================================

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return iter == other.iter;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return iter < other.iter;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }

        return iter > other.iter;
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (iter == container._pcross.end()) {
            throw std::out_of_range("Iterator out of range");
        }

        return **iter;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (iter == container._pcross.end()) {
            throw std::runtime_error("Iterator out of range");
        }

        ++iter;
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        iter = container._pcross.begin();
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        iter = container._pcross.end();
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
        if (&container != &other.container) {
            throw std::runtime_error("You can't assign iterators from different containers");
        }

        iter = other.iter;
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
