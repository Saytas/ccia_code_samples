rm -rf listing_1.1 listing_2.1
#g++ -std=c++20 -g -Llib -Wall -Wextra -Iinclude -fno-exceptions -pthread -o listing_1.1 listing_1.1.cpp 
#g++ -std=c++20 -g -Wall -Wextra -Iinclude -fno-exceptions -pthread -o listing_1.1 listing_1.1.cpp 
g++ -std=c++20 -g -Wall -Wextra -Iinclude -fno-exceptions -pthread -o listing_2.1 listing_2.1.cpp 
rm -rf *.dSYM