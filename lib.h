#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

//===============================================Structures
//>>>>>>>>>>>>>>>>>>>>POINTS
typedef struct point_node *point_pointer;

typedef struct
{
    char name[10];
    float point[3];
} point_info;

typedef struct point_node
{
    point_info info;
    point_pointer next;
} point_node;
//<<<<<<<<<<<<<<<<<<<<POINTS

//>>>>>>>>>>>>>>>>>>>>VECTORS
typedef struct vector_node *vector_pointer;

typedef struct
{
    char name[10];
    float vector[3];
} vector_info;

typedef struct vector_node
{
    vector_info info;
    vector_pointer next;
} vector_node;
//<<<<<<<<<<<<<<<<<<<<VECTORS

//>>>>>>>>>>>>>>>>>>>>LINES
typedef struct line_node *line_pointer;

typedef struct
{
    char name[10];
    float point[3];
    float vector[3];
} line_info;

typedef struct line_node
{
    line_info info;
    line_pointer next;
} line_node;
//<<<<<<<<<<<<<<<<<<<<LINES

//>>>>>>>>>>>>>>>>>>>>PLANES
typedef struct plane_node *plane_pointer;

typedef struct
{
    char name[10];
    float point[3];
    float vector1[3];
    float vector2[3];
} plane_info;

typedef struct plane_node
{
    plane_info info;
    plane_pointer next;
} plane_node;
//<<<<<<<<<<<<<<<<<<<<PLANES

typedef struct
{
    int point_amount;
    point_pointer point_first;
    int vector_amount;
    vector_pointer vector_first;
    int line_amount;
    line_pointer line_first;
    int plane_amount;
    plane_pointer plane_first;
} space;
//===============================================Structures

//===============================================Manager
int create_space(char name[], space *e, FILE **arq)
{
    if ((*arq = fopen(name, "wb")) == NULL)
        return 0;
    e->point_amount = 0;
    e->point_first = NULL;
    e->vector_amount = 0;
    e->vector_first = NULL;
    e->line_amount = 0;
    e->line_first = NULL;
    e->plane_amount = 0;
    e->plane_first = NULL;
    return 1;
}

void create_space_temp(space *e)
{
    e->point_amount = 0;
    e->point_first = NULL;
    e->vector_amount = 0;
    e->vector_first = NULL;
    e->line_amount = 0;
    e->line_first = NULL;
    e->plane_amount = 0;
    e->plane_first = NULL;
}

//>>>>>>>>>>>>>>>>>>>>POINTS
void point_push(space *e, char name[], float P[])
{

    point_pointer curr = (point_pointer)malloc(sizeof(point_node));
    point_pointer copy = (point_pointer)malloc(sizeof(point_node));

    curr->next = NULL;

    strcpy(curr->info.name, name);

    curr->info.point[0] = P[0];
    curr->info.point[1] = P[1];
    curr->info.point[2] = P[2];

    if (e->point_amount == 0)
    {
        e->point_first = curr;
    }
    else
    {
        copy = e->point_first;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        copy->next = curr;
    }
    e->point_amount++;
}

point_pointer point_search(space *e, char x[])
{
    point_pointer copy = (point_pointer)malloc(sizeof(point_node));

    copy = e->point_first;

    if (copy == NULL)
        return NULL;

    while (strcmp(copy->info.name, x) != 0 && copy->next != NULL)
        copy = copy->next;

    if (strcmp(copy->info.name, x) == 0)
        return copy;
    else
        return NULL;
}

int point_pop(space *e, char x[10])
{
    point_pointer before = (point_pointer)malloc(sizeof(point_node));
    point_pointer copy = (point_pointer)malloc(sizeof(point_node));

    before = NULL;
    copy = e->point_first;

    if (e->point_amount == 0)
        return 0;

    if (e->point_amount == 1 && strcmp(e->point_first->info.name, x) == 0)
    {
        copy = e->point_first;
        e->point_first = copy->next;
        free(copy);
        e->point_amount--;
        return 1;
    }

    if (strcmp(copy->info.name, x) == 0)
    {
        e->point_first = copy->next;
        free(copy);
        e->point_amount--;
        return 1;
    }

    while (copy->next != NULL && copy->info.name != x)
    {
        before = copy;
        copy = copy->next;
    }

    if (copy->next == NULL && copy->info.name != x)
        return 0;

    before->next = copy->next;
    free(copy);
    e->point_amount--;
    return 1;
}

void point_print(space *e)
{

    if (e->point_amount == 1)
        printf("There is 1 Point\n");
    else
        printf("There are %i Points\n", e->point_amount);

    if (e->point_amount != 0)
    {
        point_pointer copy = (point_pointer)malloc(sizeof(point_node));

        copy = e->point_first;

        if (e->point_amount == 1)
            printf("The Point:\n\n");
        else
            printf("The Points:\n\n");
        while (copy != NULL)
        {
            printf("%s = ", copy->info.name);
            printf("(%.2f,%.2f,%.2f)\n", copy->info.point[0], copy->info.point[1], copy->info.point[2]);
            copy = copy->next;
        }
    }
}

