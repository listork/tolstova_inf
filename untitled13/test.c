#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int
typedef struct cn {
    double re, im;
} ComplexNumber;

ComplexNumber add(ComplexNumber, ComplexNumber);
ComplexNumber neg(ComplexNumber);
ComplexNumber sub(ComplexNumber, ComplexNumber);
ComplexNumber mult(ComplexNumber, ComplexNumber);
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
void Vcoords(Vector *, ComplexNumber, uint);
int is_equal (struct cn a, ComplexNumber b){
    return (a.re == b.re && a.im == b.im);
}
int is_equal_v (Vector* v1, Vector* v2){
    if (v1->length != v2->length){
        return 0;
    }
    for (uint i=0; i<v1->length; i++){
        if (!is_equal(v1->coords[i], v2->coords[i])){
            return 0;
        }
    }
    return 1;
}
void test_add (){
    printf("test_add ");
    ComplexNumber c;
    ComplexNumber a = {0,1};
    ComplexNumber b = {1,0};
    c = add(a, b);
    if (is_equal(c, (ComplexNumber){1,1})) {
        printf("ok");
    }
    printf("\n");
}
void test_sub(){
    printf("test_sub ");
    ComplexNumber c;
    ComplexNumber a = {1,0};
    ComplexNumber b = {0,1};
    c = sub(a,b);
    if (is_equal(c, (ComplexNumber){1,-1})) {
        printf("ok");
    }
    printf("\n");
}
void test_mult (){
    printf("test_mult ");
    ComplexNumber c;
    ComplexNumber a = {2,1};
    ComplexNumber b = {1,2};
    c = mult(a, b);
    if (is_equal(c, (ComplexNumber){0,5})) {
        printf("ok");
    }
    printf("\n");
}
void test_add_v (){
    printf("test_add_v ");
    Vector *v1 = (Vector *) malloc(sizeof(struct v));
    v1->construct = Vconstruct;
    v1->construct(v1, 3);
    for (uint i=0; i<5; i++){
        Vcoords(v1, (ComplexNumber){i*i*i%2+2, i*i*i*(i+2)%3}, i);
    }
    Vector *v2 = (Vector *) malloc(sizeof(struct v));
    v2->construct = Vconstruct;
    v2->construct(v2, 3);
    for (uint i=0; i<5; i++){
        Vcoords(v2, (ComplexNumber){i*i*i%3+2, i*i*i*(i+2)%5}, i);
    }
    Vector *v3;
    Vector *v4 = (Vector *) malloc(sizeof(struct v));
    v4->construct = Vconstruct;
    v4->construct(v4, 3);
    Vcoords(v4, (ComplexNumber){4, 0}, 0);
    Vcoords(v4, (ComplexNumber){6, 3}, 1);
    Vcoords(v4, (ComplexNumber){6, 4}, 2);
    v3 = v1->add(v1,v2);
    if (is_equal_v(v3, v4)){
        printf("ok");
    }
    printf("\n");
}
void test_mult_v (){
    printf("test_mult_v ");
    Vector *v1 = (Vector *) malloc(sizeof(struct v));
    v1->construct = Vconstruct;
    v1->construct(v1, 3);
    for (uint i=0; i<5; i++){
        Vcoords(v1, (ComplexNumber){i*i*i%2+2, i*i*i*(i+2)%3}, i);
    }
    Vector *v2 = (Vector *) malloc(sizeof(struct v));
    v2->construct = Vconstruct;
    v2->construct(v2, 3);
    for (uint i=0; i<5; i++){
        Vcoords(v2, (ComplexNumber){i*i*i%3+2, i*i*i*(i+2)%5}, i);
    }
    ComplexNumber *v3;
    ComplexNumber *v5 = (ComplexNumber *) malloc(sizeof(struct cn));
    v5->re = 17;
    v5->im = 21;
    v3 = v1->mult(v1,v2);
    if (is_equal(*v3, *v5)){
        printf("ok");
    }
    printf("\n");
}
int test_main (){
    test_add();
    test_sub();
    test_mult();
    test_add_v();
    test_mult_v();
    return 0;
};
