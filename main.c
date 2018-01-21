#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
 * Simple example to remember about structs in C
 *   - Defines a struct;
 *   - Adds two structures on it;
 *   - Outputs a json of the data;
 *
 * $ gcc -o main main.c
 * $ ./main
 * [{"bill_id": 1, "description": "Food", "amount": 99.25}]
 */


/* TODO: Add date time field here. Could be timestamp YYYYMMDD */
struct bills {
    int bill_id;
    char description[128];
    float amount;
};


struct bills
set_bill(int bill_id, char *description, float amount) {
    struct bills bill;

    bill.bill_id = bill_id;
    strlcpy(bill.description, description, sizeof(description));
    bill.amount = amount;

    return bill;
}


int
throw_exception(char *message)
{
    printf("Error: %s \n", message);

    return 0;
}


int
main()
{
    char final_json[255];
    struct bills bill;

    if (-1 == pledge("stdio", NULL))
        err(1, "pledge");

    bill = set_bill(1, "Food", 99.25);

    snprintf(
        final_json,
        sizeof(final_json),
        "[{\"bill_id\": %d, \"description\": \"%s\", \"amount\": %.2f}]",
        bill.bill_id,
        bill.description,
        bill.amount
    );

    printf("%s \n", final_json);

    return 0;
}