void point_destroy(space *e)
{
    point_pointer copy = (point_pointer)malloc(sizeof(point_node));
    point_pointer before = (point_pointer)malloc(sizeof(point_node));

    copy = e->point_first;
    while (copy != NULL)
    {
        before = copy;
        copy = copy->next;
        free(before);
    }
    e->point_first = NULL;
    e->point_amount = 0;
}
//<<<<<<<<<<<<<<<<<<<<POINTS

//>>>>>>>>>>>>>>>>>>>>VECTOR
void vector_push(space *e, char name[], float V[])
{

    vector_pointer curr = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer copy = (vector_pointer)malloc(sizeof(vector_node));

    curr->next = NULL;

    strcpy(curr->info.name, name);

    curr->info.vector[0] = V[0];
    curr->info.vector[1] = V[1];
    curr->info.vector[2] = V[2];

    if (e->vector_amount == 0)
    {
        e->vector_first = curr;
    }
    else
    {
        copy = e->vector_first;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        copy->next = curr;
    }
    e->vector_amount++;
}

int vector_pushAlt(space *e, char p1[], char p2[], char name[])
{
    vector_pointer curr = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer copy = (vector_pointer)malloc(sizeof(vector_node));
    point_pointer a = (point_pointer)malloc(sizeof(point_node));
    point_pointer b = (point_pointer)malloc(sizeof(point_node));

    a = point_search(e, p1);
    b = point_search(e, p2);

    if (a == NULL || b == NULL)
        return 0;

    strcpy(curr->info.name, name);
    curr->next = NULL;

    curr->info.vector[0] = b->info.point[0] - a->info.point[0];
    curr->info.vector[1] = b->info.point[1] - a->info.point[1];
    curr->info.vector[2] = b->info.point[2] - a->info.point[2];

    if (e->vector_amount == 0)
    {
        e->vector_first = curr;
    }
    else
    {
        copy = e->vector_first;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        copy->next = curr;
    }
    e->vector_amount++;
    return 1;
}

vector_pointer vector_search(space *e, char x[])
{
    vector_pointer copy = (vector_pointer)malloc(sizeof(vector_node));

    copy = e->vector_first;

    if (copy == NULL)
        return NULL;

    while (strcmp(copy->info.name, x) != 0 && copy->next != NULL)
        copy = copy->next;

    if (strcmp(copy->info.name, x) == 0)
        return copy;
    else
        return NULL;
}

int vector_pop(space *e, char x[])
{
    vector_pointer before = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer copy = (vector_pointer)malloc(sizeof(vector_node));

    before = NULL;
    copy = e->vector_first;

    if (e->vector_amount == 0)
        return 0;

    if (e->vector_amount == 1 && strcmp(e->vector_first->info.name, x) == 0)
    {
        copy = e->vector_first;
        e->vector_first = copy->next;
        free(copy);
        e->vector_amount--;
        return 1;
    }

    if (strcmp(copy->info.name, x) == 0)
    {
        e->vector_first = copy->next;
        free(copy);
        e->vector_amount--;
        return 1;
    }

    while (copy->next != NULL && strcmp(copy->info.name, x) != 0)
    {
        before = copy;
        copy = copy->next;
    }

    if (copy->next == NULL && strcmp(copy->info.name, x) != 0)
        return 0;

    before->next = copy->next;
    free(copy);
    e->vector_amount--;
    return 1;
}

void vector_print(space *e)
{

    if (e->vector_amount == 1)
        printf("There is 1 Vector\n");
    else
        printf("There are %i Vectors\n", e->vector_amount);

    if (e->vector_amount != 0)
    {
        vector_pointer copy = (vector_pointer)malloc(sizeof(vector_node));

        copy = e->vector_first;

        if (e->vector_amount == 1)
            printf("The Vector:\n\n");
        else
            printf("The Vectors:\n\n");
        while (copy != NULL)
        {
            printf("%s = ", copy->info.name);
            printf("(%.2f,%.2f,%.2f)\n", copy->info.vector[0], copy->info.vector[1], copy->info.vector[2]);
            copy = copy->next;
        }
    }
}

void vector_destroy(space *e)
{
    vector_pointer copy = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer before = (vector_pointer)malloc(sizeof(vector_node));

    copy = e->vector_first;
    while (copy != NULL)
    {
        before = copy;
        copy = copy->next;
        free(before);
    }
    e->vector_first = NULL;
    e->vector_amount = 0;
}
//<<<<<<<<<<<<<<<<<<<<VECTOR

//>>>>>>>>>>>>>>>>>>>>LINES
void line_push(space *e, char name[], float P[], float V[])
{

    line_pointer curr = (line_pointer)malloc(sizeof(line_node));
    line_pointer copy = (line_pointer)malloc(sizeof(line_node));

    curr->next = NULL;

    strcpy(curr->info.name, name);

    curr->info.point[0] = P[0];
    curr->info.point[1] = P[1];
    curr->info.point[2] = P[2];

    curr->info.vector[0] = V[0];
    curr->info.vector[1] = V[1];
    curr->info.vector[2] = V[2];

    if (e->line_amount == 0)
    {
        e->line_first = curr;
    }
    else
    {
        copy = e->line_first;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        copy->next = curr;
    }
    e->line_amount++;
}

