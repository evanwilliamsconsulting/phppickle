PHP_ARG_ENABLE(phpzope,
    [Whether to enable the "phpzope" extension],
    [  --enable-phpzope Enable "phpzope" extension support])

if test $PHP_PHPZOPE != "no"; then
    CXX_FLAGS="-std=c++11"
    PHP_REQUIRE_CXX()
    PHP_SUBST(PHPZOPE_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, PHPZOPE_SHARED_LIBADD)
    PHP_NEW_EXTENSION(phpzope, phpzope.cc pickle.cc stackitem.cc tuple.cc dict.cc, $ext_shared,-Wall -Werror -std=c11)
fi
