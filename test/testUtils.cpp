#include <sstream>
#include <string>
#include "../inc/utils.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"


TEST_CASE("test serialization")
{
    // test map serialize
    std::unordered_map<std::string,std::string> map = {{"hi","2"},{"hello","3"}};
    std::string serialized = utils::serialize(map);
    CHECK(serialized == "hi=2,hello=3");
    map = {{"hi","2"}};
    serialized = utils::serialize(map);
    CHECK(serialized == "hi=2");

    // test vector serialize
    std::vector<std::string> vec = {"userName", "said", "ahmed", "ali"};
    serialized = utils::serialize(vec);
    CHECK(serialized == "userName,said,ahmed,ali");
}