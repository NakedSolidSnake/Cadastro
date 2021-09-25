#ifndef PERSON_H
#define PERSON_H

#define PERSON_NAME_LEN         120
#define PERSON_ADDRESS_LEN      120

typedef struct 
{
    char name[PERSON_NAME_LEN];
    char address[PERSON_ADDRESS_LEN];
    int age;
} person_t;

person_t person_create(void);
char *person_input_name(void);
void person_parser(char *buffer, person_t *person);

#endif /* PERSON_H */
