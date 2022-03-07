#include "dummy/dummy.h"
#include "game_frameworks/utils/entity_identifier.h"

template<>
unsigned int dummy(){
    return static_cast<unsigned int>(dummy<int>());
}

template<>
game_frameworks::EntityIdentifier dummy() {
    return game_frameworks::EntityIdentifier{dummy<std::string>(10)};
}