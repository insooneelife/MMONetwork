#include "Reference.h"

std::map<unsigned int, IReference*> Reference::references_;
unsigned int Reference::gen_id_ = 0;