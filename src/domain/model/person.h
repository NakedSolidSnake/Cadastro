#ifndef PERSON_H_
#define PERSON_H_

#define PERSON_NAME_LEN         120
#define PERSON_ADDRESS_LEN      120

typedef struct 
{
    int id;
    char name[PERSON_NAME_LEN];
    char address[PERSON_ADDRESS_LEN];
    int age;
} person_t;

person_t person_create(const char *name, const char *address, const int age);

#endif /* PERSON_H_ */