line_pointer line_search(space *e, char x[])
{
    line_pointer copy = (line_pointer)malloc(sizeof(line_node));

    copy = e->line_first;

    if (copy == NULL)
        return NULL;

    while (strcmp(copy->info.name, x) != 0 && copy->next != NULL)
        copy = copy->next;

    if (strcmp(copy->info.name, x) == 0)
        return copy;
    else
        return NULL;
}

int line_pop(space *e, char x[])
{
    line_pointer before = (line_pointer)malloc(sizeof(line_node));
    line_pointer copy = (line_pointer)malloc(sizeof(line_node));

    before = NULL;
    copy = e->line_first;

    if (e->line_amount == 0)
        return 0;

    if (e->line_amount == 1 && strcmp(e->line_first->info.name, x) == 0)
    {
        copy = e->line_first;
        e->line_first = copy->next;
        free(copy);
        e->line_amount--;
        return 1;
    }

    if (strcmp(copy->info.name, x) == 0)
    {
        e->line_first = copy->next;
        free(copy);
        e->line_amount--;
        return 1;
    }

    while (copy->next != NULL && strcmp(copy->info.name, x) != 0)
    {
        before = copy;
        copy = copy->next;
    }

    if (copy->next == NULL && strcmp(copy->info.name, x) != 0)
        return 0;

    before->next = copy->next;
    free(copy);
    e->line_amount--;
    return 1;
}

void line_print(space *e)
{

    if (e->line_amount == 1)
        printf("There is 1 Line\n");
    else
        printf("There are %i Lines\n", e->line_amount);

    if (e->line_amount != 0)
    {
        line_pointer copy = (line_pointer)malloc(sizeof(line_node));

        copy = e->line_first;

        if (e->line_amount == 1)
            printf("The Line:\n\n");
        else
            printf("The Lines:\n\n");
        while (copy != NULL)
        {
            printf("%s: ", copy->info.name);
            printf("X = (%.2f,%.2f,%.2f) + a(%.2f,%.2f,%.2f)\n", copy->info.point[0], copy->info.point[1], copy->info.point[2], copy->info.vector[0], copy->info.vector[1], copy->info.vector[2]);
            copy = copy->next;
        }
    }
}

void line_destroy(space *e)
{
    line_pointer copy = (line_pointer)malloc(sizeof(line_node));
    line_pointer before = (line_pointer)malloc(sizeof(line_node));

    copy = e->line_first;
    while (copy != NULL)
    {
        before = copy;
        copy = copy->next;
        free(before);
    }
    e->line_first = NULL;
    e->line_amount = 0;
}
//<<<<<<<<<<<<<<<<<<<<LINES

//>>>>>>>>>>>>>>>>>>>>PLANES
void plane_push(space *e, char name[], float P[], float V1[], float V2[])
{

    plane_pointer curr = (plane_pointer)malloc(sizeof(plane_node));
    plane_pointer copy = (plane_pointer)malloc(sizeof(plane_node));

    curr->next = NULL;

    strcpy(curr->info.name, name);

    curr->info.point[0] = P[0];
    curr->info.point[1] = P[1];
    curr->info.point[2] = P[2];

    curr->info.vector1[0] = V1[0];
    curr->info.vector1[1] = V1[1];
    curr->info.vector1[2] = V1[2];

    curr->info.vector2[0] = V2[0];
    curr->info.vector2[1] = V2[1];
    curr->info.vector2[2] = V2[2];

    if (e->plane_amount == 0)
    {
        e->plane_first = curr;
    }
    else
    {
        copy = e->plane_first;
        while (copy->next != NULL)
        {
            copy = copy->next;
        }
        copy->next = curr;
    }
    e->plane_amount++;
}

plane_pointer plane_search(space *e, char x[])
{
    plane_pointer copy = (plane_pointer)malloc(sizeof(plane_node));

    copy = e->plane_first;

    if (copy == NULL)
        return NULL;

    while (strcmp(copy->info.name, x) != 0 && copy->next != NULL)
        copy = copy->next;

    if (strcmp(copy->info.name, x) == 0)
        return copy;
    else
        return NULL;
}

int plane_pop(space *e, char x[])
{
    plane_pointer before = (plane_pointer)malloc(sizeof(plane_node));
    plane_pointer copy = (plane_pointer)malloc(sizeof(plane_node));

    before = NULL;
    copy = e->plane_first;

    if (e->plane_amount == 0)
        return 0;

    if (e->plane_amount == 1 && strcmp(e->plane_first->info.name, x) == 0)
    {
        copy = e->plane_first;
        e->plane_first = copy->next;
        free(copy);
        e->plane_amount--;
        return 1;
    }

    if (strcmp(copy->info.name, x) == 0)
    {
        e->plane_first = copy->next;
        free(copy);
        e->plane_amount--;
        return 1;
    }

    while (copy->next != NULL && strcmp(copy->info.name, x) != 0)
    {
        before = copy;
        copy = copy->next;
    }

    if (copy->next == NULL && strcmp(copy->info.name, x) != 0)
        return 0;

    before->next = copy->next;
    free(copy);
    e->plane_amount--;
    return 1;
}

