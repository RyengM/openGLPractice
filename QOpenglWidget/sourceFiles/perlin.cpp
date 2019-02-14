#include <headFiles/perlin.h>

Perlin::Perlin()
{
    for (int x = 0; x < 512; x++) {
        p[x] = permutation[x % 256];
    }
}

Perlin::~Perlin()
{

}

double Perlin::perlin(double x, double y, double z)
{
    // Calculate the "unit cube" that the point asked will be located in the left bound
    // And the right bound will plus one
    int xi = (int)x & 255;
    int yi = (int)y & 255;
    int zi = (int)z & 255;
    // the decimal part of number
    double xf = x - (int)x;
    double yf = y - (int)y;
    double zf = z - (int)z;
    // u,v,w for better interpolation
    double u = fade(xf);
    double v = fade(yf);
    double w = fade(zf);
    // choose a semi-random number from permutation to get each unit's grad
    int aaa = p[p[p[xi] + yi] + zi];
    int aba = p[p[p[xi] + yi + 1] + zi];
    int aab = p[p[p[xi] + yi] + zi +1];
    int abb = p[p[p[xi] + yi + 1] + zi + 1];
    int baa = p[p[p[xi +1] + yi] + zi];
    int bba = p[p[p[xi + 1] + yi + 1] + zi];
    int bab = p[p[p[xi + 1] + yi] + zi + 1];
    int bbb = p[p[p[xi + 1] + yi + 1] + zi + 1];
    // interpilation
    double x1, x2, y1, y2;      //temp variables, used for interpolating
    x1 = lerp(grad(aaa, xf, yf, zf), grad(baa, xf - 1, yf, zf), u);
    x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
    y1 = lerp(x1, x2, v);
    x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);
    x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);
    y2 = lerp(x1, x2, v);
    return (lerp(y1, y2, w) + 1) / 2;
}

double Perlin::grad(int hash, double xf, double yf, double zf)
{
    switch (hash & 0xF)
    {
        case 0x0: return  xf + yf;
        case 0x1: return -xf + yf;
        case 0x2: return  xf - yf;
        case 0x3: return -xf - yf;
        case 0x4: return  xf + zf;
        case 0x5: return -xf + zf;
        case 0x6: return  xf - zf;
        case 0x7: return -xf - zf;
        case 0x8: return  yf + zf;
        case 0x9: return -yf + zf;
        case 0xA: return  yf - zf;
        case 0xB: return -yf - zf;
        case 0xC: return  yf + xf;
        case 0xD: return -yf + zf;
        case 0xE: return  yf - xf;
        case 0xF: return -yf - zf;
        default: return 0; // never happens
    }
}

double Perlin::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double a, double b, double x)
{
    return a + x * (b - a);
}