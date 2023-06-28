#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>
using namespace ariel;
using namespace std;



// ==================================================
//            Magical Container Tests
// ==================================================
TEST_SUITE("Magical Element"){

    TEST_CASE("Add Elements") {

        SUBCASE("adding one element") {
            MagicalContainer container; 
            
            container.addElement(1);
            CHECK_EQ(container.size(), 1); 
        }

        SUBCASE("adding 20 element") {
            MagicalContainer container;

            for (int i = 1; i <= 20; ++i) {
                container.addElement(i);
            }

            CHECK_EQ(container.size(), 20);
        }
    }

    TEST_CASE("delete Elements") {

        SUBCASE("delete one element") {
            MagicalContainer container;
            container.addElement(1);
            container.removeElement(1);
            CHECK_EQ(container.size(), 0);
        }

        SUBCASE("delete non exisiting element") {
            MagicalContainer container;
            container.addElement(1);
            CHECK_THROWS(container.removeElement(2)); 
        }

        SUBCASE("delete from empty container") {
            MagicalContainer container;
            CHECK_THROWS(container.removeElement(1)); 
        }
    }

    TEST_CASE("size of magical container") {

        SUBCASE("size at creation") {
            MagicalContainer container;
            CHECK_EQ(container.size(), 0);
        }

        SUBCASE("size after creating 5 elements") {
            MagicalContainer container;
            for (int i = 1; i <= 5; i++) {
                container.addElement(i);
            }
            CHECK_EQ(container.size(), 5);
        }

        SUBCASE("size after creating 5 elements and deleting 3") {
            MagicalContainer container;

            for (int i = 1; i <= 5; ++i) {
                container.addElement(i);
            }

            container.removeElement(1);
            container.removeElement(3);
            container.removeElement(5);

            CHECK_EQ(container.size(), 2);
        }
    }

}


// ==================================================
//              AscendingIterator 
// ==================================================

TEST_SUITE("AscendingIterator"){

    TEST_CASE("AscendingIterator") {
    SUBCASE("copy constructor") {
        MagicalContainer container;
        container.addElement(1); 
        container.addElement(2); 
        container.addElement(3); 
        container.addElement(4); 
        container.addElement(5); 

        MagicalContainer::AscendingIterator originalIterator(container);
        ++originalIterator;
        ++originalIterator;
        MagicalContainer::AscendingIterator copiedIterator(originalIterator);
        CHECK_EQ(*originalIterator, 3);
        CHECK_EQ(originalIterator.begin(), copiedIterator.begin());
        CHECK_EQ(originalIterator.end(), copiedIterator.end());
    }

    SUBCASE("assignment operator") {
        MagicalContainer container;
        container.addElement(1); 
        container.addElement(2); 
        container.addElement(3); 
        container.addElement(4);
        container.addElement(5);

        MagicalContainer::AscendingIterator originalIterator(container);
        MagicalContainer::AscendingIterator assignedIterator(container);

        ++originalIterator;
        ++originalIterator;

        assignedIterator = originalIterator;
        CHECK_EQ(*originalIterator, 3);

        CHECK_EQ(originalIterator.begin(), assignedIterator.begin());
        CHECK_EQ(originalIterator.end(), assignedIterator.end());

        
        }
    }


    TEST_CASE("Iterating") {

        SUBCASE("iterating over an empty container") {
            MagicalContainer container;
            MagicalContainer::AscendingIterator iterator(container);
            CHECK_EQ(iterator.begin() , iterator.end());

        }

        SUBCASE("iterating over a container with 5 elements") {
            std::cout << "started ascending" << std::endl;
            MagicalContainer container;
            container.addElement(11);
            container.addElement(63);
            container.addElement(2);
            container.addElement(34);
            container.addElement(8);   

            

            MagicalContainer::AscendingIterator iterator(container);
            std::vector<int> expected = {2, 8, 11, 34, 63};
            std::vector<int>::size_type index = 0;

            for (int i=0;i<5;i++) {
                CHECK_EQ(*iterator, expected[index++]);

                ++iterator;
            }

            CHECK(iterator == iterator.end());
        }
    }

    TEST_CASE("Compering operaters") {
        
        SUBCASE("operators and pre-increment") {
            MagicalContainer container;
            container.addElement(1);
            container.addElement(6);
            container.addElement(3);
            container.addElement(15);
            container.addElement(12);

            

            MagicalContainer::AscendingIterator iterator1(container);
            MagicalContainer::AscendingIterator iterator2(container);

            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);
        }
    }
}

// ==================================================
//              SideIterator 
// ==================================================