void plane_print(space *e)
{

    if (e->plane_amount == 1)
        printf("There is 1 Plane\n");
    else
        printf("There are %i Planes\n", e->plane_amount);

    if (e->plane_amount != 0)
    {
        plane_pointer copy = (plane_pointer)malloc(sizeof(plane_node));

        copy = e->plane_first;

        if (e->plane_amount == 1)
            printf("The Plane:\n\n");
        else
            printf("The Planes:\n\n");
        while (copy != NULL)
        {
            printf("%s: ", copy->info.name);
            printf("X = (%.2f,%.2f,%.2f) + a(%.2f,%.2f,%.2f) + b(%.2f,%.2f,%.2f)\n", copy->info.point[0], copy->info.point[1], copy->info.point[2], copy->info.vector1[0], copy->info.vector1[1], copy->info.vector1[2], copy->info.vector2[0], copy->info.vector2[1], copy->info.vector2[2]);
            copy = copy->next;
        }
    }
}

void plane_destroy(space *e)
{
    plane_pointer copy = (plane_pointer)malloc(sizeof(plane_node));
    plane_pointer before = (plane_pointer)malloc(sizeof(plane_node));

    copy = e->plane_first;
    while (copy != NULL)
    {
        before = copy;
        copy = copy->next;
        free(before);
    }
    e->plane_first = NULL;
    e->plane_amount = 0;
}
//<<<<<<<<<<<<<<<<<<<<PLANES

void print_space(space *e)
{
    system("cls");
    printf("===============POINTS===============\n");
    point_print(e);
    printf("\n===============VECTORS===============\n");
    vector_print(e);
    printf("\n===============LINES===============\n");
    line_print(e);
    printf("\n===============PLANES===============\n");
    plane_print(e);
}

void destroy_space(space *e)
{
    if (e->point_amount > 0)
        point_destroy(e);
    if (e->vector_amount)
        vector_destroy(e);
    if (e->line_amount)
        line_destroy(e);
    if (e->plane_amount)
        plane_destroy(e);
}
//===============================================Manager

//===============================================Logic
//>>>>>>>>>>>>>>>>>>>>POINTS
float point_distance(space *e, char x[], char y[])
{
    point_pointer a = (point_pointer)malloc(sizeof(point_node));
    point_pointer b = (point_pointer)malloc(sizeof(point_node));
    float r;

    a = point_search(e, x);
    b = point_search(e, y);
    if (a == NULL || b == NULL)
        return 0;
    else
    {
        r = pow(b->info.point[0] - a->info.point[0], 2) + pow(b->info.point[1] - a->info.point[1], 2) + pow(b->info.point[2] - a->info.point[2], 2);
        r = sqrt(r);
        return r;
    }
}

//<<<<<<<<<<<<<<<<<<<<POINTS

//>>>>>>>>>>>>>>>>>>>>VECTORS
int vector_linearity_2vec(float a[], float b[])
{

    float det1, det2, det3;

    det1 = (a[0] * b[1]) - (a[1] * b[0]);
    det2 = (a[0] * b[2]) - (a[2] * b[0]);
    det3 = (a[1] * b[2]) - (a[2] * b[1]);

    if (det1 == 0 && det2 == 0 && det3 == 0)
    {
        return 1;
    }
    else
        return 2;

    return 0;
}

int vector_linearity_3vec(float a[], float b[], float c[])
{

    float det;

    det = a[0] * b[1] * c[2] + a[1] * b[2] * c[0] + a[2] * b[0] * c[1];
    det = det - (a[2] * b[1] * c[0] + a[1] * b[0] * c[2] + a[0] * b[2] * c[1]);
    if (det == 0)
    {
        return 1;
    }
    else
        return 2;

    return 0;
}

int vector_linearity(space *e, int amount, char vec1[], char vec2[], char vec3[])
{
    vector_pointer a = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer b = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer c = (vector_pointer)malloc(sizeof(vector_node));

    a = vector_search(e, vec1);
    b = vector_search(e, vec2);
    c = vector_search(e, vec3);

    if (amount == 2)
    {
        if (a == NULL || b == NULL)
            return 0;
        return vector_linearity_2vec(a->info.vector, b->info.vector);
    }
    if (amount == 3)
    {
        if (a == NULL || b == NULL || c == NULL)
            return 0;
        return vector_linearity_3vec(a->info.vector, b->info.vector, c->info.vector);
    }
    return 0;
}
//<<<<<<<<<<<<<<<<<<<<VECTORS

