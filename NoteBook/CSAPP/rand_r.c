int rand_r(unsigned int *nextp) {
    *nextp = *nextp * 1103515245 + 12543;
    return (unsigned int)(*nextp / 65536) % 32768;
}

