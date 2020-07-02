#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double pow (double value, int exp) {
    int i;
    double output = value;
    if (exp == 0) return 1;
    for (i = 0; i < exp-1; i++) {
        output *= value;
    }
    return output;
}

double ldexp (double value, int exp) {
    return value * pow((double)2, exp);
}

double frexp(double value, int* exp) {
	union {
        double v;
        struct {
			unsigned int u_mant1 :  7;
			unsigned int   u_exp :  8;
			unsigned int  u_sign :  1;
			unsigned int u_mant2 : 16;
			unsigned int u_mant3 : 32;
        } s;
    } u;

	if (value) {
		u.v = value;
		*exp = u.s.u_exp - 128;
		u.s.u_exp = 128;
		return (u.v);
	} else {
		*exp = 0;
		return (0.0);
	}
}

double sqrtf(double x) {
    double y = 1;
    int i;
    for(i = 0; i < 10; ++i)
        y = (y+x/y)/2;
    return y; 
}

// 16 bit color
// 5 red bits, 6 green bits, 5 blue bits
void getColor (color_t color, unsigned char* rp, unsigned char* gp, unsigned char* bp) {
	unsigned char r = (color >> 11) & 0b11111;
	unsigned char g = (color >> 5) & 0b111111;
	unsigned char b = color & 0b11111;
    r = map(r, 0, 0b11111, 0, 255);
    g = map(g, 0, 0b111111, 0, 255);
    b = map(b, 0, 0b11111, 0, 255);
    *rp = r;
    *gp = g;
    *bp = b;
}

color_t setColor (unsigned char r, unsigned char g, unsigned char b) {
	r = map(r, 0, 255, 0, 0b11111);
	g = map(g, 0, 255, 0, 0b111111);
	b = map(b, 0, 255, 0, 0b11111);
	return ((r &  0b11111) << 11) | ((g &  0b111111) << 5) | (b &  0b11111);
}

color_t scaleColor (color_t color, double k) {
    unsigned char r, g, b;
    getColor (color, &r, &g, &b);
    k = max(min(k, 1), 0);
    r *= k;
    g *= k;
    b *= k;
    return setColor(r, g, b);
}