//>>>>>>>>>>>>>>>>>>>>LINES
int line_relativity_calc(line_pointer r, line_pointer s)
{ //1 - Reverse, 2 - Parallel, 3 - Concurrent, 4 - Coincident
    float vec1[3], vec2[3], P1[3], P2[3];
    float vec3[3];

    for (int i = 0; i < 3; i++)
    {
        P1[i] = r->info.point[i];
        P2[i] = s->info.point[i];
        vec1[i] = r->info.vector[i];
        vec2[i] = s->info.vector[i];
        vec3[i] = vec2[i] - vec1[i];
    }

    int a = vector_linearity_3vec(vec1, vec2, vec3);
    int b = vector_linearity_2vec(vec1, vec2);

    if (a == 2)
        return 1;
    else if (a == 1)
    {
        if (b == 1)
        {
            float x1, x2, x3;
            x1 = (P2[0] - P1[0]) / vec2[0];
            x2 = (P2[1] - P1[1]) / vec2[1];
            x3 = (P2[2] - P1[2]) / vec2[2];
            if (x1 == x2 && x1 == x3 && x2 == x3)
                return 4;
            return 2;
        }
        else if (b == 2)
            return 3;
    }
    else
        return 0;
}

int line_relativity(space *e, char x[], char y[])
{
    line_pointer r = (line_pointer)malloc(sizeof(line_node));
    line_pointer s = (line_pointer)malloc(sizeof(line_node));

    r = line_search(e, x);
    s = line_search(e, y);

    if (r == NULL || s == NULL)
        return 0;
    else
        return line_relativity_calc(r, s);
}

float line_distance_calc(line_pointer r, line_pointer s)
{
    float v[3], answer[3], a, b;
    int rel;

    rel = line_relativity_calc(r, s);

    if (rel == 3 || rel == 4)
        return 0;

    for (int i = 0; i < 3; i++)
        v[i] = s->info.point[i] - r->info.point[i];

    answer[0] = v[1] * s->info.vector[2] - (v[2] * s->info.vector[1]);
    answer[1] = v[2] * s->info.vector[0] - (v[0] * s->info.vector[2]);
    answer[2] = v[0] * s->info.vector[1] - (v[1] * s->info.vector[0]);
    a = sqrt(pow(answer[0], 2) + pow(answer[1], 2) + pow(answer[2], 2));
    b = sqrt(pow(s->info.vector[0], 2) + pow(s->info.vector[1], 2) + pow(s->info.vector[2], 2));

    return a / b;
}

float line_distance(space *e, char x[], char y[])
{
    line_pointer r = (line_pointer)malloc(sizeof(line_node));
    line_pointer s = (line_pointer)malloc(sizeof(line_node));

    r = line_search(e, x);
    s = line_search(e, y);

    if (r == NULL || s == NULL)
        return 0;

    return line_distance_calc(r, s);
}
//<<<<<<<<<<<<<<<<<<<<LINES

//>>>>>>>>>>>>>>>>>>>>PLANES
int plane_relativity_calc(plane_pointer x, plane_pointer y)
{ //1 - Parallel, 2 - Concurrent
    float n1[3], n2[3];

    n1[0] = x->info.vector1[1] * x->info.vector2[2] - (x->info.vector1[2] * x->info.vector2[1]);
    n1[1] = x->info.vector1[2] * x->info.vector2[0] - (x->info.vector1[0] * x->info.vector2[2]);
    n1[2] = x->info.vector1[0] * x->info.vector2[1] - (x->info.vector1[1] * x->info.vector2[0]);

    n2[0] = y->info.vector1[1] * y->info.vector2[2] - (y->info.vector1[2] * y->info.vector2[1]);
    n2[1] = y->info.vector1[2] * y->info.vector2[0] - (y->info.vector1[0] * y->info.vector2[2]);
    n2[2] = y->info.vector1[0] * y->info.vector2[1] - (y->info.vector1[1] * y->info.vector2[0]);

    int a = vector_linearity_2vec(n1, n2);

    if (a == 1)
        return 1;
    else
        return 2;
}

int plane_relativity(space *e, char x[], char y[])
{
    plane_pointer plane1 = (plane_pointer)malloc(sizeof(plane_node));
    plane_pointer plane2 = (plane_pointer)malloc(sizeof(plane_node));

    plane1 = plane_search(e, x);
    plane2 = plane_search(e, y);

    if (plane1 == NULL || plane2 == NULL)
        return 0;
    else
        return plane_relativity_calc(plane1, plane2);
}

float plane_distance_calc(plane_pointer x, plane_pointer y)
{
    float P[3], n[3], answer[3], a, b;
    int rel;

    rel = plane_relativity_calc(x, y);

    if (rel == 2)
        return 0;

    n[0] = x->info.vector1[1] * x->info.vector2[2] - (x->info.vector1[2] * x->info.vector2[1]);
    n[1] = x->info.vector1[2] * x->info.vector2[0] - (x->info.vector1[0] * x->info.vector2[2]);
    n[2] = x->info.vector1[0] * x->info.vector2[1] - (x->info.vector1[1] * x->info.vector2[0]);

    for (int i = 0; i < 3; i++)
        P[i] = y->info.point[i];

    for (int i = 0; i < 3; i++)
    {
        answer[i] = P[i] * n[i];
    }
    a = sqrt(pow(answer[0], 2) + pow(answer[1], 2) + pow(answer[2], 2));
    b = sqrt(pow(n[0], 2) + pow(n[1], 2) + pow(n[2], 2));

    return a / b;
}

