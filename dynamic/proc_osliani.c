#include "../rpc.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    reportable_t parent;

    long unsigned int decimal_num;
    char *binary_num;
} my_struct_t;

void *parse_parameters(void *data)
{
    const char *buf = (const char *)(data);

    my_struct_t *d = (my_struct_t *)(malloc(sizeof(my_struct_t)));

    if (d)
    {
        sscanf(buf, "%lu", &d->decimal_num);
    }

    return (void *)d;
}

void *do_work(void *data)
{
    my_struct_t *d = (my_struct_t *)(data);

    long unsigned int num = d->decimal_num;
    int i = 0;
    int k = 0;
    d->binary_num = (char *)(malloc(33 * sizeof(char))); // 32 bits + \0

    if (d->binary_num)
    {
        for (i = 31; i >= 0; i--)
        {
            int bit = ((num >> i) & 1);
            d->binary_num[k] = (char)('0' + bit);
            k++;
        }
        d->binary_num[k] = '\0';
    }

    return data;
}

reportable_t *report(void *data)
{
    my_struct_t *d = (my_struct_t *)(data);

    d->parent.data = (char *)(malloc(255 * sizeof(char)));

    snprintf(d->parent.data, 255, "%lu in binary is %s\n", d->decimal_num, d->binary_num);
    d->parent.len = strlen(d->parent.data);

    return (reportable_t *)(data);
}

void clean_up(void *params, void *result, reportable_t *report)
{
    if (report && report->data)
    {
        free(report->data);
    }

    if (params)
    {
        free(params);
    }

    if (result)
    {
        my_struct_t *d = (my_struct_t *)(result);
        if (d->binary_num)
        {
            free(d->binary_num);
        }
        free(result);
    }
}