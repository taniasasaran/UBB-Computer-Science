//
// Created by TANIA on 4/8/2022.
//

#include "repository.h"
#include "service.h"
#include <assert.h>

class Tests{
private:
    Repository repo;
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
        Movie movie = Movie("1", "action", 2012, 3000, "http");
        assert(movie.getTitle() == "1");
        assert(movie.getGenre() == "action");
        assert(movie.getNumberLikes() == 3000);
        assert(movie.getYearRelease() == 2012);
        assert(movie.getTrailer() == "http");
        movie.setNumberLikes(1);
        assert(movie.getNumberLikes() == 1);
        Movie movie2 = Movie("2", "rom", 2015, 156482, "http.com");
        assert((movie == movie2)== false);
        Movie movie3 = Movie("1", "comedy", 2012, 3000, "http");
        assert((movie==movie3) == false);
    }

    void test_add(){
        Movie movie1 = Movie("1", "action", 2012, 3000, "http");
        assert(this->sv.add(movie1) == true);
        assert(this->sv.getRepoSize() == 11);
        assert(this->sv.get(10) == movie1);
        Movie movie2 = Movie("2", "rom", 2015, 156482, "http.com");
        assert(this->sv.add(movie2) == true);
        assert(this->sv.getRepoSize() == 12);
        assert(this->sv.get(10) == movie1);
        assert(this->sv.getRepoData()[11] == movie2);
        assert(this->sv.add(movie1) == false);
    }


    void test_update(){
        Movie movie1 = Movie("Titanic", "romantic", 2012, 3000, "http");
        assert(this->sv.update("Titanic", "romantic", movie1) == true);
        int pos = this->sv.search("Titanic", "romantic");
        Movie movie2 = this->sv.get(pos);
        assert(movie1 == movie2);
        Movie movie3 = Movie("gibberish", "genre", 1,1, "link");
        assert(this->sv.update("gibberish", "genre", movie3) == false);
    }

    void test_isEmptyRepo(){
        assert(this->sv.isEmptyRepo() == false);
        assert(this->repo.isEmpty() == true);
    }

    void test_search(){
        assert(this->sv.search("The Book of Eli", "action") == 0);
        assert(this->sv.search("gibberish", "genre") == -1);
    }

    void test_dyn_vector(){
        Movie movie = Movie("1", "action", 2012, 3000, "http");
        this->repo.add(movie);
        assert(this->repo.getData()[0] == movie);
        DynamicVector<Movie> v = this->repo.getData();
        v=v;
        v.add(Movie("gibberish", "genre", 1,1, "link"));
        v = this->repo.getData();
    }

    void test_remove(){
        this->repo.populateRepository();
        assert(this->sv.remove("Titanic", "romantic") == true);
        assert(this->sv.remove("gibberish", "genre") == false);
        assert(this->repo.remove("gibberish", "genre") == false);
        assert(this->repo.remove("The Matrix Resurrections", "sci-fi") == true);
        assert(this->repo.remove("The Book of Eli", "action") == true);
        assert(this->repo.remove("Schindler's List", "history") == true);
        assert(this->repo.remove("Spirited Away", "anime") == true);
        assert(this->repo.remove("Spider-Man: No Way Home", "action") == true);
        assert(this->repo.remove("Your Name", "anime") == true);
        assert(this->repo.remove("Inside Out", "animation") == true);
    }
};