float plane_distance(space *e, char x[], char y[])
{
    plane_pointer plane1 = (plane_pointer)malloc(sizeof(plane_node));
    plane_pointer plane2 = (plane_pointer)malloc(sizeof(plane_node));

    plane1 = plane_search(e, x);
    plane2 = plane_search(e, y);

    if (plane1 == NULL || plane2 == NULL)
        return 0;

    return plane_distance_calc(plane1, plane2);
}
//<<<<<<<<<<<<<<<<<<<<PLANES
//===============================================Logic

//===============================================Strings
int input(char str[], int size)
{
    int i = 0;
    char c = getchar();

    while (c != '\n')
    {
        if (size > 0)
        {
            str[i] = c;
            i++;
            size--;
        }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}
//===============================================Strings

//===============================================Save
//>>>>>>>>>>>>>>>>>>>>POINTS
int point_save(FILE *arq, space *e)
{
    point_pointer point_temp = (point_pointer)malloc(sizeof(point_node));

    int i = 0;

    fwrite(&e->point_amount, sizeof(int), 1, arq);

    point_temp = e->point_first;
    while (i < e->point_amount)
    {
        fwrite(&point_temp->info, sizeof(point_info), 1, arq);
        point_temp = point_temp->next;
        i++;
    }
    return 1;
}

int point_login(FILE **arq, space *e)
{
    int i = 0;

    point_pointer aux = (point_pointer)malloc(sizeof(point_node));
    point_pointer before = (point_pointer)malloc(sizeof(point_node));

    fread(&e->point_amount, sizeof(int), 1, *arq);
    e->point_first = aux;

    while (i < e->point_amount)
    {
        fread(&aux->info, sizeof(point_info), 1, *arq);
        aux->next = (point_pointer)malloc(sizeof(point_node));
        before = aux;
        aux = aux->next;
        i++;
    }
    before->next = NULL;
    return 1;
}
//<<<<<<<<<<<<<<<<<<<<POINTS

//>>>>>>>>>>>>>>>>>>>>VECTORS
int vector_save(FILE *arq, space *e)
{
    vector_pointer vector_temp = (vector_pointer)malloc(sizeof(vector_node));

    int i = 0;

    fwrite(&e->vector_amount, sizeof(int), 1, arq);

    vector_temp = e->vector_first;
    while (i < e->vector_amount)
    {
        fwrite(&vector_temp->info, sizeof(vector_info), 1, arq);
        vector_temp = vector_temp->next;
        i++;
    }
    return 1;
}

int vector_login(FILE **arq, space *e)
{
    int i = 0;

    vector_pointer aux = (vector_pointer)malloc(sizeof(vector_node));
    vector_pointer before = (vector_pointer)malloc(sizeof(vector_node));

    fread(&e->vector_amount, sizeof(int), 1, *arq);
    e->vector_first = aux;

    while (i < e->vector_amount)
    {
        fread(&aux->info, sizeof(vector_info), 1, *arq);
        aux->next = (vector_pointer)malloc(sizeof(vector_node));
        before = aux;
        aux = aux->next;
        i++;
    }
    before->next = NULL;
    return 1;
}
//<<<<<<<<<<<<<<<<<<<<VECTORS

//>>>>>>>>>>>>>>>>>>>>LINES
int line_save(FILE *arq, space *e)
{
    line_pointer line_temp = (line_pointer)malloc(sizeof(line_node));

    int i = 0;

    fwrite(&e->line_amount, sizeof(int), 1, arq);

    line_temp = e->line_first;
    while (i < e->line_amount)
    {
        fwrite(&line_temp->info, sizeof(line_info), 1, arq);
        line_temp = line_temp->next;
        i++;
    }
    return 1;
}

int line_login(FILE **arq, space *e)
{
    int i = 0;

    line_pointer aux = (line_pointer)malloc(sizeof(line_node));
    line_pointer before = (line_pointer)malloc(sizeof(line_node));

    fread(&e->line_amount, sizeof(int), 1, *arq);
    e->line_first = aux;

    while (i < e->line_amount)
    {
        fread(&aux->info, sizeof(line_info), 1, *arq);
        aux->next = (line_pointer)malloc(sizeof(line_node));
        before = aux;
        aux = aux->next;
        i++;
    }
    before->next = NULL;
    return 1;
}
//<<<<<<<<<<<<<<<<<<<<LINES

//>>>>>>>>>>>>>>>>>>>>PLANES
int plane_save(FILE *arq, space *e)
{
    plane_pointer plane_temp = (plane_pointer)malloc(sizeof(plane_node));

    int i = 0;

    fwrite(&e->plane_amount, sizeof(int), 1, arq);

    plane_temp = e->plane_first;
    while (i < e->plane_amount)
    {
        fwrite(&plane_temp->info, sizeof(plane_info), 1, arq);
        plane_temp = plane_temp->next;
        i++;
    }
    return 1;
}

int plane_login(FILE **arq, space *e)
{
    int i = 0;

    plane_pointer aux = (plane_pointer)malloc(sizeof(plane_node));
    plane_pointer before = (plane_pointer)malloc(sizeof(plane_node));

    fread(&e->plane_amount, sizeof(int), 1, *arq);
    e->plane_first = aux;

    while (i < e->plane_amount)
    {
        fread(&aux->info, sizeof(plane_info), 1, *arq);
        aux->next = (plane_pointer)malloc(sizeof(plane_node));
        before = aux;
        aux = aux->next;
        i++;
    }
    before->next = NULL;
    return 1;
}
//<<<<<<<<<<<<<<<<<<<<PLANES

int save(FILE *arq, space *e)
{

    rewind(arq);

    if (!point_save(arq, e))
        return 0;
    if (!vector_save(arq, e))
        return 0;
    if (!line_save(arq, e))
        return 0;
    if (!plane_save(arq, e))
        return 0;

    return 1;
}

int login(FILE **arq, char name[], space *e)
{
    if ((*arq = fopen(name, "rb+")) == NULL)
        return 0;

    point_login(*&arq, e);
    vector_login(*&arq, e);
    line_login(*&arq, e);
    plane_login(*&arq, e);
}

void logout(FILE *arq, space *e)
{
    fclose(arq);
}
//===============================================Save

//===============================================Menus
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int binary_menu(int x)
{
    int a, b, current_line, previous_line, option, bot_limit, top_limit;

    current_line = x;
    previous_line = x;
    b = x;
    bot_limit = x;
    top_limit = x + 1;
    option = 0;

    printf("   Yes\n   No\n");
    do
    {
        gotoxy(0, current_line);
        printf("-->");
        gotoxy(6, current_line);
        printf("<--");
        gotoxy(0, 5);

        a = _getch();

        if (a == 0)
            a = _getch();

        if (a == 80 && b < top_limit)
        {
            previous_line = current_line;
            current_line++;
            b++;
        }
        else if (a == 72 && b > bot_limit)
        {
            previous_line = current_line;
            current_line--;
            b--;
        }
        else if (a == 13)
        {
            option = b + 1 - x;
        }
        if (current_line != previous_line)
        {
            gotoxy(0, previous_line);
            printf("   ");
            gotoxy(6, previous_line);
            printf("   ");
            previous_line = current_line;
        }
    } while (option == 0);

    return option;
}

int menu_points(int x)
{
    int a, b, current_line, previous_line, option, bot_limit, top_limit;
    option = 0;

    if (x == 0)
    {
        bot_limit = 1;
        top_limit = 2;
    }
    else if (x == 1)
    {
        bot_limit = 1;
        top_limit = 5;
    }
    else
    {
        bot_limit = 1;
        top_limit = 6;
    }

    option = 0;
    current_line = 1;
    previous_line = 1;
    b = 1;
    system("cls");
    printf("==================POINTS==================\n   Back\n   Add Point\n   Print all Points\n   Delete Point\n   Delete all Points\n   Calculate distance between two Points\n");
    do
    {
        gotoxy(0, current_line);
        printf("-->");
        gotoxy(40, current_line);
        printf("<--");
        gotoxy(0, 7);

        a = _getch();

        if (a == 0)
            a = _getch();

        if (a == 80 && b < top_limit)
        {
            previous_line = current_line;
            current_line++;
            b++;
        }
        else if (a == 72 && b > bot_limit)
        {
            previous_line = current_line;
            current_line--;
            b--;
        }
        else if (a == 13)
        {
            option = b;
        }
        if (current_line != previous_line)
        {
            gotoxy(0, previous_line);
            printf("   ");
            gotoxy(40, previous_line);
            printf("   ");
            previous_line = current_line;
        }
    } while (option == 0);

    return option - 1;
}

int menu_vector(int x)
{
    int a, b, current_line, previous_line, option, bot_limit, top_limit;
    option = 0;

    if (x == 0)
    {
        bot_limit = 1;
        top_limit = 2;
    }
    else if (x == 1)
    {
        bot_limit = 1;
        top_limit = 5;
    }
    else
    {
        bot_limit = 1;
        top_limit = 6;
    }

    option = 0;
    current_line = 1;
    previous_line = 1;
    b = 1;
    system("cls");
    printf("==================VECTORS==================\n   Back\n   Add Vector\n   Print all Vectors\n   Delete Vector\n   Delete all Vectors\n   Calculate linearity between Vectors\n");
    do
    {
        gotoxy(0, current_line);
        printf("-->");
        gotoxy(38, current_line);
        printf("<--");
        gotoxy(0, 7);

        a = _getch();

        if (a == 0)
            a = _getch();

        if (a == 80 && b < top_limit)
        {
            previous_line = current_line;
            current_line++;
            b++;
        }
        else if (a == 72 && b > bot_limit)
        {
            previous_line = current_line;
            current_line--;
            b--;
        }
        else if (a == 13)
        {
            option = b;
        }
        if (current_line != previous_line)
        {
            gotoxy(0, previous_line);
            printf("   ");
            gotoxy(38, previous_line);
            printf("   ");
            previous_line = current_line;
        }
    } while (option == 0);

    return option - 1;
}

int menu_lines(int x)
{
    int a, b, current_line, previous_line, option, bot_limit, top_limit;
    option = 0;

    if (x == 0)
    {
        bot_limit = 1;
        top_limit = 2;
    }
    else if (x == 1)
    {
        bot_limit = 1;
        top_limit = 5;
    }
    else
    {
        bot_limit = 1;
        top_limit = 7;
    }

    option = 0;
    current_line = 1;
    previous_line = 1;
    b = 1;
    system("cls");
    printf("==================LINES==================\n   Back\n   Add Line\n   Print all Lines\n   Delete Line\n   Delete all Lines\n   Calculate distance between two Lines\n   Calculate relative position between two Lines\n");
    do
    {
        gotoxy(0, current_line);
        printf("-->");
        gotoxy(48, current_line);
        printf("<--");
        gotoxy(0, 9);

        a = _getch();

        if (a == 0)
            a = _getch();

        if (a == 80 && b < top_limit)
        {
            previous_line = current_line;
            current_line++;
            b++;
        }
        else if (a == 72 && b > bot_limit)
        {
            previous_line = current_line;
            current_line--;
            b--;
        }
        else if (a == 13)
        {
            option = b;
        }
        if (current_line != previous_line)
        {
            gotoxy(0, previous_line);
            printf("   ");
            gotoxy(48, previous_line);
            printf("   ");
            previous_line = current_line;
        }
    } while (option == 0);

    return option - 1;
}

int menu_planes(int x)
{
    int a, b, current_line, previous_line, option, bot_limit, top_limit;
    option = 0;

    if (x == 0)
    {
        bot_limit = 1;
        top_limit = 2;
    }
    else if (x == 1)
    {
        bot_limit = 1;
        top_limit = 5;
    }
    else
    {
        bot_limit = 1;
        top_limit = 7;
    }

    option = 0;
    current_line = 1;
    previous_line = 1;
    b = 1;
    system("cls");
    printf("==================PLANES==================\n   Back\n   Add Plane\n   Print all Planes\n   Delete Plane\n   Delete all Planes\n   Calculate distance between two Planes\n   Calculate relative position between two Planes\n");
    do
    {
        gotoxy(0, current_line);
        printf("-->");
        gotoxy(49, current_line);
        printf("<--");
        gotoxy(0, 9);

        a = _getch();

        if (a == 0)
            a = _getch();

        if (a == 80 && b < top_limit)
        {
            previous_line = current_line;
            current_line++;
            b++;
        }
        else if (a == 72 && b > bot_limit)
        {
            previous_line = current_line;
            current_line--;
            b--;
        }
        else if (a == 13)
        {
            option = b;
        }

        if (current_line != previous_line)
        {
            gotoxy(0, previous_line);
            printf("   ");
            gotoxy(49, previous_line);
            printf("   ");
            previous_line = current_line;
        }
    } while (option == 0);

    return option - 1;
}

int menu_geral(int point, int vector, int line, int plane)
{
    int a, b, current_line, previous_line, option, answer, top_limit, bot_limit, amount_menu, amount_option;

    amount_menu = 4;
    amount_option = 3;
    bot_limit = 1;
    top_limit = amount_option + amount_menu + bot_limit;

    do
    {
        option = 0;
        current_line = 1;
        previous_line = 1;
        b = 1;
        system("cls");
        printf("==================OPTIONS MENU==================\n   Points operations\n   Vectors operations\n   Lines operations\n   Planes operations\n   Print all\n   Delete all\n   Save\n   Exit\n");
        do
        {
            gotoxy(0, current_line);
            printf("-->");
            gotoxy(21, current_line);
            printf("<--");
            gotoxy(0, top_limit + 1);

            a = _getch();

            if (a == 0)
                a = _getch();

            if (a == 80 && b < top_limit)
            {
                previous_line = current_line;
                current_line++;
                b++;
            }
            else if (a == 72 && b > bot_limit)
            {
                previous_line = current_line;
                current_line--;
                b--;
            }
            else if (a == 13)
            {
                option = b;
            }

            if (current_line != previous_line)
            {
                gotoxy(0, previous_line);
                printf("   ");
                gotoxy(21, previous_line);
                printf("   ");
                previous_line = current_line;
            }
        } while (option == 0);

        if (option == 1)
        {
            answer = menu_points(point);

            if (answer != 0)
            {
                option = answer - 1 + 10;
                break;
            }
        }
        if (option == 2)
        {
            answer = menu_vector(vector);

            if (answer != 0)
            {
                option = answer - 1 + 20;
                break;
            }
        }
        if (option == 3)
        {
            answer = menu_lines(line);

            if (answer != 0)
            {
                option = answer - 1 + 30;
                break;
            }
        }
        if (option == 4)
        {
            answer = menu_planes(plane);

            if (answer != 0)
            {
                option = answer - 1 + 40;
                break;
            }
        }

        if (option > amount_menu)
        {
            option = option - amount_menu;
            break;
        }

    } while (option < amount_menu + 1);

    return option;
}
//===============================================Menus
