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
    double k = abs(magnitude(a));
    if (k == 0) {
        Vector output = {.x = 0, .y = 0, .z = 0};
        return output;
    } else {
        Vector output = {.x = a.x/k, .y = a.x/k, .z = a.z/k};
        return output;
    }
}

double dot (Vector a, Vector b) {
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

Ray reflect (Vector incident, Vector intersect, Vector normal) {
    incident = normalize(incident);
    normal = normalize(normal);

    Vector reflected = subtract(incident, scale(normal, 2.0*dot(normal, incident)));
    Vector origin = add(intersect, scale(reflected, 0.001));

    Ray out = {.origin = origin, .direction = normalize(reflected)};

    return out;
}