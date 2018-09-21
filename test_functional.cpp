#define BOOST_TEST_MODULE test_functional

#include "ip_filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

    BOOST_AUTO_TEST_CASE(test_functional_1) {
        BOOST_CHECK(split("1.2.3.4", '.').at(0) == "1");
    }

BOOST_AUTO_TEST_SUITE_END()