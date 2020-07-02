typedef struct {
    color_t color;
    Vector center;
    int radius;
} Primitive;

double sphereIntersect (Primitive* spherePointer, Ray* ray) {
    double A = dot(ray->direction, ray->direction);
    Vector dist = subtract(ray->origin, spherePointer->center);
    double B = 2.0 * dot(ray->direction, dist);
    double C = dot(dist, dist) - (spherePointer->radius * spherePointer->radius);
    double discr = (B*B) - (4*A*C);

    if (discr < 0.0) {
        return 0;
    }

    double t0 = (-B - sqrtf(discr))/(2*A);
    double t1 = (-B + sqrtf(discr))/(2*A);
    double d;

    if (t0 < 0 && t1 < 0) {
        d = 0;
    }
    else if (t0 < 0) {
        d = t1;
    }
    else if (t1 < 0) {
        d = t0;
    }
    else {
        d = min(t0, t1);
    }

    return d;
}

Vector sphereNormal(Primitive* spherePointer, Vector position) {
    return normalize(subtract(position, spherePointer->center));
}
