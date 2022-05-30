#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

typedef struct cn {
    double re, im;
} ComplexNumber;

ComplexNumber add(ComplexNumber a, ComplexNumber b) {
    ComplexNumber c;
    c.re = a.re + b.re;
    c.im = a.im + b.im;
    return c;
}

ComplexNumber neg(ComplexNumber a) {
    ComplexNumber c;
    c.re = -a.re;
    c.im = -a.im;
    return c;
}

ComplexNumber sub(ComplexNumber a, ComplexNumber b) {
    return add(a, neg(b));
}

ComplexNumber mult(ComplexNumber a, ComplexNumber b) {
    ComplexNumber c;
    c.re = a.re * b.re - a.im * b.im;
    c.im = a.im * b.re + a.re * b.im;
    return c;

}

int draw(ComplexNumber a) {
    if (a.im < 0) {
        return printf("%0.2f %0.2fi\n", a.re, a.im);
    }
    else if (a.im == 0){
        return printf("%0.2f\n", a.re);
    }
    return printf("%0.2f +%0.2fi\n", a.re, a.im);
}

typedef struct v {
    uint length;
    ComplexNumber *coords;
    void (*draw)(struct v*);
    void (*construct)(struct v *, uint);
    void (*Addcoords)(struct v*, ComplexNumber, uint);
    struct v* (*add)(struct v*, struct v*);
    ComplexNumber * (*mult)(struct v*, struct v*);
} Vector;
void Vconstruct(Vector *, uint);
ComplexNumber *Vmult(Vector *v2, Vector *v1){
    if (v1->length!=v2->length){
        return NULL;
    }
    ComplexNumber *c = (ComplexNumber *) malloc(sizeof(struct cn));
    ComplexNumber s={0,0};
    for (uint i=0; i<v1->length; i++){
        s = add(s, mult(v1->coords[i], v2->coords[i]));
    }
    c->im = s.im;
    c->re = s.re;
    return c;
}
Vector *Vadd(Vector *v2, Vector *v1){
    if (v1->length!=v2->length){
        return NULL;
    }
    Vector *c = (Vector*)(malloc(sizeof (struct v)));
    c->construct = Vconstruct;
    c->construct(c, v1->length);
    for (uint i=0; i<v1->length; i++){
        c->Addcoords(c, add(v1->coords[i], v2->coords[i]), i);
    }
    return c;
}
void Vdraw(Vector *v) {
    for (uint i = 0; i<v->length; i++){
        draw (v->coords[i]);
    }
}

void Vcoords(Vector *v, ComplexNumber a, uint n){
    if (n>=v->length){
        return;
    }
    v->coords[n] = a;
}
void Vconstruct(Vector *v, uint size) {
    v->length = size;
    v->coords = (ComplexNumber *) malloc(v->length * sizeof(struct cn));
    v->draw = Vdraw;
    v->Addcoords = Vcoords;
    v->add = Vadd;
    v->mult = Vmult;
}

/*Vector vadd(Vector a, Vector b) {
    Vector c;
    c.x = add(a.x, b.x);
    c.y = add(a.y, b.y);
    c.z = add(a.z, b.z);
    return c;
}

ComplexNumber vsmult(Vector a, Vector b) {
    ComplexNumber x, y, z;
    x = mult(a.x, b.x);
    y = mult(a.y, b.y);
    z = mult(a.z, b.z);
    return add(x, add(y, z));
}

int vdraw(Vector a) {
    return printf("%s\n", "{") +
           draw(a.x) +
           printf("%s\n", ",") +
           draw(a.y) +
           printf("%s\n", ",") +
           draw(a.z) +
           printf("%s\n", "}");
}*/
int test_main ();
int main() {
    test_main();
    Vector *v1 = (Vector *) malloc(sizeof(struct v));
    v1->construct = Vconstruct;
    float im, re;
    uint n;
    printf("input length vector1 ");
    scanf("%d", &n);
    v1->construct(v1, n);
    for (uint i=0; i<n; i++){
        printf("input %d real", i+1);
        scanf("%f", &re);
        printf("input %d imaginary", i+1);
        scanf("%f", &im);
        Vcoords(v1, (ComplexNumber){re, im}, i);
    }
    v1->draw(v1);
    Vector *v2 = (Vector *) malloc(sizeof(struct v));
    printf("input length vector2 ");
    scanf("%d", &n);
    v2->construct = Vconstruct;
    v2->construct(v2, n);
    for (uint i=0; i<n; i++){
        printf("input %d real", i+1);
        scanf("%f", &re);
        printf("input %d imaginary", i+1);
        scanf("%f", &im);
        Vcoords(v2, (ComplexNumber){re, im}, i);
    }
    v2->draw(v2);
    n = 0;
    while (n != 1 && n != 2){
        printf("select operation\n1) add\n2) mult\n");
        scanf("%d", &n);
    }
    if (n == 1){
        Vector *v3;
        v3 = v1->add(v1,v2);
        v3->draw(v3);
    } else {
        draw(*v1->mult(v1, v2));
    }
    return 0;
}
