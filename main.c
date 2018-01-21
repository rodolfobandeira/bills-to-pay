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
 * [{"bill_id": 1, "description": "Food", "amount": 99.25, "due_date": 20180131}]
 */


struct bills {
    int bill_id;
    char description[128];
    float amount;
    int due_date; /* YYYYMMDD */
};


struct bills
set_bill(int bill_id, char *description, float amount, int due_date) {
    struct bills bill;

    bill.bill_id = bill_id;
    strlcpy(bill.description, description, sizeof(description));
    bill.amount = amount;
    bill.due_date = due_date;

    return bill;
}


int
throw_exception(char *message)
{
    printf("Error: %s \n", message);

    return 0;
}

char *
bill_struct2json(struct bills bill)
{
    char final_json[255];

    snprintf(
        final_json,
        sizeof(final_json),
        "[{\"bill_id\": %d, \"description\": \"%s\", \"amount\": %.2f, \"due_date\": %d}]",
        bill.bill_id,
        bill.description,
        bill.amount,
        bill.due_date
    );


/* TODO: Fix this error here:
 * address of stack memory associated with local variable 'final_json' returned [-Wreturn-stack-address]
 */
    return final_json;
}


int
main()
{
    if (-1 == pledge("stdio", NULL))
        err(1, "pledge");

    printf("%s \n",
        bill_struct2json(
            set_bill(1, "Food", 99.25, 20180131)
        )
    );

    return 0;
}
