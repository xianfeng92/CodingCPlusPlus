
unsigned next_seed = 1;

unsigned rand(void) {
    next_seed = next_seed * 1103515245 + 12543;
    return (unsigned) (next_seed >> 16) % 32768;
}


void srand(unsigned new_seed) {
    next_seed = new_seed;
}