TEST_SUITE("SideCrossIterator"){

    TEST_CASE("copy constructor") {
        MagicalContainer container;
        container.addElement(1); 
        container.addElement(2);
        container.addElement(3); 
        container.addElement(4); 
        container.addElement(5); 

        MagicalContainer::SideCrossIterator originalIterator(container);
        ++originalIterator;
        ++originalIterator;
        MagicalContainer::SideCrossIterator copiedIterator(originalIterator);
        CHECK_EQ(*originalIterator, 2);
        CHECK_EQ(originalIterator.begin(), copiedIterator.begin());
        CHECK_EQ(originalIterator.end(), copiedIterator.end());
    }

    TEST_CASE("assignment operator") {
        MagicalContainer container;
        container.addElement(1); 
        container.addElement(2); 
        container.addElement(3);
        container.addElement(4);
        container.addElement(5); 

        MagicalContainer::SideCrossIterator originalIterator(container);
        MagicalContainer::SideCrossIterator assignedIterator(container);

        ++originalIterator;
        ++originalIterator;

        assignedIterator = originalIterator;
        CHECK_EQ(*originalIterator, 2);

        CHECK_EQ(originalIterator.begin(), assignedIterator.begin());
        CHECK_EQ(originalIterator.end(), assignedIterator.end());
    }


    TEST_CASE("Iterating") {

        SUBCASE("iterating over an empty container") {
            MagicalContainer container;
            MagicalContainer::SideCrossIterator iterator(container);
            CHECK_EQ(iterator.begin() , iterator.end());

        }

        SUBCASE("iterating over a container with 5 elements") {
            MagicalContainer container;
            container.addElement(11);
            container.addElement(63);
            container.addElement(2);
            container.addElement(34);
            container.addElement(8);


            MagicalContainer::SideCrossIterator iterator(container);
            std::vector<int> expected = {2, 63, 8, 34, 11};
            std::vector<int>::size_type index = 0;

            for (int i=0;i<5;i++) {
                
                CHECK_EQ(*iterator, expected[index++]);
                ++iterator;
                
            }

            CHECK(iterator == iterator.end());
        }
    }


    TEST_CASE("Comparing operators and pre-increment") {

        SUBCASE("operators and pre-increment") {
            MagicalContainer container;
            container.addElement(1);
            container.addElement(17);
            container.addElement(3);
            container.addElement(11);
            container.addElement(12);
            container.addElement(4);

            MagicalContainer::SideCrossIterator iterator1(container);
            MagicalContainer::SideCrossIterator iterator2(container);

            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);
        }
    }
 
}


// ==================================================
//              PrimteIterator 
// ==================================================

TEST_SUITE("PrimeIterator"){



    TEST_CASE("copy constructor") {
        MagicalContainer container;
        container.addElement(2); 
        container.addElement(3); 
        container.addElement(5);
        container.addElement(7); 
        container.addElement(11);

        MagicalContainer::PrimeIterator originalIterator(container);
        ++originalIterator;
        ++originalIterator;
        MagicalContainer::PrimeIterator copiedIterator(originalIterator);
        CHECK_EQ(*originalIterator, 5);
        CHECK_EQ(originalIterator.begin(), copiedIterator.begin());
        CHECK_EQ(originalIterator.end(), copiedIterator.end());
    }

    TEST_CASE("assignment operator") {
        MagicalContainer container;
        container.addElement(2); 
        container.addElement(3);
        container.addElement(5); 
        container.addElement(7); 
        container.addElement(11); 

        MagicalContainer::PrimeIterator originalIterator(container);
        MagicalContainer::PrimeIterator assignedIterator(container);

        ++originalIterator;
        ++originalIterator;

        assignedIterator = originalIterator;
        CHECK_EQ(*originalIterator, 5);

        CHECK_EQ(originalIterator.begin(), assignedIterator.begin());
        CHECK_EQ(originalIterator.end(), assignedIterator.end());
    }


    TEST_CASE("Iterating") {
        
        SUBCASE("iterating over an empty container") {
            MagicalContainer container;

            MagicalContainer::PrimeIterator iterator(container);

            CHECK_EQ(iterator.begin() , iterator.end());
        }

        SUBCASE("iterating over a container with 10 elements") {
            MagicalContainer container;
            for (int i = 1; i <= 10; ++i) {
                container.addElement(i);
            }

            MagicalContainer::PrimeIterator iterator(container);
            std::vector<int> expected = {2, 3, 5, 7};
             std::vector<int>::size_type index = 0;

            for (int i=0; i<4; ++i) {
                CHECK_EQ(*iterator, expected[index]);
                ++iterator;
                ++index;
            }

            CHECK(iterator == iterator.end());
        }
    }

   TEST_CASE("Comparing operators and pre-increment") {

        SUBCASE("operators and pre-increment") {
            MagicalContainer container;
            container.addElement(1);
            container.addElement(17);
            container.addElement(3);
            container.addElement(11);
            container.addElement(12);
            container.addElement(4);

            
            MagicalContainer::PrimeIterator iterator1(container);
            MagicalContainer::PrimeIterator iterator2(container);

            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);


            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);


            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);


            ++iterator1;
            CHECK_FALSE(iterator1 == iterator2);
            CHECK(iterator1 != iterator2);
            CHECK(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);

            ++iterator2;
            CHECK(iterator1 == iterator2);
            CHECK_FALSE(iterator1 != iterator2);
            CHECK_FALSE(iterator1 > iterator2);
            CHECK_FALSE(iterator1 < iterator2);


        }
    }
}





