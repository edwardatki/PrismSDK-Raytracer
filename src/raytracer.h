typedef struct {
    double distance;
    Primitive* closest;
} Intersect;

Intersect getFirstIntersect (Ray ray) {
    double distance = RENDER_DISTANCE;
    Primitive* closest = NULL;
    unsigned int i;
    for(i = 0; i < (sizeof(primitives)/sizeof(Primitive*)); i++) {
        Primitive* o = primitives[i];
        //if (o == NULL) continue;
        double d = sphereIntersect(o, &ray);
        if (d != 0 && d < distance) {
            distance = d;
            closest = o;
        }
    }
    
    Intersect intersect;
    intersect.distance = distance;
    intersect.closest = closest;

    return intersect;
}

color_t traceRay (Ray ray) {
    Intersect first = getFirstIntersect(ray);
    double distance = first.distance;
    Primitive* closest = first.closest;

    if (distance >= RENDER_DISTANCE) return COLOR_BLACK;

    Vector intersectPos = add(ray.origin, scale(normalize(ray.direction), distance));
    Vector normal = sphereNormal(closest, intersectPos);
    //if (dot(normalize(ray.direction), normal) < 0) normal = scale(normal, -1);
    
    // eg - diffuse = dot(normalize(subtract(light, intersectPos)), normal)
    Vector lightDir = normalize(subtract(light, intersectPos));
    double kd = dot(lightDir, normal);

    //return closest->color;
    //return scaleColor(closest->color, max(min(kd, 1.0), 0.1));
    return scaleColor(closest->color, max(min(1-((double)distance/(double)200), 1.0), 0.1));
}
