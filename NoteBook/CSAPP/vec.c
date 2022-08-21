
// Create abstract data type for vector
typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_prt;

typedef long data_t;

vec_prt new_vec(long len) {
    // Allocate header structure
    vec_prt  result = (vec_prt) malloc(sizeof(vec_rec);
    data_t *data = NULL;
    if(!result) {
        return NULL;// can't allocate storage
    }
    result->len = len;

    if(len > 0) {
        // Allocate array
        data = (data_t *) calloc(len, sizeof(data_t));
        if(!data){
            free((void*)result);
            return NULL;
        }
    }
    result->data = data;
    return result;
}

int get_vec_element(vec_prt *p, long index, data_t *dest) {
    if(index < 0 || index >= v->len) {
        return 0;
    }
    *dest = v->data[index];
    return 1;
}

long vec_length(vec_prt v) {
    return v->len;
}

#define IDENT 0
#define OP +

// #define IDENT 1
// #define OP *

void combine1(vec_prt v, data_t *dest) {
    long i;

    *dest = IDENT;
    for(i = 0 ; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

// Move call to vec_length out of loop
void combine2(vec_prt v, data_t *dest) {
    long i;
    long length = vec_length(v);
    *dest = IDENT;
    for(i = 0 ; i < length ; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

//Convert string to lowercase: slow
void lower1(char *s) {
    long i;
    for(i = 0 ; i < strlen(s) ; i++) {
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] -= ('A' - 'a');
        }
    }
}


//  Convert string to lowercase: faster
void lower2(char *s) {
    long i;
    long len = strlen(s);

    for(i = 0 ; i < len ; i++) {
        if(s[i] >= 'A' && s[i] <=  'Z'){
            s[i] -= ('A' - 'a');
        }
    }
}

size_t strlen(const char *s) {
    long length = 0;
    while(*s != '\0') {
        s++;
        length++;
    }
    return length;
}


data_t *get_vec_start(vec_prt v) {
    return v->data;
}

void combine3(vec_prt v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for(i = 0; i < length; i++) {
        *dest = *dest OP val;
    }
}

// Accumulate result in local variables
void combine4 (vec_prt v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for(i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}








