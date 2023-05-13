#include "repository.h"
#include "service.h"
#include <assert.h>

class Tests{
private:
    Service sv;

public:
    void TestAll(){
        test_add();
        test_update();
        test_isEmptyRepo();
        test_search();
        test_movie();
        test_dyn_vector();
        test_remove();
    }

    void test_movie(){
        Dog dog = Dog("1", "2", 3, "http");
        assert(dog.getBreed() == "1");
        assert(dog.getName() == "2");
        assert(dog.getAge() == 3);
        assert(dog.getPhotograph() == "http");
        Dog doggo2 = Dog("2", "4", 6, "http.com");
        assert((dog == doggo2) == false);
        Dog doggo3 = Dog("1", "3", 5, "http");
        assert((dog == doggo3) == false);
    }

    void test_add(){
        Dog doggo1 = Dog("1", "2", 3, "http");
        assert(this->sv.add(doggo1) == true);
        assert(this->sv.getRepoSize() == 11);
        assert(this->sv.get(10) == doggo1);
        Dog doggo2 = Dog("2", "4", 6,"http.com");
        assert(this->sv.add(doggo2) == true);
        assert(this->sv.getRepoSize() == 12);
        assert(this->sv.get(10) == doggo1);
        assert(this->sv.getRepoData()[11] == doggo2);
        assert(this->sv.add(doggo1) == false);
    }


    void test_update(){
        Dog doggo1 = Dog("cocker", "Costel", 1, "http");
        assert(this->sv.update("cocker", "Costel", doggo1) == true);
        int pos = this->sv.search("cocker", "Costel");
        Dog doggo2 = this->sv.get(pos);
        assert(doggo1 == doggo2);
        Dog doggo3 = Dog("gibberish", "name", 1, "link");
        assert(this->sv.update("gibberish", "name", doggo3) == false);
    }

    void test_isEmptyRepo(){
        assert(this->sv.isEmptyRepo() == false);
    }

    void test_search(){
        assert(this->sv.search("cocker", "Costel") == 0);
        assert(this->sv.search("gibberish", "name") == -1);
    }

    void test_dyn_vector(){
        Dog dog = Dog("1", "2", 3, "http");
        this->sv.add(dog);
        assert(this->sv.get(10) == dog);
        DynamicVector<Dog> v1 = this->sv.getRepoData();
        v1.add(Dog("gibberish", "name", 1, "link"));
        DynamicVector<Dog> v = this->sv.getRepoData();
        assert((v.getSize()==v1.getSize())==false);
    }

    void test_remove(){
        this->sv.populateRepository();
        assert(this->sv.remove("bulldog", "Emanuel") == true);
        assert(this->sv.remove("gibberish", "name") == false);
        assert(this->sv.remove("ciobanesc german", "Raya") == true);
        assert(this->sv.remove("cocker", "Costel") == true);

        assert(this->sv.remove("Schindler's List", "history") == true);
        assert(this->sv.remove("Spirited Away", "anime") == true);
        assert(this->sv.remove("Spider-Man: No Way Home", "action") == true);
        assert(this->sv.remove("Your Name", "anime") == true);
        assert(this->sv.remove("Inside Out", "animation") == true);
    }
};