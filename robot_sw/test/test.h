#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>
#include <inttypes.h>

#define __TESTING__
#define TEST(c, s) if (!(c)) { print_failure(s); return 1; } else { print_success(s); g_num_tests++; }

int g_num_tests = 0;

// Forward declarations

void print_success(const char *message);
void print_failure(const char *message);
void print_test_section(const char *section);
void print_test_subsection(const char *subsection);
void print_separator();
int num_tests();

// Definitions

void print_success(const char *message)
{
    printf(message);
    printf("\t\t-> OK\n");
}

void print_failure(const char *message)
{
    printf(message);
    printf("\t\t-> FAILED!\n");
}

void print_test_section(const char *section)
{
    print_separator();
    printf(" ");
    printf(section);
    printf("\n");
    print_separator();
}

void print_test_subsection(const char *subsection)
{
    printf("\n> ");
    printf(subsection);
    printf("\n");
}

void print_separator()
{
    printf("--------------------------------------\n");
}

int num_tests()
{
    return g_num_tests;
}

#endif /* __TEST_H__ */
