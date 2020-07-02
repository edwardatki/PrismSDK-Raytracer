typedef struct {
    float x, y, z;
} Vector;

typedef struct {
    Vector origin;
    Vector direction;
} Ray;

Vector add (Vector a, Vector b) {
    Vector output = {.x = a.x+b.x, .y = a.y+b.y, .z = a.z+b.z};
    return output;
}

Vector subtract (Vector a, Vector b) {
    Vector output = {.x = a.x-b.x, .y = a.y-b.y, .z = a.z-b.z};
    return output;
}

double magnitude (Vector a) {
    return sqrtf((a.x*a.x) + (a.y*a.y) + (a.z*a.z));
}

Vector scale (Vector a, double k) {
    Vector output = {.x = a.x*k, .y = a.y*k, .z = a.z*k};
    return output;
}

Vector normalize (Vector a) {
    double k = magnitude(a);
    Vector output = {.x = 0, .y = 0, .z = 0};
    if (k != 0) scale(output, 1.0/k);
    return output;
}

double dot (Vector a, Vector b) {
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}