#include <person.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

person_t person_create(const char *name, const char *address, const int age)
{
    person_t person;

    memset (&person, 0, sizeof (person_t));

    if (name != NULL)
        strncpy (person.name, name, PERSON_NAME_LEN);

    if (address != NULL)
        strncpy (person.address, address, PERSON_ADDRESS_LEN);

    person.age = age;

    return person;
}

person_t person_create_id(const int id, const char *name, const char *address, const int age)
{
    person_t person = person_create (name, address, age);
    person.id = id;
    return person;
}
