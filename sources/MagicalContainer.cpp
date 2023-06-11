#include "MagicalContainer.hpp"


namespace ariel{

    void MagicalContainer::addElement(int element) {
        elements.push_back(element);
        originalElementSort();
        sortedFix();
        primeFix();
        crossFix();

    }

    void MagicalContainer::removeElement(int element) {
         //make sure the elment is in the originalElement
        bool inList = false;
        for(auto itr = elements.begin(); itr != elements.end(); itr++)
        {
            if(*itr == element)
            {
                inList = true;
                break;
            }
        }
        if(!inList)
            throw std::runtime_error("You can't remove element that not in the list.");
        
        elements.erase(remove(elements.begin(), elements.end(), element),elements.end());
        sortedFix();
        primeFix();
        crossFix();
    }

    int MagicalContainer::size() {
        return elements.size();
    }


     void MagicalContainer::crossFix()
    {
        crossElements.clear();
        auto begin = elements.begin();
        auto end = --elements.end();

        while (begin < end)
        {
            crossElements.push_back(&(*begin));
            crossElements.push_back(&(*end));
            begin++;
            end--;
        }
        if(begin == end)
            crossElements.push_back(&(*begin));
    }
    
    void MagicalContainer::primeFix()
    {
        primeElements.clear();
        for(auto itr = elements.begin(); itr != elements.end(); ++itr)
        {
            if(isPrime(*itr))
                primeElements.push_back(&(*itr));
        }
    }

    void MagicalContainer::sortedFix()
    {
        sortedElements.clear();
        for(auto itr = elements.begin(); itr != elements.end(); ++itr)
        {
            sortedElements.push_back(&(*itr));
        }
    }

    void MagicalContainer::originalElementSort()
    {
        for(unsigned long i = 0; i < elements.size(); ++i)
        {
            for(unsigned long j = 0; j < elements.size() - i -1; j++)
            {
                if(elements[j] > elements [j+1])
                {
                    int tmp = elements[j];
                    elements[j] = elements[j+1];
                    elements[j+1] = tmp;
                }
            }
        }
    }


    /*modiy*/
    bool isPrime(int elem) {
        if (elem < 2) {
            return false;
        }
        for (int i = 2; i * i <= elem; ++i) {
            if (elem % i == 0) {
                return false;
            }
        }
        return true;
        }

}